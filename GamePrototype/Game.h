#pragma once
#include "BaseGame.h"
#include "MovementPlayer.h"
#include <vector>

class Asteroid;
class Zomb;
class Hearts;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;


	//Point2f ResetPosition(Rectf platform)const;
	//float GetRandomHeight(float heightPreviousPlatform)const;
private:

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	Point2f m_Window{GetViewPort().width,GetViewPort().height};

	static const int m_TOTALASTEROIDS{3};
	Asteroid* m_Asteroid[m_TOTALASTEROIDS];
	Point2f m_PosAsteroid[m_TOTALASTEROIDS];
	Point2f m_PreviousPosAsteroid[m_TOTALASTEROIDS];
	float m_TimerAsteroids{};

	static const int m_TOTALZOMBIES{4};
	Zomb* m_Zomb[m_TOTALZOMBIES];
	float m_TimerZombies{};

	static const int m_TOTALHEARTS{ 4 };
	Hearts* m_Hearts[m_TOTALHEARTS];
	Point2f m_PosHearts[m_TOTALHEARTS];
	Point2f m_PosDefaultHeart{ -200.f,0.f };


};