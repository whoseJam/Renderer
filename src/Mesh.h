#pragma once

#include <vector>
#include <string>

#include "Define.h"
#include "Vertex.h"
#include "Object.h"
#include "Material.h"

class Renderer;

class Mesh : public Component {
public:
    enum class Type {
        cube,
        sphere,
        quad,
        plane
    };
    Mesh(
        Object* parent,
        std::vector<Vertex> vertices,
        std::vector<VertexID> indices
    );
    Mesh(Object* parent, Type type);

    VertexArrayID getVertexArray() const;
    int getIndicesSize() const;
    
    virtual std::string toString() const override;
    virtual void showUI() override;
private:
    std::vector<Vertex> vertices;
    std::vector<VertexID> indices;

    VertexArrayID VAO;
    DataArrayID VBO;
    ElementArrayID EBO;
    Type meshType;

    void initCube();
    void initSphere();
    void initQuad();
    void initPlane();
    void mallocOnGPU();
};

