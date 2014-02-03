#include <iostream>
#include <string>
#include "display.h"
#include "GL\glew.h"
#include "screen.h"

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
}