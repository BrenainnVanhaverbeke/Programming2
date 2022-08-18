#include "pch.h"
#include "ProjectileManager.h"
#include "Projectile.h"
#include "ProjectileTag.h"
#include "Axe.h"

ProjectileManager::ProjectileManager()
	: m_IsDrawDebug{ false }
	, m_pProjectiles{}
{
}

ProjectileManager::~ProjectileManager()
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		delete m_pProjectiles.at(i);
	m_pProjectiles.clear();
}

void ProjectileManager::Update(float elapsedSec)
{
	DeleteProjectiles();
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		m_pProjectiles.at(i)->Update(elapsedSec);
}

void ProjectileManager::Draw(int zIndex) const
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
	{
		m_pProjectiles.at(i)->Draw(zIndex);
		if (m_IsDrawDebug)
			m_pProjectiles.at(i)->DrawDebug();
	}
}

void ProjectileManager::AddProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped)
{
	m_pProjectiles.push_back(CreateProjectile(tag, origin, isFriendly, isFlipped));
}

void ProjectileManager::SetBoundaries(const Rectf& boundaries)
{
	size_t nrOfProjectiles{ m_pProjectiles.size() };
	for (size_t i{ 0 }; i < nrOfProjectiles; ++i)
		m_pProjectiles.at(i)->SetBoundaries(boundaries);
}

void ProjectileManager::ToggleDrawDebug()
{
	m_IsDrawDebug = !m_IsDrawDebug;
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

Projectile* ProjectileManager::CreateProjectile(ProjectileTag tag, const Point2f& origin, bool isFriendly, bool isFlipped) const
{
	switch (tag)
	{
	case ProjectileTag::none:
		return nullptr;
	case ProjectileTag::cross:
		return nullptr;
	case ProjectileTag::dagger:
		return nullptr;
	case ProjectileTag::axe:
		return new Axe(origin, isFlipped);
	case ProjectileTag::holyWater:
		return nullptr;
	}
	return nullptr;
}