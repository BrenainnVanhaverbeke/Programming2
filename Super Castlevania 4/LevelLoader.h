#pragma once
#include "json.hpp"

using json = nlohmann::json;

class TerrainObject;
class InteractableObject;
class Stairs;
class Door;

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
	std::vector<TerrainObject*> LoadTerrain(int stage, int segment);
	std::vector<InteractableObject*> LoadInteractables(int stage, int segment);
	std::vector<Stairs*> LoadStairs(int stage, int segment);
	std::vector<Door*> LoadDoors(int stage, int segment);

private:
	std::string m_RawJson;
	std::string LoadRawJson();
	json GetJsonObject(int stage, int segment, std::string& objectName);
	std::vector<Point2f> GetVerticesFromJsonObject(json jsonObject);
	TerrainObject* TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices, bool isBackground);
	InteractableObject* InteractableFactory(const std::string& interactableType, const std::vector<Point2f>& vertices, const json& jsonObject);
	Stairs* CreateStairs(const std::vector<Point2f>& vertices, const json& jsonObject);
};