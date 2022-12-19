#pragma once

#include "Extern.h"

using Color = Eigen::Vector3f;
using WPos = Eigen::Vector3f;
using SPos = Eigen::Vector2f;

using VertexID = unsigned int;
using TextureID = unsigned int;
using ShaderID = unsigned int;
using VertexArrayID = unsigned int;
using ElementArrayID = unsigned int;
using DataArrayID = unsigned int;
using FrameID = unsigned int;

using FuncID = unsigned long long;
using OnScrollFunc = std::function<void(double, double)>;
using OnMouseMoveFunc = std::function<void(double, double)>;
using OnMouseDownFunc = std::function<void()>;
using OnButtonDownFunc = std::function<void(double)>;

using Degree = float;
using Radian = float;