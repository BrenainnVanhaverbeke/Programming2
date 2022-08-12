#include "pch.h"
#include "Player.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "ProjectileTag.h"
#include "PlayerMovement.h"
#include "utils.h"
#include <iostream>

Player::Player( LevelManager* pLevelManager)
	: Character(Transform{}, new Sprite("Player_Movement.png", Rectf(0, 0, 32.0f, 48.0f), 6, 7, 6), 28, 46.0f, Vector2f{ 0, utils::g_Gravity })
	, m_HorizontalSpeed{ 75.0f }
	, m_JumpForce{ 325.0f }
	, m_ActionState{ ActionState::idle }
	, m_pLevelManager{ pLevelManager }
	, m_IsDrawDebug{ false }
	, m_IsStill{ true }
	, m_IsDucked{ false }
	, m_IsFlipped{ false }
	, m_Weapon{ 0, 0, 50.0f, 4.0f }
	, m_IsAttacking{ false }
	, m_AttackTime{ 0.0f }
	, m_ProjectileTag{ ProjectileTag::axe }
{
	Point2f spawnPoint{ pLevelManager->GetSpawn() };
	spawnPoint.x -= m_Width / 2;
	spawnPoint.y += 1.0f;
	m_Transform.SetTranslation(spawnPoint);
	m_pMovementBehaviour = new PlayerMovement(Vector2f{ 0, utils::g_Gravity });
}

Player::~Player()
{
	delete m_pMovementBehaviour;
	m_pMovementBehaviour = nullptr;
}

void Player::Update(float elapsedSec)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	UpdateState(pKeysState);
	m_pMovementBehaviour->Update(elapsedSec, *this, m_pLevelManager->GetBoundaries());
	if (m_IsAttacking)
		UpdateAttack(elapsedSec);
	CheckDeath();
	m_pSprite->Update(elapsedSec, (int)m_ActionState, m_IsStill);
	m_pLevelManager->HandleCollisions(*this);
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
	m_pSprite->Draw(m_Transform, m_IsFlipped);
	if (m_IsDrawDebug)
		DrawDebug();
}

Rectf Player::GetShape() const
{
	Rectf shape{ Character::GetShape() };
	shape.height = (m_ActionState == ActionState::crouching
		|| m_ActionState == ActionState::ducking) ? m_Height / 1.5f : m_Height;
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
	if (!m_IsAttacking && m_pLevelManager->IsOnGround(*this))
		m_Velocity.y += m_JumpForce;
}

void Player::Attack()
{
	m_IsAttacking = true;
}

ProjectileTag Player::Shoot()
{
	m_ActionState = ActionState::subweapon;
	return m_ProjectileTag;
}

bool Player::IsFlipped() const
{
	return m_IsFlipped;
}

void Player::DrawDebug() const
{
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

	// Transform: Location
	utils::SetColor(Color4f{ 1.0f, 1.0f, 1.0f, 1.0f });
	utils::DrawPoint(m_Transform.GetTranslation());

	// Weapon
	if (m_IsAttacking)
	{
		utils::SetColor(Color4f{ 1.0f, 0, 0, 1.0f });
		utils::DrawRect(m_Weapon);
	}
}

void Player::CheckDeath()
{
	if (m_Transform.positionY < -m_Height)
	{
		m_pLevelManager->ReloadCheckpoint();
		Relocate(m_pLevelManager->GetSpawn());
	}
}

void Player::UpdateAttack(float elapsedSec)
{
	const float bottomOffset{ (m_ActionState == ActionState::crouching || m_ActionState == ActionState::ducking) ? 16.0f : 32.0f };
	const float maxAttackTime{ 0.5f };
	m_Weapon.left = m_Transform.positionX + (m_IsFlipped ? (-m_Weapon.width) : m_Width);
	m_Weapon.bottom = m_Transform.positionY + bottomOffset;
	if (m_IsAttacking && maxAttackTime < (m_AttackTime += elapsedSec))
	{
		m_AttackTime = 0;
		m_IsAttacking = false;
	}
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

std::string Player::GetActionStateString() const
{
	switch (m_ActionState)
	{
	case Player::ActionState::idle:
		return "Idle.\n";
	case Player::ActionState::walking:
		return "Walking.\n";
	case Player::ActionState::ducking:
		return "Ducking.\n";
	case Player::ActionState::crouching:
		return "Crouching.\n";
	case Player::ActionState::upstairs:
		return "Upstairs.\n";
	case Player::ActionState::downstairs:
		return "Downstairs.\n";
	case Player::ActionState::jumping:
		return "Jumping.\n";
	case Player::ActionState::subweapon:
		return "Subweapon.\n";
	case Player::ActionState::hurt:
		return "Hurt.\n";
	case Player::ActionState::death:
		return "Death.\n";
	default:
		return "\n";
	}
}

void Player::ToggleDrawDebug()
{
	m_IsDrawDebug = !m_IsDrawDebug;
}

void Player::UpdateState(const Uint8* pKeysState)
{
	const Vector2f& velocity{ m_pMovementBehaviour->GetVelocity() };
	m_IsStill = (velocity.x == 0) ? true : false;
	bool isCrouching{ pKeysState[SDL_SCANCODE_DOWN] || pKeysState[SDL_SCANCODE_S] };
	m_ActionState = ActionState::idle;
	if (velocity.x != 0)
		m_ActionState = ActionState::walking;
	if (isCrouching)
		m_ActionState = ActionState::ducking;
	if (isCrouching && !m_IsStill)
		m_ActionState = ActionState::crouching;
	if (m_pLevelManager->IsOnStairs())
		m_ActionState = m_pLevelManager->IsUpstairs(velocity) ? ActionState::upstairs : ActionState::downstairs;
	if (!m_IsStill && !m_IsAttacking)
	{
		if (velocity.x < -1.0f)
			m_IsFlipped = true;
		else if (1.0f < velocity.x)
			m_IsFlipped = false;
	}
	if (velocity.y != 0)
	{
		m_ActionState = ActionState::jumping;
		m_IsStill = true;
	}
}