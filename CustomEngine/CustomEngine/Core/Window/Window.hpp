#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"../EventSystem/EventManager.hpp"

class Window
{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void BeginDraw();
	void EndDraw();

	void Update();
	
	void ToggleFullscreen(EventDetails* pDetails);
	void Close(EventDetails* l_details = nullptr);

	bool isDone() ;
	bool isFullscreen() ;
	bool IsFocused();

	EventManager* GetEventManager();

	sf::RenderWindow* GetRenderWindow();
	sf::Vector2u GetWindowSize();
	sf::FloatRect GetViewSpace();
	void Draw(sf::Drawable&l_drawable);

private:
	void Setup(const std::string& pTitle, const sf::Vector2u& pSize);
	void Create();
	void Destroy();

	sf::RenderWindow _window;
	sf::Vector2u _windowSize;
	std::string _windowTitle;

	EventManager _eventManager;

	bool _isFocused;
	bool _isDone;
	bool _isFullScreen;
		 
};

#endif