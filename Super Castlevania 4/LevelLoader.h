#pragma once
#include "json.hpp"

using json = nlohmann::json;

class Terrain;
class Stairs;

class LevelLoader
{
public:
	LevelLoader();
	~LevelLoader();
	LevelLoader(const LevelLoader& levelLoader) = delete;
	void operator = (const LevelLoader& levelLoader) = delete;

	void LogJson();
	Terrain* LoadTerrain(int stage, int segment);
	Rectf LoadBoundaries(int stage, int segment);
	Point2f LoadPlayerSpawn(int stage, int segment);
	std::vector<Stairs*> LoadStairs(int stage, int segment);

private:
	std::string m_RawJson;
	std::string LoadRawJson();
	json GetJsonObject(int stage, int segment, std::string& objectName);
	std::vector<Point2f> GetVerticesFromJsonObject(json jsonObject);
};