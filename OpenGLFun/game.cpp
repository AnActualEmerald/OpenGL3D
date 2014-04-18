#include <iostream>
#include <string>
#include "display.h"
#include "GL\glew.h"
#include "screen.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"

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
Shader base("./res/shaders/basicVert");
Shader phong("./res/shaders/basicPhong");

Mesh mesh("./res/monkey3.obj");


Texture tex("./res/bulba.jpg");
Transform trans;
Camera cam(vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);


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
	//base.Bind();
	
	phong.Bind();
	phong.SetAmbience(vec3(0.1, 0.1, 0.1));
	trans.GetRot().y = 180;
	while (!window.IsCloseRequested()){
		update();
		render();
	}
}

void update()
{

	//trans.GetPos().x = sinf(time);
//	trans.GetPos().z = cosf(time);
	//trans.GetRot().x = time * 50;
	//trans.GetRot().z = time * 50;
	trans.GetRot().y = time * 50 + 180;
	//trans.SetScale(vec3(sinf(time), sinf(time), sinf(time)));

	//base.Update(trans, cam);
	phong.Update(trans, cam);

	window.Update();
	time += 0.001;
}

void render()
{	
	window.Clear(0.0, 0.1, 0.25, 0.0);	
	
	mesh.draw();
}