#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <iostream>
#include "Asteroid.h"
#include "Zomb.h"
#include "Hearts.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
	{
		m_Asteroid[idx] = new Asteroid(100.f, m_Window);
	}

	for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
	{
		m_Zomb[idx] = new Zomb{m_Window,30.f,30.f};

	}

	for (int idx{}; idx < m_TOTALHEARTS; ++idx)
	{
		m_PosHearts[idx] = m_PosDefaultHeart;
		m_Hearts[idx] = new Hearts{ m_PosHearts[idx]};
	}


}

void Game::Cleanup( )
{
	for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
	{
		delete m_Asteroid[idx];
		m_Asteroid[idx] = nullptr;
	}
	for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
	{
		delete m_Zomb[idx];
		m_Zomb[idx] = nullptr;
	}
}


void Game::Update( float elapsedSec )
{

	std::cout << m_PosHearts[0].x << m_PosHearts[0].y << std::endl;
	std::cout << m_PosHearts[1].x << m_PosHearts[1].y << std::endl;
	std::cout << m_PosHearts[2].x << m_PosHearts[2].y << std::endl;
	std::cout << m_PosHearts[3].x << m_PosHearts[3].y << std::endl;





	if (m_TimerAsteroids <= 1)
	{
		m_Asteroid[0]->Update(elapsedSec);

		m_TimerAsteroids += elapsedSec;
	}
	if (m_TimerAsteroids <= 2)
	{
		m_Asteroid[0]->Update(elapsedSec);
		m_Asteroid[1]->Update(elapsedSec);

		m_TimerAsteroids += elapsedSec;

	}
	if (m_TimerAsteroids > 2)
	{
		for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
		{
			m_Asteroid[idx]->Update(elapsedSec);
			m_PosAsteroid[idx] = m_Asteroid[idx]->GetPosition();
			if (m_Asteroid[idx]->GetStateOfAsteroid() == true)
			{
				if (m_Asteroid[idx]->HasAHeart() == true)
				{

					m_PreviousPosAsteroid[idx] = m_PosAsteroid[idx];



					for (int j{}; j < m_TOTALHEARTS; ++j)
					{

						if (m_PosHearts[j].x != m_PreviousPosAsteroid[idx].x && m_PosHearts[j].y != m_PreviousPosAsteroid[idx].y)
						{
							if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
							{
								if (j == 0)
								{
									if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[idx].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[idx].y)
									{
										m_PosHearts[j].x = m_PosAsteroid[idx].x;
										m_PosHearts[j].y = m_PosAsteroid[idx].y;
										m_Hearts[j]->SetPosition(m_PosHearts[j]);
									}
									else break;
								}
								else
								{
									if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[idx].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[idx].y)
									{
										m_PosHearts[j].x = m_PosAsteroid[idx].x;
										m_PosHearts[j].y = m_PosAsteroid[idx].y;
										m_Hearts[j]->SetPosition(m_PosHearts[j]);
									}
									else break;
								}

							}


						}




						//		if (j == 0)
						//	{
						//		if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PosDefaultHeart.x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PosDefaultHeart.y)
						//		{
						//			if (m_PosHearts[j].x == m_PosHearts[m_TOTALHEARTS - 1].x && m_PosHearts[j].y == m_PosHearts[m_TOTALHEARTS - 1].y) break;
						//		}
						//	}
						//	else
						//	{
						//		//std::cout << "stopped" << std::endl;

						//		if (m_PosHearts[j-1].x != m_PosDefaultHeart.x && m_PosHearts[j-1].y != m_PosDefaultHeart.y)
						//		{

						//			break;

						//			if (m_PosHearts[j].x == m_PosHearts[j - 1].x && m_PosHearts[j].y == m_PosHearts[j - 1].y)
						//			{
						//				std::cout << "stopped" << std::endl;
						//				break;
						//			}
						//		}

						//	}

						//if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
						//{
						//	m_PosHearts[j].x = m_PosAsteroid[idx].x;
						//	m_PosHearts[j].y = m_PosAsteroid[idx].y;
						//	m_Hearts[j]->SetPosition(m_PosHearts[j]);
						//}




						//}

						
					}

				}
			}

		}
		for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
		{
			m_Zomb[idx]->Update(elapsedSec);
			if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[0], m_Asteroid[0]->GetRadius(),m_Asteroid[0]->GetStateOfAsteroid()) == true)
			{
				//std::cout << "hit first" << std::endl;
				m_Zomb[idx]->ResetPos();
			}
			if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[1], m_Asteroid[1]->GetRadius(), m_Asteroid[1]->GetStateOfAsteroid()) == true)
			{
				//std::cout << "hit first" << std::endl;
				m_Zomb[idx]->ResetPos();
			}	
			if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[2], m_Asteroid[2]->GetRadius(), m_Asteroid[2]->GetStateOfAsteroid()) == true)
			{
				//std::cout << "hit first" << std::endl;
				m_Zomb[idx]->ResetPos();
			}
		
		}

	}





}

void Game::Draw( ) const
{
	ClearBackground( );

	for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
	{
		m_Asteroid[idx]->Draw();
	}

	for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
	{
		m_Zomb[idx]->Draw();
	}

	for (int idx{}; idx < m_TOTALHEARTS; ++idx)
	{
		m_Hearts[idx]->Draw();
	}
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch ( e.keysym.sym )
	{
	case SDLK_SPACE:
		//std::cout << "Left arrow key released\n";
		break;
	case SDLK_RIGHT:
		//std::cout << "`Right arrow key released\n";
		break;
	case SDLK_1:
	case SDLK_KP_1:
		//std::cout << "Key 1 released\n";
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.3f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

//Point2f Game::ResetPosition(Rectf platform) const
//{
//
//	Point2f newPos
//	{
//		platform.left + platform.width,
//		0.f
//	};
//
//	return newPos;
//}

//float Game::GetRandomHeight(float heightPreviousPlatform) const
//{
//	const float distance{100.f};
//	const float PreviousHeight{heightPreviousPlatform};
//	float newHeight{};
//	int random{};
//
//	if (platform.height == (startHeight - distance / 2))
//	{
//		random = rand() % 3 + 1;
//	}
//	else if (platform.height == (startHeight - distance))
//	{
//		random = rand() % 2 + 2;
//	}
//	else if (platform.height == (startHeight + distance / 2))
//	{
//		random = rand() % 3 + 0;
//	}
//	else if (platform.height == (startHeight + distance))
//	{
//		random = rand() % 2 + 0;
//	}
//	else
//	{
//		random = rand() % 4 + 0;
//	}
//
//	if (random == 4)
//	{
//		newHeight = platform.height + distance;
//	}
//	else if (random == 3)
//	{
//		newHeight = platform.height + distance / 2;
//	}
//	else if (random == 2)
//	{
//		newHeight = platform.height;
//	}
//	else if (random == 1)
//	{
//		newHeight = platform.height - distance / 2;
//	}
//	else
//	{
//		newHeight = platform.height - distance;
//	}
//
//
//	return newHeight;
//}
