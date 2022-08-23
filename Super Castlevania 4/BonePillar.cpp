#include "pch.h"
#include "BonePillar.h"
#include "NoMovement.h"
#include "Sprite.h"
#include <iostream>

BonePillar::BonePillar(const Transform& transform, int zIndex, int id)
	: Character
	(
		transform,
		GetSprite(),
		new NoMovement(),
		CharacterTypes::bonePillar,
		ProjectileTag::fireball,
		nullptr,
		28.0f,
		45.0f,
		zIndex,
		80,
		id
	)
	, m_ActionState{ ActionState::idle }
	, m_ElapsedTime{ 0 }
	, m_HasFiredBurst{ false }
	, m_FiredRounds{ 0 }
{
}

BonePillar::BonePillar(const Point2f& origin, int zIndex, int id)
	: BonePillar(Transform{ origin }, zIndex, id)
{
}

void BonePillar::Update(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;
	switch (m_ActionState)
	{
	case BonePillar::ActionState::idle:
		HandleIdle(elapsedSec);
		break;
	case BonePillar::ActionState::charginMahLazor:
		HandleCharginMahLazor(elapsedSec);
		break;
	case BonePillar::ActionState::firing:
		HandleFiring(elapsedSec);
		break;
	case BonePillar::ActionState::dying:
		HandleDying(elapsedSec);
		break;
	}
}

void BonePillar::Draw(int zIndex) const
{
	if (m_ZIndex == zIndex)
	{
		m_pSprite->Draw(m_Transform);
	}
}

void BonePillar::CheckOverlap(const Rectf& overlappingShape)
{
}

void BonePillar::TakeDamage(int damage)
{
	m_Health -= damage;
	if (m_Health <= 0)
	{
		m_ElapsedTime = 0;
		m_ActionState = ActionState::dying;
	}
}

bool BonePillar::ShouldFire()
{
	if (m_ShouldFire)
	{
		m_ShouldFire = false;
		return true;
	}
	return false;
}

Point2f BonePillar::GetProjectileSpawn() const
{
	const float yOffset{ 10.0f };
	return GetShape().GetCenter(0, ((m_IsFlipped) ? yOffset : -yOffset));
}

void BonePillar::HandleIdle(float elapsedSec)
{
	const float weaponCooldown{ 2 };
	if (weaponCooldown < m_ElapsedTime)
	{
		m_ElapsedTime = 0;
		m_ActionState = ActionState::charginMahLazor;
	}
}

void BonePillar::HandleCharginMahLazor(float elapsedSec)
{
	const float maxChargeTime{ 2.0f };
	m_pSprite->Update(elapsedSec, -1);
	if (maxChargeTime < m_ElapsedTime)
	{
		m_ElapsedTime = 0;
		m_pSprite->Reset(-1);
		m_ActionState = ActionState::firing;
	}
}

void BonePillar::HandleFiring(float elapsedSec)
{
	const int maxBurstFire{ 2 };
	const float burstFireCooldown{ 1.0f };
	if (!m_HasFiredBurst)
	{
		bool isCooldownOver{ burstFireCooldown < m_ElapsedTime };
		if (isCooldownOver)
		{
			m_ShouldFire = true;
			++m_FiredRounds;
			m_ElapsedTime = 0;
			if (maxBurstFire < m_FiredRounds)
			{
				m_FiredRounds = 0;
				m_HasFiredBurst = true;
			}
		}
	}
	else
	{
		m_ActionState = ActionState::idle;
		m_HasFiredBurst = false;
	}
}

void BonePillar::HandleDying(float elapsedSec)
{
	const float maxDeathTime{ 1.0f / 8 };
	m_pSprite->Update(elapsedSec, 0);
	if (maxDeathTime < m_ElapsedTime)
		m_ShouldDie = true;
}

Sprite* BonePillar::GetSprite() const
{
	std::string path{ "Enemies.png" };
	Point2f sourceRectOrigin{ 0, 622.0f };
	float sourceWidth{ 28 };
	float sourceHeight{ 45 };
	Rectf sourceRect{ sourceRectOrigin, sourceWidth, sourceHeight };
	int frames{ 2 };
	int rows{ 2 };
	int framesPerSecond{ 4 };
	return new Sprite(path, sourceRect, frames, rows, framesPerSecond);
}
