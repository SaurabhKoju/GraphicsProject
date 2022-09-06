#include <SFML/Graphics.hpp>
#include "GMath.h"
#include "Projection.h"
#include "Draw.h"
#include "Camera.h"
#include "Primitives.h"
#include "ObjectLoader.h"
#include <iostream>
const float INF = 1000000000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Cube");
    window.setFramerateLimit(60);

    std::vector<mesh >Cube;
    Cube = LoadObject("simple2.mtl", "simple2.obj");

    Camera cam;
    cam.update({ 7, 7, 7, 1 }, {0, 0, 0, 1});

    Vec4 light = {4.5, 4.5, 6.5, 1};
    Vec4 oldposition{ -1, -1, 1, 1 };
    Vec4 cubecentre{ 0, 0, 0 };

    sf::Clock clock;
    float theta = 0;

    sf::CircleShape circle;
    circle.setRadius(5);
    circle.setFillColor(sf::Color(255, 255, 187));
    Vec4 lightOrigin = worldtoScreen(cam, light);
    circle.setOrigin(sf::Vector2f(2.5, 2.5));
    circle.setPosition(sf::Vector2f(lightOrigin[0], lightOrigin[1]));
    std::vector<std::vector<float> > zbuffer(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH, INF));
    std::vector<std::vector<Vec4> > nbuffer(SCREEN_HEIGHT, std::vector<Vec4>(SCREEN_WIDTH, Zero4));
    Vec4 normal;
    std::vector<bool> transform_cubes(Cube.size(), false);
    bool rotating = false;
    bool leftRotate = true;
    float angle = 0;

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
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    cam.moveLeft(t);
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                    cam.moveRight(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    cam.rotateLeft(t);
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    cam.rotateRight(t);
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
            else if (event.type == sf::Event::MouseButtonPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !rotating) {
                sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
                int i = mouseposition.x;
                int j = mouseposition.y;
                if (i < 0 || i >= SCREEN_WIDTH || j < 0 || j >= SCREEN_HEIGHT)continue;
                normal = nbuffer[j][i];
                if (event.mouseButton.button == sf::Mouse::Left) {
                    leftRotate = true;
                }
                else {
                    leftRotate = false;
                }
                if (zbuffer[j][i] > 1 && zbuffer[j][i] < INF) {
                    for (int k = 0; k<Cube.size(); k++) {
                        bool flag = false;
                        for (triangle t : Cube[k].triangles) {
                            Vec4 v1 = t.p1 - t.p0;
                            Vec4 v2 = t.p2 - t.p0;
                            Vec4 cross_product = v1 * v2;
                            if (magnitude(normal - normalize(cross_product)) < 0.05 && t.mtl.name != "Material.001") {
                                flag = true;
                                rotating = true;
                                break;
                            }
                        }
                        transform_cubes[k] = flag;
                    }
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !rotating) {
                sf::Vector2i mouseposition = sf::Mouse::getPosition(window);
                Vec4 newposition{ mouseposition.x, mouseposition.y, 1, 1};

                Mat4 T = screentoWindow(cam);

                if (oldposition[0] == -1 )oldposition = newposition;
                if (oldposition == newposition)continue;

                Vec4 world_oldposition = T * oldposition;
                Vec4 world_newposition = T * newposition;

                float angle = magnitude(oldposition - newposition) * 0.2;
                Vec4 axis = (world_oldposition - cubecentre) * (world_newposition - cubecentre);

                Mat4 X = getRotationMatrix(cubecentre, axis, angle);
                for(mesh &m:Cube)
                    m.transform(X);
                oldposition = newposition;
            }
        }
        window.clear(sf::Color(50, 50, 50));

        // draw everything here...

        Mat4 T = getRotationMatrix(cubecentre, Vec4{1, 0, 0, 0}, 5 * theta);
        for(mesh &m:Cube)
            m.transform(T);


        if (rotating) {
            float rotate_angle = 90;
            if (!leftRotate)rotate_angle = -90;
            float rotate_time = 0.5;
            float speed = rotate_angle/rotate_time;
            Mat4 T;
            angle += speed * t;
            if (abs(angle) > 90){
                angle -= speed * t;
                T = getRotationMatrix(cubecentre, normal, rotate_angle - angle);
                angle = 0;
                rotating = false;
            }
            else T = getRotationMatrix(cubecentre, normal, speed * t);
            for (int i = 0; i < Cube.size(); i++) {
                if (transform_cubes[i]) {
                    Cube[i].transform(T);
                }
            }
        }


        zbuffer = std::vector<std::vector<float> >(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH, INF));
        nbuffer = std::vector<std::vector<Vec4> >(SCREEN_HEIGHT, std::vector<Vec4>(SCREEN_WIDTH, Zero4));
        for(mesh m:Cube)
            draw(m, window, cam, light, zbuffer, nbuffer);

        Vec4 lightOrigin = worldtoScreen(cam, light);
        circle.setPosition(sf::Vector2f(lightOrigin[0], lightOrigin[1]));
        window.draw(circle);
        //light.display();
        //cam.position.display();

        // end the current frame
        window.display();
    }

    return 0;
}
