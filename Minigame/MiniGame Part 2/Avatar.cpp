#include "pch.h"
#include "Avatar.h"
#include "Level.h"
#include "Texture.h"

#include <iostream>

Avatar::Avatar()
	: m_HorizontalSpeed{ 200.0f }
	, m_JumpSpeed{ 600.0f }
	, m_MaxTransformSec{ 1.0f }
	, m_ClipHeight{ 97.0f }
	, m_ClipWidth{ 72.0f }
	, m_NrOfFrames{ 10 }
	, m_NrFramesPerSec{ 10 }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_pSpritesTexture{ new Texture("./Resources/Images/AvatarSheet.png") }
	, m_Shape{ 50.0f, 280.0f, 36.0f, 97.0f }
	, m_Velocity{}
	, m_ActionState{ ActionState::moving }
	, m_AccuTransformSec{ 0.0f }
	, m_AnimTime{ 0.0f }
	, m_Power{ 0 }
	, m_AnimFrame{ 0 }
{
	if (!m_pSpritesTexture->IsCreationOk())
		std::cout << "Error loading Avatar spritesheet.\n";
}

void Avatar::Update(float elapsedSec, const Level* level)
{
	UpdateMotion(elapsedSec, level);
	UpdateAnimation(elapsedSec);
}

Avatar::~Avatar()
{
	delete m_pSpritesTexture;
	m_pSpritesTexture = nullptr;
}

void Avatar::Draw() const
{
	glPushMatrix();
	{
		glTranslatef(m_Shape.left - (m_Shape.width / 2), m_Shape.bottom, 0);
		if (m_Velocity.x < 0)
		{
			glScalef(-1, 1, 1);
			glTranslatef(-(m_Shape.width * 2), 0, 0);
		}
		m_pSpritesTexture->Draw(Point2f{ 0.0f, 0.0f }, GetSourceRect());
	}
	glPopMatrix();
}

void Avatar::PowerUpHit()
{
	m_AccuTransformSec = 0;
	m_ActionState = ActionState::transforming;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

void Avatar::UpdateMotion(float elapsedSec, const Level* level)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	if (m_ActionState != ActionState::transforming)
	{
		m_ActionState = ActionState::waiting;
		UpdateHorizontalVelocity(elapsedSec, pKeysState);
		UpdateVerticalVelocity(elapsedSec, level, pKeysState);
		MoveAvatar(elapsedSec, level);
	}
	else
		HandleTransformation(elapsedSec);
}

void Avatar::UpdateAnimation(float elapsedSec)
{
	const float maxFrameTime{ 1.0f / m_NrFramesPerSec };
	m_AnimTime += elapsedSec;
	if (maxFrameTime < m_AnimTime)
	{
		m_AnimFrame = (m_AnimFrame + 1) % m_NrOfFrames;
		m_AnimTime -= maxFrameTime;
	}
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

void Avatar::MoveAvatar(float elapsedSec, const Level* level)
{
	if (m_Velocity.x != 0 || m_Velocity.y != 0)
		m_ActionState = ActionState::moving;
	m_Velocity.y += m_Acceleration.y * elapsedSec;
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y * elapsedSec;
	Clamp(level);
}

void Avatar::Clamp(const Level* level)
{
	const Rectf& boundaries{ level->GetBoundaries() };
	if (m_Shape.left < boundaries.left)
		m_Shape.left = boundaries.left;
	if (boundaries.left + boundaries.width < m_Shape.left + m_Shape.width)
		m_Shape.left = boundaries.left + boundaries.width - m_Shape.width;
}

void Avatar::HandleTransformation(float elapsedSec)
{
	m_AccuTransformSec += elapsedSec;
	if (m_MaxTransformSec < m_AccuTransformSec)
	{
		m_ActionState = ActionState::waiting;
		m_Power++;
	}
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

Rectf Avatar::GetSourceRect() const
{
	return Rectf
	{
	  m_ClipWidth * m_AnimFrame,
	  m_ClipHeight * (1 + ((int)m_ActionState) + (3 * m_Power)),
	  m_ClipWidth,
	  m_ClipHeight
	};
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
