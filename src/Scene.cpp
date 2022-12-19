
#include <vector>
#include <string>

#include "Scene.h"
#include "Object.h"
#include "Logger.h"
#include "UI.h"

using namespace std;

Scene::Scene() {

}

void Scene::addObject(Object* object) {
    objects.push_back(object);
}

vector<Object*> Scene::getObjects() const {
    return objects;
}

Object* Scene::getObjectByName(const std::string& name) const {
    for (Object* object : objects) {
        if (object->getName() == name) {
            return object;
        }
    }
    return nullptr;
}

vector<Object*> Scene::getAllObjectsByName(const std::string& name) const {
    vector<Object*> result;
    for (Object* object : objects) {
        if (object->getName() == name) {
            result.push_back(object);
        }
        object->getAllChildrenByName(result, name);
    }
    return result;
}

std::vector<Object*> Scene::getAllObjectsByComponent(Component::Type type) const {
    vector<Object*> result;
    for (Object* object : objects) {
        if (object->haveComponent(type)) {
            result.push_back(object);
        }
        object->getAllChildrenByComponent(result, type);
    }
    return result;
}

Object* Scene::getAllObjectByName(const std::string& name) const {
    for (Object* object : objects) {
        if (object->getName() == name) {
            return object;
        }
        Object* tmp = object->getAllChildByName(name);
        if (tmp != nullptr) return tmp;
    }
    return nullptr;
}

Object* Scene::getAllObjectByComponent(Component::Type type) const {
    for (Object* object : objects) {
        if (object->haveComponent(type)) {
            return object;
        }
        Object* tmp = object->getAllChildByComponent(type);
        if (tmp != nullptr) return tmp;
    }
    return nullptr;
}

void Scene::showHierarchyUI() {
    static bool v[4];
    UI::begin("Hierarchy");
    for (Object* object : objects) {
        object->showHierarchyUI(0);
    }
    UI::end();
}