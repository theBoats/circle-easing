#ifndef EASING_H
#define EASING_H

#include <stdbool.h>
#include "raylib.h"

typedef struct Vertex {
	Vector2 centre;
	Vector2 position;
} Vertex;

typedef float (*EasingFunction)(float t, float b, float c, float d);

typedef struct Easer {
	Vertex currentVertex;
	Vertex finalVertex;
	float duration;
	bool isMoving;
	float transitionTime;
	EasingFunction easing;
} Easer;

float EaseOutQuad(float t, float b, float c, float d);

#endif