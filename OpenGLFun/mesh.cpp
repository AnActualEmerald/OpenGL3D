#include "mesh.h"
#include <vector>


Mesh::Mesh(const string& path)
{
	IndexedModel model = OBJModel(path).ToIndexedModel();

	InitMesh(model);
}

Mesh::Mesh(Vertex* verts, unsigned int numVerts, unsigned int* indecies, unsigned int numIndecies)
{

	IndexedModel model;

	for (unsigned int i = 0; i < numVerts; i++)
	{
		model.positions.push_back(*verts[i].GetPos());
		model.texCoords.push_back(*verts[i].GetTexCoord());
		model.normals.push_back(*verts[i].GetNormal());
	}

	for (unsigned int i = 0; i < numIndecies; i++)
	{
		model.indices.push_back(indecies[i]);
	}


	InitMesh(model);	
}

void Mesh::InitMesh(const IndexedModel& model)
{
	_drawCount = model.indices.size();

	glGenVertexArrays(1, &_vertArrayObj);
	glBindVertexArray(_vertArrayObj);
	{

		glGenBuffers(NUM_BUFFERS, _vertArrayBuffers);
		glBindBuffer(GL_ARRAY_BUFFER, _vertArrayBuffers[POSITION_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vertArrayBuffers[TEXCOORD_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _vertArrayBuffers[NORMAL_VB]);
		glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(model.normals[0]), &model.normals[0], GL_STATIC_DRAW);


		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertArrayBuffers[INDEX_VB]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);



	}
	glBindVertexArray(0);


}


Mesh::~Mesh()
{

	glDeleteBuffers(NUM_BUFFERS, _vertArrayBuffers);
	glDeleteVertexArrays(1, &_vertArrayObj);
}


void Mesh::draw()
{

	glBindVertexArray(_vertArrayObj);
	
	glDrawElementsBaseVertex(GL_TRIANGLES, _drawCount, GL_UNSIGNED_INT, 0, 0);
	
	glBindVertexArray(0);

}