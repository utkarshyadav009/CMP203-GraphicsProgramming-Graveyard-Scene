#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include "Tree.h"

bool Tree::load(char* modelFilename, char* textureFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		//MessageBoxA(NULL, "Model failed to load", "Error", MB_OK | MB_ICONEXCLAMATION);
		MessageBox(NULL, L"Model failed to load", L"Error", MB_OK);
		//MessageBox(NULL, "Model failed to load", "Error", MB_OK);
		return false;
	}

	// Load the texture for this model.
	loadTexture(textureFilename);

	return true;
}

void Tree::render()
{

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);




	glVertexPointer(3, GL_FLOAT, 0, this->vertex.data());
	glNormalPointer(GL_FLOAT, 0, this->normals.data());
	glTexCoordPointer(3, GL_FLOAT, 0, this->texCoords.data());


	//glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//glColor3f(0.486, 0.988, 0.000);
	glDrawArrays(GL_TRIANGLES, 0, vertex.size());


	//dereferencing method of choice
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);


}


// Modified from a mulit-threaded version by Mark Ropper.
bool Tree::loadModel(char* filename)
{
	vector<Vector3> verts;
	vector<Vector3> norms;
	vector<Vector3> texCs;
	vector<unsigned int> faces;

	FILE* file = fopen(filename, "r");
	if (file == NULL)
	{
		return false;
	}
	while (true)
	{
		char lineHeader[128];

		// Read first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // exit loop
		}
		else // Parse
		{
			if (strcmp(lineHeader, "v") == 0) // Vertex
			{
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				verts.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) // Tex Coord
			{
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				texCs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) // Normal
			{
				Vector3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				norms.push_back(normal);
			}
			else if (strcmp(lineHeader, "f") == 0) // Face
			{
				unsigned int face[9];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face[0], &face[1], &face[2],
					&face[3], &face[4], &face[5],
					&face[6], &face[7], &face[8]

				);
				if (matches != 9)
				{
					// Parser error, or not triangle faces
					return false;
				}

				for (int i = 0; i < 9; i++)
				{
					faces.push_back(face[i]);
				}


			}
		}
	}

#pragma region unroll_data
	// "Unroll" the loaded obj information into a list of triangles.
	// TODO: By this point all model has been read from the file, but is not in the correct order.
	// You NEED to loop over all the data and sort it into a render ready order/format.
	//std::cout << verts.size()<<std::endl;
	//std::cout << texCs.size() << std::endl;
	//std::cout << norms.size() << std::endl;

	unsigned vertpos, textpos, normpos;
	for (int i = 0; i < faces.size(); i += 3)
	{
		vertpos = 0;
		textpos = 0;
		normpos = 0;
		vertpos = faces[i];
		textpos = faces[i + 1];
		normpos = faces[i + 2];
		vertpos = vertpos - 1;
		textpos = textpos - 1;
		normpos = normpos - 1;

		//std::cout << faces[i] << "/" << faces[i + 1] << "/" << faces[i + 2] << std::endl;
		//std:: cout << "Position: "<< vertpos<<std::endl;

		//std::cout<<"x: " << verts[vertpos].x << " y: " << verts[vertpos].y << " z: " << verts[vertpos].z << std::endl;
		vertex.push_back(verts[vertpos]);
		texCoords.push_back(texCs[textpos]);
		normals.push_back(norms[normpos]);

	}


#pragma endregion unroll_data

	// Once data has been sorted clear read data (which has been copied and are not longer needed).
	verts.clear();
	norms.clear();
	texCs.clear();
	faces.clear();

	return true;
}

void Tree::loadTexture(char* filename)
{
	texture = SOIL_load_OGL_texture
	(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_INVERT_Y // Depending on texture file type some need inverted others don't.
	);

	//check for an error during the load process
	if (texture == 0)
	{
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
	}

}