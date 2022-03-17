#pragma once
#include <vector>
#include "Vector2f.h"

class Texture;

class Diamond
{
public:
	Diamond(float width = 48.0f, float height = 48.0f);
	static const int m_NrOfVertices{ 4 };

	void Draw() const;
	void Update(float elapsedSec);
	void IsClickInPolygon(const Point2f& mousePosition);

private:
	Point2f m_pVertices[m_NrOfVertices];
	Point2f m_pTransformedVertices[m_NrOfVertices];

	Texture* m_pDiamondTexture;

	const float m_Width;
	const float m_Height;
	const float m_TranslationSpeed;
	const float m_RotationSpeed;
	const float m_ScaleSpeed;

	Vector2f m_DisplacementVector;
	float m_RotationAngle;
	float m_Scale;
	bool m_IsClicked;

	void InitialiseVertices();

	void DrawOutline() const;
	void DrawTexture() const;

 	void CalculateTransform(float elapsedSec);
	void Translate(float elapsedSec, const Uint8* pKeysState);
	void Rotate(float elapsedSec, const Uint8* pKeysState);
	void Scale(float elapsedSec, const Uint8* pKeysState);
	void ApplyTransform(float elapsedSec);

	Point2f GetCenter() const;
};