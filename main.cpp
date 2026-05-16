// Chaos Game Project
// Yan Filiniuk
// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime> 

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	////// Load a font to show instructions
	Font font;
	font.loadFromFile("tuffy.ttf");

	// tell the user what to do
	Text message;
	message.setFont(font);
	message.setCharacterSize(22);
	message.setFillColor(Color::White);
	message.setPosition(25, 25);

	srand(time(0)); //Start random number generator

	while (window.isOpen())
	{
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			///generate more point(s)
			for (int i = 0; i < 50; i++)
			{
				///select random vertex
				int randomIndex = rand() % 3;
				Vector2f lastPoint = points[points.size() - 1]; // last point
				Vector2f randomVertex = vertices[randomIndex]; // get the random vertex

				///calculate midpoint between random vertex and the last point in the vector
				float newX = (lastPoint.x + randomVertex.x) / 2;
				float newY = (lastPoint.y + randomVertex.y) / 2;

				///push back the newly generated coord.
				points.push_back(Vector2f(newX, newY));
			}
		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		if (vertices.size() < 3)
		{
			message.setString("Click 3 points to create the triangle");
		}
		else if (points.size() == 0)
		{
			message.setString("Click one more point to start the Chaos Game");
		}
		else
		{
			message.setString("Chaos Game running: Sierpinski Triangle");
		}

		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(10, 10));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}
		///Draw points
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape point(Vector2f(2, 2));
			point.setPosition(points[i]);
			point.setFillColor(Color::White);
			window.draw(point);
		}
		window.draw(message);
		window.display();
	}
}