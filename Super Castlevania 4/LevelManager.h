#pragma once
#include "Vector2f.h"
#include <vector>

class LevelLoader;
class TerrainObject;
class InteractableObject;
class Sprite;
class Character;
class Background;

class LevelManager
{
public:
	LevelManager(float screenWidth, float screenHeight);
	~LevelManager();

	void NextStage();
	void NextSegment();

	Rectf GetBoundaries() const;
	Point2f GetSpawn() const;
	Background* GetBackground() const;

	void Update(float elapsedSec, const Point2f& cameraBottomLeft) const;
	void Draw() const;
	void DrawBackground() const;

	void HandleCollisions(Character& character);
	bool IsOnGround(const Character& character) const;
	bool IsOnStairs() const;
	bool IsUpstairs(const Vector2f& actorVelocity) const;
	bool IsOnBackground() const;
	bool IsInTransitionArea(const Rectf& actorShape) const;
	void ReloadCheckpoint();

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
	Rectf m_WindowSize;
	Point2f m_SpawnPoint;
	Sprite* m_pBackgroundLegacy;
	Background* m_pBackground;

	int m_BackgroundSpriteId;
	int m_StageCounter;
	int m_SegmentCounter;
	int m_CheckpointCounter;
	bool m_IsOnBackground;
	bool m_IsOnStairs;
	bool m_DrawDebug;

	void LoadSegment();
	void UnloadSegment();
	void AttemptResetActiveInteractable(const Point2f& spawnPoint);

	void DeleteTerrain();
	void DeleteInteractables();

	void DrawDebug() const;
};