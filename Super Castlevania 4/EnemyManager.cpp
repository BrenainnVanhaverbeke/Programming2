#include "pch.h"
#include "EnemyManager.h"
#include "Character.h"
#include "CharacterTypes.h"
#include "ProjectileTag.h"
#include "ProjectileManager.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "utils.h"
#include <iostream>

EnemyManager::EnemyManager(ProjectileManager* projectileManager)
	: m_pEnemies{}
	, m_pSpawners{}
	, m_EnemyCounter{ 0 }
	, m_pProjectileManager{ projectileManager }
{
	m_pSpawners.push_back(new EnemySpawner(CharacterTypes::bat, Point2f{ 200, 100 }, 0));
	m_pSpawners.push_back(new EnemySpawner(CharacterTypes::bat, Point2f{ 250, 100 }, 0));
	m_pSpawners.push_back(new EnemySpawner(CharacterTypes::bat, Point2f{ 300, 100 }, 0));
	m_pSpawners.push_back(new EnemySpawner(CharacterTypes::bonePillar, Point2f{ 128, 32 }, 0));
}

EnemyManager::~EnemyManager()
{
	DeleteEnemies();
	DeleteSpawners();
}

void EnemyManager::Update(float elapsedSec, Character* player)
{
	UpdateEnemies(elapsedSec, player);
	UpdateSpawners(elapsedSec, player);
	CheckDeletion();
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

void EnemyManager::HandleAttack(Player* player)
{
	const std::vector<Point2f>& weaponShape{ player->GetWeaponShape() };
	const std::vector<int>& immuneList{ player->GetImmunityList() };
	size_t nrOfEnemies{ m_pEnemies.size() };
	for (size_t i{ 0 }; i < nrOfEnemies; ++i)
	{
		Character*& enemy{ m_pEnemies.at(i) };
		if (enemy->GetZIndex() == player->GetZIndex() && enemy->IsOverlapping(weaponShape)
			&& std::find(immuneList.begin(), immuneList.end(), enemy->GetId()) == immuneList.end())
		{
			player->AddImmuneId(enemy->GetId());
			enemy->TakeDamage(player->GetWeaponDamage());
		}
	}
}

std::vector<Character*>& EnemyManager::GetEnemies()
{
	return m_pEnemies;
}

void EnemyManager::UpdateEnemies(float elapsedSec, Character* player)
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
		enemy->SetIsFlipped(player->GetTransform().positionX - enemy->GetTransform().positionX < 0);
		if (ShouldEnemyDespawn(enemy, player))
		{
			nrOfEnemies--;
			std::swap(enemy, m_pEnemies.back());
			delete m_pEnemies.back();
			m_pEnemies.back() = nullptr;
			m_pEnemies.pop_back();
		}
	}
}

void EnemyManager::UpdateSpawners(float elapsedSec, Character* player)
{
	size_t nrOfSpawners{ m_pSpawners.size() };
	for (size_t i{ 0 }; i < nrOfSpawners; ++i)
	{
		EnemySpawner*& spawner{ m_pSpawners.at(i) };
		spawner->Update(elapsedSec, player);
		if (spawner->ShouldSpawn())
		{
			++m_EnemyCounter;
			m_pEnemies.push_back(spawner->Spawn(player, m_EnemyCounter));
		}
	}
}

bool EnemyManager::ShouldEnemyDespawn(Character* enemy, Character* player)
{
	const float despawnDistance{ 300.0f };
	float distance{ utils::GetDistance(enemy->GetShape().GetCenter(), player->GetShape().GetCenter()) };
	return enemy->ShouldDie() || despawnDistance < distance;
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

void EnemyManager::CheckDeletion()
{
}

void EnemyManager::Update(float elapsedSec)
{
}