#include "pch.h"
#include "LevelLoader.h"
#include "Stairs.h"
#include "Door.h"
#include "DefaultTerrain.h"
#include "CrumblingBlock.h"
#include "DrawBridge.h"

#include <fstream>
#include <iostream>
#include <iomanip>

LevelLoader::LevelLoader()
	: m_RawJson{ LoadRawJson() }
{
	//LogJson();
}

LevelLoader::~LevelLoader()
{
}

void LevelLoader::LogJson()
{
	json parsedJson{ json::parse(m_RawJson) };
	std::cout << std::setw(4) << parsedJson << std::endl;
	parsedJson.clear();
}

Rectf LevelLoader::LoadBoundaries(int stage, int segment)
{
	std::cout << "Loading boundaries.\n";
	std::string objectName{ "boundaries" };
	json boundaries{ GetJsonObject(stage, segment, objectName) };
	float width{ boundaries.at("width") };
	float height{ boundaries.at("height") };
	return Rectf{ 0, 0, width, height };
}

Rectf LevelLoader::LoadTransitionArea(int stage, int segment)
{
	std::cout << "Loading transition area.\n";
	std::string objectName{ "transitionArea" };
	json transitionArea{ GetJsonObject(stage, segment, objectName) };
	float x{ transitionArea.at("origin").at(0) };
	float y{ transitionArea.at("origin").at(1) };
	float width{ transitionArea.at("width") };
	float height{ transitionArea.at("height") };
	return Rectf{ x, y, width, height };
}

Point2f LevelLoader::LoadPlayerSpawn(int stage, int segment)
{
	std::cout << "Loading player spawn.\n";
	std::string objectName{ "playerSpawn" };
	json playerSpawn{ GetJsonObject(stage, segment, objectName) };
	return Point2f{ playerSpawn.at(0), playerSpawn.at(1) };
}

std::vector<TerrainObject*> LevelLoader::LoadTerrain(int stage, int segment)
{
	std::cout << "Loading terrain.\n";
	std::string objectName{ "terrain" };
	json dynamicTerrainJsonObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfCrumblingBlocks{ dynamicTerrainJsonObjects.size() };
	std::vector<TerrainObject*> pDynamicTerrain;
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		json& test{ dynamicTerrainJsonObjects.at(i) };
		std::string terrainType{ test.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(test.at("vertices")) };
		bool isBackground{ test.at("isBackground") };
		pDynamicTerrain.push_back(TerrainFactory(terrainType, vertices, isBackground));
	}
	return pDynamicTerrain;
}

std::vector<InteractableObject*> LevelLoader::LoadInteractables(int stage, int segment)
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
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(interactable.at("vertices"))};
		pInteractables.push_back(InteractableFactory(type, vertices, interactable));
	}
	return pInteractables;
}

std::vector<Stairs*> LevelLoader::LoadStairs(int stage, int segment)
{
	std::cout << "Loading stairs.\n";
	std::string objectName{ "stairs" };
	json jsonStairObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfJsonStairs{ jsonStairObjects.size() };
	std::vector<Stairs*> stairs;
	for (size_t i{ 0 }; i < nrOfJsonStairs; ++i)
	{
		json& jsonStair{ jsonStairObjects.at(i) };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(jsonStair.at("vertices")) };
		bool autoMountTop{ jsonStair.at("autoMountTop") };
		bool autoMountBottom{ jsonStair.at("autoMountBottom") };
		bool isBackground{ jsonStair.at("isBackground") };
		stairs.push_back(new Stairs{ vertices,
									 jsonStair.at("lowPoint"),
									 jsonStair.at("highPoint"),
									 autoMountTop,
									 autoMountBottom,
									 isBackground });
	}
	return stairs;
}

std::vector<Door*> LevelLoader::LoadDoors(int stage, int segment)
{
	std::cout << "Loading Doors.\n";
	std::string objectName{ "doors" };
	json jsonDoors{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfJsonDoors{ jsonDoors.size() };
	std::vector<Door*> pDoors;
	if (jsonDoors.empty())
		return pDoors;
	for (size_t i{ 0 }; i < nrOfJsonDoors; ++i)
	{
		json& jsonDoor{ jsonDoors.at(i) };
		pDoors.push_back(new Door{ GetVerticesFromJsonObject(jsonDoor.at("vertices")) });
	}
	return pDoors;
}

std::string LevelLoader::LoadRawJson()
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

json LevelLoader::GetJsonObject(int stage, int segment, std::string& objectName)
{
	json parsedJson{ json::parse(m_RawJson) };
	if (!parsedJson.at("segments").at(segment).contains(objectName))
		return json{};
	return parsedJson.at("segments")
		.at(segment)
		.at(objectName);
}

std::vector<Point2f> LevelLoader::GetVerticesFromJsonObject(json jsonObject)
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

TerrainObject* LevelLoader::TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices, bool isBackground)
{
	DefaultTerrain* pTerrain{ nullptr };
	if (terrainType == "default")
		pTerrain = new DefaultTerrain(vertices, isBackground);
	else if (terrainType == "crumblingBlock")
		pTerrain = new CrumblingBlock(vertices, isBackground);
	else if (terrainType == "drawBridge")
		pTerrain = new DrawBridge(vertices, isBackground);
	return pTerrain;
}

InteractableObject* LevelLoader::InteractableFactory(const std::string& interactableType, const std::vector<Point2f>& vertices, const json& jsonObject)
{
	if (interactableType == "stairs")
		return CreateStairs(vertices, jsonObject);
	else if (interactableType == "door")
		return new Door{ vertices };
	return nullptr;
}

Stairs* LevelLoader::CreateStairs(const std::vector<Point2f>& vertices, const json& jsonObject)
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