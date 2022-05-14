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

float toffsetu = 0.0f;
float toffsetv = 0.0f;

//Variables para animación
float Salto;
float SaltoOffset;
bool salta;
bool baja;
float mov;
float movOffset;

float movX;
float movZ;
float movY;
float anguloV;
float rotar;
float PuntoZ;
float PuntoY;
float PuntoX;
float radio;
float rotOffset;

float movTX;
float movTZ;
float beta;

float festejoY;
float rotFestejo;
bool festejo;
bool saltaFestejo;
bool bajaFestejo;
float festejOffset;
float festejoH;

//loop

float loopX ;
float loopY;
float loopZ ;
float loopAngulo ;

//variables para animación
float movCoche, movCocheDosX, movCocheTresX, movCocheDosZ;
float movHelic;
float movHelOffset;
float rotllanta, rotllantaDos;
float rotllantaOffset;
float rotaHelic;
float anguloCoche, rotaCocheDos;
bool avanza, avanzaH, retrocedeH, avanzaCocheDos;
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;





GLint skyboxdaynight;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Camera camera2;
Camera camera3;
Camera camera4;

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
Texture FlechaTexture;

Model Ferb;
Model Dado_M;
Model Torre;

Model PerryB;
Model PerryLA;
Model PerryRA;
Model PerryLL;
Model PerryRL;

Model Muralla;

Model Loop;
Model LoopArriba;
Model LoopMitad;
Model LoopMitadAbajo;

Model Sonic;

Model Spring;
Model Faro_Unleashed;
Model Palm;
Model Tree;

Model TorrePrincesa;
Model TorreD;
Model BrazoB;
Model CabezaB;
Model CuerpoB;
Model PiernaB;
Model TorreD_1;
Model TorreD_2;
Model TorreD_3;
Model TorreD_4;

Model Lamp;

Skybox skybox;
Skybox skyboxDay;
Skybox skyboxNight;

float time_skybox;

//materiales
Material Material_brillante;
Material Material_opaco;
Material Material_metalic;


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
SpotLight spotLightsAux[MAX_SPOT_LIGHTS];


void inputKeyframes(bool* keys);


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
		-2.5f, 10.0f,  -2.5f,	0.25f,  1.0f,		0.0f,	0.0f,	1.0f,	//0 8
		2.5f, 10.0f,  -2.5f,	0.375f,  1.0f,		0.0f,	0.0f,	1.0f,	//1
		2.5f, 5.0f,  -2.5f,		0.375f,  0.875f,	0.0f,	0.0f,	1.0f,
		-2.5f, 5.0f,  -2.5f,	0.25f,  0.875f,		0.0f,	0.0f,	1.0f,	//0 8

		// DEtras
		-2.5f, 10.0f,  2.5f,	0.0f,  1.0f,		0.0f,	0.0f,	-1.0f,	//8
		2.5f, 10.0f,  2.5f,		0.125f,  1.0f,		0.0f,	0.0f,	-1.0f,	//9 8
		2.5f, 5.0f,  2.5f,		0.125f,  0.875f,	0.0f,	0.0f,	-1.0f,	//10
		-2.5f, 5.0f,  2.5f,		0.0f,  0.875f,		0.0f,	0.0f,	-1.0f,	//11 8

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
		-0.625f, -0.5f,  -0.625f,	0.875f,  1.0f,			0.0f,	0.0f,	1.0f,	//0 8
		0.625f, -0.5f,  -0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	1.0f,	//1
		0.625f, 0.5f,  -0.625f,		0.90625f,  0.96975f,	0.0f,	0.0f,	1.0f,
		-0.625f, 0.5f,  -0.625f,	0.875f,  0.96975f,		0.0f,	0.0f,	1.0f,	//0 8

		// DEtras
		-0.625f, -0.5f,  0.625f,	0.875f,  1.0f,			0.0f,	0.0f,	-1.0f,	//0 8
		0.625f, -0.5f,  0.625f,		0.90625f,  1.0f,		0.0f,	0.0f,	-1.0f,	//1
		0.625f, 0.5f,  0.625f,		0.90625f,  0.96975f,	0.0f,	0.0f,	-1.0f,
		-0.625f, 0.5f,  0.625f,		0.875f,  0.96975f,		0.0f,	0.0f,	-1.0f,	//0 8

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
		-0.625f, -1.0f,  -0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	1.0f,	//0 8
		0.625f, -1.0f,  -0.625f,	0.9375f,  1.0f,			0.0f,	0.0f,	1.0f,	//1
		0.625f, 1.0f,  -0.625f,		0.9375f,  0.9385f,		0.0f,	0.0f,	1.0f,
		-0.625f, 1.0f,  -0.625f,	0.90625f,  0.9385f,		0.0f,	0.0f,	1.0f,	//0 8

		// DEtras
		-0.625f, -1.0f,  0.625f,	0.90625f,  1.0f,		0.0f,	0.0f,	-1.0f,	//0 8
		0.625f, -1.0f,  0.625f,		0.9375f,  1.0f,			0.0f,	0.0f,	-1.0f,	//1
		0.625f, 1.0f,  0.625f,		0.9375f,  0.9385f,		0.0f,	0.0f,	-1.0f,
		-0.625f, 1.0f,  0.625f,		0.90625f,  0.9385f,		0.0f,	0.0f,	-1.0f,	//0 8

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

void CreateAgua()
{


	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-70.0f, 0.0f, -10.0f,		0.0f, 0.0f,			0.0f, -1.0f, 0.0f,
		70.0f, 0.0f, -10.0f,		10.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-70.0f, 0.0f, 10.0f,		0.0f, 10.0f,  		0.0f, -1.0f, 0.0f,
		70.0f, 0.0f, 10.0f,			10.0f, 10.0f,		0.0f, -1.0f, 0.0f
	};


	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}

void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

///////////////////////////////KEYFRAMES/////////////////////


bool animacion = false;



//NEW// Keyframes
float posXavion = 0.0, posYavion = 0.0, posZavion = 0;
float movAvion_x = 0.0f, movAvion_y = 0.0f, movAvion_z = 0.0f;
float giroAvion = 0;

float posXTorrDF_1 = 0.0, posYTorrDF_1 = 0.0, posZTorrDF_1 = 0;
float movTorrDF_1_x = 0.0f, movTorrDF_1_y = 0.0f, movTorrDF_1_z = 0.0f;
float giroTorrDF_1 = 0;

float posXTorrDF_2 = 0.0, posYTorrDF_2 = 0.0, posZTorrDF_2 = 0;
float movTorrDF_2_x = 0.0f, movTorrDF_2_y = 0.0f, movTorrDF_2_z = 0.0f;
float giroTorrDF_2 = 0;

