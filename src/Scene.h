#pragma once

#include <vector>

#include "Component.h"
#include "Object.h"

class Scene {
public:
    Scene();
    void addObject(Object* mesh);
    std::vector<Object*> getObjects() const;
    Object* getObjectByName(const std::string& name) const;
    std::vector<Object*> getAllObjectsByName(const std::string& name) const;
    std::vector<Object*> getAllObjectsByComponent(Component::Type type) const;
    Object* getAllObjectByName(const std::string& name) const;
    Object* getAllObjectByComponent(Component::Type type) const;

//private:
    void showHierarchyUI();
private:
    

    std::vector<Object*> objects;
};

