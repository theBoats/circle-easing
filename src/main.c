#include "raylib.h"
#include "easing.h"

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600



Vertex currentVertices[4] = {
    { {400.0f, 400.0f}, {500.0f, 400.0f} },  // centre, position
    { {400.0f, 400.0f}, {350.0f, 486.6f} },
    { {400.0f, 400.0f}, {350.0f, 313.4f} },
    { {400.0f, 400.0f}, {350.0f, 313.4f} }
};

Vertex nextVertices[4] = {
    { {400.0f, 400.0f}, {500.0f, 400.0f} },  // centre, position
    { {400.0f, 400.0f}, {400.0f, 500.0f} },
    { {400.0f, 400.0f}, {300.0f, 400.0f} },
    { {400.0f, 400.0f}, {400.0f, 300.0f} }
};



int main(void) {

	// Initialize window
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");
	SetTargetFPS(60);

	// Init here

	/* Initialize easing struct with default values */

	Easer easer = {
    .currentVertex = { (Vector2){400, 300}, (Vector2){500, 300} }, // centre, position
    .finalVertex   = { (Vector2){400, 300}, (Vector2){600, 300} }, // centre, position
    .duration      = 1000.0f,
    .isMoving      = false,
    .transitionTime = 0.0f,
    .easing        = EaseOutQuad   
	};



	// Game loop
	while(!WindowShouldClose()) {
		float deltaTime = GetFrameTime();

		// Update

		for (int i = 0; i < 4; i++) {
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


		// draw vertices
		for (int i = 0; i < 4; i++ ) {
			// int next = (i + 1) % 4;
			DrawCircleV(currentVertices[i].position, 4, RED);
			// DrawCircleV(nextVertices[i].position, 4, BLUE);
			// DrawCircleV(drawVertices[i].position, 4, BLUE);

			


		}

		

		EndDrawing();
	}

	CloseWindow();
	return 0;
}