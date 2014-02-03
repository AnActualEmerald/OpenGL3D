#pragma once
class Screen
{
public:
	Screen();
	virtual ~Screen();

	static void drawRect(float x, float y, float width, float height);
	static void setColor(float r, float g, float b);

private:

};

