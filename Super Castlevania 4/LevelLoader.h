#pragma once
#include "json.hpp"

using json = nlohmann::json;

enum class CharacterTypes;
class TerrainObject;
class InteractableObject;
class Stairs;
class Door;
class Sprite;
class Background;
class ParallaxLayer;
class EnemySpawner;

class LevelLoader final
{
public:
	LevelLoader();
	~LevelLoader() = default;
	LevelLoader(const LevelLoader& levelLoader) = delete;
	LevelLoader(LevelLoader&& levelLoader) = delete;
	LevelLoader& operator =(const LevelLoader& rhs) = delete;
	LevelLoader& operator =(LevelLoader&& rhs) = delete;

	void LogJson() const;
	Rectf LoadBoundaries(int stage, int segment) const;
	Rectf LoadTransitionArea(int stage, int segment) const;
	Rectf LoadBackgroundSource(int stage, int segment) const;
	Point2f LoadPlayerSpawn(int stage, int segment) const;
	std::vector<TerrainObject*> LoadTerrain(int stage, int segment) const;
	std::vector<InteractableObject*> LoadInteractables(int stage, int segment) const;
	std::vector<EnemySpawner*> GetEnemySpawners(int stage, int segment) const;
	bool IsSegmentCheckpoint(int stage, int segment) const;
	Sprite* GetBackgroundSprite(int stage, int segment) const;
	Background* GetBackground(int stage, int segment) const;

private:
	std::string m_RawJson;

	std::string LoadRawJson() const;
	std::string GetSpriteSheetString(int stage) const;
	json GetJsonObject(int stage, int segment, std::string& objectName) const;
	std::vector<Point2f> GetVerticesFromJsonObject(const json& jsonObject) const;
	CharacterTypes GetCharacterType(const json& jsonObject) const;
	TerrainObject* TerrainFactory(const std::string& terrainType, const std::vector<Point2f>& vertices, int zIndex) const;
	InteractableObject* InteractableFactory(const std::string& interactableType, const std::vector<Point2f>& vertices, const json& jsonObject) const;
	Stairs* CreateStairs(const std::vector<Point2f>& vertices, const json& jsonObject) const;
	Rectf GetRectFromJson(const json& jsonObject) const;
	Point2f GetPointFromJson(const json& jsonObject) const;
	std::vector<ParallaxLayer*> GetParallaxLayers(int stage, int segment, float staticBackgroundWidth) const;
};