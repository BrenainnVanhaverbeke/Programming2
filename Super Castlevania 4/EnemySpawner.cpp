#include "pch.h"
#include "EnemySpawner.h"
#include "utils.h"
#include "Character.h"
#include "Bat.h"
#include "Sprite.h"
#include <iostream>

EnemySpawner::EnemySpawner(std::string enemyType, const Point2f& location, int zIndex)
	: m_EnemyType{ enemyType }
	, m_Location{ location }
	, m_HasActivated{ false }
	, m_ShouldSpawn{ false }
	, m_SpawnRange{ 384.0f }
	, m_ZIndex{ zIndex }
{
}

void EnemySpawner::Update(float elapsedSec, Character* player)
{
	float distance{ utils::GetDistance(player->GetTransform().GetTranslation(), m_Location) };
	if (!m_HasActivated && distance < m_SpawnRange)
	{
		m_HasActivated = true;
		m_ShouldSpawn = true;
	}
	if (m_HasActivated && m_SpawnRange < distance)
		m_HasActivated = false;
}

bool EnemySpawner::ShouldSpawn()
{
	return m_ShouldSpawn;
}

Character* EnemySpawner::Spawn(Character* player, int id)
{
	m_ShouldSpawn = false;
	bool isMovingLeft{ 0 < m_Location.x - player->GetTransform().positionX };
	if (m_EnemyType == "Bat")
		return new Bat(m_Location, m_ZIndex, isMovingLeft, id);
	return nullptr;
}

void EnemySpawner::Update(float elapsedSec)
{
}

void EnemySpawner::Draw(int zIndex) const
{
}

void EnemySpawner::DrawDebug(int zIndex) const
{
	Color4f spawnColour{ 0, 1.0f, 0, 1.0f };
	utils::SetColor(spawnColour);
	if (m_ZIndex == zIndex)
		utils::DrawRect(m_Location, 10.0f, 10.0f);
}
