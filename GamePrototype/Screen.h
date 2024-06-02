#pragma once
#include "Texture.h"

class Screen
{
public:
	Screen(const Point2f& position, Point2f& window);
	~Screen();
	void Update(float elapsedSec);
	void Draw();
	void ChangeStateOfButton();
	void ChangeStateOfEndScreen(bool changeState);
	bool GetStateOfStartScreen()const;
	bool GetStateOfEndScreen()const;

private:
	Point2f m_Window;
	Point2f m_PosScreen;
	Point2f m_PosButton;
	bool m_StateOfStartScreen;
	bool m_StateOfEndScreen;
	bool m_StateOfButton;
	float m_AlphaValue;
	static const int m_TOTALTEXT{6};
	Texture* m_Text[m_TOTALTEXT];
};

