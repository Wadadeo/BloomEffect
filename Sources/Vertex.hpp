#pragma once

#include "glm\glm.hpp"

using namespace glm;

struct Vertex {
	vec3 position;
	vec3 normal;
	vec2 texCoords;
	vec3 tangent;
	vec3 bitTangent;
};

