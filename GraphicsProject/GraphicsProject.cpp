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

    Cube.triangles[0].fillColor = sf::Color::Green; Cube.triangles[1].fillColor = sf::Color::Green;
    Cube.triangles[2].fillColor = sf::Color::Blue; Cube.triangles[3].fillColor = sf::Color::Blue;
    Cube.triangles[4].fillColor = sf::Color::Yellow; Cube.triangles[5].fillColor = sf::Color::Yellow;
    Cube.triangles[6].fillColor = sf::Color::White; Cube.triangles[7].fillColor = sf::Color::White;
    Cube.triangles[8].fillColor = sf::Color(255, 87, 51); Cube.triangles[9].fillColor = sf::Color(255, 87, 51);
    Cube.triangles[10].fillColor = sf::Color::Red; Cube.triangles[11].fillColor = sf::Color::Red;



    Camera cam;
    Vec4 target = { 0.5, 0.5, 0.5 , 1};
    cam.update({ 2.5, 2.5, 2.5 }, {0.5, 0.5, 0.5});
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
        Mat4 T = getRotationMatrix(Vec3{ 0.5, 0.5, 0.5 }, Vec3{ 4, 6, 9}, 180 * t);
        
        
        Cube.transform(T);        
        draw(Cube, window, cam);

        // end the current frame
        window.display();
    }



    return 0;
}