#pragma once
#include "Vector2f.h"

class Avatar
{
	enum class ActionState
	{
		waiting,
		moving,
		transforming,
		END
	};

private:
	const Rectf m_Shape{ 50, 280, 36, 97 };
	const float m_HorizontalSpeed{ 200.0f };
	const float m_JumpSpeed{ 600.0f };
	Vector2f m_Velocity{ 0.0f, 0.0f };
	const Vector2f m_Acceleration{ 0.0f, -981.0f };
	ActionState m_ActionState{ ActionState::moving };
	float m_AccuTransformSec{ 0.0f };
	const float m_MaxTransformSec{ 1.0f };
	int m_Power{ 0 };
};

