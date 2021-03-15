#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
const int Width = 280;
const int Height = 280;
int const cols = 280;
int const rows = 280;

int main()
{
	sf::RenderWindow window(sf::VideoMode(Width, Height), "2D Water Ripple");
	window.setFramerateLimit(80);

	float current [cols][rows];
	float previous [cols][rows];
	float temp[cols][rows];
                     
	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {
			current[i][j] = 0;
			previous[i][j] = 0;
			temp[i][j] = 0;
		}
	}
	
	float dampening = 0.9;

	sf::Uint8* pixels = new sf::Uint8[Width * Height * 4];
	sf::Texture texture;
	texture.create(Width, Height);
	sf::Sprite sprite(texture); // needed to draw the texture on screen

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mousepos = sf::Mouse::getPosition(window);
				cout << "X: " << mousepos.x << endl;
				cout << "Y: " << mousepos.y << endl;
				current[mousepos.x][mousepos.y] = 255;
			}
		}

		for (int x = 1; x < cols-1; x++) {
			for (int y = 1; y < rows-1; y++) {

				current[x][y] = (
					previous[x - 1][y] +
					previous[x + 1][y] +
					previous[x][y - 1] +
					previous[x][y + 1]) / 2 -
					current[x][y];

				current[x][y] = current[x][y] * dampening;

				int index = (x + y * cols)*4;
				pixels[index] = current[x][y]*100;
				pixels[index + 1] = current[x][y]*100;
				pixels[index + 2] = current[x][y]*255;

			}
		}

		for (int i = 0; i < cols; i++) {
			for (int j = 0; j < rows; j++) {
				temp[i][j] = previous[i][j];
				previous[i][j] = current[i][j];
				current[i][j] = temp[i][j];
			}
		}

	    texture.update(pixels);
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}

	return 0;
}