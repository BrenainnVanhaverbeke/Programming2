#pragma once
#include <vector>
#include "utils.h"

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
	const Point2f m_Center;

	bool m_RayIsIntersecting;

	Point2f m_MousePoint;
	utils::HitInfo m_RayHitInfo;
	std::vector<Point2f> m_Points;

	// FUNCTIONS
	void Initialize( );
	void InitialisePoints();
	void InitialisePolygon();

	void Cleanup( );

	void ClearBackground( ) const;
	void DrawPolygon() const;
	void DrawRay() const;
	void DrawIntersection() const;
	void DrawNormal() const;
	void DrawReflection() const;

	void CheckRaycast();
};