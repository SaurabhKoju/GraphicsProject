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
    //Vec4 target = { 0.5, 0.5, 0.5 , 1};
    cam.update({ 2.5, 2.5, 2.5 }, {0.5, 0.5, 0.5});
    Vec4 light = {1.2, 0.8, 1.4};

    sf::Clock clock;
    float theta = 0;

    Vec4 oldposition{ -1, -1, 1, 1 };
    Vec4 cubecentre{ 0.5, 0.5, 0.5 };


    while (window.isOpen())
    {
        sf::Event event;

        sf::Time elapsed = clock.getElapsedTime();
        float t = elapsed.asSeconds();
        clock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                    cam.ZoomIn(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                    cam.ZoomOut(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    cam.moveLeft(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    cam.moveRight(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    cam.moveUp(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    cam.moveDown(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
                    theta += 1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
                    theta -= 1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                    light[0] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::O))
                    light[0] -= 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J))
                    light[1] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
                    light[1] -= 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
                    light[2] += 0.1;
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                    light[2] -= 0.1;
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    oldposition = { -1, -1, 1, 1 };
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
                Vec4 newposition{ mouseposition.x, mouseposition.y, 1, 1};

                Mat4 T = screentoPort(cam);

                if (oldposition[0] == -1 )oldposition = newposition;
                if (oldposition == newposition)continue;

                Vec4 world_oldposition = T * oldposition;
                Vec4 world_newposition = T * newposition;

                float angle = acosf(dot(normalize(world_oldposition - cubecentre), normalize(world_newposition - cubecentre)));

                Vec4 axis = (world_oldposition - cubecentre) * (world_newposition - cubecentre);

                Mat4 X = getRotationMatrix(cubecentre, cubecentre + axis, angle*180/pi*2.5); //2.5 rotation factor or something
                Cube.transform(X);
                oldposition = newposition;
            }
        }
        window.clear(sf::Color::Black);

        // draw everything here...
        Mat4 T = getRotationMatrix(cam.target, cam.position, 5 * theta);
        //T = getRotationMatrix(cubecentre, cubecentre + Vec4{ 1, 0, 0, 0 }, 5 * theta);
        Cube.transform(T);

        draw(Cube, window, cam, light);
        //std::cout << "(" << light[0] << ", " << light[1] << ", " << light[2] << ")" << std::endl;

        // end the current frame
        window.display();
    }
    




    return 0;
}
