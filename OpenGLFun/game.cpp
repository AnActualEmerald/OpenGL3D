#include <iostream>
#include <string>
#include "display.h"
#include "GL\glew.h"
#include "screen.h"
#include "shader.h"
#include "mesh.h"

using namespace std;

//declare functions
void init(void);
void loop(void);
void render(void);
void update(void);

//constant fields
const string TITLE = "3D OpenGL";
const int WIDTH = 1000;
const int HEIGHT = 500;

//window for drawing
Display window(WIDTH, HEIGHT, TITLE);


//other variables
float time = 0;
Shader shader("./res/shaders/basicVert");
Vertex verts[] = { Vertex(vec3(-1, 0.5, 0)), Vertex(vec3(0, -1, 0)), Vertex(vec3(1, 0.5, 0)) };
Mesh mesh(verts, sizeof(verts) / sizeof(verts[0]));

int main(int argc, char** argv){

	cout << glGetString(GL_VERSION) << endl;
	init();
	return 0;
}

void init()
{
	//do init things

	//Start the game loop
	loop();
}

void loop()
{

	shader.Bind();
	while (!window.IsCloseRequested()){
		update();
		render();
	}
}

void update()
{
	window.Update();
}

void render()
{	
	window.Clear();	
	
	mesh.draw();
}