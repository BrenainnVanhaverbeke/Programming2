#include "pch.h"
#include "TrafficLight.h"
#include "utils.h"

TrafficLight::TrafficLight(const Point2f& position, float width, float height)
	: m_Position{ position }, m_Width{ width }, m_Height{ height }, m_AccumulatedSec{ 0 }, m_State{ State::off }
{
	float fourthOfHeight{ height / 4 };
	float arbitraryFraction{ 5 };
	m_Red = Circlef{ width / 2 + position.x, (fourthOfHeight * 3) + position.y, width / arbitraryFraction };
	m_Orange = Circlef{ width / 2 + position.x, (fourthOfHeight * 2) + position.y, width / arbitraryFraction };
	m_Green = Circlef{ width / 2 + position.x, (fourthOfHeight * 1) + position.y, width / arbitraryFraction };
}

void TrafficLight::DoHitTest(const Point2f& position)
{
	if (utils::IsPointInCircle(position, m_Red))
	{
		m_State = (m_State == State::off) ? State::red : State::off;
		m_AccumulatedSec = 0;
	}
	else if (utils::IsPointInCircle(position, m_Orange))
	{
		m_State = (m_State == State::off) ? State::orange : State::off;
		m_AccumulatedSec = 0;
	}
	else if (utils::IsPointInCircle(position, m_Green))
	{
		m_State = (m_State == State::off) ? State::green : State::off;
		m_AccumulatedSec = 0;
	}
}

void TrafficLight::Update(float elapsedSec)
{
	m_AccumulatedSec += elapsedSec;
	if (m_State == State::red && 4 <= m_AccumulatedSec)
	{
		m_State = State::green;
		m_AccumulatedSec = 0;
	}
	if (m_State == State::orange && 1 <= m_AccumulatedSec)
	{
		m_State = State::red;
		m_AccumulatedSec = 0;
	}
	if (m_State == State::green && 4 <= m_AccumulatedSec)
	{
		m_State = State::orange;
		m_AccumulatedSec = 0;
	}
}

void TrafficLight::Draw()
{
	const Color4f frame{ 0.0f, 0.0f, 0.0f, 1.0f };
	const Color4f red{ 1.0f, 0.0f, 0.0f, 1.0f };
	const Color4f orange{ 1.0f, 0.8f, 0.0f, 1.0f };
	const Color4f green{ 0.0f, 1.0f, 0.0f, 1.0f };
	const Color4f off{ 0.2f, 0.2f, 0.2f, 1.0f };
	utils::SetColor(Color4f{ 0.0f, 0.0f, 0.0f, 1.0f });
	utils::FillRect(m_Position, m_Width, m_Height);
	utils::SetColor((m_State == State::red) ? red : off);
	utils::FillCircle(m_Red);
	utils::SetColor((m_State == State::orange) ? orange : off);
	utils::FillCircle(m_Orange);
	utils::SetColor((m_State == State::green) ? green : off);
	utils::FillCircle(m_Green);
}

float TrafficLight::GetWidth()
{
	return m_Width;
}

float TrafficLight::GetHeight()
{
	return m_Height;
}

