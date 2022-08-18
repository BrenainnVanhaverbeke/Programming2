#include "pch.h"
#include "Pendulum.h"
#include "utils.h"
#include <iostream>

Pendulum::Pendulum(float positionX, float positionY)
	: GameObject(Transform{ positionX, positionY, 270.0f })
	, m_Radius{ 5.0f }
	, m_AngleVelocity{ 0 }
	, m_AngleAcceleration{ 0 }
	, m_Damping{ 0.993f }
	, m_Gravity{ 9.810f }
	, m_Length{ 50.0f }
	, m_IsReleased{ false }
	, m_ReleaseVector{}
	, m_ReleaseSpeedCompensation{ 150.0f }
{
}

void Pendulum::Update(float elapsedSec)
{
	if (!m_IsReleased)
		UpdateSwing(elapsedSec);
	else
		UpdateRelease(elapsedSec);
}

void Pendulum::Draw(int zIndex) const
{
	if (zIndex == m_ZIndex)
	{
		if (!m_IsReleased)
			utils::DrawLine(m_Transform.GetTranslation(), m_Position);
		utils::FillEllipse(m_Position, m_Radius, m_Radius);
	}
}

Vector2f Pendulum::GetReleaseVector()
{
	const float angleRads{ ToRadians(m_Transform.angle + 90.0f) };
	float horizontalComponent{ m_AngleVelocity * m_ReleaseSpeedCompensation * sinf(angleRads) };
	float verticalComponent{ m_AngleVelocity * m_ReleaseSpeedCompensation * cosf(angleRads) };
	return Vector2f{ horizontalComponent, verticalComponent };
}

void Pendulum::ReleasePendulum()
{
	m_IsReleased = true;
	m_ReleaseVector = GetReleaseVector();
}

void Pendulum::ResetPendulum()
{
	m_IsReleased = false;
	m_Transform.angle = 270.0f;
	m_AngleAcceleration = 0;
	m_AngleVelocity = 0;
}

void Pendulum::ModifyReleaseCompensation(float compensationModifier)
{
	m_ReleaseSpeedCompensation += compensationModifier;
	std::cout << "Release compensation: " << m_ReleaseSpeedCompensation << std::endl;
}

void Pendulum::UpdateSwing(float elapsedSec)
{
	const float frameCompensationScalar{ 40.0f };
	float angleRads{ ToRadians(m_Transform.angle) };
	m_AngleAcceleration = ((m_Gravity / m_Length) * sinf(angleRads));
	UpdateInput(elapsedSec);
	m_AngleVelocity += m_AngleAcceleration * elapsedSec * frameCompensationScalar;
	m_AngleVelocity *= m_Damping;
	angleRads += m_AngleVelocity * elapsedSec;
	m_Position.x = m_Length * sinf(angleRads) + m_Transform.positionX;
	m_Position.y = m_Length * cosf(angleRads) + m_Transform.positionY;
	m_Transform.angle = ToDegrees(angleRads);
}

void Pendulum::UpdateRelease(float elapsedSec)
{
	const Vector2f accelerationVector{ 0, utils::g_Gravity };
	m_ReleaseVector += accelerationVector * elapsedSec;
	m_Position.x += m_ReleaseVector.x * elapsedSec;
	m_Position.y += m_ReleaseVector.y * elapsedSec;
}

void Pendulum::UpdateInput(float elapsedSec)
{
	const float inputForce{ 2.5f };
	const float lengtheningSpeed{ 100.0f };
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	if (pKeysState[SDL_SCANCODE_LEFT])
		m_AngleAcceleration += inputForce * elapsedSec;
	if (pKeysState[SDL_SCANCODE_RIGHT])
		m_AngleAcceleration -= inputForce * elapsedSec;
	if (pKeysState[SDL_SCANCODE_UP] && m_Length < 100.0f)
		m_Length += lengtheningSpeed * elapsedSec;
	if (pKeysState[SDL_SCANCODE_DOWN] && 10.0f < m_Length)
		m_Length -= lengtheningSpeed * elapsedSec;
}

float Pendulum::ToRadians(float degrees)
{
	return degrees * (utils::g_Pi / 180.0f);
}

float Pendulum::ToDegrees(float radians)
{
	return radians * (180 / utils::g_Pi);
}