#include "game_object.hpp"
#include "components/transform.hpp"
#include <stdexcept>
#include <algorithm>
#include <vector>

GameObject::GameObject() : GameObject(nullptr) {};

GameObject::GameObject(GameObject* parent_c) : parent(parent_c) {
    if (parent != nullptr) {
        parent->children.push_back(std::unique_ptr<GameObject>(this));
    }
    transform = new Transform(this);
}

void update_rec(GameObject* cur) {
    for (std::unique_ptr<GameObject>& go : cur->children) {
        update_rec(go.get());
    }

    for (std::unique_ptr<Component>& cmp : cur->components) {
        cmp->update();
    }
}

void GameObject::update() {
    update_rec(this);
}

void GameObject::remove_cmp(Component* cmp) {
    if (transform == cmp) {
        throw std::runtime_error{ "Cannot remove Transform component!" };
    }

    auto is_eq = [cmp](std::unique_ptr<Component>& icmp)
        { return icmp.get() == cmp; };
    auto const& i{ std::find_if(components.begin(), components.end(), is_eq) };
    components.erase(i);
}

GameObject::~GameObject() {
    for (std::unique_ptr<GameObject>& go : children) {
        go.reset();
    }

    for (std::unique_ptr<Component>& cmp : components) {
        cmp.reset();
    }
}

Component::Component(GameObject* go_c) : go(go_c) {
    go->components.push_back(std::unique_ptr<Component>{this});
}