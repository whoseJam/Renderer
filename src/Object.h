#pragma once

#include <string>
#include <vector>

#include "Extern.h"
#include "Define.h"
#include "Component.h"

class Scene;

class Object {
public:
    Object(Object* parent, const std::string& name);
    Object(Object* parent, const std::string& name, WPos pos);
    void setName(const std::string& name);
    std::string getName() const;
    Object* getParent() const;
    void setPosition(WPos pos);
    WPos getPosition() const;
    void addComponent(Component* component);
    void addChild(Object* child);
    int getChildrenSize() const;
    int getComponentSize() const;
    bool haveComponent(Component::Type type) const;
    Component* getComponentByType(Component::Type type) const;
    std::vector<Component*> getComponentsByType(Component::Type type) const;
    Object* getChildByName(const std::string& name) const;
    Object* getChildByComponent(Component::Type type) const;
    Object* getAllChildByName(const std::string& name) const;
    Object* getAllChildByComponent(Component::Type type) const;
    std::vector<Object*> getChildrenByName(const std::string& name) const;
    std::vector<Object*> getChildrenByComponent(Component::Type type) const;
    std::vector<Object*> getAllChildrenByName(const std::string& name) const;
    std::vector<Object*> getAllChildrenByComponent(Component::Type type) const;
    void getAllChildrenByName(std::vector<Object*>& result, const std::string& name) const;
    void getAllChildrenByComponent(std::vector<Object*>& result, Component::Type type) const;
    Eigen::Matrix4f getModel() const;

//  private
    void showHierarchyUI(int depth);
    bool showChildren;
    void showComponentUI();

    friend Scene;
private:
    
    Object* parent;
    std::string name;
    std::vector<Component*> components;
    std::vector<Object*> children;
    
    WPos position;
    WPos rotation;
    WPos scale;
};

