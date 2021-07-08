#pragma once
#include <iostream>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
# define M_PI           3.14159265358979323846  /* pi */
# define M_G			9.8
class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();

	void BeginDraw(); // clears the window
	void EndDraw(); // display the changes 

	void Update();

	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();

	void ToggleFullscreen();
	void Draw(sf::Drawable& l_drawable);
	void BlurDraw(sf::Drawable& l_drawable);
	//void Draw(sf::Drawable& l_drawable,sf::Shader& shader);
	sf::RenderWindow* GetRenderWindow(); 
	//sf::Event::EventType poll();
	//sf::Event CurrentEvent; 
	
private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen; 

};
