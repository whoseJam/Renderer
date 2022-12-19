
#include <vector>

#include "Forward.h"
#include "Material.h"
#include "Camera.h"
#include "Scene.h"
#include "Shader.h"
#include "Logger.h"
#include "Math.h"
#include "Mesh.h"
#include "MeshRenderer.h"

using namespace std;
using namespace Eigen;

namespace Forward {
    bool inited = false;
    Shader* objectShader = nullptr;

    void initialize() {
        if (inited) return;
        objectShader = new Shader(
            "src/shader/object.glsl",
            "src/shader/object.frag"
        );
        inited = true;
    }

    void setViewport(Camera* camera) {
        glViewport(
            camera->getLeft(), 
            camera->getButtom(), 
            camera->getWidth(), 
            camera->getHeight()
        );
    }

    void prepare(Scene& scene) {
        vector<Object*> object = scene.getAllObjectsByComponent(Component::Type::Light);

    }

    void render(Scene& scene) {
        vector<Object*> meshes = scene.getAllObjectsByComponent(Component::Type::Mesh);
        vector<Object*> lights = scene.getAllObjectsByComponent(Component::Type::Light);
        Object* tmp;
        tmp = scene.getAllObjectByComponent(Component::Type::Camera);
        if (tmp == nullptr) Logger::error("Camera Not Found");
        Camera* camera = (Camera*)(tmp->getComponentByType(Component::Type::Camera));
        setViewport(camera);

        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2, 0.2, 0.2, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        objectShader->use();
        objectShader->setVec3f("PointLight.position", lights[0]->getPosition());
        objectShader->setVec3f("ViewPos", camera->getParent()->getPosition());
        objectShader->setMat4f("View", camera->getView());
        objectShader->setMat4f("Proj", camera->getPerspective());
        for (Object* mesh : meshes) {
            Matrix4f model = mesh->getModel();
            objectShader->setMat4f("Model", model);
            objectShader->setMat4f("ModelInv", model.inverse());
            MeshRenderer* renderer = (MeshRenderer*)(mesh->getComponentByType(Component::Type::MeshRenderer));
            renderer->setShader(objectShader);
            Mesh* meshBuffer = (Mesh*)(mesh->getComponentByType(Component::Type::Mesh));
            int size = meshBuffer->getIndicesSize();
            VertexArrayID VAO = meshBuffer->getVertexArray();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
        glDisable(GL_DEPTH_TEST);
    }
}
//void Forward::dirLightShadowMapPass(Scene& scene, DirLight* light) {
//    glViewport(0, 0, shadowWidth, shadowHeight);
//    glBindFramebuffer(GL_FRAMEBUFFER, dirLightShadowFrame);
//    glEnable(GL_DEPTH_TEST);
//    glClear(GL_DEPTH_BUFFER_BIT);
//    //dirLightShadowShader.use();
//    //dirLightShadowShader.setMat4f("view", Math::getView(light));
//    //dirLightShadowShader.setMat4f("projection", Math::getOrtho(light));
//    for (const auto mesh : scene.getMeshes()) {
//        dirLightShadowShader.setMat4f("model", Math::getTranslation(mesh->getPosition()));
//        int size = mesh->getIndicesSize();
//        VertexArrayID VAO = mesh->getVertexArray();
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
//        glBindVertexArray(0);
//    }
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    glDisable(GL_DEPTH_TEST);
//}
