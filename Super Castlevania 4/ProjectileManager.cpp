#include "pch.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "ProjectileTag.h"
#include "Axe.h"
#include "Cross.h"
#include "Dagger.h"
#include "Character.h"
#include "utils.h"

ProjectileManager::ProjectileManager()
	: m_IsDrawDebug{ false }
	, m_pProjectiles{}
{
}

ProjectileManager::~ProjectileManager()
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
	{
		delete m_pProjectiles.at(i);
		m_pProjectiles.at(i) = nullptr;
	}
	m_pProjectiles.clear();
}

void ProjectileManager::Draw(int zIndex) const
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		m_pProjectiles.at(i)->Draw(zIndex);
}

void ProjectileManager::DrawDebug(int zIndex) const
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		m_pProjectiles.at(i)->DrawDebug(zIndex);
}

void ProjectileManager::CheckOverlap(std::vector<Character*>& enemies, Character* player)
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	size_t nrOfEnemies{ enemies.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
	{
		Projectile* projectile{ m_pProjectiles.at(i) };
		if (projectile->IsFriendly())
		{
			for (size_t j{ 0 }; j < nrOfEnemies; ++j)
			{
				Character* enemy{ enemies.at(j) };
				if (projectile->IsOverlapping(enemy->GetShape()))
					ResolveProjectileHit(enemy, projectile);
			}
		}
		else
		{
			if (player->IsOverlapping(projectile->GetShape()))
				ResolveProjectileHit(player, projectile);
		}
	}
}

void ProjectileManager::ResolveProjectileHit(Character* character, Projectile* projectile)
{
	const std::vector<int>& immuneList{ projectile->GetImmuneList() };
	if (std::find(immuneList.begin(), immuneList.end(), character->GetId()) == immuneList.end())
	{
		projectile->AddToImmuneList(character->GetId());
		character->TakeDamage(projectile->GetDamage());
	}
}

void ProjectileManager::AddProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped, int zIndex)
{
	Projectile* projectile{ CreateProjectile(tag, origin, isFriendly, isFlipped, zIndex) };
	m_pProjectiles.push_back(projectile);
}

void ProjectileManager::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		m_pProjectiles.at(i)->SetBoundaries(boundaries);
}

void ProjectileManager::Update(float elapsedSec, const Point2f& cameraBottomLeft)
{
	m_Boundaries.SetBottomLeft(cameraBottomLeft);
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
	{
		m_pProjectiles.at(i)->Update(elapsedSec);
		m_pProjectiles.at(i)->SetBoundaries(m_Boundaries);
	}
	//DeleteProjectiles();
}

void ProjectileManager::DeleteProjectiles()
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
	{
		if (m_pProjectiles.at(i)->IsFlaggedForDeletion())
		{
			std::swap(m_pProjectiles.at(i), m_pProjectiles.back());
			delete m_pProjectiles.back();
			m_pProjectiles.back() = nullptr;
			m_pProjectiles.pop_back();
			--nrOfProjectiles;
		}
	}
}

void ProjectileManager::DeleteProjectile(Projectile* projectile)
{
}

Projectile* ProjectileManager::CreateProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped, int zIndex) const
{
	switch (tag)
	{
	case ProjectileTag::cross:
		return new Cross(origin, m_Boundaries, isFlipped, zIndex);
	case ProjectileTag::dagger:
		return new Dagger(origin, m_Boundaries, isFlipped, zIndex);
	case ProjectileTag::axe:
		return new Axe(origin, m_Boundaries, isFlipped, zIndex);
	}
	return nullptr;
}

void ProjectileManager::Update(float elapsedSec)
{
}