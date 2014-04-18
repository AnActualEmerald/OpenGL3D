#version 330

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 texCoord0;
varying vec3 normal0;

uniform mat4 transform;

void main()
{
	texCoord0 = texCoord;
	normal0 = normal;
}