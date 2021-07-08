#pragma once
#include <ctime>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>   
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "FireworkWVec.h"
#include <cmath>
class Game
{
public:
	Game();
	~Game();
	void handleInput();
	void Update();
	void Render();
	Window* GetWindow();
	sf::Time GetElapsed();
	void RestartClock(); 
private:
	Window m_window;
	sf::Vector2f m_increment;
	sf::Clock m_clock; 
	sf::Time m_elapsed;
	FireworkWVec myFirework;
};


// make it so where setting the intiial velocity changes initVelocity