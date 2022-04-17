#include "pch.h"
#include "LevelManager.h"
#include "TerrainObject.h"
#include "InteractableObject.h"
#include "LevelLoader.h"
#include "Sprite.h"
#include "utils.h"
#include <iostream>

LevelManager::LevelManager()
	: m_StageCounter{ 0 }
	, m_SegmentCounter{ 0 }
	, m_pLevelLoader{ new LevelLoader() }
	, m_pActiveInteractable{ nullptr }
	, m_pBackground{ nullptr }
	, m_IsOnBackground{ false }
	, m_IsOnStairs{ true }
	, m_BackgroundSpriteId{}
	, m_DrawDebug{ false }
{
	LoadBackground();
	LoadSegment();
}

LevelManager::~LevelManager()
{
	delete m_pLevelLoader;
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
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->Update(elapsedSec);
}

void LevelManager::Draw() const
{
	m_pBackground->Draw(Transform{});
	if (m_DrawDebug)
		DrawDebug();
}

void LevelManager::DrawDebug() const
{
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->Draw();
	size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractableObjects; i++)
		m_pInteractableObjects.at(i)->Draw();
	utils::SetColor(Color4f{ 1.0f, 1.0f, 0, 1.0f });
	utils::DrawRect(m_TransitionArea);
	utils::SetColor(Color4f{ 0, 1.0f, 1.0f, 1.0f });
	utils::DrawPoint(m_SpawnPoint);
}

void LevelManager::HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity)
{
	if (m_IsOnStairs)
	{
		m_pActiveInteractable->HandleCollisions(actorShape, actorTransform, actorVelocity);
		if (m_pActiveInteractable->IsDoneInteracting(actorShape))
			m_IsOnStairs = false;
	}
	else
	{
		size_t nrOfTerrainObjects{ m_pTerrain.size() };
		for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		{
			if (m_pTerrain.at(i)->IsBackground() == m_IsOnBackground)
				m_pTerrain.at(i)->HandleCollisions(actorShape, actorTransform, actorVelocity);
		}
	}
}

bool LevelManager::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	if (!m_IsOnStairs)
	{
		size_t nrOfTerrainObjects{ m_pTerrain.size() };
		for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		{
			if (m_pTerrain.at(i)->IsBackground() == m_IsOnBackground
				&& m_pTerrain.at(i)->IsOnGround(actorShape, actorVelocity))
				return true;
		}
	}
	return false;
}

bool LevelManager::IsOnStairs() const
{
	return m_IsOnStairs;
}

bool LevelManager::IsUpstairs(const Vector2f& actorVelocity) const
{
	return m_pActiveInteractable->CheckDirection(actorVelocity);
}

bool LevelManager::IsInTransitionArea(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_TransitionArea);
}

void LevelManager::ToggleDebugDraw()
{
	m_DrawDebug = !m_DrawDebug;
}

void LevelManager::AttemptInteraction(const Rectf& shape)
{
	if (!m_IsOnStairs)
	{
		size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
		for (size_t i{ 0 }; i < nrOfInteractableObjects; ++i)
		{
			if (m_pInteractableObjects.at(i)->TryInteraction(shape, m_IsOnBackground, m_IsOnStairs))
			{
				m_pActiveInteractable = m_pInteractableObjects.at(i);
				return;
			}
		}
	}
}

void LevelManager::CheckOverlap(const Rectf& shape)
{
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->CheckOverlap(shape);
	size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractableObjects; ++i)
	{
		InteractableObject*& interactable{ m_pInteractableObjects.at(i) };
		if (!m_IsOnStairs && interactable->IsAutoInteracting()
			&& interactable->TryAutoInteracting(shape, m_IsOnStairs, m_IsOnBackground))
		{
			m_pActiveInteractable = interactable;
			return;
		}
	}
}

void LevelManager::DeleteTerrain()
{
	size_t nrOfStaticTerrain{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfStaticTerrain; ++i)
		delete m_pTerrain.at(i);
	m_pTerrain.clear();
}

void LevelManager::DeleteInteractables()
{
	size_t nrOfInteractables{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractables; ++i)
		delete m_pInteractableObjects.at(i);
	m_pInteractableObjects.clear();
	m_pActiveInteractable = nullptr;
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
	//if (m_pBackgroundTexture) delete m_pBackgroundTexture;
	//std::string path{ "./Resources/Images/Stage " + std::to_string(m_StageCounter) + ".png" };
	//m_pBackgroundTexture = new Texture(path);
}

void LevelManager::LoadSegment()
{
	UnloadSegment();
	m_pTerrain = m_pLevelLoader->LoadTerrain(m_StageCounter, m_SegmentCounter);
	m_pInteractableObjects = m_pLevelLoader->LoadInteractables(m_StageCounter, m_SegmentCounter);
	m_TransitionArea = m_pLevelLoader->LoadTransitionArea(m_StageCounter, m_SegmentCounter);
	m_Boundaries = m_pLevelLoader->LoadBoundaries(m_StageCounter, m_SegmentCounter);
	m_SpawnPoint = m_pLevelLoader->LoadPlayerSpawn(m_StageCounter, m_SegmentCounter);
	m_pBackground = m_pLevelLoader->GetBackground(m_StageCounter, m_SegmentCounter);
	AttemptResetActiveInteractable(m_SpawnPoint);
}

void LevelManager::UnloadSegment()
{
	DeleteTerrain();
	DeleteInteractables();
	if (m_pBackground)
	{
		delete m_pBackground;
		m_pBackground = nullptr;
	}
	m_IsOnBackground = false;
}

void LevelManager::AttemptResetActiveInteractable(const Point2f& spawnPoint)
{
	size_t nrOfInteractables{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractables; ++i)
	{
		if (m_pInteractableObjects.at(i)->CheckIfActive(spawnPoint))
		{
			m_pActiveInteractable = m_pInteractableObjects.at(i);
			return;
		}
	}
	m_IsOnStairs = false;
}
