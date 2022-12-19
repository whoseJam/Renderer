#pragma once

#include "Define.h"
#include "Shader.h"
#include "Resource.h"

class Material : public Resource {
public:
    Material();
    TextureID getAlbedoTexture() const;
    void setAlbedoTexture(TextureID albedoTexture);
    Color getAlbedo() const;
    void setAlbedo(Color albedo);
    float getMetallic() const;
    void setMetallic(float metallic);
    float getRoughness() const;
    void setRoughness(float roughness);
    void setShader(Shader* shader);
    
    virtual void showUI() override;
private:
    TextureID albedoTexture;
    Color albedo;
    TextureID metallicTexture;
    float metallic;
    float roughness;
};

