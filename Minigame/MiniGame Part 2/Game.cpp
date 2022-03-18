#include "pch.h"
#include <iostream>

#include "Game.h"
#include "utils.h"
#include "Level.h"
#include "PowerUpManager.h"
#include "Avatar.h"

Game::Game( const Window& window )
	:m_Window{ window }
	, m_pLevel{ new Level{} }
	, m_pPowerUpManager{ new PowerUpManager{} }
	, m_pAvatar{ new Avatar{} }
{	 
	Initialize( );
}

Game::~Game( )
{
	Cleanup();
}

void Game::Initialize( )
{
	ShowTestMessage( );
	AddPowerUps( );
}

void Game::Cleanup()
{
	delete m_pLevel;
	delete m_pPowerUpManager;
	delete m_pAvatar;
}

void Game::Update( float elapsedSec )
{
	// Power ups
	m_pPowerUpManager->Update( elapsedSec );

	// Update game objects
	m_pPowerUpManager->Update(elapsedSec);
	m_pAvatar->Update(elapsedSec, m_pLevel);

	// Do collision
	DoCollisionTests();

}

void Game::Draw( ) const
{
	ClearBackground( );

	// Level's backGround
	m_pLevel->DrawBackground( );

	// PowerUps
	m_pPowerUpManager->Draw( );

	// Actor
	m_pAvatar->Draw( );

	// Level's foreground
	m_pLevel->DrawForeground( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::ShowTestMessage( ) const
{
	std::cout << "--> Avatar test <--\n";
	std::cout << "Verify that the avatar behaves as follows.\n";
	std::cout << "- Moves along the level when the left/right arrow is pressed.\n";
	std::cout << "- Doesn't move when it is on the ground and no key is pressed.\n";
	std::cout << "- Jumps only when it is on the ground and the up arrow key is pressed.\n";
	std::cout << "- Doesn't move during 1 second when hitting a power up.\n";
	std::cout << "- Starts moving again ( e.g. falling ) after this second.\n";
	std::cout << "- The number of small rectangles in the bottom left corner is equal to the number of hit power ups.\n";
	std::cout << "- Has a red color when it is moving.\n";
	std::cout << "- Has a yellow color when it is waiting.\n";
	std::cout << "- Has a blue color when it is transforming.\n";
}

void Game::AddPowerUps( )
{
	m_pPowerUpManager->AddItem( Point2f{ 185.0f, 500 - 183.0f }, PowerUp::Type::brown );
	m_pPowerUpManager->AddItem( Point2f{ 435.0f, 500 - 133.0f }, PowerUp::Type::green );
	m_pPowerUpManager->AddItem( Point2f{ 685.0f, 500 - 183.0f }, PowerUp::Type::brown );
}

void Game::DoCollisionTests()
{
	if (m_pPowerUpManager->HitItem(m_pAvatar->GetShape()))
	{
		m_pAvatar->PowerUpHit();
	}
}