#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Scene.h"

namespace Forward {
    void initialize();
    void prepare(Scene& scene);
    void render(Scene& scene);
}

