#include "pch.h"
#include "EnemyManager.h"
#include "Character.h"

EnemyManager::~EnemyManager()
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		delete m_pEnemies.at(i);
		m_pEnemies.at(i) = nullptr;
	}
	m_pEnemies.clear();
}

void EnemyManager::Update(float elapsedSec)
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
		m_pEnemies.at(i)->Update(elapsedSec);
}

void EnemyManager::Draw(int zIndex) const
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
		m_pEnemies.at(i)->Draw(zIndex);
}
