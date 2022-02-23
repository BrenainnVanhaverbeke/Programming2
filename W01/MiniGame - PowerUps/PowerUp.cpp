#include "pch.h"
#include "PowerUp.h"
#include "Texture.h"
#include "utils.h"
#include <iostream>

PowerUp::PowerUp(const Point2f& center, PowerUp::Type type)
	: m_pTexture{ new Texture{"./Resources/Images/PowerUp.png" } },
	  m_RotSpeed{ 360.0f }, m_Type{ type }, m_Angle{ 0.0f }
{
	if (!m_pTexture->IsCreationOk())
		std::cout << "Error loading PowerUp texture." << std::endl;
	m_Shape = Circlef{ center, m_pTexture->GetWidth() / 2 };
}

PowerUp::~PowerUp()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += (m_RotSpeed * elapsedSec);
	if (360.0f < m_Angle)
		m_Angle -= 360.0f;
}

void PowerUp::Draw() const
{
	const float textureWidth{ m_pTexture->GetWidth() };
	const float textureHeight{ m_pTexture->GetHeight() / 2 };
	Rectf destination{ m_Shape.center.x - m_Shape.radius, m_Shape.center.y - m_Shape.radius,
					   textureWidth, textureWidth };
	Rectf source{ 0, textureHeight * (int)m_Type, textureWidth, textureHeight };
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_Shape.center.x, -m_Shape.center.y, 0);
	m_pTexture->Draw(destination, source);
	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf& rect) const
{
	return utils::IsOverlapping(rect, m_Shape);
}