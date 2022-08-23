#pragma once
#include "Vector2f.h"
#include <vector>
#include "GameObject.h"

class LevelLoader;
class TerrainObject;
class InteractableObject;
class Sprite;
class Character;
class Background;
class EnemySpawner;

class LevelManager final : public GameObject
{
public:
	LevelManager(float screenWidth, float screenHeight);
	LevelManager(const LevelManager& other) = delete;
	LevelManager(LevelManager&& other) = delete;
	LevelManager& operator=(const LevelManager& rhs) = delete;
	LevelManager& operator=(LevelManager&& rhs) = delete;
	virtual ~LevelManager();

	void NextStage();
	void NextSegment();

	Rectf GetBoundaries() const;
	Point2f GetSpawn() const;
	Background* GetBackground() const;
	std::vector<EnemySpawner*> GetEnemySpawners() const;

	void Update(float elapsedSec, const Point2f& cameraBottomLeft) const;

	void HandleCollisions(Character& character);
	bool IsOnGround(const Character& character) const;
	bool IsOnStairs() const;
	bool IsMovingUpstairs(bool isFlipped) const;
	bool IsInTransitionArea(const Rectf& actorShape) const;
	void ReloadCheckpoint();

	void AttemptInteraction(const Rectf& player, int& zIndex);
	void CheckOverlap(const Rectf& shape, int zIndex);
	
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

private:

	LevelLoader* m_pLevelLoader;
	std::vector<TerrainObject*> m_pTerrain;
	std::vector<InteractableObject*> m_pInteractableObjects;
	InteractableObject* m_pActiveInteractable;
	Rectf m_Boundaries;
	Rectf m_TransitionArea;
	Rectf m_WindowSize;
	Point2f m_SpawnPoint;
	Background* m_pBackground;

	int m_BackgroundSpriteId;
	int m_StageCounter;
	int m_SegmentCounter;
	int m_CheckpointCounter;
	bool m_IsOnStairs;
	
	void LoadSegment();
	void UnloadSegment();
	void AttemptResetActiveInteractable(const Point2f& spawnPoint);

	void DeleteTerrain();
	void DeleteInteractables();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
};