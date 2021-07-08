#include<iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <stdio.h>      
#include <stdlib.h>    
#include <time.h>   
#include <string>
#include <SFML/Audio.hpp>
#include "Game.h"
#include <algorithm>
#include<functional>
using namespace std;
int main()
{
	if (!sf::Shader::isAvailable())
	{
		std::cout << "SHADERS DONT WORK IDIOT " << std::endl; 
	}

	Game fireworks;
	
	while (!fireworks.GetWindow()->IsDone()) {
		fireworks.handleInput();
		fireworks.Update();
		fireworks.Render(); 
	}
	cin.get();
	return 0;
}