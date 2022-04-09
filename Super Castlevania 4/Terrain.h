#pragma once
#include "Vector2f.h"
#include "utils.h"
#include <vector>

class Texture;

class Terrain
{
public:
	//Terrain();
	explicit Terrain(const std::string& path);
	explicit Terrain(const std::vector<std::vector<Point2f>>& vertices);
	~Terrain();

	void Draw() const;
	void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const;
	bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

private:
	std::vector<std::vector<Point2f>> m_pVertices;

	void CheckVerticalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;
	void CheckHorizontalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;
	std::vector<Point2f> GetRaycastAnchors(const Rectf& actorShape) const;

	void LogPoints(std::vector<Point2f>& points);
};