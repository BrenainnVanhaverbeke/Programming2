#include "pch.h"
#include "Avatar.h"
#include "Enemy.h"
#include "utils.h"
#include "Bullet.h"

Avatar::Avatar()
	: Avatar(Point2f{ 0.0f, 0.0f }, 10.0f, 10.0f)
{
}

Avatar::Avatar(const Point2f& center, float width, float height)
	: m_Center{ center }, m_Width{ width }, m_Height{ height }, m_Boundaries{ Rectf{} },
	m_Speed{ 200.0f }, m_Bullet{ new Bullet(width / 8, height / 4) }
{
}

Avatar::~Avatar()
{
	delete m_Bullet;
	m_Bullet = nullptr;
}

void Avatar::Update(float elapsedSec, Enemy** pEnemies, int numEnemies)
{
	HandleMoveKeysState(elapsedSec);
	m_Bullet->Update(elapsedSec, pEnemies, numEnemies);
}

void Avatar::Draw() const
{
	DrawAvatar();
	m_Bullet->Draw();
}

void Avatar::DrawAvatar() const
{
	const Color4f avatarColour{ 1.0f, 1.0f, 0.0f, 1.0f };
	const float lineThickness{ 3.0f };
	Point2f bottomLeft{ m_Center.x - (m_Width / 2), m_Center.y - (m_Height / 2) };
	Point2f bottomRight{ bottomLeft.x + m_Width, bottomLeft.y };
	Point2f top{ utils::GetMiddle(bottomLeft, bottomRight) };
	top.y += m_Height;
	Point2f wedge{ top.x, bottomLeft.y + (m_Height / 3.0f) };
	utils::SetColor(avatarColour);
	utils::DrawLine(bottomLeft, top, lineThickness);
	utils::DrawLine(top, bottomRight, lineThickness);
	utils::DrawLine(bottomRight, wedge, lineThickness);
	utils::DrawLine(wedge, bottomLeft, lineThickness);
}

void Avatar::SetCenter(const Point2f& center)
{
	m_Center = center;
}

void Avatar::SetDimensions(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void Avatar::SetBoundaries(const Rectf& boundaries)
{
	m_Boundaries = boundaries;
	m_Bullet->SetBoundaries(boundaries);
}

void Avatar::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_UP || e.keysym.sym == SDLK_w)
	{
		const Vector2f bulletVelocity{ 0.0f, 1000.0f };
		m_Bullet->Shoot(Point2f{ m_Center.x, m_Center.y + m_Height }, bulletVelocity);
	}
}

void Avatar::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A])
		m_Center.x -= m_Speed * elapsedSec;
	if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D])
		m_Center.x += m_Speed * elapsedSec;
	Clamp();
}

void Avatar::Clamp()
{
	if (m_Center.x - (m_Width / 2.0f) < m_Boundaries.left)
		m_Center.x = (m_Width / 2);
	if (m_Boundaries.left + m_Boundaries.width < m_Center.x + (m_Width / 2))
		m_Center.x = (m_Boundaries.left + m_Boundaries.width) - (m_Width / 2);
}

