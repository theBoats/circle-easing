#include "raylib.h"
#include "easing.h"
#include <math.h>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600

#define MAX_VERTICES 100
// #define PI 3.14159265358979323846
#define RADIUS 100
#define CENTRE (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2}



// Vertex currentVertices[4] = {
//     { {400.0f, 400.0f}, {500.0f, 400.0f} },  // centre, position
//     { {400.0f, 400.0f}, {350.0f, 486.6f} },
//     { {400.0f, 400.0f}, {350.0f, 313.4f} },
//     { {400.0f, 400.0f}, {350.0f, 313.4f} }
// };

// Vertex nextVertices[4] = {
//     { {400.0f, 400.0f}, {500.0f, 400.0f} },  // centre, position
//     { {400.0f, 400.0f}, {400.0f, 500.0f} },
//     { {400.0f, 400.0f}, {300.0f, 400.0f} },
//     { {400.0f, 400.0f}, {400.0f, 300.0f} }
// };

Vertex currentVertices[MAX_VERTICES];
Vertex nextVertices[MAX_VERTICES];


int main(void) {

	// Initialize window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
	SetTargetFPS(60);

	// Init here

	/* Initialize easing struct with default values */

	Easer easer = {
    .currentVertex = { CENTRE, CENTRE }, // centre, position
    .finalVertex   = { CENTRE, CENTRE }, // centre, position
    .duration      = 1000.0f,
    .isMoving      = false,
    .transitionTime = 0.0f,
    .easing        = EaseOutQuad   
	};

	int num_vertices = 3; // initial value

	void FillCurrentVertices(int num_vertices) {
	// Fill current vertex array
	for (int i = 0; i < num_vertices; i++) {
		float current_angle = 2 * PI * i / num_vertices;
		float vert_x = CENTRE.x + cosf(current_angle) * RADIUS;
		float vert_y = CENTRE.y + sinf(current_angle) * RADIUS;
		currentVertices[i] = (Vertex){ CENTRE, (Vector2){vert_x, vert_y} };
	}
	// Duplicate last point of current vertex array as an additional point
	currentVertices[num_vertices] = currentVertices[num_vertices-1];

	}

	 void FillNextVertices(int num_vertices) {
	// Fill next vertex array
	for (int i = 0; i < (num_vertices+1); i++) {
		float current_angle = 2 * PI * i / (num_vertices+1);
		float vert_x = CENTRE.x + cosf(current_angle) * RADIUS;
		float vert_y = CENTRE.y + sinf(current_angle) * RADIUS;
		nextVertices[i] = (Vertex){ CENTRE, (Vector2){vert_x, vert_y} };
	}

	}
	
	FillCurrentVertices(num_vertices);
	FillNextVertices(num_vertices);

	// Game loop
	while(!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		// Update
		if (IsKeyPressed(KEY_ONE) && num_vertices < MAX_VERTICES) {
			num_vertices += 1;
			FillCurrentVertices(num_vertices);
			FillNextVertices(num_vertices);

			easer.transitionTime = 0.0f;
			easer.isMoving = true;
		}

		for (int i = 0; i < num_vertices+1; i++) {
			easer.currentVertex = (Vertex){currentVertices[i].centre, currentVertices[i].position};
			easer.finalVertex = (Vertex){nextVertices[i].centre, nextVertices[i].position};

			easer.isMoving = true;

			if (easer.isMoving) {
				easer.transitionTime += deltaTime;

				if (easer.transitionTime >= easer.duration) {
					easer.isMoving = false;
				} else {
					currentVertices[i].position.x = easer.easing(easer.transitionTime, easer.currentVertex.position.x, easer.finalVertex.position.x - easer.currentVertex.position.x, easer.duration);
					currentVertices[i].position.y = easer.easing(easer.transitionTime, easer.currentVertex.position.y, easer.finalVertex.position.y - easer.currentVertex.position.y, easer.duration);
				}
			}			
		}


		// Draw
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawCircleV(CENTRE, 4, BLUE);


		// draw vertices
		for (int i = 0; i < num_vertices+1; i++ ) {
			DrawCircleV(currentVertices[i].position, 4, RED);
			// DrawCircleV(nextVertices[i].position, 4, BLUE);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}