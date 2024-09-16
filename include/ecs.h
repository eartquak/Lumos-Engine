#pragma once

#include "entt/entt.hpp"
#include "gl_stuff.h"
#include "glm/glm.hpp"

class ecs {
public:
    template<typename...T> entt::entity createEntity(Position pos, T&...components);
    template<typename T> void addComponent(entt::entity entity, T component);
    template<typename T> T& get(entt::entity entity);
    
    entt::registry reg;
    ecs();
};

template<typename T>
void ecs::addComponent(entt::entity entity, T component) {
    this->reg.emplace<T>(entity, component); 
}

template<typename...T>
entt::entity ecs::createEntity(Position pos, T&...components) {
    entt::entity entity = this->reg.create();
    this->reg.emplace<Position>(entity, pos);
    (this->addComponent(entity, components), ...);
    return entity;
}

template<typename T>
T& ecs::get(entt::entity entity) {
    return this->reg.get<T>(entity);
}
