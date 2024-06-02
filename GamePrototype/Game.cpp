#include "pch.h"
#include "Game.h"
#include "utils.h"
#include <iostream>
#include "Asteroid.h"
#include "Zomb.h"
#include "Hearts.h"
#include "Player.h"
#include "Healthbar.h"
#include "SpecialZomb.h"
#include "Timer.h"
#include "Screen.h"

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
	for (int idx{}; idx < m_TOTALHEARTS; ++idx)
	{
		m_PosHearts[idx] = m_PosDefaultHeart;
		m_Hearts[idx] = new Hearts{ m_PosHearts[idx] };
	}
	for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
	{
		m_Zomb[idx] = new Zomb{m_Window,25.f,25.f};

	}
	m_PosPlayer.x = GetViewPort().width/2;
	m_PosPlayer.y = GetViewPort().height/2;
	m_Player = new Player{ m_PosPlayer,m_Window.x,m_Window.y };

	Point2f positionHealthBar{m_Window.x,m_Window.y+70.f};
	m_Healthbar = new Healthbar{ m_Player->GetHealth(),positionHealthBar};


	for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
	{
		m_SpecialZomb[idx] = new SpecialZomb{GetViewPort().width,GetViewPort().height};
	}
	m_PosCounter.x = GetViewPort().width - 50.f;
	m_PosCounter.y = GetViewPort().height - 50.f;
	m_Counter = new Timer{ m_PosCounter, m_Window};

	const Point2f positionScreen{0.f,0.f};
	m_StartScreen = new Screen{ positionScreen,m_Window};
}

void Game::Cleanup( )
{
	for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
	{
		delete m_Asteroid[idx];
		m_Asteroid[idx] = nullptr;
	}
	for (int idx{}; idx < m_TOTALHEARTS; ++idx)
	{
		delete m_Hearts[idx];
		m_Hearts[idx] = nullptr;
	}
	for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
	{
		delete m_Zomb[idx];
		m_Zomb[idx] = nullptr;
	}
	delete m_Player;
	m_Player = nullptr;

	delete m_Healthbar;
	m_Healthbar = nullptr;

	for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
	{
		delete m_SpecialZomb[idx];
		m_SpecialZomb[idx] = nullptr;
	}
	delete m_Counter;
	m_Counter = nullptr;

	delete m_StartScreen;
	m_StartScreen = nullptr;
}


