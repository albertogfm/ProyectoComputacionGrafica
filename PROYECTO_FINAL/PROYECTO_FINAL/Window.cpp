#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 0.0f;
	muevey = 0.0f;
	muevez = 0.0f;
	night = 0;
	s1 = s2 = s3 = r1 = r2 = r3 = 0.0f;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "BATTLE ROYAL SONIC & PHINEAS", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

GLint Window::nightT()
{
	GLfloat nightTrue = night % 2;

	return nightTrue;
}





void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	/*if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}*/
	if (key == GLFW_KEY_H)
	{
		theWindow->muevey += 1.0;
	}
	/*if (key == GLFW_KEY_J)
	{
		theWindow->muevey -= 1.0;
	}*/
	if (key == GLFW_KEY_N)
	{
		theWindow->muevez += 1.0;
		theWindow->spotL2 = true;
	}
	if (key == GLFW_KEY_M)
	{
		theWindow->muevez -= 1.0;
		theWindow->spotL2 = false;
	}

	if (key == GLFW_KEY_R)
	{
		theWindow->s1 += 0.5;
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->s2 += 0.5;
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow->s3 += 0.5;
	}

	if (key == GLFW_KEY_F) 
	{
		theWindow->s1 -= 0.5;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->s2 -= 0.5;
	}
	if (key == GLFW_KEY_H)
	{
		theWindow->s3 -= 0.5;
	}

	if (key == GLFW_KEY_U)
	{
		theWindow->r1 += 0.5;
	}
	if (key == GLFW_KEY_I)
	{
		theWindow->r2 += 0.5;
	}
	if (key == GLFW_KEY_O)
	{
		theWindow->r3 += 0.5;
	}


	if (key == GLFW_KEY_J)
	{
		theWindow->r1 -= 0.5;
	}
	if (key == GLFW_KEY_K)
	{
		theWindow->r2 -= 0.5;
	}
	if (key == GLFW_KEY_L)
	{
		theWindow->r3 -= 0.5;
	}

	if (key == GLFW_KEY_Z)
	{
		theWindow->night = 1;
		theWindow->spotL1 = true;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->night = 0;
		theWindow->spotL1 = false;
	}
	if (key == GLFW_KEY_C)
	{
		theWindow->cam1 = 1;
	}
	if (key == GLFW_KEY_V)
	{		
		theWindow->cam1 = 2;
	}

	if (key == GLFW_KEY_1)
	{
		theWindow->cam1 = 4;

	}
	if (key == GLFW_KEY_2)
	{
		theWindow->cam1 = 6;

	}
	if (key == GLFW_KEY_3)
	{
		theWindow->cam1 = 8;

	}
	if (key == GLFW_KEY_B)
	{
		theWindow->cam1 = 0;
	}
	if (key == GLFW_KEY_F)
	{
		theWindow->showLights = false;
	}
	if (key == GLFW_KEY_G)
	{
		theWindow->showLights = true;

	}





	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
