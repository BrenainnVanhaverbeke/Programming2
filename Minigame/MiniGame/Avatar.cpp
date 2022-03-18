#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include <iostream>

Avatar::Avatar()
	: m_HorizontalSpeed{ 200.0f }
	, m_JumpSpeed{ 600.0f }
	, m_MaxTransformSec{ 1.0f }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_Shape{ 50.0f, 280.0f, 36.0f, 97.0f }
	, m_Velocity{}
	, m_ActionState{ ActionState::moving }
	, m_AccuTransformSec{ 0.0f }
	, m_Power{ 0 }
{
}

void Avatar::Update(float elapsedSec, const Level* level)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	if (m_ActionState != ActionState::transforming)
	{
		m_ActionState = ActionState::waiting;
		UpdateHorizontalVelocity(elapsedSec, pKeysState);
		UpdateVerticalVelocity(elapsedSec, level, pKeysState);
		MoveAvatar(elapsedSec);
	}
	else
		HandleTransformation(elapsedSec);
}

void Avatar::Draw() const
{
	utils::SetColor(GetColour());
	utils::FillRect(m_Shape);
	DrawPowerUpIndicators();
}

void Avatar::PowerUpHit()
{
	m_Power++;
	m_AccuTransformSec = 0;
	m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity.x = 0;
	if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
		m_Velocity.x = -m_HorizontalSpeed;
	if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
		m_Velocity.x = m_HorizontalSpeed;
}

void Avatar::UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState)
{
	level->HandleCollision(m_Shape, m_Velocity);
	if (pKeysState[SDL_SCANCODE_SPACE] && level->IsOnGround(m_Shape))
	{
		m_Velocity.y += m_JumpSpeed;
		m_ActionState = ActionState::moving;
	}
}

void Avatar::MoveAvatar(float elapsedSec)
{
	if (m_Velocity.x != 0 || m_Velocity.y != 0)
		m_ActionState = ActionState::moving;
	m_Velocity.y += m_Acceleration.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
}

void Avatar::HandleTransformation(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	if (m_MaxTransformSec < m_AccuTransformSec)
		m_ActionState = ActionState::waiting;
}

void Avatar::DrawPowerUpIndicators() const
{
	const float indicatorSize{ 5.0f };
	const Color4f indicatorColour{ 0.0f, 0.0f, 0.0f, 1.0f };
	Rectf powerUpIndicator{ m_Shape.left + indicatorSize, m_Shape.bottom + indicatorSize
						  , indicatorSize, indicatorSize };
	for (int i = 0; i < m_Power; i++)
	{
		utils::SetColor(indicatorColour);
		utils::FillRect(powerUpIndicator);
		powerUpIndicator.left += indicatorSize * 2;
	}
}

Color4f Avatar::GetColour() const
{
	switch (m_ActionState)
	{
	case Avatar::ActionState::waiting:
		return Color4f{ 1.0f, 1.0f, 0.0f, 1.0f };
	case Avatar::ActionState::moving:
		return Color4f{ 1.0f, 0.0f, 0.0f, 1.0f };
	case Avatar::ActionState::transforming:
		return Color4f{ 0.0f, 1.0f, 1.0f, 1.0f };
	}
	return Color4f{ 0.0f, 0.0f, 0.0f, 1.0f };
}
