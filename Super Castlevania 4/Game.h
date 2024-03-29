#pragma once

class Player;
class Camera;
class LevelManager;
class ProjectileManager;
class EnemyManager;
class Bat;
class UI;

class Game final
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;

	LevelManager* m_pLevelManager;
	ProjectileManager* m_pProjectileManager;
	EnemyManager* m_pEnemyManager;
	Player* m_pPlayer;
	Camera* m_pCamera;
	UI* m_pUI;

	bool m_IsDrawDebugEnabled;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;
	void DisplayInstructions();
};