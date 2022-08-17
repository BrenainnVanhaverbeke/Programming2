#include "pch.h"
#include "PlayerMovement.h"
#include "Character.h"

PlayerMovement::PlayerMovement(const Vector2f& acceleration)
	: MovementBehaviour(acceleration)
	, m_HorizontalSpeed{ 75.0f }
	, m_JumpForce{ 325.0f }
{
}

void PlayerMovement::Update(float elapsedSec, Character& character, const Rectf& boundaries)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	UpdateVelocity(elapsedSec, pKeysState);
	Move(elapsedSec, character.GetTransform());
	Clamp(character.GetTransform(), boundaries, character.GetShape().width);
}

void PlayerMovement::Jump()
{
	m_Velocity.y += m_JumpForce;
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