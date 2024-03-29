#include "pch.h"
#include "LevelLoader.h"
#include "Stairs.h"
#include "Door.h"
#include "CrumblingBlock.h"
#include "DrawBridge.h"
#include "Trapdoor.h"
#include "Sprite.h"
#include "Background.h"
#include "ParallaxLayer.h"
#include "EnemySpawner.h"
#include "CharacterTypes.h"

#include <fstream>
#include <iostream>
#include <iomanip>

LevelLoader::LevelLoader()
	: m_RawJson{ LoadRawJson() }
{
}

void LevelLoader::LogJson() const
{
	json parsedJson{ json::parse(m_RawJson) };
	std::cout << std::setw(4) << parsedJson << std::endl;
	parsedJson.clear();
}

Rectf LevelLoader::LoadBoundaries(int stage, int segment) const
{
	std::string objectName{ "boundaries" };
	json boundaries{ GetJsonObject(stage, segment, objectName) };
	return GetRectFromJson(boundaries);
}

Rectf LevelLoader::LoadTransitionArea(int stage, int segment) const
{
	std::string objectName{ "transitionArea" };
	json transitionArea{ GetJsonObject(stage, segment, objectName) };
	return GetRectFromJson(transitionArea);
}

Rectf LevelLoader::LoadBackgroundSource(int stage, int segment) const
{
	std::string objectName{ "background" };
	json jsonBackground{ GetJsonObject(stage, segment, objectName) };
	return GetRectFromJson(jsonBackground.at("foreground"));
}

Point2f LevelLoader::LoadPlayerSpawn(int stage, int segment) const
{
	std::string objectName{ "playerSpawn" };
	json playerSpawn{ GetJsonObject(stage, segment, objectName) };
	return Point2f{ playerSpawn.at(0), playerSpawn.at(1) };
}

std::vector<TerrainObject*> LevelLoader::LoadTerrain(int stage, int segment) const
{
	std::string objectName{ "terrain" };
	json terrainJson{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfCrumblingBlocks{ terrainJson.size() };
	std::vector<TerrainObject*> pDynamicTerrain;
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		json& test{ terrainJson.at(i) };
		std::string terrainType{ test.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(test.at("vertices")) };
		int zIndex{ test.at("zIndex") };
		pDynamicTerrain.push_back(TerrainFactory(terrainType, vertices, zIndex));
	}
	return pDynamicTerrain;
}

