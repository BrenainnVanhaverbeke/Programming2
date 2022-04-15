#include "pch.h"
#include "Player.h"
#include "LevelManager.h"
#include "utils.h"
#include "Sprite.h"

#include <iostream>

Player::Player(LevelManager* pLevelManager)
	: Character(32.0f, 48.0f)
	, m_HorizontalSpeed{ 75.0f }
	//, m_HorizontalSpeed{ 200.0f }
	, m_JumpForce{ 325.0f }
	, m_Acceleration{ 0.0f, -981.0f }
	//, m_Acceleration{ 0.0f, -100.0f }
	, m_Velocity{}
	, m_ActionState{ ActionState::idle }
	, m_pLevelManager{ pLevelManager }
	, m_pSprite{ new Sprite("Player_Movement.png", GetShape()) }
{
	Point2f spawnPoint{ pLevelManager->GetSpawn() };
	spawnPoint.x -= m_Width / 2;
	spawnPoint.y += 1.0f;
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
	MovePlayer(elapsedSec);
	m_pLevelManager->HandleCollisions(GetShape(), m_Transform, m_Velocity);
	m_pLevelManager->CheckOverlap(GetShape());
}

void Player::CheckOverlap(const Rectf& overlappingShape)
{
}

bool Player::IsOverlapping(const Rectf& overlappingShape)
{
	return utils::IsOverlapping(GetShape(), overlappingShape);
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
	m_pSprite->Draw(m_Transform.GetTranslation());
	float m_AnchorOffset{ 5.0f };
	Rectf actorShape{ GetShape() };
	Point2f topCenter{ actorShape.GetTopCenter(0, -m_AnchorOffset) };
	Point2f center{ actorShape.GetCenter() };
	Point2f bottomCenter{ actorShape.GetBottomCenter(0, m_AnchorOffset) };
	Point2f topCenterMiddle{ utils::GetMiddle(topCenter, center) };
	Point2f bottomCenterMiddle{ utils::GetMiddle(center, bottomCenter) };
	Point2f centerLeft{ actorShape.GetCenterLeft(m_AnchorOffset / 2) };
	Point2f centerRight{ actorShape.GetCenterRight(-m_AnchorOffset / 2) };
	// Shape
	utils::SetColor(Color4f{ 1.0f, 0, 1.0f, 1.0f });
	utils::DrawRect(actorShape);
	// Stairs anchor
	utils::SetColor(Color4f{ 1.0f, 1.0f, 0, 1.0f });
	utils::DrawPoint(actorShape.GetBottomCenter());
	// Horizontal 'cast anchors
	utils::SetColor(Color4f{ 1.0f, 0, 0, 1.0f });
	utils::DrawPoint(topCenter);
	utils::DrawPoint(center);
	utils::DrawPoint(bottomCenter);
	utils::DrawPoint(topCenterMiddle);
	utils::DrawPoint(bottomCenterMiddle);
	// Vertical 'cast anchors
	utils::SetColor(Color4f{ 0, 1.0f, 0, 1.0f });
	utils::DrawPoint(centerLeft);
	utils::DrawPoint(centerRight);
}

Rectf Player::GetShape() const
{
	Rectf shape{ Character::GetShape() };
	shape.height = (m_ActionState == ActionState::crouch) ? m_Height / 1.5f : m_Height;
	return shape;
}

void Player::Relocate(Point2f newLocation)
{
	newLocation.x -= m_Width / 2;
	m_Transform.SetTranslation(newLocation);
}

void Player::AttemptInteraction()
{
 	m_pLevelManager->AttemptInteraction(GetShape());
}

void Player::Jump()
{
	if (m_pLevelManager->IsOnGround(GetShape(), m_Velocity))
		m_Velocity.y += m_JumpForce;
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

void Player::UpdateVerticalVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity.y += m_Acceleration.y * elapsedSec;
}

void Player::MovePlayer(float elapsedSec)
{
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