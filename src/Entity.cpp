//
// Created by Arya Rakha on 5/28/2023.
//

#include <iostream>
#include "Entity.h"

const float SCALE_FACTOR = 0.01f;

void Entity::initialize(b2World *world, const b2BodyType& type, const float& density, const sf::Color& color) {
    std::cout << "Initializing with angle " << angle << "\n";

    bodyDefinition.position.Set(position.x * SCALE_FACTOR, position.y * SCALE_FACTOR);
    bodyDefinition.angle = angle * b2_pi / 180.0f;
    bodyDefinition.type = type;

    body = world->CreateBody(&bodyDefinition);

    b2FixtureDef fixtureDefinition;

    b2PolygonShape physicsShape;
    physicsShape.SetAsBox(size.x / 2.f * SCALE_FACTOR, size.y / 2.f * SCALE_FACTOR);
    fixtureDefinition.shape = &physicsShape;
    fixtureDefinition.density = density;
    fixtureDefinition.restitution = 0.6f;
    fixtureDefinition.friction = 0.3f;

    auto fixture = body->CreateFixture(&fixtureDefinition);

    rectShape.setSize(size);
    rectShape.setOrigin(size.x / 2.f, size.y / 2.f);
    rectShape.setFillColor(color);
    rectShape.setRotation(angle);
}

Entity::~Entity() {

}

void Entity::render(sf::RenderWindow *window) {
    rectShape.setPosition(position);
    rectShape.setRotation(angle);

    window->draw(rectShape);

}

void Entity::update() {
    auto physicsPos = body->GetPosition();
    position.x = physicsPos.x / SCALE_FACTOR;
    position.y = physicsPos.y / SCALE_FACTOR;
    angle = body->GetAngle() * 180.0f / b2_pi;
}

Entity::Entity(sf::Vector2f position, sf::Vector2f size) {
    this->position = position;
    this->size = size;
}

Entity::Entity(sf::Vector2f size) {
    this->size = size;
}

Entity::Entity() {

}

bool Entity::isOverlappingPoint(sf::Vector2f point) {
    return rectShape.getGlobalBounds().contains(point);
}

void Entity::push(sf::Vector2f force, sf::Vector2f point) {
    b2Vec2 pushForce {force.x * SCALE_FACTOR, force.y * SCALE_FACTOR};
    b2Vec2 pushPoint {point.x * SCALE_FACTOR, point.y * SCALE_FACTOR};
    body->ApplyForce(pushForce, pushPoint, true);
}
