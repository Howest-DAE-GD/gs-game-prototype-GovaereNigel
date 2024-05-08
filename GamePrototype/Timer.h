#pragma once
class Timer
{
public:
	Timer(const Point2f& position);
	~Timer();
	void Draw();
	void Update(float timer);
private:
	Point2f m_FirstPosition;
	Point2f m_SecondPosition;
	int m_FirstNumber;
	int m_SecondNumber;
};