std::vector<InteractableObject*> LevelLoader::LoadInteractables(int stage, int segment) const
{
	std::string objectName{ "interactableObjects" };
	json jsonInteractables{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfInteractables{ jsonInteractables.size() };
	std::vector<InteractableObject*> pInteractables;
	for (size_t i{ 0 }; i < nrOfInteractables; ++i)
	{
		json& interactable{ jsonInteractables.at(i) };
		std::string type{ interactable.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(interactable.at("vertices")) };
		pInteractables.push_back(InteractableFactory(type, vertices, interactable));
	}
	return pInteractables;
}

std::vector<EnemySpawner*> LevelLoader::GetEnemySpawners(int stage, int segment) const
{
	std::string objectName{ "enemySpawners" };
	json jsonSpawners{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfSpawners{ jsonSpawners.size() };
	std::vector<EnemySpawner*> enemySpawners{};
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
	{
		json& spawner{ jsonSpawners.at(i) };
		enemySpawners.push_back(new EnemySpawner(GetCharacterType(spawner), GetPointFromJson(spawner), spawner.at("zIndex")));
	}
	return enemySpawners;
}

CharacterTypes LevelLoader::GetCharacterType(const json& jsonObject) const
{
	std::string type{ jsonObject.at("type") };
	if (type == "bonePillar")
		return CharacterTypes::bonePillar;
	if (type == "bat")
		return CharacterTypes::bat;
	if (type == "skeleton")
		return CharacterTypes::skeleton;

	// If this is returned, shit went wrong.
	return CharacterTypes::player;
}

bool LevelLoader::IsSegmentCheckpoint(int stage, int segment) const
{
	std::string objectName{ "isCheckPoint" };
	return GetJsonObject(stage, segment, objectName);
}

Background* LevelLoader::GetBackground(int stage, int segment) const
{
	Sprite* staticBackground{ GetBackgroundSprite(stage, segment) };
	float staticBackgroundWidth{ staticBackground->GetSourceRect().width };
	std::string objectName{ "background" };
	int zIndex{ GetJsonObject(stage, segment, objectName).at("foreground").at("zIndex") };
	std::vector<ParallaxLayer*> parallaxLayers{ GetParallaxLayers(stage, segment, staticBackgroundWidth) };
	return new Background(staticBackground, parallaxLayers, zIndex);
}

Sprite* LevelLoader::GetBackgroundSprite(int stage, int segment) const
{
	std::string path{ GetSpriteSheetString(stage) };
	std::string objectName{ "background" };
	json sourceRectJson{ GetJsonObject(stage, segment, objectName) };
	Rectf sourceRect{ GetRectFromJson(sourceRectJson.at("foreground")) };
	return new Sprite(path, sourceRect);
}

std::vector<ParallaxLayer*> LevelLoader::GetParallaxLayers(int stage, int segment, float staticBackgroundWidth) const
{
	std::vector<ParallaxLayer*> parallaxVector{};
	std::string path{ GetSpriteSheetString(stage) };
	std::string objectName{ "background" };
	json parallaxJson{ GetJsonObject(stage, segment, objectName)
		.at("parallax") };
	size_t parallaxLayers{ parallaxJson.size() };
	for (size_t i{ 0 }; i < parallaxLayers; ++i)
	{
		Rectf parallaxSource{ GetRectFromJson(parallaxJson.at(i)) };
		Sprite* parallaxSprite{ new Sprite(path, parallaxSource) };
		float offsetY{ parallaxJson.at(i).at("yOffset") };
		int zIndex{ parallaxJson.at(i).at("zIndex") };
		parallaxVector.push_back(new ParallaxLayer(parallaxSprite, staticBackgroundWidth, offsetY, zIndex));
	}
	return parallaxVector;
}

std::string LevelLoader::GetSpriteSheetString(int stage) const
{
	json parsedJson{ json::parse(m_RawJson) };
	return parsedJson.at("stages")
		.at(stage)
		.at("spritesheet");
}

std::string LevelLoader::LoadRawJson() const
{
	std::ifstream jsonStream{ "./Resources/JSON/Levels.json" };
	std::string rawJson{};
	std::string jsonLine{};
	if (!jsonStream)
	{
		std::cerr << "Failed to load JSON.";
		return rawJson;
	}
	while (!jsonStream.eof())
	{
		getline(jsonStream, jsonLine);
		rawJson += jsonLine;
	}
	jsonStream.close();
	return rawJson;
}

json LevelLoader::GetJsonObject(int stage, int segment, std::string& objectName) const
{
	json parsedJson{ json::parse(m_RawJson) };
	if (!parsedJson.at("stages").at(stage).at("segments").at(segment).contains(objectName))
		return json{};
	return parsedJson.at("stages")
		.at(stage)
		.at("segments")
		.at(segment)
		.at(objectName);
}

std::vector<Point2f> LevelLoader::GetVerticesFromJsonObject(const json& jsonObject) const
{
	size_t nrOfVertices{ jsonObject.size() };
	std::vector<Point2f> vertices;
	for (size_t i{ 0 }; i < nrOfVertices; ++i)
	{
		json verticesJson{ jsonObject.at(i) };
		float x{ verticesJson.at(0) };
		float y{ verticesJson.at(1) };
		vertices.push_back(Point2f{ x, y });
	}
	return vertices;
}

TerrainObject* LevelLoader::TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices, int zIndex) const
{
	if (terrainType == "crumblingBlock")
		return new CrumblingBlock(vertices, zIndex);
	if (terrainType == "drawBridge")
		return new DrawBridge(vertices, zIndex);
	if (terrainType == "trapDoor")
		return new TrapDoor(vertices, zIndex);
	return new TerrainObject(vertices, zIndex);
}

InteractableObject* LevelLoader::InteractableFactory(const std::string& interactableType, const std::vector<Point2f>& vertices, const json& jsonObject) const
{
	if (interactableType == "stairs")
		return CreateStairs(vertices, jsonObject);
	else if (interactableType == "door")
		return new Door{ vertices };
	return nullptr;
}

Stairs* LevelLoader::CreateStairs(const std::vector<Point2f>& vertices, const json& jsonObject) const
{
	bool autoMountTop{ jsonObject.at("autoMountTop") };
	bool autoMountBottom{ jsonObject.at("autoMountBottom") };
	int zIndex{ jsonObject.at("zIndex") };
	return new Stairs{ vertices,
					   jsonObject.at("lowPoint"),
					   jsonObject.at("highPoint"),
					   autoMountTop,
					   autoMountBottom,
					   zIndex };
}

Rectf LevelLoader::GetRectFromJson(const json& jsonObject) const
{
	Point2f origin{ GetPointFromJson(jsonObject) };
	float width{ jsonObject.at("width") };
	float height{ jsonObject.at("height") };
	return Rectf{ origin, width, height };
}

Point2f LevelLoader::GetPointFromJson(const json& jsonObject) const
{
	if (!jsonObject.contains("origin"))
		return Point2f{};
	json origin{ jsonObject.at("origin") };
	return Point2f{ origin.at(0), origin.at(1) };
}