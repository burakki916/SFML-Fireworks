#include "Game.h"

sf::Vector2f startingPosition = sf::Vector2f(50, 0);
float f_theta = M_PI / 2;
float starting = 0;
float maxLevel = 3; 
std::vector<colorpair> f_trailcolors = { colorpair(sf::Color::Red,sf::Color::Transparent),colorpair(sf::Color::Green,sf::Color::Blue), colorpair(sf::Color::Magenta, sf::Color::Blue) };
std::vector<sf::Time> f_burstTimes = { sf::seconds(0),sf::seconds(1),sf::seconds(1),sf::seconds(1) };
std::vector<sf::Time> f_destroyTimes = { sf::seconds(40),sf::seconds(40),sf::seconds(40)};
std::vector<float> f_velocities = { 30,45 ,20};
std::vector<int> f_childrenVec = { 24,10,5,5,0 };

Game::Game() :
	m_window("Fireworks", sf::Vector2u(1920/1.3, 1080/1.3)), 
	myFirework(startingPosition,f_theta,starting,maxLevel,
		f_trailcolors, f_burstTimes, f_destroyTimes,f_velocities,f_childrenVec
	)
{
	//m_window.ToggleFullscreen();
	myFirework.SetBurstToPeak(); 
	myFirework.Start();

	RestartClock();
}
Game::~Game() {}

void Game::handleInput()
{

}

void Game::Update()
{
	m_window.Update(); 
	m_elapsed = m_clock.getElapsedTime(); 
	float timestep = 1.0f / 0.011;
	if (m_elapsed > sf::seconds(5)) {
		//myFirework.SetTrailColors({ sf::Color::Blue, sf::Color::Red });
	}
	myFirework.Update(); 

}

void Game::Render()
{
	m_window.BeginDraw(); //clears screen 
	myFirework.Render(&m_window); 
	m_window.EndDraw(); // display
}

Window* Game::GetWindow()
{
	return &m_window;
}

sf::Time Game::GetElapsed()
{
	return m_elapsed; 
}

void Game::RestartClock()
{
	m_elapsed = m_clock.restart(); 
}
