#pragma once
#include "json.hpp"

using json = nlohmann::json;

class DefaultTerrain;
class Stairs;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	LevelLoader(const LevelLoader& levelLoader) = delete;
	void operator = (const LevelLoader& levelLoader) = delete;

	void LogJson();
	Rectf LoadBoundaries(int stage, int segment);
	Rectf LoadTransitionArea(int stage, int segment);
	Point2f LoadPlayerSpawn(int stage, int segment);
	std::vector<Stairs*> LoadStairs(int stage, int segment);
	std::vector<DefaultTerrain*> LoadTerrain(int stage, int segment);

private:
	std::string m_RawJson;
	std::string LoadRawJson();
	json GetJsonObject(int stage, int segment, std::string& objectName);
	std::vector<Point2f> GetVerticesFromJsonObject(json jsonObject);
	DefaultTerrain* TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices);
};