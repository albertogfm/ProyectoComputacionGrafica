#pragma once
#include "Light.h"

class PointLight :
	public Light //luz puntual ligada a la clase luz
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,//herda
		GLfloat xPos, GLfloat yPos, GLfloat zPos,//posicionada en el escenario con una ecuación de segundo grado
		GLfloat con, GLfloat lin, GLfloat exp); // luz bulbo/vela

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

	~PointLight();

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

