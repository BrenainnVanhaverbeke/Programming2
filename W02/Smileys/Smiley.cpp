// -- Smiley.cpp file --
// Decide yourself about the necessary include directives
#include "pch.h"
#include "Smiley.h"
#include "Texture.h"
#include "utils.h"

// Static Texture data
Texture* Smiley::m_pSmileyTexture{ nullptr };
int Smiley::m_InstanceCounter{ 0 };

// Constructor
// Initializes the object, among others:
//	- Initializes the data members, the velocity gets a random value within the inclusive range[60, 180] and [-180, -60]
//	- Creates a texture object to load the image, only if it hasn’t been created before( !)
//  - Adapts the instance counter
Smiley::Smiley(const Point2f& position)
	: m_Position{ position }, m_Velocity{ GetRandomVector() }, m_IsHighest{ false },
	m_IsSleeping{ false }, m_IsInSafeArea{ true }
{
	LoadTexture();
	m_InstanceCounter++;
}

// Destructor
// Deletes the Texture object when this is the last Smiley that is being destroyed.
Smiley::~Smiley()
{
	DeleteSmiley();
}

// Draw
// Draws a part of the image on the window, which part depends on the state of the smiley:
// - If the smiley is sleeping then the sleeping smiley is drawn.
// - If the smiley is at the highest position, then the happy smiley is drawn.
// - If the smiley is not in the safe area, the scary smiley is drawn.
// - If none of the above conditions is met, the neutral smiley should be drawn.
void Smiley::Draw()
{
	//const float height{ m_pSmileyTexture->GetHeight() };
	//const float width{ m_pSmileyTexture->GetWidth() / 4 };
	//Rectf sourceRect{ GetSourceRect() };
	m_pSmileyTexture->Draw(m_Position, GetSourceRect());
}


// Update
// - When the smiley is not sleeping, the new position - using the velocity and elapsed seconds - is calculated.
// - The velocity changes sign when at this new position the smiley is outside the bounding rectangle (boundingRect)
// - Checks whether at this new position, it is located in the safe area and updates m_IsInSafeArea accordingly.
void Smiley::Update(float elapsedSec, const Rectf& boundingRect, const Rectf& safeRect)
{
	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
	CheckCollision(boundingRect);
	CorrectPosition(boundingRect);
	m_IsInSafeArea = IsInSafeArea(safeRect);
}

// HitTest
// If the value of the parameter pos is within the boundaries of the smiley’s circle,
// then the sleeping state of the smiley changes.
void Smiley::HitTest(const Point2f& pos)
{
	Rectf smileyRect{ m_Position.x, m_Position.y, m_SmileyWidth, m_SmileyHeight };
	if (utils::IsPointInRect(pos, smileyRect))
		m_IsSleeping = !m_IsSleeping;
}

// IsSleeping
// Getter of the m_IsSleeping data member
bool Smiley::IsSleeping()
{
	return m_IsSleeping;
}

// GetPosition
// Getter of the m_Position data member
Point2f Smiley::GetPosition()
{
	return m_Position;
}

// SetHighest
// Setter of the m_IsHighest data member
void Smiley::SetHighest(bool isHighest)
{
	m_IsHighest = isHighest;
}

// IncreaseSpeed
// Changes the speed 5% up
void Smiley::IncreaseSpeed()
{
	const float speedFactor{ 0.05f };
	m_Velocity.x += m_Velocity.x * speedFactor;
	m_Velocity.y += m_Velocity.x * speedFactor;
}

// DecreaseSpeed
// Changes the speed 5% down
void Smiley::DecreaseSpeed()
{
	const float speedFactor{ 0.05f };
	m_Velocity.x -= m_Velocity.x * speedFactor;
	m_Velocity.y -= m_Velocity.x * speedFactor;
}

// IsInSafeArea
// Returns true when the smiley is completely inside the safe area as indicated by safeRect
bool Smiley::IsInSafeArea(const Rectf& safeRect)
{
	const float width{ m_pSmileyTexture->GetWidth() / 4 };
	const float height{ m_pSmileyTexture->GetHeight() };
	Rectf smileyRect{ m_Position.x, m_Position.y, width, height };
	Point2f topLeft{ m_Position.x, m_Position.y + height };
	Point2f topRight{ m_Position.x + width, m_Position.y + height };
	Point2f bottomRight{ m_Position.x + width, m_Position.y };
	bool isSafe{ utils::IsPointInRect(m_Position, safeRect)
			  && utils::IsPointInRect(topLeft, safeRect)
			  && utils::IsPointInRect(topRight, safeRect)
			  && utils::IsPointInRect(bottomRight, safeRect) };
	return isSafe;
}

void Smiley::LoadTexture()
{
	int spriteColumns{ 4 };
	int spriteRows{ 1 };
	if (!m_pSmileyTexture)
	{
		m_pSmileyTexture = new Texture("Resources/Smileys.png");
		if (!m_pSmileyTexture->IsCreationOk())
			std::cout << "Shit got fucked loading Smileys.png, abandon all hope" << std::endl;
		else
			std::cout << "Successfully loaded Smileys texture" << std::endl;
	}
	m_SmileyWidth = m_pSmileyTexture->GetWidth() / spriteColumns;
	m_SmileyHeight = m_pSmileyTexture->GetHeight() / spriteRows;
}

void Smiley::DeleteSmiley()
{
	m_InstanceCounter--;
	if (m_InstanceCounter <= 0)
	{
		std::cout << "Last Smiley, releasing Texture." << std::endl;
		delete m_pSmileyTexture;
		m_pSmileyTexture = nullptr;
	}
}

void Smiley::CheckCollision(const Rectf& boundingRect)
{
	if (m_Position.x < boundingRect.left ||
		boundingRect.width - (m_pSmileyTexture->GetWidth() / 4) < m_Position.x)
		m_Velocity.x *= -1;
	if (m_Position.y < boundingRect.bottom ||
		boundingRect.height - m_pSmileyTexture->GetHeight() < m_Position.y)
		m_Velocity.y *= -1;
}

void Smiley::CorrectPosition(const Rectf& boundingRect)
{
	if (m_Position.x < boundingRect.left)
		m_Position.x = boundingRect.left;
	if (boundingRect.left + boundingRect.width < m_Position.x + m_SmileyWidth)
		m_Position.x = (boundingRect.left + boundingRect.width) - m_SmileyWidth;
	if (m_Position.y < boundingRect.bottom)
		m_Position.y = boundingRect.bottom;
	if (boundingRect.bottom + boundingRect.height < m_Position.y + m_SmileyHeight)
		m_Position.y = (boundingRect.bottom + boundingRect.height) - m_SmileyHeight;
}

Vector2f Smiley::GetRandomVector()
{
	Vector2f randomVector{ (float)utils::GetRandomNumber(-100, 100),
						   (float)utils::GetRandomNumber(-100, 100) };
	return randomVector;
}

Rectf Smiley::GetSourceRect()
{
	Rectf sourceRect{ m_SmileyWidth, m_SmileyHeight, m_SmileyWidth, m_SmileyHeight };
	int offsetFactor{ 1 };
	if (m_IsSleeping)
		offsetFactor = 3;
	else if (!m_IsInSafeArea)
		offsetFactor = 2;
	else if (m_IsHighest)
		offsetFactor = 0;
	sourceRect.left = m_SmileyWidth * offsetFactor;
	return sourceRect;
}