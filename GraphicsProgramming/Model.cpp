// Below ifdef required to remove warnings for unsafe version of fopen and fscanf.
// Secure version won't work cross-platform, forcing this small hack.
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "model.h"

bool Model::load(char* modelFilename)
{
	bool result;

	// Load in the model data,
	result = loadModel(modelFilename);
	if (!result)
	{
		//MessageBoxA(NULL, "Model failed to load", "Error", MB_OK | MB_ICONEXCLAMATION);
		MessageBox(NULL, L"Model failed to load", L"Error", MB_OK);
		return false;
	}


	return true;
}

void Model::render()
{
	time++;
	
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, this->vertex.data());
	glNormalPointer(GL_FLOAT, 0, this->normals.data());
	glTexCoordPointer(3, GL_FLOAT, 0, this->texCoords.data());

	//glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);
	
	//if (input->isKeyDown('r')) {
	//	j++;
	//	input->setKeyUp('r');
	//	if (j > 23)
	//	{
	//		j = 0;
	//	}
	//}


	glBindTexture(GL_TEXTURE_2D, texture[j]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glDrawArrays(GL_TRIANGLES, 0, this->vertex.size());
	

	//dereferencing method of choice
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D );
	time_day(time);
	if (j > 23) {
		j = 0;
	}
	if (time > 23000)
	{
		time = 0;
	}
	//cout << time << endl;
	
}

void Model::time_day(int time) {
	switch (time) {
	case 1000:
		j++;
		break;
	case 2000:
		j++;
		break;
	case 3000:
		j++;
		break;
	case 4000:
		j++;
		break;
	case 5000:
		j++;
		break;
	case 6000:
		j++;
		break;
	case 7000:
		j++;
		break;
	case 8000:
		j++;
		break;
	case 9000:
		j++;
		break;
	case 10000:
		j++;
		break;	
	case 11000:
		j++;
		break;
	case 12000:
		j++;
		break;
	case 13000:
		j++;
		break;
	case 14000:
		j++;
		break;
	case 15000:
		j++;
		break;
	case 16000:
		j++;
		break;
	case 17000:
		j++;
		break;
	case 18000:
		j++;
		break;
	case 19000:
		j++;
		break;
	case 200000:
		j++;
		break;
	case 21000:
		j++;
		break;
	case 22000:
		j++;
		break;
	case 23000:
		j++;
		break;
	}
}
// Modified from a mulit-threaded version by Mark Ropper.
bool Model::loadModel(char* filename)
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
																			&face[6], &face[7], &face[8]);
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
	
	//loading data 
	unsigned vertpos,textpos,normpos;
	for (int i = 0; i <faces.size(); i += 3)
	{
		//Vector3 t;
		vertpos = 0;
		textpos = 0;
		normpos = 0;
		vertpos = faces[i];
		textpos = faces[i + 1];
		normpos = faces[i + 2];
		vertpos = vertpos - 1;
		textpos = textpos - 1;
		normpos = normpos - 1;
		
		
		//pushing data
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

void Model::loadTexture()
{
	for (int i = 0; i <24; i++)
	{
		std::string str = "gfx/gradients/" + std::to_string(i) + ".png";
		char* name = new char[str.length() + 1];
		strcpy(name, str.c_str());
		filenames.push_back(name);
		//cout << filenames[i];
		texture[i]= SOIL_load_OGL_texture
		(
			filenames[i],
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_NTSC_SAFE_RGB 
		);

		//check for an error during the load process
		if (texture[i] == 0)
		{
			printf("SOIL loading error: '%s'\n", SOIL_last_result());
		}
	}

}
