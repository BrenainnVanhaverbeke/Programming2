#pragma once
class TrafficLight
{	
public:
	enum class State
	{
		green,
		orange,
		red,
		off,
		END
	};
	TrafficLight(const Point2f& position, float width, float height);
	void DoHitTest(const Point2f& position);
	void Update(float elapsedSec);
	void Draw();
	float GetWidth();
	float GetHeight();

private:
	State m_State;
	Point2f m_Position;
	float m_AccumulatedSec;
	float m_Width;
	float m_Height;
	Circlef m_Green;
	Circlef m_Orange;
	Circlef m_Red;
};

