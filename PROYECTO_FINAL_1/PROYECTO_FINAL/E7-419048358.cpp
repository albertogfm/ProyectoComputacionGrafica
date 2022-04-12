/*
Semestre 2022-2
Práctica 8: Iluminación 1 
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

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;


Model Kitt_M;
Model Llanta_M;
Model Camino_M;
Model Blackhawk_M;
Model Dado_M;
Model Coche_Mio;
Model Llanta_Mia;
Model NeonWeed;
Model StadioLamp;

Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
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
		-0.5f, -1.5f,  0.5f,	0.340f,  0.50f,		0.0f,	0.0f,	-1.0f,	//0
		0.5f, -1.5f,  0.5f,		0.660f,	0.50f,		0.0f,	0.0f,	-1.0f,	//1
		0.5f,  1.5f,  0.5f,		0.660f,	0.740f,		0.0f,	0.0f,	-1.0f,	//2
		-0.5f,  1.5f,  0.5f,	0.340f,	0.740f,		0.0f,	0.0f,	-1.0f,	//3
		// right
		//x		y		z		S		T
		0.5f, -1.5f,  0.5f,	    0.660f,  0.50f,		-1.0f,	0.0f,	0.0f,
		0.5f, -1.5f,  -0.5f,	1.0f,	0.50f,		-1.0f,	0.0f,	0.0f,
		0.5f,  1.5f,  -0.5f,	1.0f,	0.740f,		-1.0f,	0.0f,	0.0f,
		0.5f,  1.5f,  0.5f,	    0.660f,	0.740f,		-1.0f,	0.0f,	0.0f,
		// back
		-0.5f, -1.5f, -0.5f,	0.640f,  0.00f,		0.0f,	0.0f,	1.0f,
		0.5f, -1.5f, -0.5f,		0.340f,	0.00f,		0.0f,	0.0f,	1.0f,
		0.5f,  1.5f, -0.5f,		0.340f,	0.250f,		0.0f,	0.0f,	1.0f,
		-0.5f,  1.5f, -0.5f,	0.660f, 0.250f, 0.0f, 0.0f, 1.0f,

		// left
		//x		y		z		S		T
		-0.5f, -1.5f,  -0.5f,	0.0f,  0.50f,		1.0f,	0.0f,	0.0f,
		-0.5f, -1.5f,  0.5f,	0.340f,	0.50f,		1.0f,	0.0f,	0.0f,
		-0.5f,  1.5f,  0.5f,	0.340f,	0.740f,		1.0f,	0.0f,	0.0f,
		-0.5f,  1.5f,  -0.5f,	0.0f,	0.740f,		1.0f,	0.0f,	0.0f,

		// bottom
		//x		y		z		S		T
		-0.5f, -1.5f,  0.5f,	0.660f,  0.50f,		0.0f,	1.0f,	0.0f,
		0.5f,  -1.5f,  0.5f,	0.340f,	0.50f,		0.0f,	1.0f,	0.0f,
		 0.5f, -1.5f,  -0.5f,	0.340f,	0.250f,		0.0f,	1.0f,	0.0f,
		-0.5f, -1.5f,  -0.5f,	0.660f,	0.250f,		0.0f,   1.0f, 0.0f,

		//UP
		 //x		y		z		S		T
		 -0.5f, 1.5f,  0.5f,	0.340f,  0.740f,	0.0f,	-1.0f,	0.0f,
		 0.5f,  1.5f,  0.5f,	0.660f,	0.740f,		0.0f,	-1.0f,	0.0f,
		  0.5f, 1.5f,  -0.5f,	0.660f,	1.0f,		0.0f,	-1.0f,	0.0f,
		 -0.5f, 1.5f,  -0.5f,	0.340f,	1.0f,		0.0f,	-1.0f,	0.0f,

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
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
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
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();

	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/k_rueda.3ds");
	Blackhawk_M = Model();
	Blackhawk_M.LoadModel("Models/uh60.obj");
	Camino_M = Model();
	Camino_M.LoadModel("Models/railroad track.obj");
	Coche_Mio = Model();
	Coche_Mio.LoadModel("Models/cocheText.obj");
	Llanta_Mia = Model();
	Llanta_Mia.LoadModel("Models/llantaText.obj");
	NeonWeed = Model();
	NeonWeed.LoadModel("Models/neonSign.obj");
	StadioLamp = Model();
	StadioLamp.LoadModel("Models/lamp.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,//color
		0.5f, 0.3f,//0.3 comp ambienta
		0.0f, 0.0f, -1.0f); //infinito derecha
	//contador de luces puntuales

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	//spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
	//	1.0f, 2.0f, //coef varia intensidad
	//	-5.0f, 10.0f, 0.0f,//pos
	//	0.0f, -5.0f, 0.0f,//dir
	//	1.0f, 0.0f, 0.0f,//ecua
	//	15.0f);//angulo  reduce area de alcance
	//spotLightCount++;

	//luz de helicóptero

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


	


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
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
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//// luz ligada a la cámara de tipo flash
		//	glm::vec3 lowerLight = camera.getCameraPosition();
		//lowerLight.y -= 0.3f;
		//spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());
		spotLights[1].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + 1.0f ));
		spotLights[2].SetPos(glm::vec3(mainWindow.getmuevex() - 21.50, 2.0f, mainWindow.getmuevez() + -1.0f));
		spotLights[3].SetPos(glm::vec3(mainWindow.getmuevex() + 0.0f, mainWindow.getmuevey() + 3.0f,  mainWindow.getmuevez() + -1.0));


		unsigned int pointLightCount = 0;
		//Declaración de primer luz puntual
		pointLights[0] = PointLight(0.090196f, 0.537254f, 0.090196f,
			-0.3f  , 1.0f+ mainWindow.getr2(), // uno ilumina cuanto
			10.0f, 100.0f, 120.0f,//pos
			0.7f + mainWindow.gets1() , 0.0f+ mainWindow.gets2() , 0.0f+ mainWindow.gets3() );//mainWindow.gets1() - mainWindow.getr1(), mainWindow.gets2() - mainWindow.getr2(), mainWindow.gets2() - mainWindow.getr2());//ecuacion  valores no deben dar raíz comñleja  con raiz = 0 el alcance es menor 1,2,1  el a es el ultimo
		pointLightCount++;


		//luz de faro
		spotLights[0] = SpotLight(1.0f, 0.0f, 1.0f,
			1.0f, 2.0f, //coef varia intensidad
			-10.0f, 5.0f, -100.0f,//pos
			1.0f, 0.0f, 0.0f,//dir
			0.7f + mainWindow.gets1(), 0.0f + mainWindow.gets2(), 0.0f + mainWindow.gets3(),//ecua
			20.0f+mainWindow.getr1());//angulo  reduce area de alcance
		spotLightCount++;


		std::cout <<"1.- "<< 0.7f + mainWindow.gets1()  << std::endl;
		std::cout <<"2.- " << 0.0f + mainWindow.gets2()  << std::endl;
		std::cout <<"3.- "<< 0.0f + mainWindow.gets3() << std::endl;

		std::cout << "4.- " << -0.30f + mainWindow.getr1() << std::endl;
		std::cout << "5.- " << 1.0f + mainWindow.getr2() << std::endl;


		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);



		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();


		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 0.5f, -1.5f));
		//modelaux = model;
		//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		//model = glm::rotate(model, -90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Kitt_M.RenderModel();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(mainWindow.getmuevex()+0.0f, mainWindow.getmuevey() + 3.0f, mainWindow.getmuevez() + -1.0));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
		model = glm::rotate(model, 90 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		Blackhawk_M.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f,1.0f,1.0f);
		model = glm::translate(model, glm::vec3(10.0f, 0.0f, 100.0f));
		model = glm::scale(model, glm::vec3(0.30f, 0.30f, 0.30f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		/*Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);*/
		NeonWeed.RenderModel();


		model = glm::mat4(1.0);
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = glm::translate(model, glm::vec3(-10.0f, 0.0f, -100.0f));
		model = glm::scale(model, glm::vec3(0.30f, 0.30f, 0.30f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		/*Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);*/
		StadioLamp.RenderModel();



		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(15.0f, 10.0f, -6.0f));
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//model = glm::rotate(model, mainWindow.getmuevex() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		////DadoOchoTexture.UseTexture();
		//meshList[3]->RenderMesh();

	
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(15.0f, 1.0f, -6.0f));
		//model = glm::scale(model, glm::vec3(100.0f, 100.0f, 100.0f));
		////model = glm::rotate(model, mainWindow.getmuevex() * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		////DadoOchoTexture.UseTexture();
		//meshList[4]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.53f, 0.0f));
		model = glm::scale(model,glm::vec3(25.0f, 1.0f, 4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Camino_M.RenderModel();

		//COCHE MIO AUDI
		color = glm::vec3(1.0f,1.0f,1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, 0.0f, 2.5f));
		model = glm::translate(model, glm::vec3(mainWindow.getmuevex(), -0.5f, mainWindow.getmuevez() + -2.5f));;
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Coche_Mio.RenderModel();


		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.10f, 0.50f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_Mia.RenderModel();

		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 0.50f, -1.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_Mia.RenderModel();


		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(-2.0f, 0.50f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_Mia.RenderModel();


		color = glm::vec3(1.0f, 1.0f, 1.0f);
		model = modelaux;
		model = glm::translate(model, glm::vec3(2.10f, 0.50f, 1.5f));
		model = glm::rotate(model, 180 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		Llanta_Mia.RenderModel();


		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
