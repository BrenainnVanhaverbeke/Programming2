#include "pch.h"
#include "LevelManager.h"
#include "SVGParser.h"
#include "Texture.h"
#include "Stairs.h"
#include "StaticTerrain.h"
#include "DynamicTerrain.h"
#include "LevelLoader.h"
#include <iostream>

LevelManager::LevelManager()
	: m_StageCounter{ 0 }
	, m_SegmentCounter{ 0 }
	, m_pLevelLoader{ new LevelLoader() }
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
	delete m_pLevelLoader;
	m_pBackgroundTexture = nullptr;
	m_pLevelLoader = nullptr;
	UnloadSegment();
}

Rectf LevelManager::GetBoundaries() const
{
	return m_Boundaries;
}

Point2f LevelManager::GetSpawn() const
{
	return m_SpawnPoint;
}

void LevelManager::Update(float elapsedSec, const Rectf& actorShape)
{
	size_t nrCrumblingBlocks{ m_pDynamicTerrain.size() };
	for (size_t i{ 0 }; i < nrCrumblingBlocks; ++i)
		m_pDynamicTerrain.at(i)->Update(elapsedSec, actorShape);
}

void LevelManager::Draw() const
{
	//m_pBackgroundTexture->Draw();
	size_t nrOfStaticTerrain{ m_pStaticTerrain.size() };
	for (size_t i{ 0 }; i < nrOfStaticTerrain; ++i)
		m_pStaticTerrain.at(i)->Draw();
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i{ 0 }; i < nrOfStairs; i++)
		m_pStairs.at(i)->Draw();
	size_t nrCrumblingBlocks{ m_pDynamicTerrain.size() };
	for (size_t i{ 0 }; i < nrCrumblingBlocks; ++i)
		m_pDynamicTerrain.at(i)->Draw();
}

void LevelManager::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity)
{
	size_t nrOfStairs{ m_pStairs.size() };
	size_t nrOfStaticTerrain{ m_pStaticTerrain.size() };
	size_t nrOfCrumblingBlocks{ m_pDynamicTerrain.size() };
	switch (m_CollisionMode)
	{
	case CollisionMode::terrain:
		for (size_t i{ 0 }; i < nrOfStaticTerrain; ++i)
			m_pStaticTerrain.at(i)->HandleCollisions(actorShape, actorTransform, actorVelocity);
		for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
			m_pDynamicTerrain.at(i)->HandleCollisions(actorShape, actorTransform, actorVelocity);
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
	size_t nrOfStaticTerrain{ m_pStaticTerrain.size() };
	for (size_t i{ 0 }; i < nrOfStaticTerrain; ++i)
	{
		if (m_pStaticTerrain.at(i)->IsOnGround(actorShape, actorVelocity))
			return true;
	}
	size_t nrOfCrumblingBlocks{ m_pDynamicTerrain.size() };
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
	{
		if (m_pDynamicTerrain.at(i)->IsOnGround(actorShape, actorVelocity))
			return true;
	}
	return false;
}

bool LevelManager::IsOnStairs() const
{
	return m_CollisionMode == CollisionMode::stairs;
}

bool LevelManager::IsInTransitionArea(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_TransitionArea);
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

void LevelManager::DeleteStaticTerrain()
{
	size_t nrOfStaticTerrain{ m_pStaticTerrain.size() };
	for (size_t i{ 0 }; i < nrOfStaticTerrain; ++i)
		delete m_pStaticTerrain.at(i);
	m_pStaticTerrain.clear();
}

void LevelManager::DeleteStairs()
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i{ 0 }; i < nrOfStairs; ++i)
		delete m_pStairs.at(i);
	m_pStairs.clear();
}

void LevelManager::DeleteDynamicTerrain()
{
	size_t nrOfCrumblingBlocks{ m_pDynamicTerrain.size() };
	for (size_t i{ 0 }; i < nrOfCrumblingBlocks; ++i)
		delete m_pDynamicTerrain.at(i);
	m_pDynamicTerrain.clear();
}

void LevelManager::NextStage()
{
	m_StageCounter++;
	m_SegmentCounter = 0;
	LoadSegment();
}

void LevelManager::NextSegment()
{
	m_SegmentCounter++;
	LoadSegment();
}

void LevelManager::LoadBackground()
{
	if (m_pBackgroundTexture) delete m_pBackgroundTexture;
	std::string path{ "./Resources/Images/Stage " + std::to_string(m_StageCounter) + ".png" };
	m_pBackgroundTexture = new Texture(path);
}

void LevelManager::LoadSegment()
{
	UnloadSegment();
	m_pStaticTerrain = m_pLevelLoader->LoadTerrain(m_StageCounter, m_SegmentCounter);
	m_TransitionArea = m_pLevelLoader->LoadTransitionArea(m_StageCounter, m_SegmentCounter);
	m_Boundaries = m_pLevelLoader->LoadBoundaries(m_StageCounter, m_SegmentCounter);
	m_SpawnPoint = m_pLevelLoader->LoadPlayerSpawn(m_StageCounter, m_SegmentCounter);
	m_pStairs = m_pLevelLoader->LoadStairs(m_StageCounter, m_SegmentCounter);
	m_pDynamicTerrain = m_pLevelLoader->LoadDynamicTerrain(m_StageCounter, m_SegmentCounter);
}

void LevelManager::UnloadSegment()
{
	DeleteStaticTerrain();
	DeleteDynamicTerrain();
	DeleteStairs();
}