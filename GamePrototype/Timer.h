#pragma once


class Timer
{
public:
	Timer(const Point2f& position, Point2f& window);
	~Timer();
	void Draw(bool stateEndScreen);
	void Update(float elapsedSec,float timer, bool stateEndScreen);
private:
	Point2f m_Window;
	Point2f m_FirstPosition;
	Point2f m_SecondPosition;
	int m_FirstNumber;
	int m_SecondNumber;
	float m_Scale;
};

