#include "pch.h"
#include "Trapdoor.h"
#include <iostream>
#include "Matrix2x3.h"
#include "Character.h"

TrapDoor::TrapDoor(const std::vector<Point2f>& vertices, bool isBackground)
	: TerrainObject(vertices, GetPivot(vertices), isBackground)
	, m_ActivationDelay{ 0.3f }
	, m_RotationSpeed{ 360.0f }
	, m_MaxAngle{ 180.0f }
	, m_BaseVertices{ vertices }
	, m_State{ TrapDoorState::idle }
	, m_AccumulatedTime{ 0.0f }
{
}

TrapDoor::~TrapDoor()
{
}

void TrapDoor::Draw() const
{
	TerrainObject::Draw();
}

void TrapDoor::Update(float elapsedSec)
{
	if (m_State == TrapDoorState::activated) 
		m_AccumulatedTime += elapsedSec;
	if (m_ActivationDelay < m_AccumulatedTime)
	{
		m_AccumulatedTime = 0;
		m_State = TrapDoorState::rotating;
	}
	if (m_State == TrapDoorState::rotating)
	{
		std::cout << m_Transform.angle << std::endl;
		m_Transform.angle += m_RotationSpeed * elapsedSec;
		RotateVertices(elapsedSec);
	}
	if (m_MaxAngle < m_Transform.angle)
	{
		std::cout << "Resetting.\n";
		m_Transform.angle = 0;
		m_Vertices = m_BaseVertices;
		m_State = TrapDoorState::idle;
	}
}

bool TrapDoor::HandleCollisions(Character& character)
{
	if (m_State == TrapDoorState::rotating) 
		return false;
	const float velocityThreshold{ -30.0f };
	bool isFalling{ character.GetVelocity().y < velocityThreshold};
	bool isColliding{ TerrainObject::HandleCollisions(character) };
	if (isColliding && isFalling)
	{
		std::cout << "Activating.\n";
		m_State = TrapDoorState::activated;
		return true;
	}
	return isColliding;
}

bool TrapDoor::IsOnGround(const Character& character)
{
	if (m_State == TrapDoorState::rotating)
		return false;
	return TerrainObject::IsOnGround(character);
}

Point2f TrapDoor::GetPivot(const std::vector<Point2f>& vertices)
{
	const size_t nrOfVertices{ vertices.size() };
	float left{ vertices.at(0).x }, bottom{ vertices.at(0).y }
		, width{ vertices.at(0).x }, height{ vertices.at(0).y };
	for (size_t i{ 0 }; i < nrOfVertices; ++i)
	{
		const Point2f& vertex{ vertices.at(i) };
		if (vertex.x < left) left = vertex.x;
		if (vertex.y < bottom) bottom = vertex.y;
		if (width < vertex.x) width = vertex.x;
		if (height < vertex.y) height = vertex.y;
	}
	width -= left;
	height -= bottom;
	Rectf shape{ left, bottom, width, height };
	Point2f pivot{ shape.GetCenter() };
	return pivot;
}

void TrapDoor::RotateVertices(float elapsedSec)
{
	Matrix2x3 rotationMatrix, originMatrix, resetMatrix;
	rotationMatrix.SetAsRotate(m_Transform.angle);
	originMatrix.SetAsTranslate(-m_Transform.positionX, -m_Transform.positionY);
	resetMatrix.SetAsTranslate(m_Transform.positionX, m_Transform.positionY);
	Matrix2x3 transformationMatrix{ resetMatrix * rotationMatrix * originMatrix };
	m_Vertices = transformationMatrix.Transform(m_BaseVertices);
}