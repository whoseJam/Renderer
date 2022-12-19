#include "Window.h"
#include "Input.h"
#include "Camera.h"
#include "Scene.h"
#include "Object.h"
#include "Light.h"
#include "Forward.h"
#include "Math.h"
#include "Mesh.h"
#include "Logger.h"
#include "Define.h"
#include "MeshRenderer.h"
#include "UI.h"

using namespace std;

void initialize() {
    UI::initialize();
    Window::initialize();
    Input::initialize();
    Forward::initialize();
}

void destroy() {
    UI::destroy();
    Window::destroy();
}

int main() {
    initialize();

    Material* boxMat = new Material();
    boxMat->setAlbedo(Color(0.8, 0.2, 0.1));
    boxMat->setRoughness(1);
    boxMat->setMetallic(0.01);

    Material* planeMat = new Material();
    planeMat->setAlbedo(Color(0.1, 0.7, 0.3));
    planeMat->setRoughness(0.3);
    planeMat->setMetallic(0.7);

    Object* mainCamera = new Object(nullptr, "main camera", WPos(1, 1, 5));
    Camera* camera = new Camera(mainCamera, 1200, 900);
    camera->setUnityControl();
    mainCamera->addComponent(camera);
    Object* plane = new Object(nullptr, "plane");
    plane->addComponent(new Mesh(plane, Mesh::Type::plane));
    MeshRenderer* planeRender = new MeshRenderer(plane);
    planeRender->addMaterial(planeMat);
    plane->addComponent(planeRender);
    Object* box = new Object(nullptr, "box");
    box->addComponent(new Mesh(box, Mesh::Type::cube));
    MeshRenderer* boxRender = new MeshRenderer(box);
    boxRender->addMaterial(boxMat);
    box->addComponent(boxRender);

    Object* light = new Object(nullptr, "point light", WPos(1.2, 1, 1.2));
    Light* pointLight = new Light(light, Light::Type::PointLight);
    pointLight->setRadius(1);
    light->addComponent(pointLight);

    Object* emptyObject1 = new Object(plane, "empty object1");
    plane->addChild(emptyObject1);
    Object* emptyObject2 = new Object(box, "empty object2");
    box->addChild(emptyObject2);


    Scene scene;
    
    scene.addObject(box);
    scene.addObject(plane);
    scene.addObject(light);
    scene.addObject(mainCamera);

    UI::whichSceneDisplayHierarchy(&scene);
    Forward::prepare(scene);

    WPos pos;
    bool flag1;
    bool flag2;
    while (true) {
        Input::update();
        UI::update();

        Forward::render(scene);
        UI::render();
    }
    destroy();
    return 0;
}