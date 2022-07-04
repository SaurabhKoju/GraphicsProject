#include <SFML/Graphics.hpp>
#include "GMath.h"
#include "Projection.h"
#include "Draw.h"
#include "Camera.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "My window");

    mesh Cube{ { 
                {{1, -0.5, 2, 1}, {1, 0.5, 2, 1}, {2, -0.5, 2, 1}}, {{2, 0.5, 2, 1}, {1, 0.5, 2, 1}, {2, -0.5, 2, 1}},
                {{1, -0.5, 3, 1}, {1, 0.5, 3, 1}, {2, -0.5, 3, 1}}, {{2, 0.5, 3, 1}, {1, 0.5, 3, 1}, {2, -0.5, 3, 1}},
                {{1, -0.5, 2, 1}, {1, -0.5, 3, 1}, {1, 0.5, 3, 1}}, {{1, 0.5, 2, 1}, {1, -0.5, 2, 1}, {1, 0.5, 3, 1}},
                {{2, -0.5, 2, 1}, {2, -0.5, 3, 1}, {2, 0.5, 3, 1}}, {{2, 0.5, 2, 1}, {2, -0.5, 2, 1}, {2, 0.5, 3, 1}},
                {{1, -0.5, 2, 1}, {2, -0.5, 2, 1}, {2, -0.5, 3, 1}}, {{1, -0.5, 2, 1}, {1, -0.5, 3, 1}, {2, -0.5, 3, 1}},
                {{1, 0.5, 2, 1}, {2, 0.5, 2, 1}, {2, 0.5, 3, 1}}, {{1, 0.5, 2, 1}, {1, 0.5, 3, 1}, {2, 0.5, 3, 1}}
        } };

    Camera cam;
    cam.update({ 0, 0, 0 }, {0, -1, 1});

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
        draw(Cube, window, cam);

        // end the current frame
        window.display();
    }
    return 0;
}