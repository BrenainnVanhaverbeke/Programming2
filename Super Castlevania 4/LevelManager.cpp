#include "pch.h"
#include "LevelManager.h"
#include "SVGParser.h"
#include "Texture.h"
#include "Stairs.h"
#include "Terrain.h"
#include "LevelLoader.h"
#include <iostream>

LevelManager::LevelManager()
	: m_StageCounter{ 0 }
	, m_SegmentCounter{ 0 }
	, m_pLevelLoader{ new LevelLoader() }
	, m_pTerrain{ nullptr }
	, m_pBackgroundTexture{ nullptr }
	, m_pActiveStairs{ nullptr }
	, m_CollisionMode{ CollisionMode::terrain }
{
	LoadBackground();
	LoadSegment();
}

LevelManager::~LevelManager()
{
	delete m_pBackgroundTexture;
	delete m_pTerrain;
	delete m_pLevelLoader;
	m_pBackgroundTexture = nullptr;
	m_pTerrain = nullptr;
	m_pLevelLoader = nullptr;
	DeleteStairs();
}

Terrain* LevelManager::GetTerrain() const
{
	return m_pTerrain;
}

Rectf LevelManager::GetBoundaries() const
{
	return m_Boundaries;
}

Point2f LevelManager::GetSpawn() const
{
	return m_SpawnPoint;
}

void LevelManager::Draw() const
{
	//m_pBackgroundTexture->Draw();
	m_pTerrain->Draw();
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i = 0; i < nrOfStairs; i++)
		m_pStairs.at(i)->Draw();
}

void LevelManager::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity)
{
	size_t nrOfStairs{ m_pStairs.size() };
	switch (m_CollisionMode)
	{
	case CollisionMode::terrain:
		m_pTerrain->HandleCollisions(actorShape, actorTransform, actorVelocity);
		break;
	case CollisionMode::stairs:
		m_pActiveStairs->HandleCollisions(actorShape, actorTransform, actorVelocity);
		if (m_pActiveStairs->IsEndReached(actorShape))
			m_CollisionMode = CollisionMode::terrain;
		break;
	case CollisionMode::background:
		break;
	default:
		break;
	}
}

bool LevelManager::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return m_pTerrain->IsOnGround(actorShape, actorVelocity);
}

bool LevelManager::IsOnStairs() const
{
	return m_CollisionMode == CollisionMode::stairs;
}

void LevelManager::AttemptInteraction(const Rectf& shape)
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i{ 0 }; i < nrOfStairs; ++i)
	{
		if (m_pStairs.at(i)->IsOverlapping(shape))
		{
			m_pActiveStairs = m_pStairs.at(i);
			m_CollisionMode = CollisionMode::stairs;
			return;
		}
	}
}

void LevelManager::CheckOverlap(const Rectf& shape)
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i{ 0 }; i < nrOfStairs; ++i)
	{
		if (m_pStairs.at(i)->CheckAutoMount(shape))
		{
			m_pActiveStairs = m_pStairs.at(i);
			m_CollisionMode = CollisionMode::stairs;
			return;
		}
	}
}

void LevelManager::DeleteStairs()
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i{ 0 }; i < nrOfStairs; ++i)
		delete m_pStairs.at(i);
	m_pStairs.clear();
}

void LevelManager::NextStage()
{
	m_StageCounter++;
}

void LevelManager::NextSegment()
{
	m_SegmentCounter++;
}

void LevelManager::LoadBackground()
{
	if (m_pBackgroundTexture) delete m_pBackgroundTexture;
	std::string path{ "./Resources/Images/Stage " + std::to_string(m_StageCounter) + ".png" };
	m_pBackgroundTexture = new Texture(path);
}

void LevelManager::LoadSegment()
{
	std::string path{ "./Resources/SVGs/Segment " + std::to_string(m_StageCounter) + std::to_string(m_SegmentCounter) };
	m_pTerrain = m_pLevelLoader->LoadTerrain(m_StageCounter, m_SegmentCounter);
	m_Boundaries = m_pLevelLoader->LoadBoundaries(m_StageCounter, m_SegmentCounter);
	m_SpawnPoint = m_pLevelLoader->LoadPlayerSpawn(m_StageCounter, m_SegmentCounter);
	m_pStairs = m_pLevelLoader->LoadStairs(m_StageCounter, m_SegmentCounter);
}