float posXTorrDF_3 = 0.0, posYTorrDF_3 = 0.0, posZTorrDF_3 = 0;
float movTorrDF_3_x = 0.0f, movTorrDF_3_y = 0.0f, movTorrDF_3_z = 0.0f;
float giroTorrDF_3 = 0;

float posXTorrDF_4 = 0.0, posYTorrDF_4 = 0.0, posZTorrDF_4 = 0;
float movTorrDF_4_x = 0.0f, movTorrDF_4_y = 0.0f, movTorrDF_4_z = 0.0f;
float giroTorrDF_4 = 0;


#define MAX_FRAMES 10  //num max de cuadros (valor grande)
int i_max_steps = 90; //numero de interpolcaciones entre un caudro y otro (mato ses igual a in between y es mas smooth)
int i_curr_steps = 2; //valor de keyframes guardado o declarado para sobreescribir esa info
typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float movAvion_x;		//Variable para PosicionX
	float movAvion_y;		//Variable para PosicionY
	float movAvion_z;
	float movAvion_xInc;		//Variable para IncrementoX
	float movAvion_yInc;		//Variable para IncrementoY
	float movAvion_zInc;
	float giroAvion;
	float giroAvionInc;

	float movTorrDF_1_x;		//Variable para PosicionX
	float movTorrDF_1_y;		//Variable para PosicionY
	float movTorrDF_1_z;
	float movTorrDF_1_xInc;		//Variable para IncrementoX
	float movTorrDF_1_yInc;		//Variable para IncrementoY
	float movTorrDF_1_zInc;
	float giroTorrDF_1;
	float giroTorrDF_1Inc;

	float movTorrDF_2_x;		//Variable para PosicionX
	float movTorrDF_2_y;		//Variable para PosicionY
	float movTorrDF_2_z;
	float movTorrDF_2_xInc;		//Variable para IncrementoX
	float movTorrDF_2_yInc;		//Variable para IncrementoY
	float movTorrDF_2_zInc;
	float giroTorrDF_2;
	float giroTorrDF_2Inc;


	float movTorrDF_3_x;		//Variable para PosicionX
	float movTorrDF_3_y;		//Variable para PosicionY
	float movTorrDF_3_z;
	float movTorrDF_3_xInc;		//Variable para IncrementoX
	float movTorrDF_3_yInc;		//Variable para IncrementoY
	float movTorrDF_3_zInc;
	float giroTorrDF_3;
	float giroTorrDF_3Inc;


	float movTorrDF_4_x;		//Variable para PosicionX
	float movTorrDF_4_y;		//Variable para PosicionY
	float movTorrDF_4_z;
	float movTorrDF_4_xInc;		//Variable para IncrementoX
	float movTorrDF_4_yInc;		//Variable para IncrementoY
	float movTorrDF_4_zInc;
	float giroTorrDF_4;
	float giroTorrDF_4Inc;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 2;			//introducir datos
bool play = false;
int playIndex = 0;

void saveFrame(void) //cuando se mande por teclado y lo guarde el grame
{
	printf("==============================\n");
	printf("Se guardó el frameindex %d\n", FrameIndex);
	printf("Valor movAvion_x %f\n", movAvion_x);
	printf("Valor movAvion_y %f\n", movAvion_y);
	printf("Valor movAvion_z %f\n", movAvion_z);
	printf("Valor giro %f\n", giroAvion);
	printf("==============================\n");

	KeyFrame[FrameIndex].movAvion_x = movAvion_x;
	KeyFrame[FrameIndex].movAvion_y = movAvion_y;
	KeyFrame[FrameIndex].movAvion_z = movAvion_z;
	KeyFrame[FrameIndex].giroAvion = giroAvion;
	FrameIndex++;
}

void resetElements(void)
{

	movAvion_x = KeyFrame[0].movAvion_x;
	movAvion_y = KeyFrame[0].movAvion_y;
	movAvion_z = KeyFrame[0].movAvion_z;
	giroAvion = KeyFrame[0].giroAvion;


	movTorrDF_1_x = KeyFrame[0].movTorrDF_1_x;
	movTorrDF_1_y = KeyFrame[0].movTorrDF_1_y;
	movTorrDF_1_z = KeyFrame[0].movTorrDF_1_z;
	giroTorrDF_1 = KeyFrame[0].giroTorrDF_1;

	movTorrDF_2_x = KeyFrame[0].movTorrDF_2_x;
	movTorrDF_2_y = KeyFrame[0].movTorrDF_2_y;
	movTorrDF_2_z = KeyFrame[0].movTorrDF_2_z;
	giroTorrDF_2 = KeyFrame[0].giroTorrDF_2;

	movTorrDF_3_x = KeyFrame[0].movTorrDF_3_x;
	movTorrDF_3_y = KeyFrame[0].movTorrDF_3_y;
	movTorrDF_3_z = KeyFrame[0].movTorrDF_3_z;
	giroTorrDF_3 = KeyFrame[0].giroTorrDF_3;

	movTorrDF_4_x = KeyFrame[0].movTorrDF_4_x;
	movTorrDF_4_y = KeyFrame[0].movTorrDF_4_y;
	movTorrDF_4_z = KeyFrame[0].movTorrDF_4_z;
	giroTorrDF_4 = KeyFrame[0].giroTorrDF_4;

}

