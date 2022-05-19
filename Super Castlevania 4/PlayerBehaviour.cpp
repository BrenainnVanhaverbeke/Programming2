#include "pch.h"
#include "PlayerBehaviour.h"
#include "ActionState.h"
#include "LevelManager.h"
#include "utils.h"
#include "Character.h"

PlayerBehaviour::PlayerBehaviour(LevelManager* pLevelManager)
	: MovementBehaviour(Vector2f{ 0, utils::g_Gravity })
	, m_ActionState{ ActionState::idle }
	, m_pLevelManager{ pLevelManager }
	, m_IsFlipped{ false }
	, m_IsStill{ false }
	, m_IsAttacking{ false }
	, m_HorizontalSpeed{ 75.0f }
	, m_JumpForce{ 325.0f }
	, m_AttackTime{ 0 }
{
}

bool PlayerBehaviour::IsStill() const
{
	return m_IsStill;
}

bool PlayerBehaviour::IsFlipped() const
{
	return m_IsFlipped;
}

bool PlayerBehaviour::IsAttacking() const
{
	return m_IsAttacking;
}

void PlayerBehaviour::Update(float elapsedSec, Character& character)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	UpdateState(pKeysState);
	UpdateVelocity(elapsedSec, pKeysState);
	Move(elapsedSec, character);
	m_pLevelManager->HandleCollisions(character);
	m_pLevelManager->CheckOverlap(character.GetShape());
	character.GetTransform().GetTranslation().Log();
}

ActionState PlayerBehaviour::GetActionState()
{
	return m_ActionState;
}

int PlayerBehaviour::GetActionStateInt()
{
	return (int)m_ActionState;
}

void PlayerBehaviour::Jump(Character& character)
{
	if (!m_IsAttacking && m_pLevelManager->IsOnGround(character))
		m_Velocity.y += m_JumpForce;
}

void PlayerBehaviour::Attack()
{
	m_IsAttacking = true;
}

void PlayerBehaviour::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
	UpdateHorizontalVelocity(elapsedSec, pKeysState);
	UpdateVerticalVelocity(elapsedSec, pKeysState);
}

void PlayerBehaviour::Move(float elapsedSec, Character& character)
{
	Transform& transform{ character.GetTransform()};
	transform.positionX += m_Velocity.x * elapsedSec;
	transform.positionY += m_Velocity.y * elapsedSec;
	Clamp(transform, character);
}

void PlayerBehaviour::UpdateState(const Uint8* pKeysState)
{
	m_IsStill = (m_Velocity.x == 0) ? true : false;
	bool isCrouching{ pKeysState[SDL_SCANCODE_DOWN] || pKeysState[SDL_SCANCODE_S] };
	m_ActionState = ActionState::idle;
	if (m_Velocity.x != 0)
		m_ActionState = ActionState::walking;
	if (isCrouching)
		m_ActionState = ActionState::ducking;
	if (isCrouching && !m_IsStill)
		m_ActionState = ActionState::crouching;
	if (m_pLevelManager->IsOnStairs())
		m_ActionState = m_pLevelManager->IsUpstairs(m_Velocity) ? ActionState::upstairs : ActionState::downstairs;
	if (!m_IsStill && !m_IsAttacking)
	{
		if (m_Velocity.x < -1.0f)
			m_IsFlipped = true;
		else if (1.0f < m_Velocity.x)
			m_IsFlipped = false;
	}
	if (m_Velocity.y != 0)
	{
		m_ActionState = ActionState::jumping;
		m_IsStill = true;
	}
}

void PlayerBehaviour::UpdateAttack(float elapsedSec, Character& character)
{
	const float bottomOffset{ (m_ActionState == ActionState::crouching || m_ActionState == ActionState::ducking) ? 16.0f : 32.0f };
	const float maxAttackTime{ 0.5f };
	const Transform& transform{ character.GetTransform() };
	m_Weapon.left = transform.positionX + (m_IsFlipped ? (-m_Weapon.width) : character.GetShape().width);
	m_Weapon.bottom = transform.positionY + bottomOffset;
	if (m_IsAttacking && maxAttackTime < (m_AttackTime += elapsedSec))
	{
		m_AttackTime = 0;
		m_IsAttacking = false;
	}
}

void PlayerBehaviour::UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity.x = 0;
	float speedModifier{ (m_ActionState == ActionState::crouching) ? 2.0f : 1.0f };
	if (!m_IsAttacking || m_ActionState == ActionState::jumping)
	{
		if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
			m_Velocity.x -= m_HorizontalSpeed / speedModifier;
		if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
			m_Velocity.x += m_HorizontalSpeed / speedModifier;
	}
}

void PlayerBehaviour::UpdateVerticalVelocity(float elapsedSec, const Uint8* pKeysState)
{
	m_Velocity.y += m_Acceleration.y * elapsedSec;
}

void PlayerBehaviour::Clamp(Transform& transform, Character& character)
{
	const Rectf& boundaries{ m_pLevelManager->GetBoundaries() };
	const float width{ character.GetShape().width };
	if (transform.positionX < boundaries.left)
		transform.positionX = boundaries.left;
	if (boundaries.left + boundaries.width < transform.positionX + width)
		transform.positionX = boundaries.left + boundaries.width - width;
}