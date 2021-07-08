#include "Window.h"
Window::Window() {
	Setup("THE EPIC WINDOW", sf::Vector2u(640, 480));
}
Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}
Window::~Window() {
	Destroy();
}
void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size){
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullScreen = false; 
	m_isDone = false;


	Create(); 

}
void Window::Create() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	auto style = (m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x,m_windowSize.y,32 }, m_windowTitle, style,settings);	

}
void Window::Destroy() {
	m_window.close();
}
void Window::Update(){
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: 
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::F5:
				ToggleFullscreen();
				break;
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			case sf::Keyboard::W:
				//std::cout << "W has been pressed!" << std::endl; 
				break;
			case sf::Keyboard::F4 : 
				Destroy();
				break;
			}
			break;
		}
	}

}
void Window::ToggleFullscreen() {
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create(); 
}
void Window::BeginDraw() { m_window.clear(sf::Color(30,30,30,255)); }
void Window::EndDraw() { m_window.display(); }

bool Window::IsDone() { return m_isDone; }
bool Window::IsFullScreen() { return m_isFullScreen; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }

void Window::Draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}
void Window::BlurDraw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable); // figure out how to make it glow 
}

sf::RenderWindow* Window::GetRenderWindow()
{
	return &m_window; 
}
