#include <SFML/Graphics.hpp>
#include "mandelbrot.h"
#include <iostream>
#include <cstdint>

int main() {
	const unsigned int width = 800;
	const unsigned int height = 600;
	const unsigned int maxIter = 100;

	sf::RenderWindow window(sf::VideoMode({ width,height }), "Madelbrot Set");

	sf::Image image;
	image.resize({ width, height });
	double minX = -2.5, maxX = 1.0;
	double minY = -1.0, maxY = 1.0;

	bool isGenerated = false;

	sf::Texture texture;
	sf::Sprite sprite(texture);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		if(!isGenerated)
		{
			for (unsigned int px = 0; px < width; px++)
			{
				for (unsigned int py =0 ; py < height; py++)
				{
					double x = minX + (static_cast<double>(px) / width) * (maxX - minX);
					double y = minY + (static_cast<double>(py) / height) * (maxY - minY);
					int iter = mandelbrot(x, y, maxIter);
					
					sf::Color color;

					if (iter == maxIter)
					{
						color = sf::Color::Black;
					}
					else
					{
						int c = (255 * iter) / maxIter;
						color = sf::Color(  static_cast<std::uint8_t>(c),
											static_cast<std::uint8_t>(c),
											static_cast<std::uint8_t>(255 - c));
					}
					image.setPixel({ px,py }, color);
				}
			}
			if (texture.loadFromImage(image)) {
				sprite.setTexture(texture, true);
				std::cout << "frattale generato con successo.\n";
				isGenerated = true;
			}
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}