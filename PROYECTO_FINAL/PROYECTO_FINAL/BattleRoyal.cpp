/*
Semestre 2022-2
Pr�ctica 8: Iluminaci�n 1 
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;
const float escalaX = 20.0f;
const float escalaZ = 12.0f;
const float duracion_dia = 4000.0f;
GLint skyboxdaynight;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Camera camera2;
Camera camera3;

Texture brickTexture;
Texture greenTexture;
Texture lawnTexture;
Texture beachTexture;
Texture agua;
Texture DadoTexture;
Texture bridgeTexture;
Texture barandalTexture;
Texture perryTexture;
Texture EggRobo;
Model Ferb;
Model Dado_M;
Model Torre;

Model PerryB;
Model PerryLA;
Model PerryRA;
Model PerryLL;
Model PerryRL;

Model Muralla;

Model Spring;
Model Faro_Unleashed;
Model Palm;

Model TorrePrincesa;

Skybox skybox;
Skybox skyboxDay;
Skybox skyboxNight;

float time_skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
DirectionalLight mainLightAuxiliar[3];
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";



void CrearDado()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		10.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		10.0f,  10.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	10.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	10.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	10.0f,	10.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	10.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	10.0f,  0.00f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.0f,  0.00f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.0f,  10.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	10.0f,  10.0f,    	0.0f,   0.0f,   1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	10.0f,  10.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,	10.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	10.0f,	0.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	10.0f,  10.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.0f,  10.0f,		0.0f,	1.0f,	0.0f,
		 0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	10.0f,  10.0f,		0.0f,   1.0f,   0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  10.0f,    	0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	10.0f,  10.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	10.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}

void CrearEggRobo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,

		24,25,26,
		26,27,24, //1

		28,29,30,
		30,31,28,

		32,33,34,
		34,35,32,

		36,37,38,
		38,39,36,

		40,41,42,
		42,43,40,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat eggRobo_vertices[] = {
		// Down
		//x		y		z		S		T			NX		NY		NZ
		-2.5f, 5.0f,  2.5f,		0.0f,  0.125f,		0.0f,	1.0f,	0.0f,	//1
		2.5f, 5.0f,  2.5f,		0.125f,  0.125f,	0.0f,	1.0f,	0.0f,	//2
		2.5f, 5.0f,  -2.5f,		0.125f,  0.25f,		0.0f,	1.0f,	0.0f, //3
		-2.5f,5.0f,  -2.5f,		0.0f,  0.25f,		0.0f,	1.0f,	0.0f,	//0 8
			//4
		// Adelante
		-2.5f, 10.0f,  -2.5f,	0.25f,  1.0f,		0.0f,	0.0f,	-1.0f,	//0 8
		2.5f, 10.0f,  -2.5f,	0.375f,  1.0f,		0.0f,	0.0f,	-1.0f,	//1
		2.5f, 5.0f,  -2.5f,		0.375f,  0.875f,	0.0f,	0.0f,	-1.0f,
		-2.5f, 5.0f,  -2.5f,	0.25f,  0.875f,		0.0f,	0.0f,	-1.0f,	//0 8

		// DEtras
		-2.5f, 10.0f,  2.5f,	0.0f,  1.0f,		0.0f,	0.0f,	1.0f,	//8
		2.5f, 10.0f,  2.5f,		0.125f,  1.0f,		0.0f,	0.0f,	1.0f,	//9 8
		2.5f, 5.0f,  2.5f,		0.125f,  0.875f,	0.0f,	0.0f,	1.0f,	//10
		-2.5f, 5.0f,  2.5f,		0.0f,  0.875f,		0.0f,	0.0f,	1.0f,	//11 8

		//Costado Izquierdo
		-2.5f,10.0f,  -2.5f,	0.125f,  1.0f,		1.0f,	0.0f,	0.0f,	//
		-2.5f, 10.0f,  2.5f,	0.25f,  1.0f,		1.0f,	0.0f,	0.0f,	//
		-2.5f, 5.0f,  2.5f,		0.25f,  0.875f,		1.0f,	0.0f,	0.0f,	//
		-2.5f, 5.0f,  -2.5f,	0.125f,  0.875f,	1.0f,	0.0f,	0.0f,	//

		//Costado Derecho
		2.5f,10.0f,  -2.5f,		0.125f,  1.0f,		-1.0f,	0.0f,	0.0f,	//
		2.5f, 10.0f,  2.5f,		0.25f,  1.0f,		-1.0f,	0.0f,	0.0f,	//
		2.5f, 5.0f,  2.5f,		0.25f,  0.875f,		-1.0f,	0.0f,	0.0f,	//
		2.5f, 5.0f,  -2.5f,		0.125f,  0.875f,	-1.0f,	0.0f,	0.0f,	//

		// Cabeza Arriba
		-2.5f, 12.5f,  2.5f,	0.75f,	1.0f,		0.0f,	-1.0f,	0.0f,	//0 8
		2.5f, 12.5f,  2.5f,		0.875f,  1.0f,		0.0f,	-1.0f,	0.0f,	//1
		2.5f, 12.5f,  -2.5f,	0.875f,  0.875f,	0.0f,	-1.0f,	0.0f,	//2
		-2.5f,12.5f, -2.5f,		0.75f,  0.875f,		0.0f,	-1.0f,	0.0f, //3
		//Cabeza Delante
		-2.5f, 12.5f,  2.5f,	0.375f,	1.0f,		0.0f,	0.0f,	-1.0f,	//0 8
		2.5f, 12.5f,  2.5f,		0.5f, 1.0f,			0.0f,	0.0f,	-1.0f,	//1
		2.5f, 10.0f,  2.5f,		0.5f, 0.9385f,		0.0f,	0.0f,	-1.0f,
		-2.5f, 10.0f,  2.5f,	0.375f,  0.9385f,	0.0f,	0.0f,	-1.0f,	//0 8

		// Cabeza Detras
		-2.5f, 12.5f,  -2.5f,	0.625f,  1.0f,		0.0f,	0.0f,	1.0f,	//8
		2.5f, 12.5f,  -2.5f,	0.75f,  1.0f,		0.0f,	0.0f,	1.0f,	//9 8
		2.5f, 10.0f,  -2.5f,	0.75f,  0.9385f,	0.0f,	0.0f,	1.0f,	//10
		-2.5f, 10.0f,  -2.5f,	0.625f,  0.9385f,	0.0f,	0.0f,	1.0f,	//11 8

		//Cabeza Costado Izquierdo
		-2.5f,	12.5f,  -2.5f,	0.5f,  1.0f,		1.0f,	0.0f,	0.0f,	//
		-2.5f,	12.5f,  2.5f,	0.625f,  1.0f,		1.0f,	0.0f,	0.0f,	//
		-2.5f,	10.0f,  2.5f,	0.625f,  0.9385f,	1.0f,	0.0f,	0.0f,	//
		-2.5f,	10.0f,  -2.5f,	0.5f,  0.9385f,		1.0f,	0.0f,	0.0f,	//

		//Cabeza Costado Derecho
		2.5f,	12.5f,  -2.5f,	0.5f,  1.0f,		-1.0f,	0.0f,	0.0f,	//
		2.5f,	12.5f,  2.5f,	0.625f,  1.0f,		-1.0f,	0.0f,	0.0f,	//
		2.5f,	10.0f,  2.5f,	0.625f,  0.9385f,	-1.0f,	0.0f,	0.0f,	//
		2.5f,	10.0f,  -2.5f,	0.5f,  0.9385f,		-1.0f,	0.0f,	0.0f,	//
		

	};

	Mesh* egg = new Mesh();
	egg->CreateMesh(eggRobo_vertices, cubo_indices, 320, 66);
	meshList.push_back(egg);

}

void CrearEggRoboArticulacion()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat eggRobo_vertices[] = {
		// Down
		//x		y		z		S		T			NX		NY		NZ
		-0.625f, 0.5f,  0.625f,		0.875f,  1.0f,			0.0f,	1.0f,	0.0f,	//1
		0.625f, 0.5f,  0.625f,		0.90625f,  1.0f,		0.0f,	1.0f,	0.0f,	//2
		0.625f, 0.5f,  -0.625f,		0.90625f,  0.96975f,	0.0f,	1.0f,	0.0f, //3
		-0.625f,0.5f,  -0.625f,		0.875f,  0.96975f,		0.0f,	1.0f,	0.0f,	//0 8
		
			//4
		// Adelante
		-0.625f, -0.5f,  -0.625f,	0.875f,  1.0f,			0.0f,	0.0f,	-1.0f,	//0 8
		0.625f, -0.5f,  -0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.625f, 0.5f,  -0.625f,		0.90625f,  0.96975f,	0.0f,	0.0f,	-1.0f,
		-0.625f, 0.5f,  -0.625f,	0.875f,  0.96975f,		0.0f,	0.0f,	-1.0f,	//0 8

		// DEtras
		-0.625f, -0.5f,  0.625f,	0.875f,  1.0f,			0.0f,	0.0f,	1.0f,	//0 8
		0.625f, -0.5f,  0.625f,		0.90625f,  1.0f,		0.0f,	0.0f,	1.0f,	//1
		0.625f, 0.5f,  0.625f,		0.90625f,  0.96975f,	0.0f,	0.0f,	1.0f,
		-0.625f, 0.5f,  0.625f,		0.875f,  0.96975f,		0.0f,	0.0f,	1.0f,	//0 8

		//Costado Izquierdo
		-0.625f, -0.5f,  -0.625f,	0.875f,  1.0f,			1.0f,	0.0f,	0.0f,	//0 8
		-0.625f, -0.5f,  0.625f,	0.90625f,  1.0f,		1.0f,	0.0f,	0.0f,	//1
		-0.625f, 0.5f,  0.625f,		0.90625f,  0.96975f,	1.0f,	0.0f,	0.0f,
		-0.625f, 0.5f,  -0.625f,	0.875f,  0.96975f,		1.0f,	0.0f,	0.0f,	//0 8

		//Costado Derecho
		0.625f, -0.5f,  -0.625f,	0.875f,  1.0f,			-1.0f,	0.0f,	0.0f,	//0 8
		0.625f, -0.5f,  0.625f,		0.90625f,  1.0f,		-1.0f,	0.0f,	0.0f,	//1
		0.625f, 0.5f,  0.625f,		0.90625f,  0.96975f,	-1.0f,	0.0f,	0.0f,
		0.625f, 0.5f,  -0.625f,		0.875f,  0.96975f,		-1.0f,	0.0f,	0.0f,	//0 8

		// Cabeza Arriba
		-0.625f, -0.5f,  0.625f,	0.875f,  1.0f,			0.0f,	-1.0f,	0.0f,	//1
		0.625f, -0.5f,  0.625f,		0.90625f,  1.0f,		0.0f,	-1.0f,	0.0f,	//2
		0.625f, -0.5f,  -0.625f,	0.90625f,  0.96975f,	0.0f,	-1.0f,	0.0f, //3
		-0.625f,-0.5f,  -0.625f,	0.875f,  0.96975f,		0.0f,	-1.0f,	0.0f,	//0 8
		

	};

	Mesh* egg = new Mesh();
	egg->CreateMesh(eggRobo_vertices, cubo_indices, 192, 66);
	meshList.push_back(egg);

}

void CrearEggRoboBrazo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat eggRobo_vertices[] = {
		// Down
		//x		y		z		S		T			NX		NY		NZ
		-0.625f, 1.0f,  0.625f,		0.875f,  1.0f,			0.0f,	1.0f,	0.0f,	//1
		0.625f, 1.0f,  0.625f,		0.90625f,  1.0f,		0.0f,	1.0f,	0.0f,	//2
		0.625f, 1.0f,  -0.625f,		0.90625f,  0.96975f,	0.0f,	1.0f,	0.0f, //3
		-0.625f,1.0f,  -0.625f,		0.875f,  0.96975f,		0.0f,	1.0f,	0.0f,	//0 8

			//4
		// Adelante
		-0.625f, -1.0f,  -0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	-1.0f,	//0 8
		0.625f, -1.0f,  -0.625f,	0.9375f,  1.0f,			0.0f,	0.0f,	-1.0f,	//1
		0.625f, 1.0f,  -0.625f,		0.9375f,  0.9385f,		0.0f,	0.0f,	-1.0f,
		-0.625f, 1.0f,  -0.625f,	0.90625f,  0.9385f,		0.0f,	0.0f,	-1.0f,	//0 8

		// DEtras
		-0.625f, -1.0f,  0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	1.0f,	//0 8
		0.625f, -1.0f,  0.625f,		0.9375f,  1.0f,			0.0f,	0.0f,	1.0f,	//1
		0.625f, 1.0f,  0.625f,		0.9375f,  0.9385f,		0.0f,	0.0f,	1.0f,
		-0.625f, 1.0f,  0.625f,		0.90625f,  0.9385f,		0.0f,	0.0f,	1.0f,	//0 8

		//Costado Izquierdo
		-0.625f, -1.0f,  -0.625f,	0.90625f,  1.0f,		1.0f,	0.0f,	0.0f,	//0 8
		-0.625f, -1.0f,  0.625f,	0.9375f,  1.0f,			1.0f,	0.0f,	0.0f,	//1
		-0.625f, 1.0f,  0.625f,		0.9375f,  0.9385f,		1.0f,	0.0f,	0.0f,
		-0.625f, 1.0f,  -0.625f,	0.90625f,  0.9385f,		1.0f,	0.0f,	0.0f,	//0 8

		//Costado Derecho
		0.625f, -1.0f,  -0.625f,	0.90625f,  1.0f,		-1.0f,	0.0f,	0.0f,	//0 8
		0.625f, -1.0f,  0.625f,		0.9375f,  1.0f,			-1.0f,	0.0f,	0.0f,	//1
		0.625f, 1.0f,  0.625f,		0.9375f,  0.9385f,		-1.0f,	0.0f,	0.0f,
		0.625f, 1.0f,  -0.625f,		0.90625f,  0.9385f,		-1.0f,	0.0f,	0.0f,	//0 8

		// Cabeza Arriba
		-0.625f, -1.0f,  0.625f,	0.90625f,  1.0f,		0.0f,	-1.0f,	0.0f,	//1
		0.625f, -1.0f,  0.625f,		0.9375f,  1.0f,			0.0f,	-1.0f,	0.0f,	//2
		0.625f, -1.0f,  -0.625f,	0.9375f,  0.9385f,		0.0f,	-1.0f,	0.0f, //3
		-0.625f,-1.0f,  -0.625f,	0.90625f,  0.9385f,		0.0f,	-1.0f,	0.0f,	//0 8


	};

	Mesh* egg = new Mesh();
	egg->CreateMesh(eggRobo_vertices, cubo_indices, 192, 66);
	meshList.push_back(egg);

}


void CrearEggRoboPie()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,

	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat eggRobo_vertices[] = {
		// Arriba
		//x		y		z		S		T			NX		NY		NZ
		-1.25f, 0.625f,  3.25f,		0.125f,  0.75f,			0.0f,	-1.0f,	0.0f,	//1
		1.25f, 0.625f,  3.25f,		0.21875f,  0.75f,		0.0f,	-1.0f,	0.0f,	//2
		1.25f, 0.625f,  -1.25f,		0.21875f,  0.875,		0.0f,	-1.0f,	0.0f, //3
		-1.25f,0.625f,  -1.25f,		0.125f,  0.875f,		0.0f,	-1.0f,	0.0f,	//0 8

		// Adelante
		-1.25f, 0.625f,  3.25f,		0.125f,  0.875f,		0.0f,	0.0f,	-1.0f,	//1
		1.25f, 0.625f,  3.25f,		0.21875f,  0.875f,		0.0f,	0.0f,	-1.0f,	//2
		1.25f, -0.625f,  3.25f,		0.21875f,  0.8f,		0.0f,	0.0f,	-1.0f,	//2
		-1.25f, -0.625f,  3.25f,	0.125f,  0.8f,			0.0f,	0.0f,	-1.0f,	//1
		

		// DEtras
		-1.25f, -0.625f,  -1.25f,	0.125f,  0.8f,			0.0f,	0.0f,	1.0f,	//0 8
		1.25f, -0.625f,  -1.25f,	0.21875f,  0.8f,		0.0f,	0.0f,	1.0f,	//1
		1.25f, 0.625f,  -1.25f,		0.21875f,  0.875f,		0.0f,	0.0f,	1.0f,
		-1.25f, 0.625f,  -1.25f,	0.125f,  0.875f,		0.0f,	0.0f,	1.0f,	//0 8

		//Costado Izquierdo
		-1.25f, -0.625f,  -1.25f,	0.4375f,  0.875f,		1.0f,	0.0f,	0.0f,	//0 8
		-1.25f, -0.625f,  3.25f,	0.4375f,  0.75f,		1.0f,	0.0f,	0.0f,	//1
		-1.25f, 0.625f,  3.25f,		0.375f,  0.75f,			1.0f,	0.0f,	0.0f,
		-1.25f, 0.625f,  -1.25f,	0.375f,  0.875f,		1.0f,	0.0f,	0.0f,	//0 8

		//Costado Derecho
		1.25f, -0.625f,  -1.25f,	0.4375f,  0.875f,		-1.0f,	0.0f,	0.0f,	//0 8
		1.25f, -0.625f,  3.25f,		0.4375f,  0.75f,		-1.0f,	0.0f,	0.0f,	//1
		1.25f, 0.625f,  3.25f,		0.375f,  0.75f,			-1.0f,	0.0f,	0.0f,
		1.25f, 0.625f,  -1.25f,		0.375f,  0.875f,		-1.0f,	0.0f,	0.0f,	//0 8

		//Abajo
		-1.25f, -0.625f,  3.25f,	0.25f,  0.75f,			0.0f,	1.0f,	0.0f,	//1
		1.25f, -0.625f,  3.25f,		0.33875f,  0.75f,		0.0f,	1.0f,	0.0f,	//2
		1.25f, -0.625f,  -1.25f,	0.33875f,  0.875,		0.0f,	1.0f,	0.0f, //3
		-1.25f,-0.625f,  -1.25f,	0.25f,  0.875f,			0.0f,	1.0f,	0.0f,	//0 8


	};

	Mesh* egg = new Mesh();
	egg->CreateMesh(eggRobo_vertices, cubo_indices, 192, 66);
	meshList.push_back(egg);

}

void CrearEggRoboMano()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10,11,8,

		12,13,14,
		14,15,12,

		16,17,18,
		18,19,16,

		20,21,22,
		22,23,20,


		//// back
		//8, 9, 10,
		//10, 11, 8,

		//// left
		//12, 13, 14,
		//14, 15, 12,
		//// bottom
		//16, 17, 18,
		//18, 19, 16,
		//// top
		//20, 21, 22,
		//22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat eggRobo_vertices[] = {
		// Arriba
		//x		y		z		S		T			NX		NY		NZ
		-1.25f, 1.75f,  1.25f,		0.25f,  0.75f,		0.0f,	-1.0f,	0.0f,	//1
		1.25f, 1.75f,  1.25f,		0.315f,  0.75f,		0.0f,	-1.0f,	0.0f,	//2
		1.25f, 1.75f,  -1.25f,		0.315f,  0.685,		0.0f,	-1.0f,	0.0f, //3
		-1.25f,1.75f,  -1.25f,		0.25f,  0.685f,		0.0f,	-1.0f,	0.0f,	//0 8

			//4
		// Adelante
		-1.25f, 1.75f,  1.25f,		0.0f,  0.75f,		0.0f,	0.0f,	-1.0f,	//1
		1.25f, 1.75f,  1.25f,		0.0625f,  0.75f,	0.0f,	0.0f,	-1.0f,	//2
		1.25f, -1.75f,  1.25f,		0.0625f,  0.625f,	0.0f,	0.0f,	-1.0f,	//2
		-1.25f,-1.75f,  1.25f,		0.0f,  0.625f,		0.0f,	0.0f,	-1.0f,	//1


		// DEtras
		-1.25f, -1.75f,  -1.25f,	0.0625f,  0.625f,	0.0f,	0.0f,	1.0f,	//0 8
		1.25f, -1.75f,  -1.25f,		0.125f,  0.625f,	0.0f,	0.0f,	1.0f,	//1
		1.25f, 1.75f,  -1.25f,		0.125f,  0.75f,		0.0f,	0.0f,	1.0f,
		-1.25f, 1.75f,  -1.25f,		0.0625f,  0.75f,	0.0f,	0.0f,	1.0f,	//0 8

		//Costado Izquierdo
		-1.25f, -1.75f,  -1.25f,	0.125f,  0.625f,	1.0f,	0.0f,	0.0f,	//0 8
		-1.25f, -1.75f,  1.25f,		0.1875f,  0.625f,	1.0f,	0.0f,	0.0f,	//1
		-1.25f, 1.75f,  1.25f,		0.1875f,  0.75f,	1.0f,	0.0f,	0.0f,
		-1.25f, 1.75f,  -1.25f,		0.125f,  0.75f,		1.0f,	0.0f,	0.0f,	//0 8

		//Costado Derecho
		1.25f, -1.75f,  -1.25f,		0.125f,  0.625f,	-1.0f,	0.0f,	0.0f,	//0 8
		1.25f, -1.75f,  1.25f,		0.1875f,  0.625f,	-1.0f,	0.0f,	0.0f,	//1
		1.25f, 1.75f,  1.25f,		0.1875f,  0.75f,	-1.0f,	0.0f,	0.0f,
		1.25f, 1.75f,  -1.25f,		0.125f,  0.75f,		-1.0f,	0.0f,	0.0f,	//0 8

		//Abajo
		-1.25f, -1.75f,  1.25f,		0.25f,  0.685f,		0.0f,	1.0f,	0.0f,	//1
		1.25f, -1.75f,  1.25f,		0.315f,  0.685f,	0.0f,	1.0f,	0.0f,	//2
		1.25f, -1.75f,  -1.25f,		0.315f,  0.625,		0.0f,	1.0f,	0.0f, //3
		-1.25f,-1.75f,  -1.25f,		0.25f,  0.625f,		0.0f,	1.0f,	0.0f,	//0 8


	};

	Mesh* egg = new Mesh();
	egg->CreateMesh(eggRobo_vertices, cubo_indices, 192, 66);
	meshList.push_back(egg);

}


void CrearPhineas()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		4, 5, 6,
		6, 7, 4,
		// back
		8, 9, 10,
		10, 11, 8,

		// left
		12, 13, 14,
		14, 15, 12,
		// bottom
		16, 17, 18,
		18, 19, 16,
		// top
		20, 21, 22,
		22, 23, 20,
	};
	//Ejercicio 1: reemplazar con sus dados de 6 caras texturizados, agregar normales
	// average normals
	GLfloat cubo_vertices[] = {
		// front
		//x		y		z		S		T			NX		NY		NZ
		-0.5f, -0.5f,  0.5f,	0.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -0.5f,  0.5f,		10.0f,  0.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  0.5f,  0.5f,		10.0f,  10.0f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  0.5f,  0.5f,	0.0f,	10.0f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -0.5f,  0.5f,	    0.0f,  0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f, -0.5f,  -0.5f,	10.0f,	0.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  -0.5f,	10.0f,	10.0f,		-1.0f,	0.0f,	0.0f,
		0.5f,  0.5f,  0.5f,	    0.0f,	10.0f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -0.5f, -0.5f,	10.0f,  0.00f,		0.0f,	0.0f,	1.0f,
		0.5f, -0.5f, -0.5f,		0.0f,  0.00f,		0.0f,	0.0f,	1.0f,
		0.5f,  0.5f, -0.5f,		0.0f,  10.0f,		0.0f,	0.0f,	1.0f,
		-0.5f,  0.5f, -0.5f,	10.0f,  10.0f,    	0.0f,   0.0f,   1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -0.5f,  -0.5f,	10.0f,  10.0f,		1.0f,	0.0f,	0.0f,
		-0.5f, -0.5f,  0.5f,	0.0f,	10.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  0.5f,	0.0f,	0.0f,		1.0f,	0.0f,	0.0f,
		-0.5f,  0.5f,  -0.5f,	10.0f,	0.0f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -0.5f,  0.5f,	10.0f,  10.0f,		0.0f,	1.0f,	0.0f,
		0.5f,  -0.5f,  0.5f,	0.0f,  10.0f,		0.0f,	1.0f,	0.0f,
		 0.5f, -0.5f,  -0.5f,	0.0f,  0.0f,		0.0f,	1.0f,	0.0f,
		-0.5f, -0.5f,  -0.5f,	10.0f,  10.0f,		0.0f,   1.0f,   0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 0.5f,  0.5f,	0.0f,  10.0f,    	0.0f,	-1.0f,	0.0f,
		 0.5f,  0.5f,  0.5f,	10.0f,  10.0f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 0.5f,  -0.5f,	10.0f,  0.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 0.5f,  -0.5f,	0.0f,	0.0f,		0.0f,	-1.0f,	0.0f,

	};

	Mesh* dado = new Mesh();
	dado->CreateMesh(cubo_vertices, cubo_indices, 192, 36);
	meshList.push_back(dado);

}





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,  	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,		0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado();
	
	brickTexture = Texture("Textures/ladrillo_hill.tga");
	brickTexture.LoadTextureA();
	greenTexture = Texture("Textures/green_hill.tga");
	greenTexture.LoadTextureA();
	lawnTexture = Texture("Textures/phineas_lawn_wflower.tga");
	lawnTexture.LoadTextureA();
	beachTexture = Texture("Textures/playa.tga");
	beachTexture.LoadTextureA();

	EggRobo = Texture("Textures/eggrobo.tga");
	EggRobo.LoadTextureA();

	CrearEggRobo();
	CrearEggRoboArticulacion();
	CrearEggRoboBrazo();
	CrearEggRoboPie();
	CrearEggRoboMano();

	Spring = Model();
	Spring.LoadModel("Models/spring.obj");


	agua = Texture("Textures/agua.tga");
	agua.LoadTextureA();
	bridgeTexture = Texture("Textures/maderavoxel.tga");
	bridgeTexture.LoadTextureA();
	barandalTexture = Texture("Textures/madera2.tga");
	barandalTexture.LoadTextureA();
	perryTexture = Texture("Textures/Image_0.png");
	
	
	Ferb = Model();
	Ferb.LoadModel("Models/ferb.obj");
	
	PerryB = Model();
	PerryB.LoadModel("Models/perry/perry_body.obj");

	Torre = Model();
	Torre.LoadModel("Models/torre.obj");
	PerryLL = Model();
	PerryLL.LoadModel("Models/perry/perry_l_foot.obj");

	PerryRL = Model();
	PerryRL.LoadModel("Models/perry/perry_r_foot.obj");

	PerryLA  = Model();
	PerryLA.LoadModel("Models/perry/perry_l_arm.obj");

	PerryRA = Model();
	PerryRA.LoadModel("Models/perry/perry_R_arm.obj");

	Muralla = Model();
	Muralla.LoadModel("Models/muralla.obj");

	Faro_Unleashed = Model();
	Faro_Unleashed.LoadModel("Models/faro_unl.obj");



	Palm = Model();
	Palm.LoadModel("Models/palm_tree.obj");


	TorrePrincesa = Model();
	TorrePrincesa.LoadModel("Models/torreprincesa.obj");

	std::vector<std::string> skyboxFaces;
	//skyboxFaces.push_back("Textures/Skybox/skybox_skyjungle_day.tga"); // Lado
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); // Lado
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Inverso
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Abajo
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day.tga"); //Arriba
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Phineas
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Sonic

	std::vector<std::string> skyboxFacesNight;
	//skyboxFaces.push_back("Textures/Skybox/skybox_skyjungle_day.tga"); // Lado
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); // Lado
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Inverso
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Abajo
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night.tga"); //Arriba
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Phineas
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Sonic

	skybox = Skybox(skyboxFaces);
	skyboxDay = Skybox(skyboxFaces);
	skyboxNight = Skybox(skyboxFacesNight);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,//color
		0.03f, 0.3f,//0.3 comp ambienta
		0.0f, 1.0f, 0.0f); //infinito derecha

	//AUxiliar para la luz direccional
	 
	mainLightAuxiliar[0] = mainLight;
	mainLightAuxiliar[1] = DirectionalLight(1.0f, 1.0f, 1.0f,//color
		
		0.5f, 0.3f,//0.3 comp ambienta
		0.0f, 1.0f, 0.0f); //infinito derecha

	mainLight = mainLightAuxiliar[1];
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	unsigned int spotLightCount = 0;
	//linterna
	/*spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;*/

	//luz fija Faro
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f, //coef varia intensidad
		-20.0f, 5.0f, 40.0f,//pos
		0.0f, -1.0f, 0.0f,//dir
		1.0f, 0.0f, 0.0f,//ecua
		80.0f);//angulo  reduce area de alcance
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f, //coef varia intensidad
		20.0f, 5.0f, 40.0f,//pos
		0.0f, -1.0f, 0.0f,//dir
		1.0f, 0.0f, 0.0f,//ecua
		80.0f);//angulo  reduce area de alcance
	spotLightCount++;

	//luz de helic�ptero

	////luz de faro
	//spotLights[1] = SpotLight(0.0f, 1.0f, 1.0f,//color
	//	1.0f, 2.0f, //coef varia intensidad
	//	-21.50, 2.0f, 1.0f,//pos
	//	-1.0f, 0.0f, 0.0f,//dir
	//	1.0f,0.60f,0.00f,//ecua
	//	50.0f);//angulo  reduce area de alcance
	//spotLightCount++;

	////luz de faro
	//spotLights[2] = SpotLight(1.0f, 0.0f, 1.0f,
	//	1.0f, 2.0f, //coef varia intensidad
	//	-21.50, 2.0f, -1.0f,//pos
	//	-1.0f, 0.0f, 0.0f,//dir
	//	1.0f, 0.5f, 0.0f,//ecua
	//	50.0f);//angulo  reduce area de alcance
	//spotLightCount++;


	////luz de heliocopterrrr
	//spotLights[3] = SpotLight(0.70f, 0.30f, 0.10f,
	//	1.0f, 2.0f, //coef varia intensidad
	//	0.0f, 3.0f, -1.0,//pos
	//	0.0f, -1.0f, 0.0f,//dir
	//	1.0f, 0.1f, 0.0f,//ecua
	//	70.0f);//angulo  reduce area de alcance
	//spotLightCount++;


	float cambios = 0.0f;
	time_skybox = 0.0f;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	
	/*CSAMARA DE ARRIBAD*/
	bool cam1 = true;
	camera = Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);

	
	camera2 = Camera(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,-90.0f/*-90.0f+mainWindow.getr1()*/, 5.0f, 0.5f);

	camera3 = Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);

	float articulacionpelvis = 0;
	float articulacionpelvis1 = 0;
	float articulacionhombro = 0;
	float articulacionhombro1 = 0;
	float avance = 0.0f;

	bool regreso = false;
	bool pie = false;
	
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(),true);

		if (pie == false) {
			if (articulacionpelvis >= 0.0f and regreso == false) {
				articulacionpelvis += 1.0f;
				articulacionhombro += 1.0f;
				if (articulacionpelvis >= 45.0f) {
					regreso = true;
				}
			}
			else if (articulacionpelvis <= 45.0f and regreso == true) {
				articulacionpelvis -= 1.0f;
				articulacionhombro -= 1.0f;
				if (articulacionpelvis <= 0.0f) {
					regreso = false;
					pie = true;
				}
			}
			avance += 0.1f * deltaTime;
		}
		else if (pie = true) {
			if (articulacionpelvis1 >= 0.0f and regreso == false) {
				articulacionpelvis1 += 1.0f;
				articulacionhombro -= 1.0f;
				if (articulacionpelvis1 >= 45.0f) {
					regreso = true;
				}
			}
			else if (articulacionpelvis1 <= 45.0f and regreso == true) {
				articulacionpelvis1 -= 1.0f;
				articulacionhombro += 1.0f;
				if (articulacionpelvis1 <= 0.0f) {
					regreso = false;
					pie = false;
				}
			}
			avance += 0.1f *deltaTime;
		}

		
		/*if (mainWindow.getcam1()) {
			camera = camera2;
			camera2.keyControl(mainWindow.getsKeys(), deltaTime);
		}
		else {
			camera = camera3;
			camera3.keyControl(mainWindow.getsKeys(), deltaTime);
			camera3.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(), false);

		}
		std::cout << "cam1" << (mainWindow.getcam1()) << std::endl;*/


		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//skyboxdaynight = mainWindow.nightT();
		/*if (time_skybox < (duracion_dia/2.0f)) {
			skybox = skyboxDay;
			time_skybox += 1.0f;
			mainLight = mainLightAuxiliar[1];
			spotLightCount = 0;
		}
		else {
			skybox = skyboxNight;
			time_skybox += 1.0f;
			mainLight = mainLightAuxiliar[0];
			spotLightCount = 2;
			if (time_skybox > duracion_dia) {
				time_skybox = 0.0f;
				printf("Cambio %f'\n", cambios);
				cambios += 1.0f;
			}
		}*/
		
		
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		//spotLights[1].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + 1.0f ));
		//spotLights[2].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + -1.0f));
		//spotLights[3].SetPos(glm::vec3(mainWindow.getmuevex() + 0.0f, mainWindow.getmuevey() + 3.0f,  mainWindow.getmuevez() + -1.0));

		


		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modeleggrobo(1.0);
		glm::mat4 modeleggroboArt1(1.0);
		glm::mat4 modeleggroboArt2(1.0);
		glm::mat4 modeleggroboArt1Brazo(1.0);
		glm::mat4 modeleggroboArt2Brazo(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		// ==========================================  EGROBO  ==================================================
		model = glm::mat4(1.0);
		
		model = glm::translate(model, glm::vec3(0.0f, 6.0f, avance));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		modeleggrobo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//dadoDoceTexture.UseTexture();
		meshList[4]->RenderMesh();

		//===========================================   PIERNA DERECHA   =======================================
		//Articulacion Derecha Pelvis
		model = modeleggrobo;
		model = glm::translate(model, glm::vec3(-1.5f, 4.5f, 1.0f));
		model = glm::rotate(model, -articulacionpelvis * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Derecha Pierna Muslo
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Derecha Pierna Rodilla
		model = modeleggroboArt2;

		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::rotate(model, articulacionpelvis * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Pierna Pantorilla
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		//Derecha Pierna Tobillo
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Pie Derecha
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.25f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[7]->RenderMesh();




		//===========================================   PIERNA IZQUIERDA   =======================================
		//Articulacion Izquierda Pelvis
		model = modeleggrobo;
		model = glm::translate(model, glm::vec3(1.5f, 4.5f, 1.0f));
		model = glm::rotate(model, -articulacionpelvis1 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		modeleggroboArt1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Izquierda Pierna Muslo
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Izquierda Pierna Rodilla
		model = modeleggroboArt1;

		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::rotate(model, articulacionpelvis1 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modeleggroboArt1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Izquierda Pierna Pantorilla
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		//Izquierda Pierna Tobillo
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		modeleggroboArt1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Pie Izquierda
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.25f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[7]->RenderMesh();

		//===========================================   BRAZO IZQUIERDA   =======================================

		//Articulacion Derecha Hombro
		model = modeleggrobo;
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::translate(model, glm::vec3(-2.4f, 6.0f, 0.0f));
		model = glm::rotate(model, -articulacionhombro * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modeleggroboArt1Brazo = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Brazo 
		model = modeleggroboArt1Brazo;
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Articulacion Derecha Hombro
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Codo
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Mano Derecha
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();

		//===========================================   BRAZO DERECHA   =======================================

		//Articulacion Derecha Hombro
		model = modeleggrobo;
		model = glm::scale(model, glm::vec3(-1.5f, 1.5f, 1.5f));
		model = glm::translate(model, glm::vec3(-2.4f, 6.0f, 0.0f));
		model = glm::rotate(model, articulacionhombro * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modeleggroboArt2Brazo = model;

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Brazo 
		model = modeleggroboArt2Brazo;
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Articulacion Derecha Hombro
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Codo
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Mano Derecha
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();
		


		//PISTA
		//CARRIL DE AGUA
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * 1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * 2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * 3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * -1.0f, 0.0f,0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * -2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(escalaX * -3.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		agua.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//camino sonic

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX *2.0f , 0.0f, escalaZ * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * -2.0f, 0.0f, escalaZ * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//pasto laterales
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * 3.0f, 0.0f, escalaZ * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * -3.0f, 0.0f, escalaZ * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//cuadros atras
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
		model = glm::translate(model, glm::vec3(25.0f , 0.0f, 65.0f ));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-25.0f, 0.0f, 65.0f ));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//pasto enfrente sonic
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaZ * -0.0f, 0.0f, escalaX * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		greenTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//camino phineas

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * 2.0f, 0.0f, escalaZ * -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * -2.0f, 0.0f, escalaZ * -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		//pasto laterales
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * 3.0f, 0.0f, escalaZ * -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX * -3.0f, 0.0f, escalaZ * - 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();








		//cuadros atras
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
		model = glm::translate(model, glm::vec3(25.0f, 0.0f, -65.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 2.0f));
		model = glm::translate(model, glm::vec3(-25.0f, 0.0f, -65.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		//pasto enfrente sonic
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaZ * -0.0f, 0.0f, escalaX * -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();


		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(escalaX * -0.0f, 0.0f, escalaX * -7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		/*CAMINO	*/

		//SUDIDA 1
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(20.0f ,1.0f , 1.0f ));
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, 10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model= modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f,-1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		//SUBIDA 2
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-2.0f, 0.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//PLAIN

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		//puente 2



		//subida 1

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		//SUBIDA 2
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(20.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();




		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//PLAIN

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		bridgeTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();






		////baramd
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(30.50f, 1.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//plain
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();






		//BARANDAL 2
		////baramd
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(49.50f, 1.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//plain
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();




		//barandal 3


		////baramd
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-49.5f, 1.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//plain
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		//barandal 4


		////baramd
		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		model = glm::translate(model, glm::vec3(-30.50f, 1.0f, -10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		//plain
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();



		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();


		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 1.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		barandalTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		
		//Torres Lado Normal
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -125.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Torre.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();



		//Torres Lado Sonic

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 125.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Torre.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 100.0f));
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		//model = glm::translate(model, glm::vec3(40.0f, 0.0f, 100.0f));
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();

		
		

		//perry instancia

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f , 1.0f ));
		model = glm::translate(model, glm::vec3(30.50f,1.0f,-10.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PerryB.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.0f , 20.0f , 2.0f ));
		model = glm::rotate(model, mainWindow.getr1() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PerryLA.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(3.5f,20.0f,2.0f));
		model = glm::rotate(model, mainWindow.getr1() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PerryRA.RenderModel();

		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.00f,9.0f,2.0f));
		model = glm::rotate(model, mainWindow.getr2() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f + mainWindow.getr1(), 1.0f + mainWindow.getr2(), 1.0f + mainWindow.getr3()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PerryLL.RenderModel();


		model = modelaux;
		model = glm::translate(model, glm::vec3(4.0f + mainWindow.gets1(), 9.0f + mainWindow.gets2(), 2.0f + mainWindow.gets3()));
		model = glm::rotate(model, mainWindow.getr2() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		PerryRL.RenderModel();







	/*	model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f + mainWindow.getr1(), 1.0f + mainWindow.getr2(), 1.0f + mainWindow.getr3()));
		model = glm::translate(model, glm::vec3(30.50f + mainWindow.gets1(), 1.0f + mainWindow.gets2(), -10.0f + mainWindow.gets3()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		beachTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();*/

		/*std::cout << "S1.-> "<<mainWindow.gets1() << std::endl;
		std::cout << "S2.-> " << mainWindow.gets2() << std::endl;
		std::cout << "S3.-> " << mainWindow.gets3() << std::endl;

		std::cout << "R1.-> " << mainWindow.getr1() << std::endl;
		std::cout << "R2.-> " << mainWindow.getr2() << std::endl;
		std::cout << "R3.-> " << mainWindow.getr3() << std::endl;*/















		//model = glm::mat4(1.0);
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		////model = glm::translate(model, glm::vec3(-45.0f, 0.0f, 2.5f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//Ferb.RenderModel();


		// Lado de Sonic
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Spring.RenderModel();
		
		
		
		// Palmeras

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-60.0f, 0.0f, 120.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Palm.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 140.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Palm.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(60.0f, 0.0f, 120.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Palm.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 140.0f));
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Palm.RenderModel();





		// Faros
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 40.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Faro_Unleashed.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 40.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Faro_Unleashed.RenderModel();




		//Murallas Lado Sonic Arriba
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(60.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-60.0f, 0.0f, 150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		//Murallas Lado Phineas Arriba
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -150.0f)); //80 Lado
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(20.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(60.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-60.0f, 0.0f, -150.0f)); //80 Lado
		//model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();
		// Lado Negativo
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -140.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -120.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -100.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -80.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -60.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -40.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, -20.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 0.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 20.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 40.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 60.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 80.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 100.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 120.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 0.0f, 140.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		//Lado Positivo

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -140.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -120.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -100.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -80.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -60.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -40.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, -20.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 0.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 20.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 40.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 60.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 80.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 100.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 120.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 0.0f, 140.0f)); //80 Lado
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Muralla.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
