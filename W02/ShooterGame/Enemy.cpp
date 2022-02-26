#include "pch.h"
#include "Enemy.h"
#include "utils.h"

Enemy::Enemy()
	:Enemy{ Point2f{0.0f, 0.0f}, 0.0f, 0.0f }
{
}

Enemy::Enemy(const Point2f& center, float width, float height)
	: m_Center{ center }, m_Width{ width }, m_Height{ height }, m_IsDead{ false }
{
}

void Enemy::Draw()
{
	const Color4f enemyColour{ 1.0f, 0.0f, 0.0f, 0.0f };
	utils::SetColor(enemyColour);
	utils::DrawRect(GetEnemyRect());
}

bool Enemy::DoHitTest(const Rectf& other)
{
	return utils::IsOverlapping(GetEnemyRect(), other);
}

void Enemy::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Enemy::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

bool Enemy::IsDead()
{
	return m_IsDead;
}

Rectf Enemy::GetEnemyRect()
{
	return Rectf(m_Center.x - (m_Width / 2), m_Center.y - (m_Height / 2), m_Width, m_Height);
}
