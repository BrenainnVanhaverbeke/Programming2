#include "pch.h"
#include "LevelLoader.h"
#include "StaticTerrain.h"
#include "DynamicTerrain.h"
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

std::vector<StaticTerrain*> LevelLoader::LoadTerrain(int stage, int segment)
{
	std::cout << "Loading static terrain.\n";
	std::string objectName{ "staticTerrain" };
	json terrainObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfTerrainObjects{ terrainObjects.size() };
	std::vector<StaticTerrain*> pStaticTerrain;
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
	{
		pStaticTerrain.push_back(new StaticTerrain(GetVerticesFromJsonObject(terrainObjects.at(i))));
	}
	return pStaticTerrain;
}

std::vector<DynamicTerrain*> LevelLoader::LoadDynamicTerrain(int stage, int segment)
{
	std::cout << "Loading dynamic terrain.\n";
	std::string objectName{ "dynamicTerrain" };
	json dynamicTerrainJsonObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfCrumblingBlocks{ dynamicTerrainJsonObjects.size() };
	std::vector<DynamicTerrain*> pDynamicTerrain;
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		json& test{ dynamicTerrainJsonObjects.at(i) };
		std::string terrainType{ test.at("type") };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(test.at("vertices")) };
		if (terrainType == "crumblingBlock")
			pDynamicTerrain.push_back(new CrumblingBlock(vertices));
		else if (terrainType == "drawBridge")
			pDynamicTerrain.push_back(new DrawBridge(vertices));
	}
	return pDynamicTerrain;
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

std::vector<Stairs*> LevelLoader::LoadStairs(int stage, int segment)
{
	std::cout << "Loading stairs.\n";
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