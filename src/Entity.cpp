
#include "Entity.h"

using namespace Meadows;

Entity::Entity() : enabled(true) {

}

Entity::Entity(const Entity &other) : enabled(other.enabled) {

}

Entity::~Entity() {

}

void Entity::tick(float delta) {

}

void Entity::enable() {
    enabled = true;
}

void Entity::disable() {
    enabled = false;
}

void Entity::setId(std::size_t id) {
    this->id = id;
}

void Entity::setLocation(entity_location location) {
    this->location = location;
}

Entity::entity_location Entity::getLocation() {
    return location;
}

std::size_t Entity::getId() const {
    return id;
}

bool Entity::operator==(const Entity &rhs) {
    return id == rhs.id;
}
