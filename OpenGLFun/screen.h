#pragma once
class Screen
{
public:
	Screen();
	virtual ~Screen();

	static void drawRect(float x, float y, float width, float height);
	static void setColor(float r, float g, float b);
	static void drawCube(float x, float y, float z);
	static void drawCube(float x, flaot y, float z, float w, float h);

private:

};

