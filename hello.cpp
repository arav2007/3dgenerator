#include <iostream>
#include <cmath> //for mathematical functions
#include <vector> //vector library
#include "raylib.h" //3D rendering library
#include <cstring> //for taking strings as inputs
#include <cstdlib> //for other general functions
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h" //gui library 

using namespace std;




vector<pair<int,int>> edges; //a vector called edges which stores elements, which each have 2 more elements, which are the beginning index and ending index of an edge
vector<Vector3> uniquepoints; //a vector called uniquepoints which stores data in the form of Vector3, which in turn holds (x,y,z)



int findOrAddPoint(Vector3 p) {
    for (int i = 0; i < (int)uniquepoints.size(); i++) {
        if (Vector3Distance(uniquepoints[i], p) < 0.001f) {
            return i;
        }
    }
    uniquepoints.push_back(p);
    return (int)uniquepoints.size() - 1;
(

int main () {



	// _store every point so all lines are remembered (not overwritten)
	vector<int> selectedIndices;
	uniquepoints.push_back({0,0,0}); //initializing the initial starting point
	Vector3 temp_point={0,0,0};
	vector<pair<int,point*>> linked_list;

	int i,j=0;	

	
	InitWindow(1000,800,"CAD viewer"); //initialising a window with width 1000, height 800 and the title as CAD viewer

	Camera3D camera = {0}; //initialising a type called camera using Camera3D
	camera.position=uniquepoints[0]; //what position is the camera looking at
	camera.target=uniquepoints[0]; //which coordinate is the camera targeting
	camera.up={0,0,1}; // which axis is facing up
	camera.fovy=60.0f; //sets up field of view
	camera.projection=CAMERA_PERSPECTIVE;
	
	float b=10.0f; //setting an appropriate distance from the 3d object
	float radius=b;
	float yaw=PI/2.0f; //setting initial angle from the z axis pi/2; 0 means to the left; pi means to the right
	float pitch=0; //setting initial vertical angle as 0
	
	char xText[16] = "0";
	char yText[16] = "0";
	char zText[16] = "0";
	bool xEditMode = false, yEditMode = false, zEditMode = false;
	const int panelX = 800;

	SetTargetFPS(60);

	while(!WindowShouldClose()){
		
		       


			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                Vector2 d = GetMouseDelta(); //gets info from the mouse, has 2 parameters x and y
                yaw   -= d.x * 0.003f; // uses the mouse to change your left-right orientation
                pitch += d.y * 0.003f; //uses the mouse to change your z axis orientation
			}
			
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			Ray mouseRay = GetScreenToWorldRay(GetMousePosition(), camera); //gets info from the mouse upon a single click, not a hold
			
			int closestIndex = -1; //initializing closest index
			float closestDist = INFINITY; // initializing closest di
			
			for (int i = 0; i < (int)uniquepoints.size(); i++) {
			RayCollision collision = GetRayCollisionSphere(mouseRay, uniquepoints[i], 0.2f);
			if (collision.hit && collision.distance < closestDist) {
				closestDist = collision.distance;
				closestIndex = i;
					}
				}
				
				
			if (closestIndex != -1) {
				selectedIndices.push_back(closestIndex);
				}	
				
			}	
			

			if (pitch >  1.55f) pitch =  1.55f;
            if (pitch < -1.55f) pitch = -1.55f;
            
            radius -= GetMouseWheelMove() * 1.0f;
            if (radius < 1.0f) radius = 1.0f;
            
			// cartesian to spherical conversion to update camera position information
            camera.position.x = uniquepoints[0].x + radius * cosf(pitch) * cosf(yaw); 
            camera.position.y = uniquepoints[0].y + radius * cosf(pitch) * sinf(yaw);
            camera.position.z = uniquepoints[0].z + radius * sinf(pitch);
            
        BeginDrawing(); //this is where the rendering begins
        ClearBackground((Color){ 12, 12, 20, 255 });
        
        BeginMode3D(camera);
			
			DrawLine3D(uniquepoints[0], uniquepoints[0], GREEN);
			for (auto&e : edges) {
				DrawLine3D(uniquepoints[e.first],uniquepoints[e.second], SKYBLUE); //draws a line from the current starting point to current ending point
			}
			
			for (int i = 0; i < (int)uniquepoints.size(); i++) {
				bool isSelected = false;
				for (int idx : selectedIndices) {
					if (idx == i) { isSelected = true; break; }
				}
				DrawSphere(uniquepoints[i], 0.05f, isSelected ? ORANGE : YELLOW);
					}
			DrawGrid(20,1.0f); //draws the GRID
		EndMode3D();
		
		DrawText(TextFormat("endpoint: (%.1f, %.1f, %.1f)",uniquepoints[j].x, uniquepoints[j].y, uniquepoints[j].z), 10, 10 , 20 , GREEN);                                                                             
		
		GuiLabel((Rectangle){ panelX + 10, 20, 20, 20 }, "X:");
		
		if (GuiTextBox((Rectangle){ panelX + 40, 20, 140, 20 }, xText, 16, xEditMode)) {
			xEditMode = true; yEditMode = false; zEditMode = false; //allows only the x box to get modified
		}
		
		GuiLabel((Rectangle){ panelX + 10, 50, 20, 20 }, "Y:");
		
		if (GuiTextBox((Rectangle){ panelX + 40, 50, 140, 20 }, yText, 16, yEditMode)) {
			xEditMode = false; yEditMode = true; zEditMode = false; //allows only the y box to get modified
		}

		GuiLabel((Rectangle){ panelX + 10, 80, 20, 20 }, "Z:");
		
		if (GuiTextBox((Rectangle){ panelX + 40, 80, 140, 20 }, zText, 16, zEditMode)) {
			xEditMode = false; yEditMode = false; zEditMode = true; // allows only the z box to get modified
		}
		
		if (GuiButton((Rectangle){ panelX + 10, 120, 85, 30 }, "Commit")) {
			
			float dx = atof(xText); //ascii to float value
			float dy = atof(yText);
			float dz = atof(zText);
 
			temp_point = Vector3Add(uniquepoints[j], (Vector3){dx, dy, dz});
			int idxA= findOrAddPoint(uniquepoints[j]);
			int idxB= findOrAddPoint(temp_point);
			
			bool alreadyConnected=false;
			for (auto&e : edges) {
				if ((e.first == idxA && e.second == idxB ) || (e.first == idxB && e.second == idxA)) {
					
					alreadyConnected=true;
					j=idxB;
					break;
					}
				
				}
			if (!alreadyConnected) {
				
				edges.push_back({idxA,idxB});
				j=idxB;
				} 
			
 
			strcpy(xText, "0");
			strcpy(yText, "0");
			strcpy(zText, "0");
			xEditMode = yEditMode = zEditMode = false;
		}
 
		if (GuiButton((Rectangle){ panelX + 105, 120, 85, 30 }, "Erase")) {
			int startidx = edges.back().first;
			int endidx = edges.back().second;
			edges.pop_back();
			
			bool stillreferenced = false;
			for (auto&e : edges ) {
				
				if (e.first == endidx || e.second == endidx) {stillreferenced = true; break; }
				
				}
				
			if (!stillreferenced && endidx == (int)uniquepoints.size() - 1) {
				
				uniquepoints.pop_back();
				}	
				
			j=startidx;			
		}
		
		if (GuiButton((Rectangle){ panelX + 10, 150, 180, 30 }, "Extend Selected")) {
			float dx = atof(xText);
			float dy = atof(yText);
			float dz = atof(zText);
			Vector3 offset = {dx, dy, dz};
    
			for (int idx : selectedIndices) {
			uniquepoints[idx] = Vector3Add(uniquepoints[idx], offset);
				}
    
			selectedIndices.clear();  // deselect after applying
			strcpy(xText, "0"); strcpy(yText, "0"); strcpy(zText, "0");
				}
		
		
		
		EndDrawing();

		}

	CloseWindow();

	}
