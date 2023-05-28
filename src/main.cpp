#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "box2d/box2d.h"
#include "Entity.h"

int main()
{
    const unsigned int width = 1280.0f;
    const unsigned int height = 720.0f;

    std::random_device rd;
    std::mt19937 gen(rd());

    sf::View worldView;

    worldView.setSize(width, height);
    worldView.setCenter(0, 0);

    std::cout << "INITIALIZING\n";

    b2Vec2 gravity {0.0f, 4.8f};
    b2World world {gravity};

    auto window = sf::RenderWindow{ { width, height }, "CMake SFML Project" };
    window.setFramerateLimit(144);
    window.setView(worldView);

    Entity ground{sf::Vector2f {0, 300}, sf::Vector2f {1000, 20}};
    ground.initialize(&world, b2_staticBody, 0.f, sf::Color{0, 0, 255});

    std::cout << "INITIALIZED GROUND WITH POSITION x:" << ground.position.x << ", y:" << ground.position.y << "\n";

    //entities setup
    Entity entities[50];

    for (auto& entity : entities) {
        std::uniform_real_distribution<float> randomPositionX(-300.f, 300.f);
        std::uniform_real_distribution<float> randomPositionY(-300.f, 100.f);
        std::uniform_real_distribution<float> randomSize(20.0f, 40.0f);
        std::uniform_real_distribution<float> randomAngle(0.0f, 360.f);

        entity.position = sf::Vector2f (randomPositionX(gen), randomPositionY(gen));
        entity.size = sf::Vector2f (randomSize(gen), randomSize(gen));
        entity.angle = randomAngle(gen);

        entity.initialize(&world, b2_dynamicBody, 1.f, sf::Color{255, 0, 0});
        std::cout << "INITIALIZED ENTITY WITH POSITION x:" << entity.position.x << ", y:" << entity.position.y << "\n";
    }

    sf::Clock deltaClock;
    float dt = 0.f;
    float accumulator = 0.f;
    float fixedTickRate = 1 / 60.f;

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                auto mousePos = sf::Mouse::getPosition(window);

                auto worldPos = window.mapPixelToCoords(mousePos, worldView);

                sf::Vector2f pushDirection {0.0f, 5000.0f};

                for (auto& entity : entities) {
                    if(entity.isOverlappingPoint(worldPos)) entity.push(pushDirection, worldPos);
                }
            }
        }

        ////////////////////////////////////////////////////////////////

        //Update DT
        dt = deltaClock.restart().asSeconds();
        accumulator += dt;
        while (accumulator >= fixedTickRate){
            world.Step(fixedTickRate, 6, 2);
            accumulator -= fixedTickRate;
        }

        //Update Step
        ground.update();
        for (auto& entity : entities) {
            entity.update();
        }

        //Render Step
        window.clear();

        ground.render(&window);
        for (auto& entity : entities) {
            entity.render(&window);
        }

        window.display();
    }
}