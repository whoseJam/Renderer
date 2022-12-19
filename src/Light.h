#pragma once

#include <string>

#include "Define.h"
#include "Component.h"

class Light : public Component {
public:
    enum class Type : int {
        PointLight = 0,
        DirLight = 1,
        SpotLight = 2
    };
    Light(Object* parent, Type type);
    Color getColor() const;
    void setColor(Color color);
    float getRadius() const;
    void setRadius(float radius);
    WPos getDirection() const;
    void setDirection(WPos direction);
    Type getLightType() const;

    virtual std::string toString() const override;
    virtual void showUI() override;
private:
//  common
    Type lightType;
    Color color;

//  point light
    float radius;

//  direction light
    WPos direction;
};

