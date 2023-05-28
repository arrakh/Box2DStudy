//
// Created by Arya Rakha on 5/28/2023.
//

#ifndef CMAKESFMLPROJECT_ENTITY_H
#define CMAKESFMLPROJECT_ENTITY_H

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>


class Entity {
public:
    Entity(sf::Vector2f position, sf::Vector2f size);
    Entity(sf::Vector2f size);
    Entity();
    ~Entity();
    void initialize(b2World* world, const b2BodyType& type, const float& density, const sf::Color& color);
    bool isOverlappingPoint(sf::Vector2f point);
    void push(sf::Vector2f direction, sf::Vector2f point);
    void render(sf::RenderWindow* window);
    void update();
    sf::Vector2f position {0.f, 0.f};
    sf::Vector2f size {100.f, 100.f};
    float angle {0.f};

private:
    b2BodyDef bodyDefinition;
    b2Body* body;
    sf::RectangleShape rectShape;

};


#endif //CMAKESFMLPROJECT_ENTITY_H
