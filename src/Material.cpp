#include "Material.h"
#include "UI.h"

void Material::showUI() {
    UI::begin("Resouce : Material");
    UI::inputColor("albedo", &albedo);
    UI::sliderFloat("metallic", &metallic, 0, 1);
    UI::sliderFloat("roughness", &roughness, 0, 1);
    UI::end();
}

Material::Material() : Resource("untitled") {
}

void Material::setAlbedoTexture(TextureID albedoTexture) {
    this->albedoTexture = albedoTexture;
}

TextureID Material::getAlbedoTexture() const {
    return albedoTexture;
}

void Material::setAlbedo(Color albedo) {
    this->albedo = albedo;
}

Color Material::getAlbedo() const {
    return albedo;
}

void Material::setMetallic(float metallic) {
    this->metallic = metallic;
}

float Material::getMetallic() const {
    return metallic;
}

void Material::setRoughness(float roughness) {
    this->roughness = roughness;
}

float Material::getRoughness() const {
    return roughness;
}

void Material::setShader(Shader* shader) {
    shader->setColor("Material.albedo", albedo);
    shader->setTexture("Material.albedoTexture", albedoTexture, 0);
    shader->setFloat("Material.metallic", metallic);
    shader->setTexture("Meterial.metallicTexture", metallicTexture, 0);
    shader->setFloat("Material.roughness", roughness);
}