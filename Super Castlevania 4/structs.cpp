#include "pch.h"
#include "structs.h"
#include <iostream>

//-----------------------------------------------------------------
// Window Constructors
//-----------------------------------------------------------------
Window::Window(const std::string& title, float width, float height, bool isVSyncOn)
	:title{ title }
	, width{ width }
	, height{ height }
	, isVSyncOn{ isVSyncOn }
{
}

//-----------------------------------------------------------------
// Point2f Constructors
//-----------------------------------------------------------------
Point2f::Point2f()
	:Point2f{ 0.0f, 0.0f }
{
}
Point2f::Point2f(float x, float y)
	: x{ x }, y{ y }
{
}

void Point2f::Log() const
{
	std::cout << "{ " << x << ", " << y << " }\n";
}

//-----------------------------------------------------------------
// Rectf Constructors
//-----------------------------------------------------------------
Rectf::Rectf()
	:Rectf{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}

Rectf::Rectf(float left, float bottom, float width, float height)
	: left{ left }
	, bottom{ bottom }
	, width{ width }
	, height{ height }
{
}

//-----------------------------------------------------------------
// Rectf Helpers
//-----------------------------------------------------------------
void Rectf::Log()
{
	std::string logMessage{ "{ l: " + std::to_string(left) };
	logMessage += ", b: " + std::to_string(bottom);
	logMessage += ", w: " + std::to_string(width);
	logMessage += ", h: " + std::to_string(height);
	std::cout << logMessage << std::endl;
}

void Rectf::SetBottomLeft(const Point2f& point)
{
	left = point.x;
	bottom = point.y;
}

Point2f Rectf::GetBottomLeft(float offsetX, float offsetY) const
{
	Point2f point{ left, bottom };
	point.x += offsetX;
	point.y += offsetY;
	return point;
}

Point2f Rectf::GetBottomCenter(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomLeft() };
	point.x += (width / 2) + offsetX;
	point.y += offsetY;
	return point;
}

Point2f Rectf::GetBottomRight(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomLeft() };
	point.x += width + offsetX;
	point.y += offsetY;
	return point;
}

Point2f Rectf::GetTopLeft(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomLeft() };
	point.x += offsetX;
	point.y += height + offsetY;
	return point;
}

Point2f Rectf::GetTopCenter(float offsetX, float offsetY) const
{
	Point2f point{ GetTopLeft() };
	point.x += (width / 2) + offsetX;
	point.y += offsetY;
	return point;
}

Point2f Rectf::GetTopRight(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomRight() };
	point.x += offsetX;
	point.y += height + offsetY;
	return point;
}

Point2f Rectf::GetCenterLeft(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomLeft() };
	point.x += offsetX;
	point.y += (height / 2) + offsetY;
	return point;
}

Point2f Rectf::GetCenter() const
{
	Point2f point{ GetBottomLeft() };
	point.x += width / 2;
	point.y += height / 2;
	return point;
}

Point2f Rectf::GetCenterRight(float offsetX, float offsetY) const
{
	Point2f point{ GetBottomRight() };
	point.x += offsetX;
	point.y += (height / 2) + offsetY;
	return point;
}

//-----------------------------------------------------------------
// Color4f Constructors
//-----------------------------------------------------------------
Color4f::Color4f()
	:Color4f{ 0.0f, 0.0f, 0.0f, 1.0f }
{
}

Color4f::Color4f(float r, float g, float b, float a)
	: r{ r }
	, g{ g }
	, b{ b }
	, a{ a }
{
}

//-----------------------------------------------------------------
// Circlef Constructors
//-----------------------------------------------------------------
Circlef::Circlef()
	:Circlef{ 0.0f, 0.0f, 0.0f }
{
}

Circlef::Circlef(float centerX, float centerY, float radius)
	: Circlef{ Point2f{ centerX, centerY }, radius }
{
}

Circlef::Circlef(const Point2f& center, float radius)
	: center{ center }
	, radius{ radius }
{
}

//-----------------------------------------------------------------
// Ellipsef Constructors
//-----------------------------------------------------------------
Ellipsef::Ellipsef()
	:Ellipsef{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}


Ellipsef::Ellipsef(const Point2f& center, float radiusX, float radiusY)
	: center{ center }
	, radiusX{ radiusX }
	, radiusY{ radiusY }
{
}

Ellipsef::Ellipsef(float centerX, float centerY, float radiusX, float radiusY)
	: Ellipsef{ Point2f{ centerX, centerY }, radiusX, radiusY }
{
}

Transform::Transform()
	: Transform(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Transform::Transform(const Point2f& position, float angle, float scale)
	: Transform(position.x, position.y, angle, scale)
{
}

Transform::Transform(float positionX, float positionY, float angle, float scale)
	: positionX{ positionX }
	, positionY{ positionY }
	, angle{ angle }
	, scale{ scale }
{
}

void Transform::SetTranslation(const Point2f& point)
{
	positionX = point.x;
	positionY = point.y;
}
