
#include "MeshRenderer.h"
#include "Material.h"
#include "Object.h"
#include "UI.h"

using namespace std;

void MeshRenderer::showUI() {
    UI::text("<Mesh Renderer>");
    for (int i = 0; i < materials.size(); i++) {
        Material* material = materials[i];
        UI::text("mat_%d", i);
        UI::sameLine();
        UI::text(material->getName());
        if (UI::isItemClicked()) {
            UI::whichResourceDisplay(material);
        }
    }
}

MeshRenderer::MeshRenderer(Object* parent) :
    Component(Component::Type::MeshRenderer, parent) {
}

string MeshRenderer::toString() const {
    return "MeshRenderer";
}

void MeshRenderer::addMaterial(Material* material) {
    materials.push_back(material);
}

void MeshRenderer::setShader(Shader* shader) {
    Material* material = materials[0];
    material->setShader(shader);
}