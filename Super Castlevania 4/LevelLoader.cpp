#include "pch.h"
#include "LevelLoader.h"
#include "Terrain.h"
#include "Stairs.h"

#include <fstream>
#include <iostream>
#include <iomanip>


void LevelLoader::LogJson()
{
	json parsedJson{ json::parse(m_RawJson) };
	std::cout << std::setw(4) << parsedJson << std::endl;
	parsedJson.clear();
}

Terrain* LevelLoader::LoadTerrain(int stage, int segment)
{
	std::string objectName{ "terrain" };
	json terrainObjects{ GetJsonObject(stage, segment, objectName) };
	size_t nrOfTerrainObjects{ terrainObjects.size() };
	std::vector<std::vector<Point2f>> terrainVertices;
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
	{
		terrainVertices.push_back(GetVerticesFromJsonObject(terrainObjects.at(i)));
	}
	return new Terrain(terrainVertices);
}

Rectf LevelLoader::LoadBoundaries(int stage, int segment)
{
	std::string objectName{ "boundaries" };
	json boundaries{ GetJsonObject(stage, segment, objectName) };
	int width{ boundaries.at("width") };
	int height{ boundaries.at("height") };
	return Rectf{ 0, 0, (float)width, (float)height };
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
		json jsonStair{ jsonStairObjects.at(i) };
		std::vector<Point2f> vertices{ GetVerticesFromJsonObject(jsonStair.at("vertices")) };
		bool autoMountTop{ jsonStair.at("autoMountTop") };
		bool autoMountBottom{ jsonStair.at("autoMountBottom") };
		stairs.push_back(new Stairs{ vertices,
									 jsonStair.at("lowPoint"), 
									 jsonStair.at("highPoint"), 
									 autoMountTop, 
									 autoMountBottom});
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
		vertices.push_back(Point2f{ jsonObject.at(i).at(0), jsonObject.at(i).at(1) });
	}
	return vertices;
}