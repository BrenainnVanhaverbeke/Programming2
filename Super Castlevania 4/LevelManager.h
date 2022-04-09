#pragma once
#include "Vector2f.h"
#include <vector>

class LevelLoader;
class Terrain;
class Texture;
class Stairs;

class LevelManager
{
	enum class CollisionMode
	{
		terrain,
		stairs,
		background
	};

public:
	LevelManager();
	~LevelManager();

	void NextStage();
	void NextSegment();

	Terrain* GetTerrain() const;
	Rectf GetBoundaries() const;
	Point2f GetSpawn() const;

	void Draw() const;

	void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;
	bool IsOnStairs() const;

	void AttemptInteraction(const Rectf& player);
	void CheckOverlap(const Rectf& shape);

private:
	LevelLoader* m_pLevelLoader;
	Texture* m_pBackgroundTexture;
	Terrain* m_pTerrain;
	std::vector<Stairs*> m_pStairs;
	Stairs* m_pActiveStairs;
	Rectf m_Boundaries;
	Point2f m_SpawnPoint;
	CollisionMode m_CollisionMode;

	int m_StageCounter;
	int m_SegmentCounter;

	void LoadBackground();
	void LoadSegment();

	void DeleteStairs();
};