#include "pch.h"
#include "Card.h"
#include "Texture.h"

Card::Card(Suit suit, int rank)
	: Card(suit, rank, 0.0f, Circlef{})
{
}

Card::Card(Suit suit, int rank, float angle, const Circlef& circle)
	: m_Suit{ suit }, m_Rank{ rank }, m_Angle{ angle }, m_Circle{ circle }, m_RotationSpeed{ 180.0f }
{
	m_pTexture = new Texture(GetImagePath(suit, rank));
	m_Width = m_pTexture->GetWidth();
	m_Height = m_pTexture->GetHeight();
}

Card::~Card()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void Card::Update(float elapsedSec)
{
	m_Angle += m_RotationSpeed * elapsedSec;
}

float Card::GetWidth() const
{
	return m_Width;
}

float Card::GetHeight() const
{
	return m_Height;
}

std::string Card::GetImagePath(Suit suit, int rank) const
{
	std::string prefix{ "Resources/Cards/" };
	int index = ((int)suit * 100) + rank;
	std::string suffix{ ".png" };
	return prefix + std::to_string(index) + suffix;
}

void Card::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Circle.center.x, m_Circle.center.y, 0.0f);
	glScalef(0.5f, 0.5f, 1.0f);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(m_Circle.radius, 0.0f, 0.0f);
	m_pTexture->Draw();
	glPopMatrix();
}