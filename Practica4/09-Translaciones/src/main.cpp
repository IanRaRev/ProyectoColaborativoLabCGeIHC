//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"
#include "Headers/Shader.h"
//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Shader shader;
Shader shader2;
GLuint VBO, VAO,VBO2,VAO2, EBO,EBO2;


struct Vertex {
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
};

// This is for the render with index element
Vertex vertices[] =
{
	//CARA 1
	{ glm::vec3(-0.5f, -0.5f, 0.5f) , glm::vec3(1.0f, 0.0f, 0.0f) },
	{ glm::vec3(0.5f , -0.5f, 0.5f) , glm::vec3(1.0f, 0.0f, 0.0f) },
	{ glm::vec3(0.5f ,  0.5f, 0.5f) , glm::vec3(1.0f, 0.0f, 0.0f) },
	{ glm::vec3(-0.5f,  0.5f, 0.5f) , glm::vec3(1.0f, 0.0f, 0.0f) }, 

	//CARA 2
	{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(2.0f, 0.0f, 1.0f) }, 
	{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(2.0f, 0.0f, 1.0f) },
	{ glm::vec3(-0.5f , 0.5f, -0.5f) ,glm::vec3(2.0f, 0.0f, 1.0f) },
	{ glm::vec3(-0.5f , -0.5f, -0.5f),glm::vec3(2.0f, 0.0f, 1.0f) }, 

	//CARA 3
	{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f) },
	{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f) },
	{ glm::vec3(-0.5f , 0.5f, -0.5f) ,glm::vec3(1.0f, 1.0f, 0.0f) },	
	{ glm::vec3(-0.5f , -0.5f, -0.5f),glm::vec3(1.0f, 0.0f, 0.0f) },


	//CARA 4
	{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f) },
	{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f) },
	{ glm::vec3(-0.5f , 0.5f, -0.5f) ,glm::vec3(0.0f, 0.0f, 0.0f) },
	{ glm::vec3(-0.5f , -0.5f, -0.5f),glm::vec3(0.0f, 0.0f, 0.0f) },

};

GLuint indices[] = {  // Note that we start from 0!
	0, 1, 2,
	0, 2, 3,

	4,5,6,
	4,6,7,

	0, 3, 6,
	0, 6, 7,

	0, 4, 1,
	0, 7, 4,

	3, 2, 5,
	3, 5, 6,

	4, 5, 6,
	4, 6, 7

};

Vertex vertices2[] =

{
	{ glm::vec3(-0.5f, -0.5f, 0.5f) , glm::vec3(0.0f, 1.0f, 0.0f) },
	{ glm::vec3(0.5f , -0.5f, 0.5f) , glm::vec3(0.0f, 0.0f, 2.0f) },
	{ glm::vec3(0.5f ,  0.5f, 0.5f) , glm::vec3(0.0f, 1.0f, 1.0f) },
	{ glm::vec3(-0.5f,  0.5f, 0.5f) , glm::vec3(0.0f, 1.0f, 1.0f) },
	{ glm::vec3(0.5f , -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f) },
	{ glm::vec3(0.5f ,  0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f) },
	{ glm::vec3(-0.5f , 0.5f, -0.5f) ,glm::vec3(0.0f, 1.0f, 1.0f) },
	{ glm::vec3(-0.5f , -0.5f, -0.5f),glm::vec3(0.0f, 1.0f, 0.0f) },
	
};

GLuint indices2[] = {  // Note that we start from 0!



	8,9,10,
	8,10,11,
	9,12,13,
	9,13,10,
	8,11,14,
	8,14,15,
	8,10,9,
	8,14,12,
	11,10,13,
	11,13,14,
	12,13,14,
	12,14,15

   /*
	0, 1, 2,
	0, 2, 3,
	1, 4, 5,
	1, 5, 2,
	0, 3, 6,
	0, 6, 7,
	0, 4, 1,
	0, 7, 4,
	3, 2, 5,
	3, 5, 6,
	4, 5, 6,
	4, 6, 7*/
};


int screenWidth;
int screenHeight;

GLFWwindow * window;

bool exitApp = false;
int lastMousePosX;
int lastMousePosY;

double deltaTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroyWindow();
void destroy();
bool processInput(bool continueApplication = true);
void cubo();
void cubo1();

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroyWindow();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(3.0f, 0.0f, 0.5f, 0.0f);

	//Habilitamos prueba de profundidad
	// limipiamos el  bit correspondiente al buffer de color 
	glEnable(GL_DEPTH_TEST);

	shader.initialize("../../Shaders/transformaciones.vs", "../../Shaders/transformaciones.fs");
	shader2.initialize("../../Shaders/transformaciones.vs", "../../Shaders/transformaciones.fs");
	cubo();
	cubo1();
	
}

void cubo() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// This is for the render with index element
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)sizeof(vertices[0].m_Pos));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



