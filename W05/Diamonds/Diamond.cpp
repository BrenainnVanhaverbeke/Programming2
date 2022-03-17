#include "pch.h"
#include "Diamond.h"
#include "utils.h"
#include "Matrix2x3.h"
#include "Texture.h"
#include <iostream>

Diamond::Diamond(const Point2f& origin, float width, float height)
	: m_Width{ width }
	, m_Height{ height }
	, m_TranslationSpeed{ 120.0f }
	, m_RotationSpeed{ 60.0f }
	, m_ScaleSpeed{ 3.0f }
	, m_DisplacementVector{}
	, m_RotationAngle{ 0.0f }
	, m_Scale{ 1.0f }
	, m_IsClicked{ false }
	, m_pDiamondTexture{ new Texture("./Resources/Images/Diamond.png") }
{
	InitialiseVertices(origin);
	if (!m_pDiamondTexture->IsCreationOk())
		std::cout << "Error loading Diamond texture.";
}

Diamond::~Diamond()
{
	delete m_pDiamondTexture;
	m_pDiamondTexture = nullptr;
}

void Diamond::Draw() const
{
	DrawTexture();
	DrawOutline();
}

void Diamond::Update(float elapsedSec)
{
	if (m_IsClicked)
		CalculateTransform(elapsedSec);
	ApplyTransform(elapsedSec);
}

void Diamond::IsClickInPolygon(const Point2f& mousePosition)
{
	if (utils::IsPointInPolygon(mousePosition, m_pTransformedVertices, m_NrOfVertices))
		m_IsClicked = !m_IsClicked;
}

void Diamond::Reset()
{
	m_DisplacementVector = Vector2f{};
	m_RotationAngle = 0;
	m_Scale = 1.0f;
	m_IsClicked = false;
}

void Diamond::InitialiseVertices(const Point2f& origin)
{
	m_pVertices[0] = Point2f{ origin.x, origin.y + m_Height / 2 };
	m_pVertices[1] = Point2f{ origin.x + m_Width / 2, origin.y + m_Height };
	m_pVertices[2] = Point2f{ origin.x + m_Width, origin.y + m_Height / 2 };
	m_pVertices[3] = Point2f{ origin.x + m_Width / 2, origin.y };
}

void Diamond::DrawOutline() const
{
	Color4f inactiveColour{ 0.25f, 0.28f, 0.8f, 1.0f };
	Color4f activeColour{ 1.0f, 0.0f, 0.0f, 1.0f };

	utils::SetColor((m_IsClicked) ? activeColour : inactiveColour);
	utils::DrawPolygon(m_pTransformedVertices, m_NrOfVertices, true, 3.0f);
}

void Diamond::DrawTexture() const
{
	Point2f center{ GetCenter() };
	glPushMatrix();
	{
		glTranslatef(m_DisplacementVector.x + center.x, m_DisplacementVector.y + center.y, 0);
		glRotatef(m_RotationAngle, 0, 0, 1);
		glScalef(m_Scale, m_Scale, 0);
		glTranslatef(-(m_Width / 2), -(m_Height / 2), 0);
		m_pDiamondTexture->Draw();
	}
	glPopMatrix();
}

void Diamond::CalculateTransform(float elapsedSec)
{
	const Uint8* pKeysState{ SDL_GetKeyboardState(nullptr) };
	Translate(elapsedSec, pKeysState);
	Rotate(elapsedSec, pKeysState);
	Scale(elapsedSec, pKeysState);
}

void Diamond::Translate(float elapsedSec, const Uint8* pKeysState)
{
	int directionX{ 0 };
	int directionY{ 0 };
	if (pKeysState[SDL_SCANCODE_UP])
		directionY = 1;
	if (pKeysState[SDL_SCANCODE_DOWN])
		directionY = -1;
	if (pKeysState[SDL_SCANCODE_LEFT])
		directionX = -1;
	if (pKeysState[SDL_SCANCODE_RIGHT])
		directionX = 1;
	m_DisplacementVector.x += directionX * m_TranslationSpeed * elapsedSec;
	m_DisplacementVector.y += directionY * m_TranslationSpeed * elapsedSec;
}

void Diamond::Rotate(float elapsedSec, const Uint8* pKeysState)
{
	int rotationDirection{ 0 };
	if (pKeysState[SDL_SCANCODE_A])
		rotationDirection = 1;
	if (pKeysState[SDL_SCANCODE_D])
		rotationDirection = -1;
	m_RotationAngle += rotationDirection * m_RotationSpeed * elapsedSec;
}

void Diamond::Scale(float elapsedSec, const Uint8* pKeysState)
{
	float scaleFactor{ 1 + (m_ScaleSpeed * elapsedSec) };
	if (pKeysState[SDL_SCANCODE_W])
		m_Scale *= scaleFactor;
	if (pKeysState[SDL_SCANCODE_S])
		m_Scale /= scaleFactor;
}

void Diamond::ApplyTransform(float elapsedSec)
{
	Matrix2x3 translationMatrix{}, rotationMatrix{}, scaleMatrix{}, trsMatrix{}, centeringMatrix{}, resetMatrix{};
	Vector2f diamondCenter{ GetCenter() };
	translationMatrix.SetAsTranslate(m_DisplacementVector);
	rotationMatrix.SetAsRotate(m_RotationAngle);
	scaleMatrix.SetAsScale(m_Scale);
	centeringMatrix.SetAsTranslate(-diamondCenter);
	trsMatrix = translationMatrix * rotationMatrix * scaleMatrix * centeringMatrix;
	centeringMatrix.SetAsTranslate(diamondCenter);
	trsMatrix = centeringMatrix * trsMatrix;
	trsMatrix.Transform(m_pVertices, m_pTransformedVertices, m_NrOfVertices);
}

Point2f Diamond::GetCenter() const
{
	return utils::GetMiddle(m_pVertices[0], m_pVertices[2]);
}