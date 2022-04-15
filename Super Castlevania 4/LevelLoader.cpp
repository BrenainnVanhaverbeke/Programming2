#include "pch.h"
#include "LevelLoader.h"
#include "Stairs.h"
#include "Door.h"
#include "CrumblingBlock.h"
#include "DrawBridge.h"
#include "Trapdoor.h"
#include "Sprite.h"

#include <fstream>
#include <iostream>
#include <iomanip>

LevelLoader::LevelLoader()
	: m_RawJson{ LoadRawJson() }
{
}

LevelLoader::~LevelLoader()
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
	std::cout << "Loading boundaries.\n";
	std::string objectName{ "boundaries" };
	json boundaries{ GetJsonObject(stage, segment, objectName) };
	return GetRectFromJson(boundaries);
}

Rectf LevelLoader::LoadTransitionArea(int stage, int segment) const
{
	std::cout << "Loading transition area.\n";
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
	std::cout << "Loading player spawn.\n";
	std::string objectName{ "playerSpawn" };
	json playerSpawn{ GetJsonObject(stage, segment, objectName) };
	return Point2f{ playerSpawn.at(0), playerSpawn.at(1) };
}

std::vector<TerrainObject*> LevelLoader::LoadTerrain(int stage, int segment) const
{
	std::cout << "Loading terrain.\n";
	std::string objectName{ "terrain" };
	json terrainJson{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfCrumblingBlocks{ terrainJson.size() };
	std::vector<TerrainObject*> pDynamicTerrain;
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		json& test{ terrainJson.at(i) };
		std::string terrainType{ test.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(test.at("vertices")) };
		bool isBackground{ test.at("isBackground") };
		pDynamicTerrain.push_back(TerrainFactory(terrainType, vertices, isBackground));
	}
	return pDynamicTerrain;
}

std::vector<InteractableObject*> LevelLoader::LoadInteractables(int stage, int segment) const
{
	std::cout << "Loading interactables.\n";
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

std::string LevelLoader::GetSpriteSheetString(int stage) const
{
	json parsedJson{ json::parse(m_RawJson) };
	return parsedJson.at("stages")
		.at(stage)
		.at("spritesheet");
}

Sprite* LevelLoader::GetBackground(int stage, int segment) const
{
	json parsedJson{ json::parse(m_RawJson) };
	std::string path{ parsedJson.at("stages")
								.at(stage)
								.at("spritesheet") };
	std::string objectName{ "background" };
	json durr{ GetJsonObject(stage, segment, objectName) };
	Rectf sourceRect{ GetRectFromJson(durr.at("foreground")) };
	return new Sprite(path, sourceRect);
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

TerrainObject* LevelLoader::TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices, bool isBackground) const
{
	if (terrainType == "crumblingBlock")
	{
		std::cout << "Creating crumbling block.\n";
		return new CrumblingBlock(vertices, isBackground);
	}
	if (terrainType == "drawBridge")
	{
		std::cout << "Creating drawbridge.\n";
		return new DrawBridge(vertices, isBackground);
	}
	if (terrainType == "trapDoor")
	{
		std::cout << "Creating trapdoor.\n";
		return new TrapDoor(vertices, isBackground);
	}
	std::cout << "Creating default terrain.\n";
	return new TerrainObject(vertices, isBackground);
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
	bool isBackground{ jsonObject.at("isBackground") };
	return new Stairs{ vertices,
					   jsonObject.at("lowPoint"),
					   jsonObject.at("highPoint"),
					   autoMountTop,
					   autoMountBottom,
					   isBackground };
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
	json origin{ jsonObject.at("origin")};
	return Point2f{ origin.at(0), origin.at(1) };
}
