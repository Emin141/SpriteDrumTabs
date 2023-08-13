#pragma once

#include "Globals.h"

#include <functional>

#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>

BEGIN_SDT_NAMESPACE
class Application
{
	using json = nlohmann::json;

	using KeyboardCallbackMap = std::map<sf::Keyboard::Key, std::vector<std::function<void()>>>;
	using MouseButtonCallbackMap = std::map<sf::Mouse::Button, std::vector<std::function<void()>>>;

public:
	//Public functions. Should be used sparingly.
	~Application();

	//Deleted constructors.
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;
	
	static void Run();

private:
	//Forces the use of Run().
	Application() = default;

	//Init related functions.
	void Init();
	void InitLogging();
	void LoadConfigFile();
	void SetupInputCallbacks();
	void LoadAssets();
	void Update();

	//Input callback convenience functions.
	void InvokeCallbacks(sf::Keyboard::Key inputKey, KeyboardCallbackMap callbacksMap) const;
	void InvokeCallbacks(sf::Mouse::Button inputMouseButton, MouseButtonCallbackMap callbacksMap) const;

	//Fields.
	sf::RenderWindow _renderWindow{ sf::VideoMode(800, 600), "Sprite drum tabs" + GetVersionString() };

	nlohmann::json _configFile;

	//Callback maps.
	KeyboardCallbackMap _keyPressedCallbackMap;
	KeyboardCallbackMap _keyReleasedCallbackMap;
	MouseButtonCallbackMap _mouseButtonPressedCallbackMap;
	MouseButtonCallbackMap _mouseButtonReleasedCallbackMap;

	//Drawing related.
	
};
END_SDT_NAMESPACE