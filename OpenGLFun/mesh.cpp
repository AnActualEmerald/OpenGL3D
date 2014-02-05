#include "mesh.h"


Mesh::Mesh(Vertex* verts, unsigned int numVerts)
{

	_drawCount = numVerts;

	glGenVertexArrays(1, &_vertArrayObj);
	glBindVertexArray(_vertArrayObj);
	{
		glGenBuffers(NUM_BUFFERS, _vertArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, _vertArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(verts[0]), verts, GL_STATIC_DRAW);
		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}
	glBindVertexArray(0);
}


Mesh::~Mesh()
{

	glDeleteVertexArrays(1, &_vertArrayObj);
}


void Mesh::draw()
{

	glBindVertexArray(_vertArrayObj);
	
	glDrawArrays(GL_TRIANGLES, 0, _drawCount);
	
	glBindVertexArray(0);

}