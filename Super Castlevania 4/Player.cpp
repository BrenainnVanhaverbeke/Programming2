#include "pch.h"
#include "Player.h"
#include "LevelManager.h"
#include "utils.h"

#include <iostream>

Player::Player(LevelManager* pLevelManager)
	: Character(24.0f, 46.0f)
	, m_HorizontalSpeed{ 200.0f }
	, m_JumpForce{ 325.0f }
	, m_Acceleration{ 0.0f, -981.0f }
	, m_Velocity{}
	, m_ActionState{ ActionState::idle }
	, m_pLevelManager{ pLevelManager }
{
	Point2f spawnPoint{ pLevelManager->GetSpawn() };
	m_Transform.SetTranslation(spawnPoint);
}

Player::~Player()
{
}

void Player::Update(float elapsedSec)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	UpdateState(pKeysState);
	UpdateVelocity(elapsedSec, pKeysState);
	MoveAvatar(elapsedSec);
	m_pLevelManager->CheckOverlap(GetShape());
}

void Player::CheckOverlap(const Rectf& overlappingShape)
{
}

void Player::Draw() const
{
	//glPushMatrix();
	//{
	//	glTranslatef(m_Shape.left - (m_Shape.width / 2), m_Shape.bottom, 0);
	//	if (m_Velocity.x < 0)
	//	{
	//		glScalef(-1, 1, 1);
	//		glTranslatef(-(m_Shape.width * 2), 0, 0);
	//	}
	//	//m_pSpritesTexture->Draw(Point2f{ 0.0f, 0.0f }, GetSourceRect());
	//}
	//glPopMatrix();
	utils::DrawRect(GetShape());
}

Rectf Player::GetShape() const
{
	Rectf shape{ Character::GetShape() };
	shape.height = (m_ActionState == ActionState::crouch) ? m_Height / 1.5f : m_Height;
	return shape;
}

void Player::Relocate(const Point2f& newLocation)
{
	m_Transform.SetTranslation(newLocation);
}

void Player::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
	UpdateHorizontalVelocity(elapsedSec, pKeysState);
	UpdateVerticalVelocity(elapsedSec, pKeysState);
}

void Player::UpdateAnimation(float elapsedSec)
{
}

void Player::UpdateState(const Uint8* pKeysState)
{
	m_ActionState = (pKeysState[SDL_SCANCODE_DOWN] || pKeysState[SDL_SCANCODE_S]) ? ActionState::crouch : ActionState::idle;
	m_ActionState = (m_pLevelManager->IsOnStairs()) ? ActionState::stairs : m_ActionState;
	if (pKeysState[SDL_SCANCODE_UP] || pKeysState[SDL_SCANCODE_W])
		m_pLevelManager->AttemptInteraction(GetShape());
}

void Player::UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity.x = 0;
	float speedModifier{ (m_ActionState == ActionState::crouch) ? 2.0f : 1.0f };
	if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
		m_Velocity.x -= m_HorizontalSpeed / speedModifier;
	if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
		m_Velocity.x += m_HorizontalSpeed / speedModifier;
}

void Player::UpdateVerticalVelocity(float elapsedsec, const Uint8* pKeysState)
{
	Rectf shape{ GetShape() };
	m_pLevelManager->HandleCollisions(shape, m_Transform, m_Velocity);
	if (pKeysState[SDL_SCANCODE_SPACE] && m_pLevelManager->IsOnGround(shape, m_Velocity))
		m_Velocity.y += m_JumpForce;
}

void Player::MoveAvatar(float elapsedSec)
{
	m_Velocity.y += m_Acceleration.y * elapsedSec;
	m_Transform.positionX += m_Velocity.x * elapsedSec;
	m_Transform.positionY += m_Velocity.y * elapsedSec;
	Clamp();
}

void Player::Clamp()
{
	const Rectf& boundaries{ m_pLevelManager->GetBoundaries() };
	if (m_Transform.positionX < boundaries.left)
		m_Transform.positionX = boundaries.left;
	if (boundaries.left + boundaries.width < m_Transform.positionX + m_Width)
		m_Transform.positionX = boundaries.left + boundaries.width - m_Width;
}