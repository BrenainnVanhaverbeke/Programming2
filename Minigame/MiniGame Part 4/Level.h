#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>

class Texture;
class Platform;

class Level
{
public:
	Level();
	~Level();
	void DrawBackground() const;
	void DrawForeground() const;
	void DrawGameOver() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;
	bool HasReachedEnd(const Rectf& actorShape) const;
	Rectf GetBoundaries() const;

private:
	const Texture* m_pBackgroundTexture;
	const Texture* m_pForegroundTexture;
	const Texture* m_pEndSignTexture;
	const Rectf m_Boundaries;
	const Rectf m_EndSignShape;
	
	std::vector<Point2f> m_Vertices;
	std::vector<Platform*> m_pPlatforms;
	Point2f m_FenceBottomLeft;

	void InitialiseVertices();
	void InitialisePlatforms();
	bool DoRaycast(const Rectf& actorShape, utils::HitInfo& hitInfo) const;
};