void Game::Update( float elapsedSec )
{

	if (m_StateOfGame == true)
	{
		if (m_StartScreen->GetStateOfStartScreen() == false)
		{
			m_Timer += elapsedSec;

			m_SpeedPlayer = 500.f * elapsedSec;
			const Uint8* pStates = SDL_GetKeyboardState(nullptr);
			m_Player->Update(elapsedSec, pStates);
			m_PosPlayer = m_Player->GetPosition();


			if (m_Timer < 10.f)
			{
				m_SpeedAsteroid = 40.f * elapsedSec;
				m_SpeedZomb = 120.f * elapsedSec;

				if (m_Timer < 2.5)
				{
					for (int idx{}; idx < m_TOTALZOMBIES - 4; ++idx)
					{
						m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
					}
					m_Asteroid[0]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[0] = m_Asteroid[0]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[0], m_Asteroid[0]->GetRadius(), m_Asteroid[0]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[0]->GetDamage());
						m_Asteroid[0]->ResetAsteroid();
						m_PosAsteroid[0] = m_Asteroid[0]->GetPosition();
					}
					if (m_Asteroid[0]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[0]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[0] = m_PosAsteroid[0];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[0].x && m_PosHearts[j].y != m_PreviousPosAsteroid[0].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[0].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[0].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[0].x;
												m_PosHearts[j].y = m_PosAsteroid[0].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[0].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[0].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[0].x;
												m_PosHearts[j].y = m_PosAsteroid[0].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}

						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[0], m_Asteroid[0]->GetRadius(), m_Asteroid[0]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}
					}
					for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
					{
						if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
						{
							m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
							m_Zomb[idx]->ResetPos();
						}
					}
					for (int idx{}; idx < m_TOTALHEARTS; ++idx)
					{
						if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
						{
							m_PosHearts[idx] = m_PosDefaultHeart;
							m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
							if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
						}
					}
					if (m_Player->GetHealth() <= 0)
					{
						m_StateOfGame = false;
						m_StartScreen->ChangeStateOfEndScreen(true);

					}

				}
				else if (m_Timer < 5)
				{
					for (int idx{}; idx < m_TOTALZOMBIES - 2; ++idx)
					{
						m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
					}
					for (int k{}; k < m_TOTALASTEROIDS - 1; ++k)
					{
						m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
						if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
						{
							std::cout << m_Player->GetHealth() << std::endl;
							m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
							m_Asteroid[k]->ResetAsteroid();
							m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
						}
						if (m_Asteroid[k]->GetStateOfAsteroid() == true)
						{
							if (m_Asteroid[k]->HasAHeart() == true)
							{
								m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
								for (int j{}; j < m_TOTALHEARTS; ++j)
								{
									if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
									{
										if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
										{
											if (j == 0)
											{
												if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
												{
													m_PosHearts[j].x = m_PosAsteroid[k].x;
													m_PosHearts[j].y = m_PosAsteroid[k].y;
													m_Hearts[j]->SetPosition(m_PosHearts[j]);
												}
												else return;
											}
											else
											{
												if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
												{
													m_PosHearts[j].x = m_PosAsteroid[k].x;
													m_PosHearts[j].y = m_PosAsteroid[k].y;
													m_Hearts[j]->SetPosition(m_PosHearts[j]);
												}
												else return;
											}

										}


									}
								}
							}


							for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
							{
								if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
								{
									m_Zomb[idx]->ResetPos();
								}
							}
						}
					}
					for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
					{
						if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
						{
							m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
							m_Zomb[idx]->ResetPos();
						}
					}
					for (int idx{}; idx < m_TOTALHEARTS; ++idx)
					{
						if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
						{
							m_PosHearts[idx] = m_PosDefaultHeart;
							m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
							if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
						}
					}
					if (m_Player->GetHealth() <= 0)
					{
						m_StateOfGame = false;
						m_StartScreen->ChangeStateOfEndScreen(true);
					}
				}
				else
				{
					for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
					{
						m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
					}
					for (int k{}; k < m_TOTALASTEROIDS; ++k)
					{
						m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
						if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
						{
							std::cout << m_Player->GetHealth() << std::endl;
							m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
							m_Asteroid[k]->ResetAsteroid();
							m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
						}
						if (m_Asteroid[k]->GetStateOfAsteroid() == true)
						{
							if (m_Asteroid[k]->HasAHeart() == true)
							{
								m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
								for (int j{}; j < m_TOTALHEARTS; ++j)
								{
									if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
									{
										if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
										{
											if (j == 0)
											{
												if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
												{
													m_PosHearts[j].x = m_PosAsteroid[k].x;
													m_PosHearts[j].y = m_PosAsteroid[k].y;
													m_Hearts[j]->SetPosition(m_PosHearts[j]);
												}
												else return;
											}
											else
											{
												if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
												{
													m_PosHearts[j].x = m_PosAsteroid[k].x;
													m_PosHearts[j].y = m_PosAsteroid[k].y;
													m_Hearts[j]->SetPosition(m_PosHearts[j]);
												}
												else return;
											}

										}


									}
								}
							}


							for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
							{
								if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
								{
									m_Zomb[idx]->ResetPos();
								}
							}
						}
					}
					for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
					{
						if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
						{
							m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
							m_Zomb[idx]->ResetPos();
						}
					}
					for (int idx{}; idx < m_TOTALHEARTS; ++idx)
					{
						if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
						{
							m_PosHearts[idx] = m_PosDefaultHeart;
							m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
							if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
						}
					}
					if (m_Player->GetHealth() <= 0)
					{
						m_StateOfGame = false;
						m_StartScreen->ChangeStateOfEndScreen(true);
					}
				}
			}
			else if (m_Timer < 20.f)
			{
				m_SpeedAsteroid = 45.f * elapsedSec;
				m_SpeedZomb = 125.f * elapsedSec;
				m_SpeedSpecialZomb = 90.f * elapsedSec;

				for (int idx{}; idx < m_TOTALSPECIALZOMBS - 2; ++idx)
				{
					m_SpecialZomb[idx]->Update(elapsedSec, m_PosPlayer, m_SpeedSpecialZomb);
					if (m_Player->IshHitZomb(m_SpecialZomb[idx]->GetBounds()))
					{
						m_Player->LoseHealth(1);
						m_SpecialZomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
				}
				for (int k{}; k < m_TOTALASTEROIDS; ++k)
				{
					m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
						m_Asteroid[k]->ResetAsteroid();
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					}
					if (m_Asteroid[k]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[k]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}


						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}

						for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
						{
							if (m_SpecialZomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_SpecialZomb[idx]->ResetPos();
							}
						}
					}

				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
					{
						m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
						m_Zomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALHEARTS; ++idx)
				{
					if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
					{
						m_PosHearts[idx] = m_PosDefaultHeart;
						m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
						if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
					}
				}
				if (m_Player->GetHealth() <= 0)
				{
					m_StateOfGame = false;
					m_StartScreen->ChangeStateOfEndScreen(true);
				}
			}
			else if (m_Timer < 30.f)
			{
				m_SpeedAsteroid = 50.f * elapsedSec;
				m_SpeedZomb = 130.f * elapsedSec;
				m_SpeedSpecialZomb = 90.f * elapsedSec;

				for (int idx{}; idx < m_TOTALSPECIALZOMBS - 1; ++idx)
				{
					m_SpecialZomb[idx]->Update(elapsedSec, m_PosPlayer, m_SpeedSpecialZomb);
					if (m_Player->IshHitZomb(m_SpecialZomb[idx]->GetBounds()))
					{
						m_Player->LoseHealth(1);
						m_SpecialZomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
				}
				for (int k{}; k < m_TOTALASTEROIDS; ++k)
				{
					m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
						m_Asteroid[k]->ResetAsteroid();
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					}
					if (m_Asteroid[k]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[k]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}


						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}

						for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
						{
							if (m_SpecialZomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_SpecialZomb[idx]->ResetPos();
							}
						}
					}

				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
					{
						m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
						m_Zomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALHEARTS; ++idx)
				{
					if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
					{
						m_PosHearts[idx] = m_PosDefaultHeart;
						m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
						if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
					}
				}
				if (m_Player->GetHealth() <= 0)
				{
					m_StateOfGame = false;
					m_StartScreen->ChangeStateOfEndScreen(true);
				}
			}
			else if (m_Timer < 40.f)
			{
				m_SpeedAsteroid = 55.f * elapsedSec;
				m_SpeedZomb = 135.f * elapsedSec;
				m_SpeedSpecialZomb = 95.f * elapsedSec;

				for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
				{
					m_SpecialZomb[idx]->Update(elapsedSec, m_PosPlayer, m_SpeedSpecialZomb);
					if (m_Player->IshHitZomb(m_SpecialZomb[idx]->GetBounds()))
					{
						m_Player->LoseHealth(1);
						m_SpecialZomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
				}
				for (int k{}; k < m_TOTALASTEROIDS; ++k)
				{
					m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
						m_Asteroid[k]->ResetAsteroid();
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					}
					if (m_Asteroid[k]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[k]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}


						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}

						for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
						{
							if (m_SpecialZomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_SpecialZomb[idx]->ResetPos();
							}
						}
					}

				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
					{
						m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
						m_Zomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALHEARTS; ++idx)
				{
					if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
					{
						m_PosHearts[idx] = m_PosDefaultHeart;
						m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
						if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
					}
				}
				if (m_Player->GetHealth() <= 0)
				{
					m_StateOfGame = false;
					m_StartScreen->ChangeStateOfEndScreen(true);
				}
			}
			else if (m_Timer < 50.f)
			{
				m_SpeedAsteroid = 60.f * elapsedSec;
				m_SpeedZomb = 140.f * elapsedSec;
				m_SpeedSpecialZomb = 100.f * elapsedSec;

				for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
				{
					m_SpecialZomb[idx]->Update(elapsedSec, m_PosPlayer, m_SpeedSpecialZomb);
					if (m_Player->IshHitZomb(m_SpecialZomb[idx]->GetBounds()))
					{
						m_Player->LoseHealth(1);
						m_SpecialZomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
				}
				for (int k{}; k < m_TOTALASTEROIDS; ++k)
				{
					m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
						m_Asteroid[k]->ResetAsteroid();
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					}
					if (m_Asteroid[k]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[k]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}


						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}

						for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
						{
							if (m_SpecialZomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_SpecialZomb[idx]->ResetPos();
							}
						}
					}

				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
					{
						m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
						m_Zomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALHEARTS; ++idx)
				{
					if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
					{
						m_PosHearts[idx] = m_PosDefaultHeart;
						m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
						if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
					}
				}
				if (m_Player->GetHealth() <= 0)
				{
					m_StateOfGame = false;
					m_StartScreen->ChangeStateOfEndScreen(true);
				}
			}
			else if (m_Timer < 60.f)
			{
				m_SpeedAsteroid = 65.f * elapsedSec;
				m_SpeedZomb = 145.f * elapsedSec;
				m_SpeedSpecialZomb = 100.f * elapsedSec;

				for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
				{
					m_SpecialZomb[idx]->Update(elapsedSec, m_PosPlayer, m_SpeedSpecialZomb);
					if (m_Player->IshHitZomb(m_SpecialZomb[idx]->GetBounds()))
					{
						m_Player->LoseHealth(1);
						m_SpecialZomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					m_Zomb[idx]->Update(elapsedSec, m_SpeedZomb, m_SpeedZomb / 2);
				}
				for (int k{}; k < m_TOTALASTEROIDS; ++k)
				{
					m_Asteroid[k]->Update(elapsedSec, m_SpeedAsteroid);
					m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					if (m_Player->IsHitAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
					{
						std::cout << m_Player->GetHealth() << std::endl;
						m_Player->LoseHealth(m_Asteroid[k]->GetDamage());
						m_Asteroid[k]->ResetAsteroid();
						m_PosAsteroid[k] = m_Asteroid[k]->GetPosition();
					}
					if (m_Asteroid[k]->GetStateOfAsteroid() == true)
					{
						if (m_Asteroid[k]->HasAHeart() == true)
						{
							m_PreviousPosAsteroid[k] = m_PosAsteroid[k];
							for (int j{}; j < m_TOTALHEARTS; ++j)
							{
								if (m_PosHearts[j].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j].y != m_PreviousPosAsteroid[k].y)
								{
									if (m_PosHearts[j].x == m_PosDefaultHeart.x && m_PosHearts[j].y == m_PosDefaultHeart.y)
									{
										if (j == 0)
										{
											if (m_PosHearts[m_TOTALHEARTS - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[m_TOTALHEARTS - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}
										else
										{
											if (m_PosHearts[j - 1].x != m_PreviousPosAsteroid[k].x && m_PosHearts[j - 1].y != m_PreviousPosAsteroid[k].y)
											{
												m_PosHearts[j].x = m_PosAsteroid[k].x;
												m_PosHearts[j].y = m_PosAsteroid[k].y;
												m_Hearts[j]->SetPosition(m_PosHearts[j]);
											}
											else return;
										}

									}


								}
							}
						}


						for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
						{
							if (m_Zomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_Zomb[idx]->ResetPos();
							}
						}

						for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
						{
							if (m_SpecialZomb[idx]->IsHitByAsteroid(m_PosAsteroid[k], m_Asteroid[k]->GetRadius(), m_Asteroid[k]->GetStateOfAsteroid()) == true)
							{
								m_SpecialZomb[idx]->ResetPos();
							}
						}
					}

				}
				for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
				{
					if (m_Player->IshHitZomb(m_Zomb[idx]->GetBounds()) == true)
					{
						m_Player->LoseHealth(m_Zomb[idx]->GetDamage());
						m_Zomb[idx]->ResetPos();
					}
				}
				for (int idx{}; idx < m_TOTALHEARTS; ++idx)
				{
					if (m_Player->IsHitHeart(m_PosHearts[idx], m_Hearts[idx]->GetRadius()))
					{
						m_PosHearts[idx] = m_PosDefaultHeart;
						m_Hearts[idx]->SetPosition(m_PosDefaultHeart);
						if (m_Player->GetHealth() < m_MaxHeatlhPlayer)m_Player->ReceiveHealth(m_Hearts[idx]->GetHealth());
					}
				}
				if (m_Player->GetHealth() <= 0)
				{
					m_StateOfGame = false;
					m_StartScreen->ChangeStateOfEndScreen(true);
				}
			}
			else if (m_Timer > 60.f)
			{
				m_StartScreen->ChangeStateOfEndScreen(true);
			}

			m_Healthbar->Update(m_Player);
		}


	}
	      m_Counter->Update(elapsedSec, m_Timer, m_StartScreen->GetStateOfEndScreen());
          m_StartScreen->Update(elapsedSec);

}

void Game::Draw( ) const
{
	ClearBackground( );
	

	if (m_StartScreen->GetStateOfStartScreen() == false)
	{
		for (int idx{}; idx < m_TOTALASTEROIDS; ++idx)
		{
			m_Asteroid[idx]->Draw();
		}




		for (int idx{}; idx < m_TOTALSPECIALZOMBS; ++idx)
		{
			m_SpecialZomb[idx]->Draw();
		}

		for (int idx{}; idx < m_TOTALZOMBIES; ++idx)
		{
			m_Zomb[idx]->Draw();
		}

		for (int idx{}; idx < m_TOTALHEARTS; ++idx)
		{
			m_Hearts[idx]->Draw();
		}



		m_Player->Draw();

		utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
		utils::FillRect(0.f, GetViewPort().height - m_HeightBar, GetViewPort().width, m_HeightBar);

		if (m_StartScreen->GetStateOfEndScreen() == false)
		{
			m_Healthbar->Draw();
			m_Counter->Draw(m_StartScreen->GetStateOfEndScreen());
		}
	}
	m_StartScreen->Draw();
	if (m_StartScreen->GetStateOfEndScreen() == true)
	{
		m_Counter->Draw(m_StartScreen->GetStateOfEndScreen());
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
	//if(e.keysym.sym == SDLK_LEFT) m_PosPlayer.x -= m_SpeedPlayer;
	//if (e.keysym.sym == SDLK_RIGHT) m_PosPlayer.x += m_SpeedPlayer;
	//if (e.keysym.sym == SDLK_UP) m_PosPlayer.y += m_SpeedPlayer;
	//if (e.keysym.sym == SDLK_DOWN) m_PosPlayer.y -= m_SpeedPlayer;
	

}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (e.keysym.sym == SDLK_SPACE)
	{
		m_StartScreen->ChangeStateOfButton();
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

