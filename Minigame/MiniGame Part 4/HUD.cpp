#include "pch.h"
#include "HUD.h"
#include "Texture.h"

HUD::HUD(const Point2f& topLeft, int totalPowerUps)
	: m_TotalPowerUps{ totalPowerUps }
	, m_pLeftTexture{ new Texture("./Resources/Images/HudLeft.png") }
	, m_pRightTexture{ new Texture("./Resources/Images/HudRight.png") }
	, m_pPowerUpTexture{ new Texture("./Resources/Images/HudPowerUp.png") }
	, m_HitPowerUps{ 0 }
{
	m_BottomLeft = Point2f{ topLeft.x, topLeft.y - m_pLeftTexture->GetHeight() };
}

HUD::~HUD()
{
	delete m_pLeftTexture;
	delete m_pRightTexture;
	delete m_pPowerUpTexture;
}

void HUD::Draw() const
{
	Point2f elementOrigin { m_BottomLeft };
	DrawLeft(elementOrigin);
	DrawCenter(elementOrigin);
	DrawRight(elementOrigin);
}

void HUD::PowerUpHit()
{
	++m_HitPowerUps;
}

void HUD::DrawLeft(Point2f& elementOrigin) const
{
	m_pLeftTexture->Draw(elementOrigin);
	elementOrigin.x += m_pLeftTexture->GetWidth();
}

void HUD::DrawCenter(Point2f& elementOrigin) const
{
	const float spriteElementWidth{ m_pPowerUpTexture->GetWidth() / 2 };
	const float spriteElementHeight{ m_pPowerUpTexture->GetHeight() };
	bool powerUpActive{ false };
	Rectf sourceRect{ 0.0f, spriteElementHeight, spriteElementWidth, spriteElementHeight };
	for (int i{ 0 }; i < m_TotalPowerUps; ++i)
	{
		sourceRect.left = (i < m_HitPowerUps) ? 0.0f : spriteElementWidth;
		m_pPowerUpTexture->Draw(elementOrigin, sourceRect);
		elementOrigin.x += spriteElementWidth;
	}
}

void HUD::DrawRight(Point2f& elementOrigin) const
{
	m_pRightTexture->Draw(elementOrigin);
}
