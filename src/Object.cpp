#include "Object.h"
#include "Math.h"
#include "Logger.h"
#include "UI.h"

using namespace std;
using namespace Eigen;

Object::Object(Object* parent, const string& name) {
    this->name = name;
    this->position = WPos(0, 0, 0);
    this->rotation = WPos(0, 0, 0);
    this->scale = WPos(1, 1, 1);
    this->parent = parent;
    showChildren = false;
}

Object::Object(Object* parent, const string& name, WPos pos) {
    this->name = name;
    this->position = pos;
    this->rotation = WPos(0, 0, 0);
    this->scale = WPos(1, 1, 1);
    this->parent = parent;
    showChildren = false;
}

Object* Object::getParent() const {
    return parent;
}

void Object::setName(const string& name) {
    this->name = name;
}

void Object::setPosition(WPos pos) {
    this->position = pos;
}

string Object::getName() const {
    return name;
}

WPos Object::getPosition() const {
    return position;
}
void Object::addComponent(Component* component) {
    components.push_back(component);
}

void Object::addChild(Object* child) {
    children.push_back(child);
}

int Object::getChildrenSize() const {
    return children.size();
}

int Object::getComponentSize() const {
    return components.size();
}

bool Object::haveComponent(Component::Type type) const {
    for (Component* component : components) {
        if (component->getType() == type) {
            return true;
        }
    }
    return false;
}

Matrix4f Object::getModel() const {
    return Math::getTranslation(position);
}

Component* Object::getComponentByType(Component::Type type) const {
    for (Component* component : components) {
        if (component->getType() == type) {
            return component;
        }
    }
    return nullptr;
}

vector<Component*> Object::getComponentsByType(Component::Type type) const {
    vector<Component*> result;
    for (Component* component : components) {
        if (component->getType() == type) {
            result.push_back(component);
        }
    }
    return result;
}

Object* Object::getChildByName(const std::string& name) const {
    for (Object* child : children) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}

Object* Object::getChildByComponent(Component::Type type) const {
    for (Object* child : children) {
        if (child->haveComponent(type)) {
            return child;
        }
    }
    return nullptr;
}

Object* Object::getAllChildByName(const std::string& name) const {
    for (Object* child : children) {
        if (child->getName() == name) {
            return child;
        }
        Object* tmp = child->getAllChildByName(name);
        if (tmp != nullptr) return tmp;
    }
    return nullptr;
}

Object* Object::getAllChildByComponent(Component::Type type) const {
    for (Object* child : children) {
        if (child->haveComponent(type)) {
            return child;
        }
        Object* tmp = child->getAllChildByComponent(type);
        if (tmp != nullptr) return tmp;
    }
    return nullptr;
}

vector<Object*> Object::getChildrenByName(const std::string& name) const {
    vector<Object*> result;
    for (Object* child : children) {
        if (child->getName() == name) {
            result.push_back(child);
        }
    }
    return result;
}

std::vector<Object*> Object::getChildrenByComponent(Component::Type type) const {
    vector<Object*> result;
    for (Object* child : children) {
        if (child->haveComponent(type)) {
            result.push_back(child);
        }
    }
    return result;
}

std::vector<Object*> Object::getAllChildrenByComponent(Component::Type type) const {
    vector<Object*> result;
    for (Object* child : children) {
        if (child->haveComponent(type)) {
            result.push_back(child);
        }
    }
    return result;
}

vector<Object*> Object::getAllChildrenByName(const std::string& name) const {
    vector<Object*> result;
    for (Object* child : children) {
        if (child->getName() == name) {
            result.push_back(child);
        }
        child->getAllChildrenByName(result, name);
    }
    return result;
}

void Object::getAllChildrenByName(std::vector<Object*>& result, const std::string& name) const {
    for (Object* child : children) {
        if (child->getName() == name) {
            result.push_back(child);
        }
        child->getAllChildrenByName(result, name);
    }
}

void Object::getAllChildrenByComponent(std::vector<Object*>& result, Component::Type type) const {
    for (Object* child : children) {
        if (child->haveComponent(type)) {
            result.push_back(child);
        }
        child->getAllChildrenByComponent(result, type);
    }
}

void Object::showHierarchyUI(int depth) {
    if (depth > 0) {
        char buffer[32];
        for (int i = 0; i < depth * 2; i++) buffer[i] = ' ';
        buffer[depth * 2] = '\0';
        UI::text(buffer);
        UI::sameLine();
    }
    UI::textWrapped(showChildren ? "[#]" : "[ ]");
    if (UI::isItemClicked()) {
        showChildren ^= 1;
    }
    UI::sameLine();
    UI::text(name);
    if (UI::isItemClicked()) {
        UI::whichObjectDisplayComponent(this);
    }
    if (showChildren) {
        for (Object* child : children) {
            child->showHierarchyUI(depth + 1);
        }
    }
}

void Object::showComponentUI() {
    static char buffer[64];
    UI::begin(name + "'s components");
    sprintf(buffer, "%s", name.c_str());
    ImGui::InputText("name", buffer, 64);
    if (!ImGui::IsItemHovered()) 
        setName(buffer);

    UI::inputWPos("position", &position);
    UI::sliderWPos("rotation", &rotation, -360, 360);
    UI::inputWPos("scale", &scale);

    for (Component* component : components) {
        component->showUI();
    }
    UI::end();
}