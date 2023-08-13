#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>

int main()
{
	plog::init(plog::verbose, "Log.txt");
	PLOG(plog::info) << "Starting log file.";

	// Create a window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Export to PNG");

	// Create a texture and a sprite
	sf::RenderTexture renderTexture;
	renderTexture.create(window.getSize().x, window.getSize().y);
	sf::Sprite sprite(renderTexture.getTexture());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Clear the render texture
		renderTexture.clear(sf::Color::White);

		// Draw something to the render texture
		sf::CircleShape circle(50);
		circle.setFillColor(sf::Color::Blue);
		circle.setPosition(375, 275);
		renderTexture.draw(circle);

		// Display the contents of the render texture on the window
		renderTexture.display();

		// Export the render texture as a PNG image
		sf::Image screenshot = renderTexture.getTexture().copyToImage();
		if (screenshot.saveToFile("screenshot.png")) {
			std::cout << "Screenshot saved as 'screenshot.png'" << std::endl;
		}
		else {
			std::cout << "Failed to save screenshot" << std::endl;
		}

		// Clear the window and draw the sprite
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}