void interpolation(void)
{
	KeyFrame[playIndex].movAvion_xInc = (KeyFrame[playIndex + 1].movAvion_x - KeyFrame[playIndex].movAvion_x) / i_max_steps;
	KeyFrame[playIndex].movAvion_yInc = (KeyFrame[playIndex + 1].movAvion_y - KeyFrame[playIndex].movAvion_y) / i_max_steps;
	KeyFrame[playIndex].movAvion_zInc = (KeyFrame[playIndex + 1].movAvion_z - KeyFrame[playIndex].movAvion_z) / i_max_steps;
	KeyFrame[playIndex].giroAvionInc = (KeyFrame[playIndex + 1].giroAvion - KeyFrame[playIndex].giroAvion) / i_max_steps;


	KeyFrame[playIndex].movTorrDF_1_xInc = (KeyFrame[playIndex + 1].movTorrDF_1_x - KeyFrame[playIndex].movTorrDF_1_x) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_1_yInc = (KeyFrame[playIndex + 1].movTorrDF_1_y - KeyFrame[playIndex].movTorrDF_1_y) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_1_zInc = (KeyFrame[playIndex + 1].movTorrDF_1_z - KeyFrame[playIndex].movTorrDF_1_z) / i_max_steps;
	KeyFrame[playIndex].giroTorrDF_1Inc = (KeyFrame[playIndex + 1].giroTorrDF_1 - KeyFrame[playIndex].giroTorrDF_1) / i_max_steps;


	KeyFrame[playIndex].movTorrDF_2_xInc = (KeyFrame[playIndex + 1].movTorrDF_2_x - KeyFrame[playIndex].movTorrDF_2_x) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_2_yInc = (KeyFrame[playIndex + 1].movTorrDF_2_y - KeyFrame[playIndex].movTorrDF_2_y) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_2_zInc = (KeyFrame[playIndex + 1].movTorrDF_2_z - KeyFrame[playIndex].movTorrDF_2_z) / i_max_steps;
	KeyFrame[playIndex].giroTorrDF_2Inc = (KeyFrame[playIndex + 1].giroTorrDF_2 - KeyFrame[playIndex].giroTorrDF_2) / i_max_steps;

	KeyFrame[playIndex].movTorrDF_3_xInc = (KeyFrame[playIndex + 1].movTorrDF_3_x - KeyFrame[playIndex].movTorrDF_3_x) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_3_yInc = (KeyFrame[playIndex + 1].movTorrDF_3_y - KeyFrame[playIndex].movTorrDF_3_y) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_3_zInc = (KeyFrame[playIndex + 1].movTorrDF_3_z - KeyFrame[playIndex].movTorrDF_3_z) / i_max_steps;
	KeyFrame[playIndex].giroTorrDF_3Inc = (KeyFrame[playIndex + 1].giroTorrDF_3 - KeyFrame[playIndex].giroTorrDF_3) / i_max_steps;

	KeyFrame[playIndex].movTorrDF_4_xInc = (KeyFrame[playIndex + 1].movTorrDF_4_x - KeyFrame[playIndex].movTorrDF_4_x) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_4_yInc = (KeyFrame[playIndex + 1].movTorrDF_4_y - KeyFrame[playIndex].movTorrDF_4_y) / i_max_steps;
	KeyFrame[playIndex].movTorrDF_4_zInc = (KeyFrame[playIndex + 1].movTorrDF_4_z - KeyFrame[playIndex].movTorrDF_4_z) / i_max_steps;
	KeyFrame[playIndex].giroTorrDF_4Inc = (KeyFrame[playIndex + 1].giroTorrDF_4 - KeyFrame[playIndex].giroTorrDF_4) / i_max_steps;


}


void animate(void)
{
	//Movimiento del objeto
	if (play)
	{
		if (i_curr_steps >= i_max_steps) //end of animation between frames?
		{
			playIndex++;
			printf("frane[%d]reproducido :\n", playIndex - 1);
			if (playIndex > FrameIndex - 2)	//end of total animation?
			{
				printf("ultimo frome es = %d\n", FrameIndex - 1);
				printf("termina animacion\n");
				playIndex = 0;
				play = false;
			}
			else //Next frame interpolations
			{
				//printf("entro aquí\n");
				i_curr_steps = 0; //Reset counter
				//Interpolation
				interpolation();
			}
		}
		else
		{
			//printf("se quedó aqui\n");
			//printf("max steps: %f", i_max_steps);
			//Draw animation
			movAvion_x += KeyFrame[playIndex].movAvion_xInc;
			movAvion_y += KeyFrame[playIndex].movAvion_yInc;
			movAvion_z += KeyFrame[playIndex].movAvion_zInc;
			giroAvion += KeyFrame[playIndex].giroAvionInc;

			movTorrDF_1_x += KeyFrame[playIndex].movTorrDF_1_xInc;
			movTorrDF_1_y += KeyFrame[playIndex].movTorrDF_1_yInc;
			movTorrDF_1_z += KeyFrame[playIndex].movTorrDF_1_zInc;
			giroTorrDF_1 += KeyFrame[playIndex].giroTorrDF_1Inc;


			movTorrDF_2_x += KeyFrame[playIndex].movTorrDF_2_xInc;
			movTorrDF_2_y += KeyFrame[playIndex].movTorrDF_2_yInc;
			movTorrDF_2_z += KeyFrame[playIndex].movTorrDF_2_zInc;
			giroTorrDF_2 += KeyFrame[playIndex].giroTorrDF_2Inc;


			movTorrDF_3_x += KeyFrame[playIndex].movTorrDF_3_xInc;
			movTorrDF_3_y += KeyFrame[playIndex].movTorrDF_3_yInc;
			movTorrDF_3_z += KeyFrame[playIndex].movTorrDF_3_zInc;
			giroTorrDF_3 += KeyFrame[playIndex].giroTorrDF_3Inc;


			movTorrDF_4_x += KeyFrame[playIndex].movTorrDF_4_xInc;
			movTorrDF_4_y += KeyFrame[playIndex].movTorrDF_4_yInc;
			movTorrDF_4_z += KeyFrame[playIndex].movTorrDF_4_zInc;
			giroTorrDF_4 += KeyFrame[playIndex].giroTorrDF_4Inc;


			i_curr_steps++;
		}

	}
}

