// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Timber Game!!", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    Font font;
    font.loadFromFile("times-new-roman-bold-italic.ttf");

    Text instructions;
    instructions.setFont(font);
    instructions.setString("Click 3 points in the shape of a triangle, then a 4th point inside to begin.");
    instructions.setCharacterSize(28);
    instructions.setFillColor(sf::Color::Green);

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

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
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

        srand(time(0));
        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
    
            for (int i = 0; i < 500; i++)
            {
                int randNum = rand() % 3;
                Vector2f midpoint;
                //midpoint = ((x1 + x2)/2, (y1 + y2)/2)
                midpoint.x = ((vertices[randNum].x + points.back().x) / 2);
                midpoint.y = ((vertices[randNum].y + points.back().y) / 2);
                points.push_back(midpoint);
            }
    
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();

        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Green);
            window.draw(rect);
        }

        for (int i = 0; i < points.size(); i++)
        {

            
            CircleShape newPointCircle(2.5f);
            newPointCircle.setPosition(points[i]);
            newPointCircle.setFillColor(Color::Green);
            window.draw(newPointCircle);
            
        }
        window.draw(instructions);

        window.display();
    }
}