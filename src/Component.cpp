#include "Component.h"

Component::Component(Component::Type type, Object* parent) {
    this->type = type;
    this->parent = parent;
}

Component::Type Component::getType() const {
    return type;
}

Object* Component::getParent() const {
    return parent;
}