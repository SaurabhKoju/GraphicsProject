#include <SFML/Graphics.hpp>
#include "GMath.h"
#include "Projection.h"
#include "Draw.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    mesh Cube{ { 
                {{1, -0.5, 2}, {1, 0.5, 2}, {2, -0.5, 2}}, {{2, 0.5, 2}, {1, 0.5, 2}, {2, -0.5, 2}},
                {{1, -0.5, 3}, {1, 0.5, 3}, {2, -0.5, 3}}, {{2, 0.5, 3}, {1, 0.5, 3}, {2, -0.5, 3}},
                {{1, -0.5, 2}, {1, -0.5, 3}, {1, 0.5, 3}}, {{1, 0.5, 2}, {1, -0.5, 2}, {1, 0.5, 3}},
                {{2, -0.5, 2}, {2, -0.5, 3}, {2, 0.5, 3}}, {{2, 0.5, 2}, {2, -0.5, 2}, {2, 0.5, 3}},
                {{1, -0.5, 2}, {2, -0.5, 2}, {2, -0.5, 3}}, {{1, -0.5, 2}, {1, -0.5, 3}, {2, -0.5, 3}},
                {{1, 0.5, 2}, {2, 0.5, 2}, {2, 0.5, 3}}, {{1, 0.5, 2}, {1, 0.5, 3}, {2, 0.5, 3}}
        } };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        // draw everything here...
        draw(Cube, window);

        // end the current frame
        window.display();
    }
    return 0;
}