#pragma once
#include <string>
#include <vector>

struct Window
{
	explicit Window(const std::string& title = "Title", float width = 320.0f,
		float height = 180.0f, bool isVSyncOn = true);

	std::string title;
	float width;
	float height;
	bool isVSyncOn;
};

struct Point2f
{
	Point2f();
	explicit Point2f(float x, float y);

	void Log() const;

	float x;
	float y;
};



struct Rectf
{
	Rectf();
	explicit Rectf(const Point2f& origin, float width, float height);
	explicit Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

	void Log() const;
	void SetBottomLeft(const Point2f& point);
	Point2f GetBottomLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetBottomRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetTopRight(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenterLeft(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenter(float offsetX = 0, float offsetY = 0) const;
	Point2f GetCenterRight(float offsetX = 0, float offsetY = 0) const;
	std::vector<Point2f> ConvertToVector() const;
};


struct Color4f
{
	Color4f();
	explicit Color4f(float r, float g, float b, float a);

	float r;
	float g;
	float b;
	float a;
};

struct Circlef
{
	Circlef();
	explicit Circlef(const Point2f& center, float radius);
	explicit Circlef(float centerX, float centerY, float radius);

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef();
	explicit Ellipsef(const Point2f& center, float radiusX, float radiusY);
	explicit Ellipsef(float centerX, float centerY, float radiusX, float radiusY);

	Point2f center;
	float radiusX;
	float radiusY;
};

struct Transform
{
	Transform();
	explicit Transform(const Point2f& position, float angle = 0.0f, float scale = 1.0f);
	explicit Transform(float positionX, float positionY, float angle= 0.0f, float scale = 1.0f);

	void SetTranslation(const Point2f& point);
	Point2f GetTranslation() const;

	float positionX;
	float positionY;
	float angle;
	float scale;
};