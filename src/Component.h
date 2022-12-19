#pragma once

#include <vector>
#include <string>

class Object;

class Component {
public:
    enum class Type {
        Mesh, MeshRenderer,
        Light,
        Camera
    };
    Component(Type type, Object* parent);
    Type getType() const;
    Object* getParent() const;

    virtual std::string toString() const = 0;
    virtual void showUI() = 0;
private:
    Object* parent;
    Type type;
};

