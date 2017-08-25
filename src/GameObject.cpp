
#include "GameObject.h"

using namespace Meadows;

GameObject::GameObject() : enabled(true) {

}

GameObject::GameObject(const GameObject &other) : enabled(other.enabled) {

}

GameObject::~GameObject() {

}

void GameObject::tick(float delta) {

}

void GameObject::enable() {
    enabled = true;
}

void GameObject::disable() {
    enabled = false;
}

void GameObject::setId(std::size_t id) {
    this->id = id;
}

std::size_t GameObject::getId() const {
    return id;
}

bool GameObject::operator==(const GameObject &rhs) {
    return id == rhs.id;
}
