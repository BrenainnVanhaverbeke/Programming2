#include "pch.h"
#include "Bullet.h"
#include "utils.h"
#include "Enemy.h"

Bullet::Bullet()
	: Bullet(0.0f, 0.0f)
{
}

Bullet::Bullet(float width, float height)
	: m_Width{ width }, m_Height{ height }, m_IsActivated{ false }, m_Center{ },
	m_Velocity{ 0.0f, 200.0f }, m_Boundaries{}
{
}

void Bullet::Draw() const
{
	if (m_IsActivated)
		utils::FillRect(GetBulletRect());
}

void Bullet::Update(float elapsedSec, Enemy** pEnemies, int numEnemies)
{
	if (m_IsActivated)
	{
		m_Center.x += m_Velocity.x * elapsedSec;
		m_Center.y += m_Velocity.y * elapsedSec;
		for (int i{ 0 }; i < numEnemies; ++i)
		{
			if (pEnemies[i] && pEnemies[i]->DoHitTest(GetBulletRect()))
			{
				delete pEnemies[i];
				pEnemies[i] = nullptr;
				m_IsActivated = false;
				return;
			}
		}
	}
}

void Bullet::Shoot(const Point2f& center, const Vector2f& velocity)
{
	m_Center = center;
	m_Velocity = velocity;
	m_IsActivated = true;
}

void Bullet::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Bullet::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
}

void Bullet::CheckBoundaries()
{
	if (m_Boundaries.bottom + m_Boundaries.height < m_Center.y)
		m_IsActivated = false;
}

Rectf Bullet::GetBulletRect() const
{
	float left{ m_Center.x - (m_Width / 2) };
	float bottom{ m_Center.y - (m_Height / 2) };
	return Rectf(left, bottom, m_Width, m_Height);
}
