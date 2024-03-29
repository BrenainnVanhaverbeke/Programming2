#include "pch.h"
#include "PlayerMovement.h"

PlayerMovement::PlayerMovement(const Vector2f& acceleration)
	: MovementBehaviour(acceleration)
	, m_HorizontalSpeed{ 75.0f }
	, m_JumpForce{ 325.0f }
{
}

void PlayerMovement::Update(float elapsedSec, Transform& transform, const Rectf& shape, const Rectf& boundaries, const Vector2f& forcedMovement)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	if (m_LockMovement && forcedMovement.x != 0)
		m_Velocity.x = forcedMovement.x;
	else
		m_LockMovement = false;
	UpdateVelocity(elapsedSec, pKeysState);
	Move(elapsedSec, transform);
	Clamp(transform, boundaries, shape.width);
}

void PlayerMovement::Jump()
{
	m_Velocity.y += m_JumpForce;
}

void PlayerMovement::Knockback(float force)
{
	m_LockMovement = true;
	m_Velocity.y += force;
}

void PlayerMovement::UpdateVelocity(float elapsedSec, const Uint8* pKeysState)
{
	UpdateHorizontalVelocity(elapsedSec, pKeysState, m_Velocity);
	UpdateVerticalVelocity(elapsedSec, pKeysState, m_Velocity);
}

void PlayerMovement::Move(float elapsedSec, Transform& transform)
{
	transform.positionX += m_Velocity.x * elapsedSec;
	transform.positionY += m_Velocity.y * elapsedSec;
}

void PlayerMovement::Clamp(Transform& m_Transform, const Rectf& boundaries, float characterWidth)
{
	if (m_Transform.positionX < boundaries.left)
		m_Transform.positionX = boundaries.left;
	if (boundaries.left + boundaries.width < m_Transform.positionX + characterWidth)
		m_Transform.positionX = boundaries.left + boundaries.width - characterWidth;
}

void PlayerMovement::UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity)
{
	if (!m_LockMovement)
		velocity.x = 0;
	if (pKeysState[SDL_SCANCODE_LEFT] || pKeysState[SDL_SCANCODE_A])
		velocity.x -= m_HorizontalSpeed;
	if (pKeysState[SDL_SCANCODE_RIGHT] || pKeysState[SDL_SCANCODE_D])
		velocity.x += m_HorizontalSpeed;
}

void PlayerMovement::UpdateVerticalVelocity(float elapsedSec, const Uint8* pKeysState, Vector2f& velocity)
{
	velocity.y += m_Acceleration.y * elapsedSec;
}