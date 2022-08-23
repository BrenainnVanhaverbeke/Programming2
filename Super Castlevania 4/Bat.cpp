#include "pch.h"
#include "Bat.h"
#include "SinewaveMovement.h"
#include "Sprite.h"
#include "utils.h"
#include <iostream>

Bat::Bat(const Transform& transform, int zIndex, bool isMovingLeft, int id)
	: Character(transform, GetSprite(), new SinewaveMovement(50, 25.0f, 2, transform.positionY, isMovingLeft), 16.0f, 16.0f, zIndex, 20, id)
{
}

Bat::Bat(const Point2f location, int zIndex, bool isMovingLeft, int id)
	: Bat(Transform{ location }, zIndex, isMovingLeft, id)
{
}

void Bat::Update(float elapsedSec)
{
	Rectf boundaries{ 0, 0, 1000, 1000 };
	//m_pMovementBehaviour->Update(elapsedSec, m_Transform, GetShape(), boundaries);
	m_pSprite->Update(elapsedSec);
}

void Bat::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
		m_pSprite->Draw(m_Transform, 0 < m_pMovementBehaviour->GetVelocity().x);
}

void Bat::CheckOverlap(const Rectf& overlappingShape)
{
}

Sprite* Bat::GetSprite() const
{
	std::string path{ "Enemies.png" };
	Point2f sourceRectOrigin{ 233.0f, 2330.0f };
	float sourceWidth{ 16 };
	float sourceHeight{ 16 };
	Rectf sourceRect{ sourceRectOrigin, sourceWidth, sourceHeight };
	int frames{ 4 };
	int rows{ 1 };
	int framesPerSecond{ 4 };
	return new Sprite(path, sourceRect, frames, rows, framesPerSecond);
}