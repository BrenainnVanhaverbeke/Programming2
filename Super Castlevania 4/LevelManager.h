#pragma once
#include "Vector2f.h"
#include <vector>

class LevelLoader;
class TerrainObject;
class InteractableObject;
class Texture;

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
	bool IsInTransitionArea(const Rectf& actorShape) const;

	void AttemptInteraction(const Rectf& player);
	void CheckOverlap(const Rectf& shape);

private:
	LevelLoader* m_pLevelLoader;
	Texture* m_pBackgroundTexture;
	std::vector<TerrainObject*> m_pTerrain;
	std::vector<InteractableObject*> m_pInteractableObjects;
	InteractableObject* m_pActiveInteractable;
	Rectf m_Boundaries;
	Rectf m_TransitionArea;
	Point2f m_SpawnPoint;

	int m_StageCounter;
	int m_SegmentCounter;
	bool m_IsOnBackground;
	bool m_IsOnStairs;

	void LoadBackground();
	void LoadSegment();
	void UnloadSegment();
	void AttemptResetActiveInteractable(const Rectf& actorShape);

	void DeleteTerrain();
	void DeleteInteractables();
};