#pragma once
#include "Vector2f.h"
#include <vector>

class LevelLoader;
class StaticTerrain;
class DynamicTerrain;
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

	Rectf GetBoundaries() const;
	Point2f GetSpawn() const;

	void Update(float elapsedSec, const Rectf& actorShape);
	void Draw() const;

	void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity);
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;
	bool IsOnStairs() const;
	bool IsInTransitionArea(const Rectf& actorShape) const;

	void AttemptInteraction(const Rectf& player);
	void CheckOverlap(const Rectf& shape);

private:
	LevelLoader* m_pLevelLoader;
	Texture* m_pBackgroundTexture;
	std::vector<StaticTerrain*> m_pStaticTerrain;
	std::vector<DynamicTerrain*> m_pDynamicTerrain;
	std::vector<Stairs*> m_pStairs;
	Stairs* m_pActiveStairs;
	Rectf m_Boundaries;
	Rectf m_TransitionArea;
	Point2f m_SpawnPoint;
	CollisionMode m_CollisionMode;

	int m_StageCounter;
	int m_SegmentCounter;

	void LoadBackground();
	void LoadSegment();
	void UnloadSegment();

	void DeleteStaticTerrain();
	void DeleteDynamicTerrain();
	void DeleteStairs();
};