#include "pch.h"
#include "Player.h"
#include "Sprite.h"
#include "LevelManager.h"
#include "ProjectileTag.h"
#include "PlayerMovement.h"
#include "utils.h"
#include "Matrix2x3.h"
#include <iostream>

Player::Player(LevelManager* pLevelManager)
	: Character(Transform{}
		, GetSprite()
		, new PlayerMovement(Vector2f{ 0, G_GRAVITY })
		, 28.0f
		, 46.0f
		, 0
		, 100
		, 0
	)
	, m_pAttackSprite{ GetAttackSprite() }
	, m_ActionState{ ActionState::idle }
	, m_AttackDirection{ AttackDirection::right }
	, m_pLevelManager{ pLevelManager }
	, m_IsDrawDebug{ false }
	, m_IsStill{ true }
	, m_IsDucked{ false }
	, m_IsFlipped{ false }
	, m_WeaponBaseShape{ 0, 0, 50.0f, 4.0f }
	, m_IsAttacking{ false }
	, m_AttackTime{ 0.0f }
	, m_ProjectileTag{ ProjectileTag::axe }
{
	Point2f spawnPoint{ pLevelManager->GetSpawn() };
	spawnPoint.x -= m_Width / 2;
	spawnPoint.y += 1.0f;
	m_Transform.SetTranslation(spawnPoint);

}

Player::~Player()
{
	delete m_pMovementBehaviour;
	delete m_pAttackSprite;
	m_pMovementBehaviour = nullptr;
	m_pAttackSprite = nullptr;
}

void Player::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
	{
		if (m_IsAttacking)
			m_pAttackSprite->Draw(m_AttackTransform, m_IsFlipped);
		else
			m_pSprite->Draw(m_Transform, m_IsFlipped);
	}
}

void Player::Update(float elapsedSec)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	const float thrownWeaponCooldown{ 3.0f };
	UpdateState(pKeysState);
	if (m_IsAttacking)
	{
		int rowOffset{ ((int)m_ActionState) * 3 + (int)m_AttackDirection };
		m_pAttackSprite->Update(elapsedSec, rowOffset);
		UpdateAttack(elapsedSec);
		// Horrid magic numbers of death. My deepest apologies to whomever has found this.
		const float xCentering{ 54.0f };
		const float yCentering{ 30.0f };
		m_AttackTransform = m_Transform;
		m_AttackTransform.positionX -= xCentering;
		if (m_AttackDirection == AttackDirection::down)
			m_AttackTransform.positionY -= yCentering;
	}
	if (!m_IsAttacking || m_IsAttacking && m_pMovementBehaviour->GetVelocity().y != 0)
		m_pMovementBehaviour->Update(elapsedSec, m_Transform, GetShape(), m_pLevelManager->GetBoundaries());
	if (!m_CanThrow)
	{
		m_AccumulatedTime += elapsedSec;
		if (thrownWeaponCooldown < m_AccumulatedTime)
		{
			m_AccumulatedTime = 0;
			m_CanThrow = true;
		}
	}
	CheckDeath();
	m_pSprite->Update(elapsedSec, (int)m_ActionState, m_IsStill);
	m_pLevelManager->HandleCollisions(*this);
	m_pLevelManager->CheckOverlap(GetShape(), m_ZIndex);
}

void Player::CheckOverlap(const Rectf& overlappingShape)
{
}

Rectf Player::GetShape() const
{
	Rectf shape{ Character::GetShape() };
	shape.height = (m_ActionState == ActionState::crouching
		|| m_ActionState == ActionState::ducking) ? m_Height / 1.5f : m_Height;
	return shape;
}

// Again, my deepest apologies for magic number hell;
std::vector<Point2f> Player::GetWeaponShape() const
{
	const float bottomOffset{ 10.0f };
	const float leftOffset{ 15.0f };
	Rectf weaponShapeRect{ m_WeaponBaseShape };
	float rotationAngle{};
	if (m_AttackDirection == AttackDirection::upRight)
	{
		weaponShapeRect.bottom += bottomOffset;
		weaponShapeRect.left += leftOffset;
		rotationAngle = 45.0f;
	}
	if (m_AttackDirection == AttackDirection::downRight)
		rotationAngle = -45.0f;
	if (m_AttackDirection == AttackDirection::up
		|| m_AttackDirection == AttackDirection::down)
	{
		weaponShapeRect.SetBottomLeft(GetShape().GetTopCenter());
		weaponShapeRect.width = m_WeaponBaseShape.height;
		weaponShapeRect.height = m_WeaponBaseShape.width;
		if (m_IsFlipped)
			weaponShapeRect.left -= weaponShapeRect.width;
		if (m_AttackDirection == AttackDirection::down)
			weaponShapeRect.bottom = GetShape().bottom - weaponShapeRect.height;
	}
	std::vector<Point2f> weaponShape{ weaponShapeRect.ConvertToVector() };
	if (rotationAngle != 0)
		return RotateWeaponShape(weaponShape, rotationAngle);
	return weaponShape;
}

int Player::GetWeaponDamage() const
{
	return m_WeaponDamage;
}

void Player::Relocate(Point2f newLocation)
{
	newLocation.x -= m_Width / 2;
	m_Transform.SetTranslation(newLocation);
	m_ZIndex = 0;
}

void Player::AttemptInteraction()
{
	m_pLevelManager->AttemptInteraction(GetShape(), m_ZIndex);
}

void Player::Jump()
{
	if (!m_IsAttacking && m_pLevelManager->IsOnGround(*this))
		m_pMovementBehaviour->Jump();
}

