#include "pch.h"
#include "EnemySpawner.h"
#include "utils.h"
#include "Character.h"

EnemySpawner::EnemySpawner(std::string enemyType, const Point2f& location)
	: m_EnemyType{ enemyType }
	, m_Location{ location }
	, m_HasActivated{ false }
{
}

bool EnemySpawner::ShouldSpawn(Character* player)
{
	utils::GetDistance(player->GetTransform().GetTranslation(), m_Location);
	return false;
}
