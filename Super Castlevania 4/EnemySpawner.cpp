#include "pch.h"
#include "EnemySpawner.h"
#include "utils.h"
#include "Character.h"
#include "CharacterTypes.h"
#include "LevelManager.h"
#include "Bat.h"
#include "BonePillar.h"
#include "Skeleton.h"
#include "Sprite.h"

EnemySpawner::EnemySpawner(CharacterTypes enemyType, const Point2f& location, int zIndex)
	: m_EnemyType{ enemyType }
	, m_Location{ location }
	, m_HasActivated{ false }
	, m_ShouldSpawn{ false }
	, m_ZIndex{ zIndex }
{
}

void EnemySpawner::Update(float elapsedSec, Character* player)
{
	const float spawnRange{ 290.0f };
	float distance{ utils::GetDistance(player->GetTransform().GetTranslation(), m_Location) };
	if (!m_HasActivated && distance < spawnRange)
	{
		m_HasActivated = true;
		m_ShouldSpawn = true;
	}
	if (m_HasActivated && spawnRange < distance)
	{
		m_HasActivated = false;
	}
}

bool EnemySpawner::ShouldSpawn()
{
	return m_ShouldSpawn;
}

Character* EnemySpawner::Spawn(Character* pPlayer, LevelManager* pLevelManager, int id)
{
	m_ShouldSpawn = false;
	bool isMovingLeft{ 0 < m_Location.x - pPlayer->GetTransform().positionX };
	switch (m_EnemyType)
	{
	case CharacterTypes::bat:
		return new Bat(m_Location, m_ZIndex, isMovingLeft, id);
	case CharacterTypes::bonePillar:
		return new BonePillar(m_Location, m_ZIndex, id);
	case CharacterTypes::skeleton:
		return new Skeleton(m_Location, pLevelManager, m_ZIndex, id);
	}
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