/* FIN KEYFRAMES*/



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();
	CrearDado();
	CrearEggRobo();
	CrearEggRoboArticulacion();
	CrearEggRoboBrazo();
	CrearEggRoboPie();
	CrearEggRoboMano();
	CreateAgua();

	/*TEXTURAS*/
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
	Spring = Model();
	Spring.LoadModel("Models/spring.obj");
	Sonic = Model();
	Sonic.LoadModel("Models/sonic_spindash.obj");


	agua = Texture("Textures/agua.tga");
	agua.LoadTextureA();
	bridgeTexture = Texture("Textures/maderavoxel.tga");
	bridgeTexture.LoadTextureA();
	barandalTexture = Texture("Textures/madera2.tga");
	barandalTexture.LoadTextureA();
	perryTexture = Texture("Textures/Image_0.png");

	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	/*MODELOS*/
	
	Loop = Model();
	Loop.LoadModel("Models/loop.obj");

	LoopArriba = Model();
	LoopArriba.LoadModel("Models/loop_arriba.obj");

	LoopMitad = Model();
	LoopMitad.LoadModel("Models/loop_arriba.obj");

	LoopMitadAbajo = Model();
	LoopMitadAbajo.LoadModel("Models/loop_mitad_abajo.obj");

	Spring = Model();
	Spring.LoadModel("Models/spring.obj");

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

	PerryLA = Model();
	PerryLA.LoadModel("Models/perry/perry_l_arm.obj");

	PerryRA = Model();
	PerryRA.LoadModel("Models/perry/perry_R_arm.obj");

	Muralla = Model();
	Muralla.LoadModel("Models/muralla.obj");

	Faro_Unleashed = Model();
	Faro_Unleashed.LoadModel("Models/faro_unl.obj");

	Lamp = Model();
	Lamp.LoadModel("Models/lamp.obj");

	Palm = Model();
	Palm.LoadModel("Models/palm_tree.obj");

	Tree = Model();
	Tree.LoadModel("Models/tree.obj");


	TorrePrincesa = Model();
	TorrePrincesa.LoadModel("Models/torreprincesa.obj");

	TorreD_1 = Model();
	TorreD_1.LoadModel("Models/torreD_1.obj");
	TorreD_2 = Model();
	TorreD_2.LoadModel("Models/torreD_2.obj");
	TorreD_3 = Model();
	TorreD_3.LoadModel("Models/torreD_3.obj");
	TorreD_4 = Model();
	TorreD_4.LoadModel("Models/torreD_4.obj");

	CabezaB = Model();
	CabezaB.LoadModel("Models/cabezabarbaro.obj");

	CuerpoB = Model();
	CuerpoB.LoadModel("Models/cuerpobarbaro.obj");

	BrazoB = Model();
	BrazoB.LoadModel("Models/brazobarbaro.obj");

	PiernaB = Model();
	PiernaB.LoadModel("Models/piernabarbaro.obj");

	std::vector<std::string> skyboxFaces;
	//skyboxFaces.push_back("Textures/Skybox/skybox_skyjungle_day.tga"); // Lado
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); // Lado
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Inverso
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic_abajo.tga"); //Abajo
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day.tga"); //Arriba
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Phineas
	skyboxFaces.push_back("Textures/Skybox/skybox_sky_day_sonic.tga"); //Lado Sonic

	std::vector<std::string> skyboxFacesNight;
	//skyboxFaces.push_back("Textures/Skybox/skybox_skyjungle_day.tga"); // Lado
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); // Lado
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Inverso
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night.tga"); //Abajo
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night.tga"); //Arriba
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Phineas
	skyboxFacesNight.push_back("Textures/Skybox/skybox_sky_night_sonic.tga"); //Lado Sonic

	skybox = Skybox(skyboxFaces);
	skyboxDay = Skybox(skyboxFaces);
	skyboxNight = Skybox(skyboxFacesNight);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);
	Material_metalic = Material(0.0f,256);


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


	/*ARREGLO PRINCIPAL SPOTLIGHT*/
	//LUZ FARO 1
	spotLights[2] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f, 
		40.0f, 10.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		80.0f);
	spotLightCount++;

	//LUZ FARO 2
	spotLights[3] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f, 
		-40.0f, 10.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		80.0f);
	spotLightCount++;

	//LUZ ESTADI0 1
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.5f, 
		-70.0f, 40.0f, -41.0f,
		1.0f, -0.30f, -.70f,
		1.0f, 0.0f, 0.0f,
		60.0f);
	spotLightCount++;


	//LUZ ESTADIO 2
	spotLights[1] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.5f, //coef varia intensidad
		70.0f,40.0f, 41.0f,
		//0.0f, 6.0f, 30.0f,//pos
		-1.0f, -0.30f, .70f,//dir
		1.0f, 0.0f, 0.0f,//ecua
		60.0f);//angulo  reduce area de alcance
	spotLightCount++;



	/*ARREGLO AUXILIAR SPOTLIGHT*/
	//LUZ FARO 1
	spotLightsAux[0] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f,
		40.0f, 10.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		80.0f);
	spotLightCount++;

	//LUZ FARO 2
	spotLightsAux[1] = SpotLight(1.0f, 1.0f, 1.0f,
		3.0f, 0.5f,
		-40.0f, 10.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		80.0f);
	spotLightCount++;

	//LUZ ESTADI0 1
	spotLightsAux[2] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.5f,
		-70.0f, 40.0f, -41.0f,
		1.0f, -0.30f, -.70f,
		1.0f, 0.0f, 0.0f,
		60.0f);
	spotLightCount++;;


	//LUZ ESTADIO 2
	spotLightsAux[3] = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 0.5f, //coef varia intensidad
		70.0f, 40.0f, 41.0f,
		//0.0f, 6.0f, 30.0f,//pos
		-1.0f, -0.30f, .70f,//dir
		1.0f, 0.0f, 0.0f,//ecua
		60.0f);//angulo  reduce area de alcance
	spotLightCount++;;


	float cambios = 0.0f;
	time_skybox = 0.0f;


	movCoche = movCocheDosX = movCocheDosZ = anguloCoche = rotaCocheDos = movCocheTresX = 0.0f;
	movOffset = 0.05f;
	rotllanta = rotllantaDos = 0.0f;
	rotllantaOffset = 10.0f;
	float alturah = 0.0f;
	avanzaCocheDos = avanza = avanzaH = true;
	retrocedeH = false;
	movHelOffset = 0.5f;
	movHelic = 0.0f;
	rotaHelic = 0.0f;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

		//KEYFRAMES DECLARADOS INICIALES

	KeyFrame[0].movAvion_x = 0.0f;
	KeyFrame[0].movAvion_y = 0.0f;
	KeyFrame[0].movAvion_z = 0.0f;
	KeyFrame[0].giroAvion = 0;
	KeyFrame[0].movTorrDF_1_x = 0.0f;
	KeyFrame[0].movTorrDF_1_y = 0.0f;
	KeyFrame[0].movTorrDF_1_z = 0.0f;
	KeyFrame[0].giroTorrDF_1 = 0;
	KeyFrame[0].movTorrDF_2_x = 0.0f;
	KeyFrame[0].movTorrDF_2_y = 0.0f;
	KeyFrame[0].movTorrDF_2_z = 0.0f;
	KeyFrame[0].giroTorrDF_2 = 0;
	KeyFrame[0].movTorrDF_3_x = 0.0f;
	KeyFrame[0].movTorrDF_3_y = 0.0f;
	KeyFrame[0].movTorrDF_3_z = 0.0f;
	KeyFrame[0].giroTorrDF_3 = 0;

	KeyFrame[0].movTorrDF_4_x = 0.0f;
	KeyFrame[0].movTorrDF_4_y = 0.0f;
	KeyFrame[0].movTorrDF_4_z = 0.0f;
	KeyFrame[0].giroTorrDF_4 = 0;



	KeyFrame[1].movAvion_x = 0.0f;
	KeyFrame[1].movAvion_y = -54.0f;
	KeyFrame[1].movAvion_z = 3.0f;
	KeyFrame[1].giroAvion = -10;



	KeyFrame[1].movTorrDF_1_x = 17.0f;
	KeyFrame[1].movTorrDF_1_y = -42.0f;
	KeyFrame[1].movTorrDF_1_z = 1.0f;
	KeyFrame[1].giroTorrDF_1 = -10;


	KeyFrame[1].movTorrDF_2_x = -12.0f;
	KeyFrame[1].movTorrDF_2_y = -37.0f;
	KeyFrame[1].movTorrDF_2_z = 15.0f;
	KeyFrame[1].giroTorrDF_2 = -20;



	KeyFrame[1].movTorrDF_3_x = -42.0f;
	KeyFrame[1].movTorrDF_3_y = -3.0f;
	KeyFrame[1].movTorrDF_3_z =-12.0f;
	KeyFrame[1].giroTorrDF_3 = -90;


	KeyFrame[1].movTorrDF_4_x = -15.0f;
	KeyFrame[1].movTorrDF_4_y = -14.0f;
	KeyFrame[1].movTorrDF_4_z = -10.0f;
	KeyFrame[1].giroTorrDF_4 = -65;





	/*CSAMARA DE ARRIBAD*/
	bool cam1 = true;
	camera = Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 5.0f, 0.5f);
	camera2 = Camera(glm::vec3(0.0f, 20.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,-90.0f/*-90.0f+mainWindow.getr1()*/, 1.0f, 0.5f);
	camera3 = Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.5f, 0.5f);
	camera4 = Camera(glm::vec3(0.0f, 15.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 1.0f, 0.5f);



	float articulacionpelvis = 0;
	float articulacionpelvis1 = 0;
	float articulacionhombro = 0;
	float articulacionhombro1 = 0;
	float voltear = 180.0f;
	float giro = 1.0f;
	float avance = 0.0f;
	bool* keys = mainWindow.getsKeys();
	bool regreso = false;
	bool pie = false;
	

	
	//Para el salto
	Salto = 5.0f;
	SaltoOffset = 0.35f;
	salta = true;
	baja = false;
	
	//Para la vuelta 360
	movX = 0.0f;
	movZ = 0.0f;
	movY = 0.005f;
	movOffset= 0.2f;
	anguloV = 90.0f;
	rotar = 0.0f;
	PuntoZ = 30.0f;
	PuntoX = -160.0f;
	PuntoY = 10.0f;
	radio = 30.0f;
	rotOffset = 10.0;


	movTZ = 0.0f;
	movTX = 0.0f;
	beta = 900.0f;

	//Festejo
	festejoY = 5.0f;
	rotFestejo = 0.0f;
	festejo = true;
	saltaFestejo = true;
	bajaFestejo = true;
	festejOffset = 0.1f;
	festejoH = 0.0f;

	//Loop
	/*loopX = -60.0f;
	loopY = 0.0f;
	loopZ = 14.0f;
	loopAngulo = 270.0f;
	*/loopX = 60.0f;
	loopY = 5.0f;
	loopZ = 27.42f;
	loopAngulo = 270.0f;



	float avanceSpinDash = 0.1f;
	float aumentoz = 0.02f;
	float girospin = 0.0f;
	float movsetspin = 0.1f;
	//float PuntoX = 5.0f;
	float PuntoYSpin = 14.0f;
	float radioSpin = 10.0f;
	bool regresoloop = false;
	bool spot1 = false, spot2 = false;
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Subida
		

		//Loop
		if (regresoloop == false and loopX <= 60.0f and loopX >= -60.0f) {
			girospin += movsetspin * deltaTime;
			if (loopX >= -30.0f and loopX < 20.0f and loopY < 50.0f and loopY >= 0.0f and loopZ < 17.0f) {
				if (loopAngulo >= 0.0 and loopX < 30.0f and loopX > 0.0f and loopZ < 17.0f) {
					girospin += movsetspin * deltaTime;

					loopY = PuntoYSpin + radioSpin * glm::sin(loopAngulo * toRadians);
					loopX = 0 + radioSpin * glm::cos(loopAngulo * toRadians);
					//rotCocheY += rotOffset * deltaTime;
					loopAngulo += 0.5f * deltaTime;
					loopZ += aumentoz * deltaTime;
				}
				else {
					girospin += movsetspin * deltaTime ;
					loopX += avanceSpinDash * deltaTime;

				}
			}
			else if (loopX >= -30.0f and loopX < 20.0f and loopY < 50.0f and loopY >= 0.0f and loopZ < 27.42f) {
				girospin += movsetspin;
				if (loopAngulo >= 0.0 and loopX < 30.0f and loopX > -15.0f) {
					girospin += movsetspin * deltaTime;
					loopY = PuntoYSpin + radioSpin * glm::sin(loopAngulo * toRadians);
					loopX = 0 + radioSpin * glm::cos(loopAngulo * toRadians);
					//rotCocheY += rotOffset * deltaTime;
					loopAngulo += 0.5f * deltaTime;
					loopZ += aumentoz * deltaTime;
				}
				else {
					girospin += movsetspin * deltaTime;
					loopX += avanceSpinDash * deltaTime;
				}
			}
			else {
				loopX += avanceSpinDash * deltaTime;

				if (loopX >= 60.0f) {
					regresoloop = true;
					printf("True\n");
					loopX = 60.0f;
					loopY = 5.0f;
					loopZ = 27.42f;
					loopAngulo = 270.0f;

				}
			}
			
		}
		else if (regresoloop == true and loopX >= -60.0f) {
			girospin += movsetspin * deltaTime;

			if (loopX <= 30.0f and loopX > -20.0f and loopY < 50.0f and loopY >= 0.0f and loopZ > 20.0f) {

				if (loopAngulo >= 0.0 and loopX > -30.0f and loopX < 1.0f and loopZ > 17.5f) {

					girospin += movsetspin * deltaTime;
					loopY = PuntoYSpin + radioSpin * glm::sin(loopAngulo * toRadians);
					loopX = 0 + radioSpin * glm::cos(loopAngulo * toRadians);
					//rotCocheY += rotOffset * deltaTime;
					loopAngulo -= 0.5f * deltaTime;
					loopZ -= aumentoz * deltaTime;
				}
				else {
					girospin += movsetspin * deltaTime;
					loopX -= avanceSpinDash * deltaTime;
					//printf("LoopY %f'\n", loopY);
					//rotllanta += rotllantaOffset * deltaTime;
				}
			}
			else if (loopX <= 30.0f and loopX > -20.0f and loopY < 50.0f and loopY >= 0.0f and loopZ > 14.0f) {
				girospin += movsetspin * deltaTime;

				if (loopAngulo >= -90.0 and loopX > -30.0f and loopX < 30.0f) {
					printf("Entro?\n");
					girospin += movsetspin * deltaTime;
					loopY = PuntoYSpin + radioSpin * glm::sin(loopAngulo * toRadians);
					loopX = 0 + radioSpin * glm::cos(loopAngulo * toRadians);
					loopAngulo -= 0.5f * deltaTime;
					loopZ -= aumentoz * deltaTime ;
				}
				else {
					girospin += movsetspin * deltaTime;
					loopX -= avanceSpinDash * deltaTime;
				}
			}
			else {
				girospin += movsetspin * deltaTime;
				loopX -= avanceSpinDash * deltaTime;

				if (loopX <= -60.0f and regresoloop == true) {
					regresoloop = false;
					loopX = -60.0f;
					loopY = 5.0f;
					loopZ = 14.0f;
					loopAngulo = 270.0f;

				}
				
			}
			

		}
		

		



		/*SALTO*/
		if (Salto < 20.0f and salta) {
			Salto += SaltoOffset * deltaTime;
			rotar += rotOffset* deltaTime;
			if (rotar > 359.0f) {
				rotar = 0.0f;
			}
			if (Salto > 20) {
				salta = false;
				baja = true;
			}
		}
		if (baja) {
			Salto -= SaltoOffset * deltaTime;
			if (Salto < 5) {
				salta = true;
				baja = false;
			}
		}


		if (movX >= -180.0f and movZ < 8.0f and movZ > -20.0f) {
			if (anguloV > 45.0 and movX < -160.0f and movZ < 30.0f) {
				movZ = PuntoZ - radio * glm::sin(anguloV * toRadians);
				movX = PuntoX - radio * glm::cos(anguloV * toRadians);
				//rotCocY += rotOffset * deltaTime;
				anguloV -= 1.0f * deltaTime * 2;
			}
			else {
				movX -= movOffset * deltaTime;
			}
		}
		/*TORNADO*/

		movTZ = -50.0f + (1 + 0.1 * beta) * glm::sin(beta * toRadians);
		movTX =-10.0f + (1 + 0.1 * beta) * glm::cos(beta * toRadians);
		if (beta > 0.0f) {
				beta -= 1.f * deltaTime;
		}
		
		/*FESTEJO*/
		if (festejo) {
			if (festejoY < 15.0f and saltaFestejo) {
				festejoY += festejOffset * deltaTime;
				festejoH = 1.0f;
				rotFestejo = 180.0f;
				
				if (festejoY > 5) {
					saltaFestejo = false;
					bajaFestejo = true;
				}
			}
			if (bajaFestejo) {
				festejoY -= festejOffset * deltaTime;
				rotFestejo = 0.0f;
				festejoH = 0.0f;
				if (festejoY < 0) {
					saltaFestejo = true;
					bajaFestejo = false;
				}
			}

		}

		// Loop


			
		
		//Recibir eventos del usuario
		glfwPollEvents();



		/*MOVIMIENTO CAMARA CON PERSONAJE*/
		/*camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(),true);*/
		keys = mainWindow.getsKeys();
		if ((keys[GLFW_KEY_W] or keys[GLFW_KEY_A] or keys[GLFW_KEY_S] or keys[GLFW_KEY_D]) and (mainWindow.getcam1() == 2)) {
			//std::cout << "Voltear" << voltear << std::endl;
			if (keys[GLFW_KEY_A] ) {
				if ((voltear <= 270.0f and voltear >= 180.0f) or (voltear <= 180.0f and voltear >= 90.0f) ) {
					voltear += giro;
				}
				else if ((voltear <= 360.0f and voltear >= 270.0f) or (voltear >= 0.0f and voltear < 180.0f)) {
					voltear -= giro;
					if (voltear >= 360.0f or voltear <= 0.0f) {
						voltear = 360.0f;
					}
				}

				
			}else if (keys[GLFW_KEY_D] ) {
				if ((voltear <= 270.0f and voltear >= 180.0f) or (voltear <= 180.0f and voltear >= 90.0f)) {
					voltear -= giro;
				}

				else if ((voltear <= 360.0f and voltear >= 270.0f) or (voltear >= 0.0f and voltear <180.0f) ) {
					voltear += giro;
					if (voltear >= 360.0f or voltear <= 0.0f) {
						voltear = 0.0f;
					}
				}

			}

			if (keys[GLFW_KEY_W]) {
				if ((voltear <= 360.0f and voltear >= 270.0f) or (voltear <= 270.0f and voltear >= 180.0f)) {
					voltear -= giro;
					
				}
				else if ((voltear <= 180.0f and voltear >= 90.0f) or (voltear >= 0.0f and voltear < 90.0f)) {
					voltear += giro;

				}
				if (voltear >= 360.0f or voltear <= 0.0f) {
					voltear = 360.0f;
				}


			}
			else if (keys[GLFW_KEY_S]) {
				if ((voltear <= 360.0f and voltear >= 270.0f) or (voltear <= 270.0f and voltear >= 180.0f)) {
					voltear += giro;
					
				}
				else if ((voltear <= 180.0f and voltear >= 90.0f) or (voltear >= 0.0f and voltear < 90.0f)) {
					voltear -= giro;
					
				}
				if (voltear >= 360.0f or voltear <= 0.0f) {
					voltear = 360.0f;
				}

			}
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
				//avance += 0.1f * deltaTime;
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
				//avance += 0.1f *deltaTime;
			}


		}

		

		
		if (mainWindow.getcam1() == 0) {
			camera = camera2;
			camera2.keyControl(mainWindow.getsKeys(), deltaTime);
		}
		else {
			if (mainWindow.getcam1() == 2) {
				camera = camera3;
				camera3.keyControl(mainWindow.getsKeys(), deltaTime);
				camera3.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(), false);
			}
			else {
				camera = camera4;
				camera4.keyControl(mainWindow.getsKeys(), deltaTime);
				camera4.mouseControl(mainWindow.getXChange(), mainWindow.getYChange(), true);
			}
			

		}

		//para keyframes
		inputKeyframes(mainWindow.getsKeys());
		animate();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//skyboxdaynight = mainWindow.nightT();
		if (time_skybox < (duracion_dia/2.0f)) {
			skybox = skyboxDay;
			time_skybox += 1.0f;
			mainLight = mainLightAuxiliar[1];
			spotLightCount = 0;
			if (mainWindow.getsp1() == false && mainWindow.getsp2() == false)
				spotLightCount = 0;
			else
				if (mainWindow.getsp1() == true && mainWindow.getsp2() == true) {
					spotLightCount = 2;
					spotLights[0] = spotLightsAux[2];
					spotLights[1] = spotLightsAux[3];
				}
				else
					if (mainWindow.getsp1() == true && mainWindow.getsp2() == false) {
						spotLightCount = 1;
						spotLights[0] = spotLightsAux[2];
					}
					else {
						spotLightCount = 1;
						spotLights[0] = spotLightsAux[3];
					}

		}
		else {
			skybox = skyboxNight;
			time_skybox += 1.0f;
			mainLight = mainLightAuxiliar[0];
			spotLightCount = 4;
			spotLights[0] = spotLightsAux[0];
			spotLights[1] = spotLightsAux[1];
			spotLights[2] = spotLightsAux[2];
			spotLights[3] = spotLightsAux[3];
			if (mainWindow.getsp1() == false && mainWindow.getsp2() == false)
				spotLightCount = 2;
			else
				if (mainWindow.getsp1() == true && mainWindow.getsp2() == true) {
					spotLightCount = 4;
				}
				else
					if (mainWindow.getsp1() == true && mainWindow.getsp2() == false) {
						spotLightCount = 3;
						spotLights[2] = spotLightsAux[2];
					}
					else {
						spotLightCount = 3;
						spotLights[2] = spotLightsAux[3];
					}


			if (time_skybox > duracion_dia) {
				time_skybox = 0.0f;
				printf("Cambio %f'\n", cambios);
				cambios += 1.0f;
			}
		}
		
		
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la c�mara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[4].SetFlash(lowerLight, camera.getCameraDirection());
		//spotLights[1].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + 1.0f ));
		//spotLights[2].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + -1.0f));
		//spotLights[3].SetPos(glm::vec3(mainWindow.getmuevex() + 0.0f, mainWindow.getmuevey() + 3.0f,  mainWindow.getmuevez() + -1.0));

		


		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);


		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

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
		
		//model = glm::translate(model, glm::vec3(0.0f, 5.0f, avance));
		model = glm::translate(model, camera3.getCameraPosition() - glm::vec3(0.0f, 11.0f, -40.0f));
		model = glm::rotate(model, (voltear - 180) * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

		modeleggrobo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Derecha Pierna Muslo
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Derecha Pierna Rodilla
		model = modeleggroboArt2;

		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::rotate(model, articulacionpelvis * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));

		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Pierna Pantorilla
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		//Derecha Pierna Tobillo
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Pie Derecha
		model = modeleggroboArt2;
		model = glm::translate(model, glm::vec3(0.0f, -1.25f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		//Izquierda Pierna Muslo
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Izquierda Pierna Rodilla
		model = modeleggroboArt1;

		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		model = glm::rotate(model, articulacionpelvis1 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modeleggroboArt1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Izquierda Pierna Pantorilla
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[6]->RenderMesh();

		//Izquierda Pierna Tobillo
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
		modeleggroboArt1 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Pie Izquierda
		model = modeleggroboArt1;
		model = glm::translate(model, glm::vec3(0.0f, -1.25f, 0.0f));
		modeleggroboArt2 = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Brazo 
		model = modeleggroboArt1Brazo;
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Articulacion Derecha Hombro
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Codo
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Mano Derecha
		model = modeleggroboArt1Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
		modeleggroboArt1Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
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
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Brazo 
		model = modeleggroboArt2Brazo;
		model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));

		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[6]->RenderMesh();

		//Articulacion Derecha Hombro
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Derecha Codo
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, 0.0f));
		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[5]->RenderMesh();

		// Mano Derecha
		model = modeleggroboArt2Brazo;
		model = glm::translate(model, glm::vec3(0.0f, -2.25f, 0.0f));
		modeleggroboArt2Brazo = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		EggRobo.UseTexture();
		Material_metalic.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[8]->RenderMesh();
		



		/*PLANO PISTA*/
		////CARRIL DE AGUA

		//toffsetu += 0.001;
		//toffsetv += 0.0;
		////para que no se desborde la variable
		//if (toffsetu > 1.0)
		//	toffsetu = 0.0;

		//toffset = glm::vec2(toffsetu, toffsetv);

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		///*glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));*/
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * 1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * 2.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * 3.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * -1.0f, 0.0f,0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * -2.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(escalaX * -3.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//agua.UseTexture();
		//Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[2]->RenderMesh();

		//toffset = glm::vec2(0, 0);
		//toffsetu += 0.001;
		//toffsetv += 0.0;
		/*CAMINOS SONIC*/

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		model = glm::translate(model, glm::vec3(escalaX *2.0f , 0.0f, escalaZ * 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
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


		/*PASO LATERALES*/
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

		/*CUADRO ATRAS*/
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


		/*PASTO ENFRENTE SONIC*/
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


		/*PHINEAS*/
		/*CAMINOS PHINEAS*/
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

		/*PASTO LATERALES*/
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



		/*CUADROS ATRAS*/
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


		/*PASTO ENFRENTE PHINEAS*/
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
		lawnTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh();

		/*PUENTES*/

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



		/*PUENTE 2*/
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

		




		//Torres Lado PHINEAS
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(16.0f, -18.0f, -135.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_1.RenderModel();

		glm::vec3 torrerTop_4 = glm::vec3(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0);
		//torrerTop_4 = glm::vec3(posXavion + movAvion_x, posYavion + movAvion_y, posZavion + movAvion_z);
		torrerTop_4 = glm::vec3(posXTorrDF_4 + movTorrDF_4_x, posYTorrDF_4 + movTorrDF_4_y, posZTorrDF_4 + movTorrDF_4_z);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, torrerTop_4);
		model = glm::translate(model, glm::vec3(16.0f, -17.9f, -135.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -giroAvion/*TorrDF_4*/ * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_2.RenderModel();

		glm::vec3 torrerTop_3 = glm::vec3(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0);
		torrerTop_3 = glm::vec3(posXTorrDF_3 + movTorrDF_3_x, posYTorrDF_3 + movTorrDF_3_y, posZTorrDF_3 + movTorrDF_3_z);
		model = glm::translate(model, torrerTop_3);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(16.0f, -7.2f, -135.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -giroTorrDF_3 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_2.RenderModel();


		glm::vec3 torrerTop_2 = glm::vec3(0.0f, 0.0f, 0.0f);		
		model = glm::mat4(1.0);
		torrerTop_2= glm::vec3(posXTorrDF_2 + movTorrDF_2_x, posYTorrDF_2 + movTorrDF_2_y, posZTorrDF_2 + movTorrDF_2_z);
		model = glm::translate(model, torrerTop_2);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(16.0f, 3.5f, -135.0f));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model,- giroTorrDF_2 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_2.RenderModel();

		glm::vec3 torrerTop_1 = glm::vec3(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0);
		torrerTop_1 = glm::vec3(posXTorrDF_1 + movTorrDF_1_x, posYTorrDF_1 + movTorrDF_1_y, posZTorrDF_1 + movTorrDF_1_z);
		model = glm::translate(model, torrerTop_1);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(16.0f , -25.5f , -135.0f ));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giroTorrDF_1 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_3.RenderModel();



		glm::vec3 torrerTop = glm::vec3(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0);
		torrerTop = glm::vec3(posXavion + movAvion_x, posYavion + movAvion_y, posZavion + movAvion_z);
		model = glm::translate(model, torrerTop);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(16.0f, -25.5f, -135.0f ));
		model = glm::scale(model, glm::vec3(9.0f, 9.0f, 9.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, giroAvion * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorreD_4.RenderModel();







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
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		TorrePrincesa.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-40.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
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

		
		

		/*PERRY*/

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f ));
		model = glm::translate(model, glm::vec3(0.0f,1.0f,-320.0f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
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



		/*ARBOLES DE LADO PHINEAS*/
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-65.0f, -6.0f, -120.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tree.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-25.0f, -6.0f, -130.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tree.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(55.0f, -6.0f, -120.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tree.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(15.0f, -6.0f, -130.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Tree.RenderModel();

		/*LAMPARAS TIPO ESTADIO*/

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-70.0f, 19.0f, -41.0f));
		model = glm::rotate(model, 20 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, 0 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lamp.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(70.0f, 19.0f, 43.0f ));
		model = glm::rotate(model, 200 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Lamp.RenderModel();


		//std::cout<<"S1" << mainWindow.getr1() << std::endl;
		//std::cout << "S2" << mainWindow.getr2() << std::endl;
		//std::cout << "S3" << mainWindow.getr3() << std::endl;


		// Faros
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-40.0f, 5.0f, 0.0f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Faro_Unleashed.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(40.0f, 5.0f, 0.0f));
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


		
		
		//Barbaro 1
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, Salto, -40.0f));
		model = glm::rotate(model, rotar * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CuerpoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CabezaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.75f, 0.0f, 0.0f));
		//model = glm::rotate(model, rotFestejo * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		//model = glm::rotate(model, rotFestejo * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		//Barbaro 2
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, festejoY+3.0f, -70.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CuerpoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CabezaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.75f, festejoH, 0.0f));
		model = glm::rotate(model, rotFestejo * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.75f, festejoH, 0.0f));
		model = glm::rotate(model, rotFestejo * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		//Barbaro 3
		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(movTX, 5.0f, movTZ));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CuerpoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		CabezaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.3f, -1.7f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		PiernaB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-0.75f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		model = modelaux;
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		BrazoB.RenderModel();

		//Loop

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 25.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Loop.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		
		model = glm::translate(model, glm::vec3(7.5f, 0.0f, 16.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 7.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Loop.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		
		model = glm::translate(model, glm::vec3(-10.0f, 27.0f, 25.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 7.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopArriba.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(7.5f, 27.0f, 16.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 7.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopArriba.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::translate(model, glm::vec3(-10.0f, 27.0f, 15.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 6.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopMitad.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(7.5f, 27.0f, 26.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 6.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopMitad.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(67.0f, 5.0f, 27.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Spring.RenderModel();

		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-67.0f, 5.0f, 14.0f));
		model = glm::rotate(model, 90.0f * toRadians, glm::vec3(0.0f, 0.0f, -1.0f));
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Spring.RenderModel();


		/*model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, 18.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopMitadAbajo.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.5f, 0.0f, 23.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 4.0f));
		model = glm::rotate(model, 180.0f * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		LoopMitadAbajo.RenderModel();*/


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(loopX, loopY, loopZ));
		model = glm::rotate(model, girospin * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		//model = glm::rotate(model, 180.0f * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Sonic.RenderModel();





		toffsetu += 0.001;
		toffsetv += 0.0;

		if (toffsetu > 1.0)
			toffsetu = 0.0;

		toffset = glm::vec2(toffsetu, toffsetv);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		agua.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[9]->RenderMesh();
		glDisable(GL_BLEND);


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
void inputKeyframes(bool* keys)
{
	if (keys[GLFW_KEY_SPACE])
	{
		if (reproduciranimacion < 1)
		{
			if (play == false && (FrameIndex > 1))
			{
				resetElements();
				//First Interpolation				
				interpolation();
				play = true;
				playIndex = 0;
				i_curr_steps = 0;
				reproduciranimacion++;
				printf("presiona 0 para habilitar reproducir de nuevo la animación'\n");
				habilitaranimacion = 0;

			}
			else
			{
				play = false;
			}
		}
	}
	if (keys[GLFW_KEY_0])
	{
		if (habilitaranimacion < 1)
		{
			reproduciranimacion = 0;
		}
	}

	if (keys[GLFW_KEY_L])
	{
		if (guardoFrame < 1)
		{
			saveFrame();
			printf("movAvion_x es: %f\n", movAvion_x);
			//printf("movAvion_y es: %f\n", movAvion_y);
			printf("presiona P para habilitar guardar otro frame'\n");
			guardoFrame++;
			reinicioFrame = 0;
		}
	}
	if (keys[GLFW_KEY_P])
	{
		if (reinicioFrame < 1)
		{
			guardoFrame = 0;
		}
	}


	if (keys[GLFW_KEY_1])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x += 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_2])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

	if (keys[GLFW_KEY_3])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_x -= 1.0f;
			printf("movAvion_x es: %f\n", movAvion_x);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_4])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

	if (keys[GLFW_KEY_5])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_y += 1.0f;
			printf("movAvion_y es: %f\n", movAvion_y);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_6])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}

	if (keys[GLFW_KEY_7])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_y -= 1.0f;
			printf("movAvion_y es: %f\n", movAvion_y);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_8])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}
	//if (keys[GLFW_KEY_N])
	//{
	//	if (ciclo < 1)
	//	{
	//		//printf("movAvion_x es: %f\n", movAvion_x);
	//		giroAvion -= 5.0f;
	//		printf("giroAvion es: %f\n", giroAvion);
	//		ciclo++;
	//		ciclo2 = 0;
	//		printf("reinicia con 2\n");
	//	}

	//}
	//if (keys[GLFW_KEY_M])
	//{
	//	if (ciclo2 < 1)
	//	{
	//		ciclo = 0;
	//	}
	//}
	if (keys[GLFW_KEY_V])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_z -= 1.0f;
			printf("movAvion_z es: %f\n", movAvion_z);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_B])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}
	if (keys[GLFW_KEY_X])
	{
		if (ciclo < 1)
		{
			//printf("movAvion_x es: %f\n", movAvion_x);
			movAvion_z += 1.0f;
			printf("movAvion_z es: %f\n", movAvion_z);
			ciclo++;
			ciclo2 = 0;
			printf("reinicia con 2\n");
		}

	}
	if (keys[GLFW_KEY_C])
	{
		if (ciclo2 < 1)
		{
			ciclo = 0;
		}
	}
}
