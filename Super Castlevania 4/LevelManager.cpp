#include "pch.h"
#include "LevelManager.h"
#include "TerrainObject.h"
#include "InteractableObject.h"
#include "LevelLoader.h"
#include "Sprite.h"
#include "Character.h"
#include "Background.h"
#include "utils.h"
#include <iostream>

LevelManager::LevelManager(float screenWidth, float screenHeight)
	: m_StageCounter{ 0 }
	, m_SegmentCounter{ 7 }
	, m_CheckpointCounter{ 0 }
	, m_pLevelLoader{ new LevelLoader() }
	, m_pActiveInteractable{ nullptr }
	, m_pBackground{ nullptr }
	, m_IsOnStairs{ true }
	, m_BackgroundSpriteId{}
	, m_WindowSize{ 0, 0, screenWidth, screenHeight }
{
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

Background* LevelManager::GetBackground() const
{
	return nullptr;
}

void LevelManager::Update(float elapsedSec, const Point2f& cameraBottomLeft) const
{
	m_pBackground->Update(elapsedSec, cameraBottomLeft);
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->Update(elapsedSec);
}

void LevelManager::Draw(int zIndex) const
{
	m_pBackground->Draw(zIndex);
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->Draw(zIndex);
}

void LevelManager::DrawDebug(int zIndex) const
{
	size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractableObjects; i++)
		m_pInteractableObjects.at(i)->DrawDebug(zIndex);
	size_t nrOfTerrainObjects{ m_pTerrain.size() };
	for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		m_pTerrain.at(i)->DrawDebug(zIndex);
	utils::SetColor(Color4f{ 1.0f, 1.0f, 0, 1.0f });
	utils::DrawRect(m_TransitionArea);
	utils::SetColor(Color4f{ 0, 1.0f, 1.0f, 1.0f });
	utils::DrawPoint(m_SpawnPoint);
}

void LevelManager::Update(float elapsedSec)
{
}

void LevelManager::HandleCollisions(Character& character)
{
	if (m_IsOnStairs)
	{
		m_pActiveInteractable->HandleCollisions(character);
		if (m_pActiveInteractable->IsDoneInteracting(character))
			m_IsOnStairs = false;
	}
	else
	{
		size_t nrOfTerrainObjects{ m_pTerrain.size() };
		for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		{
			if (m_pTerrain.at(i)->GetZIndex() == character.GetZIndex())
				m_pTerrain.at(i)->HandleCollisions(character);
		}
	}
}

bool LevelManager::IsOnGround(const Character& character) const
{
	if (!m_IsOnStairs)
	{
		size_t nrOfTerrainObjects{ m_pTerrain.size() };
		for (size_t i{ 0 }; i < nrOfTerrainObjects; ++i)
		{
			if (m_pTerrain.at(i)->GetZIndex() == character.GetZIndex()
				&& m_pTerrain.at(i)->IsOnGround(character))
				return true;
		}
	}
	return false;
}

bool LevelManager::IsOnStairs() const
{
	return m_IsOnStairs;
}

bool LevelManager::IsMovingUpstairs(bool isFlipped) const
{
	return m_pActiveInteractable->CheckDirection(isFlipped);
}

bool LevelManager::IsInTransitionArea(const Rectf& actorShape) const
{
	return utils::IsOverlapping(actorShape, m_TransitionArea);
}

void LevelManager::AttemptInteraction(const Rectf& shape, int& zIndex)
{
	if (!m_IsOnStairs)
	{
		size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
		for (size_t i{ 0 }; i < nrOfInteractableObjects; ++i)
		{
			if (m_pInteractableObjects.at(i)->TryInteraction(shape, zIndex, m_IsOnStairs))
			{
				m_pActiveInteractable = m_pInteractableObjects.at(i);
				return;
			}
		}
	}
}

void LevelManager::CheckOverlap(const Rectf& shape, int zIndex)
{
	size_t nrOfInteractableObjects{ m_pInteractableObjects.size() };
	for (size_t i{ 0 }; i < nrOfInteractableObjects; ++i)
	{
		InteractableObject*& interactable{ m_pInteractableObjects.at(i) };
		if (!m_IsOnStairs && interactable->IsAutoInteracting()
			&& interactable->TryAutoInteracting(shape, m_IsOnStairs, zIndex))
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

void LevelManager::LoadSegment()
{
	UnloadSegment();
	m_pTerrain = m_pLevelLoader->LoadTerrain(m_StageCounter, m_SegmentCounter);
	m_pInteractableObjects = m_pLevelLoader->LoadInteractables(m_StageCounter, m_SegmentCounter);
	m_TransitionArea = m_pLevelLoader->LoadTransitionArea(m_StageCounter, m_SegmentCounter);
	m_Boundaries = m_pLevelLoader->LoadBoundaries(m_StageCounter, m_SegmentCounter);
	m_SpawnPoint = m_pLevelLoader->LoadPlayerSpawn(m_StageCounter, m_SegmentCounter);
	m_pBackground = m_pLevelLoader->GetBackground(m_StageCounter, m_SegmentCounter);
	m_pBackground->SetWindowSize(m_WindowSize);
	if (m_pLevelLoader->IsSegmentCheckpoint(m_StageCounter, m_SegmentCounter))
		m_CheckpointCounter = m_SegmentCounter;
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
}

void LevelManager::ReloadCheckpoint()
{
	m_SegmentCounter = m_CheckpointCounter;
	LoadSegment();
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