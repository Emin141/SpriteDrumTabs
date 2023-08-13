#include "Application.h"
#include "Globals.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

sdt::Application::~Application()
{
	PLOG(plog::info) << "Closed log file.";
}

/*static */ void sdt::Application::Run()
{
	plog::init(plog::verbose, "Log.txt");
	PLOG(plog::info) << "Created and started log file.";

	//Forces only one application to exist.
	static Application applicationSingleton;
	applicationSingleton.Init();
	applicationSingleton.Update();
}

void sdt::Application::Init()
{
	LoadConfigFile();
	SetupInputCallbacks();
	LoadAssets();
}

void sdt::Application::LoadConfigFile()
{
	try
	{
		std::ifstream configFileInput("Config.json");
		if (configFileInput.is_open() == false) 
		{
			throw std::string("Could not open \"Config.json\". Does the file exist in the executable directory?");
		} 

		_configFile = json::parse(configFileInput);
	}
	catch (const std::string& exception)
	{
		PLOG(plog::error) << exception;
		PLOG(plog::error) << "No initialization will be done. The program will not work as intended.";
	}
}

void sdt::Application::SetupInputCallbacks()
{
	for (int32_t keyToBindAsInt = -1; keyToBindAsInt < int32_t(sf::Keyboard::KeyCount); keyToBindAsInt++)
	{
		_keyPressedCallbackMap.emplace(sf::Keyboard::Key(keyToBindAsInt), std::vector<std::function<void()>>());
		_keyReleasedCallbackMap.emplace(sf::Keyboard::Key(keyToBindAsInt), std::vector<std::function<void()>>());
	}

	_mouseButtonPressedCallbackMap.emplace(sf::Mouse::Button::Left, std::vector<std::function<void()>>());
	_mouseButtonReleasedCallbackMap.emplace(sf::Mouse::Button::Left, std::vector<std::function<void()>>());

	PLOG(plog::info) << "Custom keybindings as shortcuts for drum kit piece selection are not supported yet.";
}

void sdt::Application::LoadAssets()
{
	UNIMPLEMENTED
}

void sdt::Application::Update()
{
	while (_renderWindow.isOpen())
	{
		sf::Event inputEvent;
		while (_renderWindow.pollEvent(inputEvent))
		{
			switch (inputEvent.type)
			{
				case sf::Event::Closed:
					_renderWindow.close();
					break;

				case sf::Event::KeyPressed:
					InvokeCallbacks(inputEvent.key.code, _keyPressedCallbackMap);
					break;

				case sf::Event::KeyReleased:
					InvokeCallbacks(inputEvent.key.code, _keyReleasedCallbackMap);
					break;

				case sf::Event::MouseButtonPressed:
					InvokeCallbacks(inputEvent.mouseButton.button, _mouseButtonPressedCallbackMap);
					break;

				case sf::Event::MouseButtonReleased:
					InvokeCallbacks(inputEvent.mouseButton.button, _mouseButtonReleasedCallbackMap);
					break;

				default:
					break;
			}
		}

		//Clear the window.
		_renderWindow.clear(sf::Color::White);
		
		//Draw all.
		UNIMPLEMENTED

		//Swap buffers.
		_renderWindow.display();
	}
}

void sdt::Application::InvokeCallbacks(sf::Keyboard::Key inputKey, KeyboardCallbackMap callbacksMap) const
{
	try
	{
		const auto& callbackList = callbacksMap.at(inputKey);
		for (const auto& callback : callbackList)
		{
			std::invoke(callback);
		}
	}
	catch (std::out_of_range&)
	{
		PLOG(plog::warning) << "Attempted to invoke a callback list for key " << inputKey << " but the key was not bound.";
	}
}

void sdt::Application::InvokeCallbacks(sf::Mouse::Button inputMouseButton, MouseButtonCallbackMap callbacksMap) const
{
	try
	{
		const auto& callbackList = callbacksMap.at(inputMouseButton);
		for (const auto& callback : callbackList)
		{
			std::invoke(callback);
		}
	}
	catch (std::out_of_range&)
	{
		PLOG(plog::warning) << "Attempted to invoke a callback list for mouse button " << inputMouseButton << " but the mouse button was not bound.";
	}
}
