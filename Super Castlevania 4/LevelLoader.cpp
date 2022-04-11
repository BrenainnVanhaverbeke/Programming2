#include "pch.h"
#include "LevelLoader.h"
#include "DefaultTerrain.h"
#include "Stairs.h"
#include "CrumblingBlock.h"
#include "DrawBridge.h"

#include <fstream>
#include <iostream>
#include <iomanip>


void LevelLoader::LogJson()
{
	json parsedJson{ json::parse(m_RawJson) };
	std::cout << std::setw(4) << parsedJson << std::endl;
	parsedJson.clear();
}

std::vector<DefaultTerrain*> LevelLoader::LoadTerrain(int stage, int segment)
{
	std::string objectName{ "terrain" };
	json dynamicTerrainJsonObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfCrumblingBlocks{ dynamicTerrainJsonObjects.size() };
	std::vector<DefaultTerrain*> pDynamicTerrain;
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		json& test{ dynamicTerrainJsonObjects.at(i) };
		std::string terrainType{ test.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(test.at("vertices")) };
		pDynamicTerrain.push_back(TerrainFactory(terrainType, vertices));
	}
	return pDynamicTerrain;
}

Rectf LevelLoader::LoadBoundaries(int stage, int segment)
{
	std::string objectName{ "boundaries" };
	json boundaries{ GetJsonObject(stage, segment, objectName) };
	float width{ boundaries.at("width") };
	float height{ boundaries.at("height") };
	return Rectf{ 0, 0, width, height };
}

Rectf LevelLoader::LoadTransitionArea(int stage, int segment)
{
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
	std::string objectName{ "playerSpawn" };
	json playerSpawn{ GetJsonObject(stage, segment, objectName) };
	return Point2f{ playerSpawn.at(0), playerSpawn.at(1) };
}

std::vector<Stairs*> LevelLoader::LoadStairs(int stage, int segment)
{
	std::string objectName{ "stairs" };
	json jsonStairObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfJsonStairObjects{ jsonStairObjects.size() };
	std::vector<Stairs*> stairs;
	for (size_t i{ 0 }; i < nrOfJsonStairObjects; ++i)
	{
		json& jsonStair{ jsonStairObjects.at(i) };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(jsonStair.at("vertices")) };
		bool autoMountTop{ jsonStair.at("autoMountTop") };
		bool autoMountBottom{ jsonStair.at("autoMountBottom") };
		stairs.push_back(new Stairs{ vertices,
									 jsonStair.at("lowPoint"),
									 jsonStair.at("highPoint"),
									 autoMountTop,
									 autoMountBottom });
	}
	return stairs;
}

LevelLoader::LevelLoader()
	: m_RawJson{ LoadRawJson() }
{
	LogJson();
}

LevelLoader::~LevelLoader()
{
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

DefaultTerrain* LevelLoader::TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices)
{
	DefaultTerrain* pTerrain{ nullptr };
	if (terrainType == "default")
		pTerrain = new DefaultTerrain(vertices);
	else if (terrainType == "crumblingBlock")
		pTerrain = new CrumblingBlock(vertices);
	else if (terrainType == "drawBridge")
		pTerrain = new DrawBridge(vertices);
	return pTerrain;
}