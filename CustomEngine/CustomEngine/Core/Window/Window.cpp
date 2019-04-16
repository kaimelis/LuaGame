#include "Window.hpp"

Window::Window() 
{
	Setup("Window", sf::Vector2u(640, 480));
}

Window::Window(const std::string& pTitle, const sf::Vector2u& pSize)
	//_renderer(this)
{
	Setup(pTitle, pSize);
}

Window::~Window()
{
	Destroy();
}

void Window::Setup(const std::string& pTitle, const sf::Vector2u& pSize)
{
	_windowTitle = pTitle;
	_windowSize = pSize;
	_isFullScreen = false;
	_isDone = false;
	_isFocused = true;
	
	_eventManager.AddCallback(StateType(0), "Fullscreen_toggle", &Window::ToggleFullscreen, this);
	_eventManager.AddCallback(StateType(0), "Window_close", &Window::Close, this);

	Create();
}

void Window::Create()
{
	sf::Uint32 style = sf::Style::Default;
	if (_isFullScreen)
	{
		style = sf::Style::Fullscreen;
	}

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 4;
	settings.minorVersion = 5;

	_window.create(sf::VideoMode(_windowSize.x, _windowSize.y, 32), _windowTitle, style);
}

void Window::Destroy() 
{ 
	_window.close(); 
}

void Window::BeginDraw()
{
	_window.clear(sf::Color::Black);
	//_renderer.BeginDrawing();
}
void Window::EndDraw()
{
	_window.display();
	//_renderer.EndDrawing();
}

bool Window::isDone()
{
	return _isDone;
}
bool Window::isFullscreen()
{
	return _isFullScreen;
}
bool Window::IsFocused() 
{
	return _isFocused; 
}


sf::RenderWindow* Window::GetRenderWindow()
{
	return &_window;
}
EventManager* Window::GetEventManager()
{
	return &_eventManager;
}
sf::Vector2u Window::GetWindowSize() 
{
	return _windowSize; 
}

sf::FloatRect Window::GetViewSpace()
{
	sf::Vector2f viewCenter(_window.getView().getCenter());
	sf::Vector2f viewSize(_window.getView().getSize());
	sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
	sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
	return viewSpace;
}

void Window::ToggleFullscreen(EventDetails* pDetails)
{
	_isFullScreen = !_isFullScreen;
	_window.close();
	Create();
}

void Window::Close(EventDetails* pDetails)
{
	//_isDone = true;
	_window.close();
}

void Window::Draw(sf::Drawable&l_drawable) 
{ 
	_window.draw(l_drawable); 
}

void Window::Update() {
	sf::Event event;

	while (_window.pollEvent(event)) 
	{
		/*if (event.type == sf::Event::LostFocus)
		{
			_isFocused = false;
			_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			_isFocused = true;
			_eventManager.HandleEvent(event);
		}
		else 
		{
			_eventManager.HandleEvent(event);
		}*/

		_eventManager.HandleEvent(event);
	}
	_eventManager.Update();
}