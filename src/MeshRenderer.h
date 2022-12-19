#pragma once

#include <string>
#include <vector>

#include "Define.h"
#include "Component.h"
#include "Shader.h"
#include "Material.h"

class MeshRenderer : public Component {
public:
    MeshRenderer(Object* parent);
    void addMaterial(Material* material);
    void setShader(Shader* shader);

    virtual std::string toString() const override;
    virtual void showUI() override;
private:
    std::vector<Material*> materials;
};

