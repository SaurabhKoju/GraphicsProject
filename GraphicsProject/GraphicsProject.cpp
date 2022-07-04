#include <SFML/Graphics.hpp>
#include "GMath.h"
#include "Projection.h"
#include "Draw.h"
#include "Camera.h"
#include "Primitives.h"
#include <iostream>


int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Cube");
    window.setFramerateLimit(60);

    mesh Cube{ { 
                {{0, 0, 0, 1}, {1, 0, 0, 1}, {1, 0, 1, 1}}, {{0, 0, 1, 1}, {0, 0, 0, 1}, {1, 0, 1, 1}},
                {{0, 1, 0, 1}, {1, 1, 1, 1}, {1, 1, 0, 1}}, {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 0, 1}},
                {{1, 0, 1, 1}, {1, 1, 0, 1}, {1, 1, 1, 1}}, {{1, 0, 1, 1}, {1, 0, 0, 1}, {1, 1, 0, 1}},
                {{0, 0, 1, 1}, {0, 1, 1, 1}, {0, 1, 0, 1}}, {{0, 0, 1, 1}, {0, 1, 0, 1}, {0, 0, 0, 1}},
                {{0, 0, 0, 1}, {1, 1, 0, 1}, {1, 0, 0, 1}}, {{0, 0, 0, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}},
                {{0, 0, 1, 1}, {1, 0, 1, 1}, {1, 1, 1, 1}}, {{0, 0, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}}
        } };

    Camera cam;
    cam.update({ 2, 1.5, 3 }, {0.5, 0.5, 0.5});
    //Cube.transform(rotateAboutZ(120));

    sf::Clock clock;

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
        sf::Time elapsed = clock.getElapsedTime();
        float t = elapsed.asSeconds();
        clock.restart();
        Mat4 T = getRotationMatrix(Vec3{ 0.5, 0.5, 0.5 }, Vec3{ 0.5, 0, 0.5 }, 180 * t);
        Cube.transform(T);
        //Cube.transform(rotateAboutY(90 * t));
        draw(Cube, window, cam);

        // end the current frame
        window.display();
    }



    return 0;
}