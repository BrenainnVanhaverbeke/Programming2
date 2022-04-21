#include "pch.h"
#include "Pendulum.h"
#include "utils.h"
#include <iostream>

Pendulum::Pendulum(float positionX, float positionY)
	: GameObject(Transform{ positionX, positionY, 90 })
	, m_Radius{ 5.0f }
	, m_AngleVelocity{ 0 }
	, m_AngleAcceleration{ 0 }
	, m_Damping{ 0.995f }
	, m_Gravity{ 9.810f }
	, m_Length{ 50.0f }
{
}

void Pendulum::Update(float elapsedSec)
{
	float& angle{ m_Transform.angle };
	m_AngleAcceleration = ((m_Gravity / m_Length) * sinf(angle));
	UpdateInput(elapsedSec);
	m_AngleVelocity += m_AngleAcceleration * elapsedSec;
	m_AngleVelocity *= m_Damping;
	angle += m_AngleVelocity;
	m_Position.x = m_Length * sinf(angle) + m_Transform.positionX;
	m_Position.y = m_Length * cosf(angle) + m_Transform.positionY;
}

void Pendulum::Draw() const
{
	utils::DrawLine(m_Transform.GetTranslation(), m_Position);
	utils::FillEllipse(m_Position, m_Radius, m_Radius);
}

void Pendulum::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Pendulum::IsOverlapping(const Rectf& overlappingShape)
{
	return false;
}

void Pendulum::UpdateInput(float elapsedSec)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	if (pKeysState[SDL_SCANCODE_LEFT])
		m_AngleAcceleration += 2.5f * elapsedSec;
	if (pKeysState[SDL_SCANCODE_RIGHT])
		m_AngleAcceleration -= 2.5f * elapsedSec;
	if (pKeysState[SDL_SCANCODE_UP] && m_Length < 100.0f)
		m_Length += 100.0f * elapsedSec;
	if (pKeysState[SDL_SCANCODE_DOWN] && 10.0f < m_Length)
		m_Length -= 100.0f * elapsedSec;
}