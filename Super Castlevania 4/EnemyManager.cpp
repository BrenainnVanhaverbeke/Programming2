#include "pch.h"
#include "EnemyManager.h"
#include "Character.h"
#include "CharacterTypes.h"
#include "ProjectileTag.h"
#include "ProjectileManager.h"
#include "LevelManager.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "utils.h"
#include <iostream>

EnemyManager::EnemyManager(ProjectileManager* pProjectileManager, LevelManager* pLevelManager)
	: m_pEnemies{}
	, m_pSpawners{}
	, m_EnemyCounter{ 0 }
	, m_pProjectileManager{ pProjectileManager }
	, m_pLevelManager{ pLevelManager }
{
}

EnemyManager::~EnemyManager()
{
	DeleteEnemies();
	DeleteSpawners();
}

void EnemyManager::Update(float elapsedSec, Character* pPlayer)
{
	UpdateEnemies(elapsedSec, pPlayer);
	UpdateSpawners(elapsedSec, pPlayer);
	CheckDeletion(pPlayer);
}

void EnemyManager::Draw(int zIndex) const
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
		m_pEnemies.at(i)->Draw(zIndex);
	size_t nrOfSpawners{ m_pSpawners.size() };
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
		m_pSpawners.at(i)->Draw(zIndex);
}

void EnemyManager::DrawDebug(int zIndex) const
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
		m_pEnemies.at(i)->DrawDebug(zIndex);
	size_t nrOfSpawners{ m_pSpawners.size() };
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
		m_pSpawners.at(i)->DrawDebug(zIndex);
}

void EnemyManager::HandleAttack(Player* pPlayer)
{
	const std::vector<Point2f>& weaponShape{ pPlayer->GetWeaponShape() };
	const std::vector<int>& immuneList{ pPlayer->GetImmunityList() };
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		Character*& enemy{ m_pEnemies.at(i) };
		if (enemy->GetZIndex() == pPlayer->GetZIndex() && enemy->IsOverlapping(weaponShape)
			&& std::find(immuneList.begin(), immuneList.end(), enemy->GetId()) == immuneList.end())
		{
			pPlayer->AddImmuneId(enemy->GetId());
			enemy->TakeDamage(pPlayer->GetWeaponDamage());
		}
	}
}

void EnemyManager::CheckOverlap(Player* player)
{
	const int contactDamage{ 10 };
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		if (player->GetZIndex() == m_pEnemies.at(i)->GetZIndex() && player->IsOverlapping(m_pEnemies.at(i)->GetShape()))
		{
			player->TakeDamage(10);
			return;
		}
	}
}

std::vector<Character*>& EnemyManager::GetEnemies()
{
	return m_pEnemies;
}


void EnemyManager::LoadSegment()
{
	DeleteEnemies();
	DeleteSpawners();
	m_pSpawners = m_pLevelManager->GetEnemySpawners();
}

void EnemyManager::UpdateEnemies(float elapsedSec, Character* pPlayer)
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		Character*& enemy{ m_pEnemies.at(i) };
		m_pEnemies.at(i)->Update(elapsedSec);
		if (enemy->ShouldFire())
		{
			m_pProjectileManager->AddProjectile(enemy->GetProjectileTag(), enemy->GetProjectileSpawn(), false, enemy->IsFlipped(), enemy->GetZIndex());
		}
		enemy->SetIsFlipped(pPlayer->GetTransform().positionX - enemy->GetTransform().positionX < 0);
	}
}

void EnemyManager::UpdateSpawners(float elapsedSec, Character* pPlayer)
{
	size_t nrOfSpawners{ m_pSpawners.size() };
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
	{
		EnemySpawner*& spawner{ m_pSpawners.at(i) };
		spawner->Update(elapsedSec, pPlayer);
		if (spawner->ShouldSpawn())
		{
			++m_EnemyCounter;
			m_pEnemies.push_back(spawner->Spawn(pPlayer, m_pLevelManager, m_EnemyCounter));
		}
	}
}

bool EnemyManager::ShouldEnemyDespawn(Character*& pEnemy, Character* pPlayer)
{
	const float despawnDistance{ 300.0f };
	float distance{ utils::GetDistance(pEnemy->GetShape().GetCenter(), pPlayer->GetShape().GetCenter()) };
	return pEnemy->ShouldDie() || despawnDistance < distance;
}

void EnemyManager::DeleteEnemies()
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		delete m_pEnemies.at(i);
		m_pEnemies.at(i) = nullptr;
	}
	m_pEnemies.clear();
}

void EnemyManager::DeleteSpawners()
{
	size_t nrOfSpawners{ m_pSpawners.size() };
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
	{
		delete m_pSpawners.at(i);
		m_pSpawners.at(i) = nullptr;
	}
	m_pSpawners.clear();
}

void EnemyManager::CheckDeletion(Character* pPlayer)
{
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		Character*& enemy{ m_pEnemies.at(i) };
		if (ShouldEnemyDespawn(enemy, pPlayer))
		{
			--nrOfEnemies;
			std::swap(enemy, m_pEnemies.back());
			delete m_pEnemies.back();
			m_pEnemies.back() = nullptr;
			m_pEnemies.pop_back();
		}
	}
}

void EnemyManager::Update(float elapsedSec)
{
}