void Player::Attack()
{
	if (!m_IsAttacking)
	{
		m_IsAttacking = true;
		UpdateAttackDirection();
	}
}

ProjectileTag Player::Shoot()
{
	if (m_CanThrow)
	{
		m_ActionState = ActionState::subweapon;
		return m_ProjectileTag;
	}
	return ProjectileTag::none;
}

void Player::CycleProjectileType()
{
	m_ProjectileTag = ProjectileTag(((int)m_ProjectileTag + 1) % (int)ProjectileTag::END);
	if (m_ProjectileTag == ProjectileTag::none)
		m_ProjectileTag = ProjectileTag::cross;
}

bool Player::IsFlipped() const
{
	return m_IsFlipped;
}

bool Player::IsAttacking() const
{
	return m_IsAttacking;
}

void Player::DrawDebug(int zIndex) const
{
	if (m_ZIndex == zIndex)
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
			utils::DrawPolygon(GetWeaponShape());
		}
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

void Player::UpdateAttackDirection()
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	UpdateGeneralAttackDirection(pKeysState);
	if (m_ActionState == ActionState::jumping)
		UpdateJumpingAttackDirection(pKeysState);
	if (m_ActionState == ActionState::crouching || m_ActionState == ActionState::ducking)
		m_AttackDirection = AttackDirection::right;
}

void Player::UpdateGeneralAttackDirection(const Uint8* pKeysState)
{
	m_AttackDirection = AttackDirection::right;
	if (pKeysState[SDL_SCANCODE_W])
		m_AttackDirection = AttackDirection::up;
	if ((m_AttackDirection == AttackDirection::up
		&& (pKeysState[SDL_SCANCODE_D] || pKeysState[SDL_SCANCODE_A]))
		|| (m_AttackDirection == AttackDirection::up && m_ActionState == ActionState::downstairs))
		m_AttackDirection = AttackDirection::upRight;
}

void Player::UpdateJumpingAttackDirection(const Uint8* pKeysState)
{
	if (pKeysState[SDL_SCANCODE_S])
		m_AttackDirection = AttackDirection::down;
	if (m_AttackDirection == AttackDirection::down && (pKeysState[SDL_SCANCODE_D] || pKeysState[SDL_SCANCODE_A]))
		m_AttackDirection = AttackDirection::downRight;
}

void Player::UpdateAttack(float elapsedSec)
{
	const float bottomOffset{ (m_ActionState == ActionState::crouching || m_ActionState == ActionState::ducking) ? 16.0f : 32.0f };
	const float maxAttackTime{ 0.5f };
	m_WeaponBaseShape.left = m_Transform.positionX + (m_IsFlipped ? (-m_WeaponBaseShape.width) : m_Width);
	m_WeaponBaseShape.bottom = m_Transform.positionY + bottomOffset;
	if (m_IsAttacking && maxAttackTime < (m_AttackTime += elapsedSec))
	{
		m_AttackTime = 0;
		m_IsAttacking = false;
		m_pAttackSprite->Reset();
	}
}

std::vector<Point2f> Player::RotateWeaponShape(std::vector<Point2f>& weaponShape, float rotationAngle) const
{
	Matrix2x3 originMatrix{}, rotationMatrix{}, resetMatrix{};
	resetMatrix.SetAsTranslate(m_WeaponBaseShape.left, m_WeaponBaseShape.bottom);
	originMatrix.SetAsTranslate(-m_WeaponBaseShape.left, -m_WeaponBaseShape.bottom);
	rotationMatrix.SetAsRotate(rotationAngle);
	Matrix2x3 transformationMatrix{ resetMatrix * rotationMatrix * originMatrix };
	if (m_IsFlipped)
	{
		Matrix2x3 scaleMatrix{};
		scaleMatrix.SetAsScale(-1, 1);
		resetMatrix.SetAsTranslate(m_WeaponBaseShape.left + m_Width * 2, m_WeaponBaseShape.bottom);
		transformationMatrix = resetMatrix * scaleMatrix * rotationMatrix * originMatrix;
	}
	return transformationMatrix.Transform(weaponShape);
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

std::string Player::GetAttackDirectionString() const
{
	switch (m_AttackDirection)
	{
	case Player::AttackDirection::up:
		return "Up.";
	case Player::AttackDirection::upRight:
		return "Up right.";
	case Player::AttackDirection::right:
		return "Right.";
	case Player::AttackDirection::down:
		return "Down.";
	case Player::AttackDirection::downRight:
		return "Down right.";
	}
	return "None.";
}

Sprite* Player::GetAttackSprite() const
{
	std::string path{ "Player_Attack.png" };
	Point2f sourceRectOrigin{ 0, 0 };
	float sourceWidth{ 140 };
	float sourceHeight{ 112 };
	Rectf sourceRect{ sourceRectOrigin, sourceWidth, sourceHeight };
	int frames{ 3 };
	int rows{ 1 };
	int framesPerSecond{ 7 };
	return new Sprite(path, sourceRect, frames, rows, framesPerSecond);
}

Sprite* Player::GetSprite() const
{
	std::string path{ "Player_Movement.png" };
	Point2f sourceRectOrigin{ 0, 0 };
	float sourceWidth{ 32 };
	float sourceHeight{ 48 };
	Rectf sourceRect{ sourceRectOrigin, sourceWidth, sourceHeight };
	int frames{ 6 };
	int rows{ 7 };
	int framesPerSecond{ 8 };
	return new Sprite(path, sourceRect, frames, rows, framesPerSecond);
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
		m_ActionState = m_pLevelManager->IsMovingUpstairs(m_IsFlipped) ? ActionState::upstairs : ActionState::downstairs;
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