//CUBO 2
void cubo1() {
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	// This is for the render with index element
	glGenBuffers(1, &EBO2);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices2[0]), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices2[0]),
		(GLvoid*)sizeof(vertices2[0].m_Pos));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



void destroyWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void destroy() {
	destroyWindow();
	//CUBO 1
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

	//CUBO 2
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EBO2);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO2);
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}
	deltaTime = 1 / TimeManager::Instance().CalculateFrameRate(false);
	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;
	double lastTime = TimeManager::Instance().GetTime();

	float fovy = 0;

	while (psi) {
		psi = processInput(true);
		
		// LIMPIE BUFFER DE PROFUNDIDAD
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.3f, 0.3f, 1.0f);

		shader.turnOn();
		shader2.turnOn();

		glBindVertexArray(VAO);

		//CUBO 1
	    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 
		(float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		GLuint locProj = shader.getUniformLocation("projection");
		glUniformMatrix4fv(locProj, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -8.0));
		GLuint locView= shader.getUniformLocation("view");
		glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 2.0f, -4.0f));
		GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

	  // segundo cubo 
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.25,1.0,0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//  cubo  3
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 0.0f, -4.0f));

		//CUBO 3
		glm::mat4 projection1 = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
		GLuint locProj1 = shader2.getUniformLocation("projection");
		glUniformMatrix4fv(locProj1, 1, GL_FALSE, glm::value_ptr(projection1));


		glm::mat4 view1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -8.0));
		GLuint locView1 = shader2.getUniformLocation("view");
		glUniformMatrix4fv(locView1, 1, GL_FALSE, glm::value_ptr(view1));

		glm::mat4 model1 = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 0.0f, -4.0f));
		model1 = glm::scale(model1, glm::vec3(0.8, 1.5, 0.15));
		GLuint locModel1 = shader2.getUniformLocation("model");
		glUniformMatrix4fv(locModel1, 1, GL_FALSE, glm::value_ptr(model1));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//  cubo 4
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, -1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5, 2.0, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		//  cubo 5
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, -2.0f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.10, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//  cubo 6
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(.0, 0.10, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//  cubo 7
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-5.0f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.10, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//cuerpo
		//  cubo 7
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(2.5,0.9, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		//  cubo 7
		//cola
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(1.0f, 0.0f, -4.0f));
		model = glm::scale(model, glm::vec3(1.0, 0.2, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);




		//Patas
		//  cubo 7
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-0.8f, -1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3, 1.0, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//  cubo 7
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.8f, -1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3, 1.0, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		//cabeza
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-0.8, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(1.2, 1.0, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		

		//legua 
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-1.0, 1.0f, -4.0f));
		model = glm::scale(model, glm::vec3(0.5, 0.2, 0.15));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		/*
		//--------------------------------------------
		//
		//Codigo de la letra C
		//--------------------------------------------
		glm::mat4 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, 3.0f, - 4.0f));
		GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0); 

		//Segundo cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-7.0f, 3.0f, - 4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Tercer cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-8.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//cuarto cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-8.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//5o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-8.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//6o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-8.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//7o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-8.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//8o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-7.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//9o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-6.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		
		//--------------------------------------------
		//
		//Codigo de la letra G
		//--------------------------------------------
		 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-2.0f, 3.0f, -4.0f));
		//GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Segundo cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-3.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Tercer cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-4.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//cuarto cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-4.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//5o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-4.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//6o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-4.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//7o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-4.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//8o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-3.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//9o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-2.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//10o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-3.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//11o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-2.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//12o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(-2.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		

		//--------------------------------------------
		//
		//Codigo de la letra H
		//--------------------------------------------
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(2.0f, 3.0f, -4.0f));
		//GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Segundo cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(2.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Tercer cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(2.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//cuarto cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(2.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//5o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(2.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//6o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//7o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//8o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//9o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//10o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(0.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);

		//11o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(1.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		//--------------------------------------------
		//
		//Codigo de la letra I
		//--------------------------------------------
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(4.0f, 3.0f, -4.0f));
		//GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		
		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Segundo cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(4.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Tercer cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(4.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//cuarto cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(4.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//5o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(4.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);


		//--------------------------------------------
//
//Codigo de la letra C
//--------------------------------------------
		 model = glm::translate(glm::mat4(1.0f),
			glm::vec3(8.0f, 3.0f, -4.0f));
		//GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));

		// This is for the render with index element
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Segundo cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(7.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//Tercer cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(6.0f, 3.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//cuarto cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(6.0f, 2.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//5o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(6.0f, 1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//6o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(6.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//7o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(6.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//8o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(7.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		//9o cubo
		model = glm::translate(glm::mat4(1.0f),
			glm::vec3(8.0f, -1.0f, -4.0f));
		glUniformMatrix4fv(locModel, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (GLuint *)0);
		*/

		shader.turnOff();
		shader2.turnOff();
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}