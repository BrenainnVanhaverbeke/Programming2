#pragma once
#include "Vector2f.h"
#include <vector>

class LevelLoader;
class TerrainObject;
class InteractableObject;
class Sprite;

class LevelManager
{
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
	bool IsUpstairs(const Vector2f& actorVelocity) const;
	bool IsInTransitionArea(const Rectf& actorShape) const;

	void ToggleDebugDraw();
	void AttemptInteraction(const Rectf& player);
	void CheckOverlap(const Rectf& shape);

private:
	LevelLoader* m_pLevelLoader;
	std::vector<TerrainObject*> m_pTerrain;
	std::vector<InteractableObject*> m_pInteractableObjects;
	InteractableObject* m_pActiveInteractable;
	Rectf m_Boundaries;
	Rectf m_TransitionArea;
	Point2f m_SpawnPoint;
	Sprite* m_pBackground;

	int m_BackgroundSpriteId;
	int m_StageCounter;
	int m_SegmentCounter;
	bool m_IsOnBackground;
	bool m_IsOnStairs;
	bool m_DrawDebug;

	void LoadBackground();
	void LoadSegment();
	void UnloadSegment();
	void AttemptResetActiveInteractable(const Point2f& spawnPoint);

	void DeleteTerrain();
	void DeleteInteractables();

	void DrawDebug() const;
};