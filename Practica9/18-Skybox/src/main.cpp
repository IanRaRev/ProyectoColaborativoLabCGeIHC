//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

//glfw include
#include <GLFW/glfw3.h>

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// program include
#include "Headers/TimeManager.h"
#include "Headers/Shader.h"
// Geometry primitives
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
//Texture includes
#include "Headers/Texture.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere sphere(20, 20);
Sphere sphere2(20, 20);
Cylinder cylinder(20, 20, 0.5, 0.5);
Cylinder cylinder2(20, 20, 0.5, 0.5);
Cylinder cylinder3(20, 20, 0.5, 0.5);
Cylinder cylinder4(20, 20, 0.5, 0.5);
Box box,box1,box2,box3,box4,box5,box6,box7;


Shader shaderColor;
Shader shaderTexture;
Shader shaderCubeTexture;
Shader shaderMateriales;
Shader shaderDirectionLight;
Shader shaderPointLight;
Shader shaderSpotLight;

GLuint textureID1, textureID2, textureID3,textureID4,
textureID5,textureID6, textureID7, textureID8, 
textureID9, textureID10,textureID11, textureID12, 
textureID13, textureID14, textureID15, 
textureID16, textureID17, textureID18, 
textureID19, textureID20, textureID21,
textureID22, textureID23, textureID24,
textureID25, textureID26, textureCubeTexture;
GLuint cubeTextureID;

GLenum types[6] = {
	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

std::string fileNames[6] = { 
	"../../Textures/ely_hills/hills_ft.tga",
	"../../Textures/ely_hills/hills_bk.tga",
	"../../Textures/ely_hills/hills_up.tga",
	"../../Textures/ely_hills/hills_dn.tga",
	"../../Textures/ely_hills/hills_rt.tga",
	"../../Textures/ely_hills/hills_lf.tga"
};

int screenWidth;
int screenHeight;

GLFWwindow * window;

bool exitApp = false;
bool ilumina = true;
bool ilumina2 = true;
int lastMousePosX, offsetX;
int lastMousePosY, offsetY;
float rot1 = 0.0f, rot2 = 0.0f;
float i = 0.0f;

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
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	shaderColor.initialize("../../Shaders/transformaciones.vs", "../../Shaders/transformaciones.fs");
	shaderTexture.initialize("../../Shaders/texturizado_res.vs", "../../Shaders/texturizado_res.fs");
	shaderCubeTexture.initialize("../../Shaders/cubeTexture.vs", "../../Shaders/cubeTexture.fs");
	shaderMateriales.initialize("../../Shaders/iluminacion_materiales_res.vs", "../../Shaders/iluminacion_materiales_res.fs");
	shaderDirectionLight.initialize("../../Shaders/typeLight.vs", "../../Shaders/directionalLight.fs");
	shaderPointLight.initialize("../../Shaders/typeLight.vs", "../../Shaders/pointLight.fs");
	shaderSpotLight.initialize("../../Shaders/typeLight.vs", "../../Shaders/spotLight.fs");

	sphere.init();
	sphere2.init();
	cylinder.init();
	cylinder2.init();
	cylinder3.init();
	cylinder4.init();
	box.init();
	box1.init();
	box2.init();
	box3.init();
	box4.init();
	box5.init();
	box6.init();
	box7.init();

	camera->setPosition(glm::vec3(0.0f, 0.0f, 0.4f));
	/*
	//-------TEXTURAS----------------------------
	Texturas para cada uno de los juegos
	|
	|
	|
	|-------------------------------------------
	*/

	// Textura										JUEGO 1
	int imageWidth, imageHeight;
	Texture texture("../../Textures/azul.jpg");
	FIBITMAP* bitmap = texture.loadImage(false);
	unsigned char * data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID1);
	glBindTexture(GL_TEXTURE_2D, textureID1);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);

	//textura colores 
	texture = Texture("../../Textures/colores.jpg");
	bitmap = texture.loadImage(false);
	data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID2);
	glBindTexture(GL_TEXTURE_2D, textureID2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);


	//textura FLECHA
	texture = Texture("../../Textures/flecha.jpg");
	bitmap = texture.loadImage(false);
	data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID3);
	glBindTexture(GL_TEXTURE_2D, textureID3);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);

	//textura martillo
	texture = Texture("../../Textures/martillo.jpg");
	bitmap = texture.loadImage(false);
	data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID4);
	glBindTexture(GL_TEXTURE_2D, textureID4);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);

	//textura tiras
	texture = Texture("../../Textures/tiras.jpg");
	bitmap = texture.loadImage(false);
	data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID5);
	glBindTexture(GL_TEXTURE_2D, textureID5);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);


	//textura letrero juego del cohete
	texture = Texture("../../Textures/letrero1.png");
	bitmap = texture.loadImage(false);
	data = texture.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureID6);
	glBindTexture(GL_TEXTURE_2D, textureID6);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	texture.freeImage(bitmap);


	//---------------------------------------------------------------------------

	glGenTextures(1, &cubeTextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		texture = Texture(fileNames[i]);
		FIBITMAP* bitmap = texture.loadImage(true);
		data = texture.convertToData(bitmap, imageWidth, imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		texture.freeImage(bitmap);
	}

}

//------------					DESTRUYE PANTALLA


void destroyWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}


//------------					DESTRUYE OBJETOS

void destroy() {
	destroyWindow();

	shaderColor.destroy();
	shaderTexture.destroy();
	shaderCubeTexture.destroy();
	shaderMateriales.destroy();
	shaderDirectionLight.destroy();
	shaderPointLight.destroy();
	shaderSpotLight.destroy();
	sphere.destroy();
	cylinder.destroy();
	cylinder2.destroy();
	cylinder3.destroy();
	cylinder4.destroy();
	box.destroy();
	box1.destroy();
	box2.destroy();
	box3.destroy();
	box4.destroy();
	box5.destroy();
	box6.destroy();
	box7.destroy();



}


/*------------					CALL BACK				-------------------

Incluye teclas para :
	Cambiar el tipo de iluminaci�n.}
	Cmabiar la rotaci�n de los objetos

*/

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
		case GLFW_KEY_1:
			ilumina= true;
			break;
		case GLFW_KEY_2:
			ilumina= false;
			break;
		case GLFW_KEY_3:
			ilumina2 =false;
			break;


	
		}
	}
}


/*------------					MOUSE CALL BACK				-------------------

Imprime las posiciones en la pantalla.

*/


void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
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


/*------------				PROCESS INPUT				-------------------

Se manejan los eventos para mover izquierda, dercha , acercar y alejar. 

*/

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}
	TimeManager::Instance().CalculateFrameRate(false);
	deltaTime = TimeManager::Instance().DeltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFrontCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveFrontCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRightCamera(false, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveRightCamera(true, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		rot1 += 0.03;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		rot2 -= 0.03;
		
		

	glfwPollEvents();
	return continueApplication;
}



/*------------				APLICATION		-------------------

Manejo  y construcci�n de cada uno de los obejtos.
*/

void applicationLoop() {
	bool psi = true;
	double lastTime = TimeManager::Instance().GetTime();

	glm::vec3 objPosition = glm::vec3(0.0f, 0.0f, -3.0f);
	float angle = 0.0;
	float ratio = 20.0;

	while (psi) {
		psi = processInput(true);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		// Matrix de proyeccion en perspectiva
		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / screenWidth, 0.01f, 100.0f);
		// matrix de vista
		glm::mat4 view = camera->getViewMatrix();

		glm::mat4 cubeModelMatrix = glm::translate(glm::mat4(1.0f), objPosition);

		glm::mat4 matrix0 = glm::mat4(1.0f);
		// Se coloca el torso en la coordenada (0, 0, -1.0)
		matrix0 = glm::translate(matrix0, glm::vec3(0.0f, 0.0f, -4.0f));
		

		
		glm::mat4 matrixs1 = glm::translate(matrix0, glm::vec3(0.0f,0.9f, 0.0f)); // esfera para primer juego 
		glm::mat4 matrix1 = glm::translate(matrix0, glm::vec3(0.0f, 0.9f, 0.0f)); //caja 
		glm::mat4 matrix2 = glm::translate(matrixs1, glm::vec3(0.0f, -0.25f, 0.0f));// cilindro medio
		glm::mat4 matrixs2 = glm::translate(matrix2, glm::vec3(0.0f, 0.0f, 0.35f));//brazo posterior 
		glm::mat4 matrixs2_1 = glm::translate(matrix2, glm::vec3(0.0f, 0.0f, -0.35f));// brazo anterior 
		

		/*----------
		/									MOVIMINETOS JUEGO 1
	    */

		matrix2 = glm::rotate(matrixs2, rot1, glm::vec3(0.0f, 0.0f, 0.01f));
		matrixs2 = glm::rotate(matrixs2, rot1, glm::vec3(0.0f, 0.0f, 0.01f));
		matrixs2_1 = glm::rotate(matrixs2_1,rot1, glm::vec3(0.0f, 0.0f, 0.01f));
		matrixs2 = glm::rotate(matrixs2, rot2, glm::vec3(0.0f, 0.0f, 0.01f));
		matrixs2_1 = glm::rotate(matrixs2_1, rot2, glm::vec3(0.0f, 0.0f, 0.01f));

		
		// Se dibuja el cylindro principal del juego martillo 
		matrix0 = glm::scale(matrix0, glm::vec3(0.6f, 1.0f, 0.6f));
		glBindTexture(GL_TEXTURE_2D, textureID1);
		cylinder.setShader(&shaderDirectionLight);
		cylinder.setProjectionMatrix(projection);
		cylinder.setViewMatrix(view);
		cylinder.setScale(glm::vec3(0.5, 1.8, 0.5));
		cylinder.render(matrix0);





		//esfera  central del juego
		glBindTexture(GL_TEXTURE_2D, textureID2);
		matrixs1 = glm::rotate(matrixs1, 1.5708f, glm::vec3(0.1f, 0.0f, 0.0f));
		matrixs1 = glm::scale(matrixs1, glm::vec3(0.4f, 0.4f, 0.4f));
		sphere.setShader(&shaderDirectionLight);
		sphere.setProjectionMatrix(projection);
		sphere.setViewMatrix(view);
		sphere.setPosition(glm::vec3(0.0, 0.0, 0.7));
		sphere.setScale(glm::vec3(1.0, 1.0, 1.0));
		sphere.render(matrixs1);

		//caja superior del juego 
		glBindTexture(GL_TEXTURE_2D, textureID1);
		matrix1 = glm::scale(matrix1, glm::vec3(0.2f, 0.2f, 0.2f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.enableWireMode();
		box.setScale(glm::vec3(1.0, 1.0, 1.0));
		box.render(matrix1);

		// cilindro de en medio 
		glBindTexture(GL_TEXTURE_2D, textureID2);
		matrix2 = glm::rotate(matrix2, 1.5708f, glm::vec3(0.1f, 0.0f, 0.0f));
		matrix2 = glm::scale(matrix2, glm::vec3(0.1f, 0.6f, 0.1f));
		cylinder2.setShader(&shaderDirectionLight);
		cylinder2.setProjectionMatrix(projection);
		cylinder2.setViewMatrix(view);
		cylinder2.render(matrix2);
		// brazo posterior 
		glBindTexture(GL_TEXTURE_2D, textureID3);
		matrixs2 = glm::rotate(matrixs2, 1.5708f, glm::vec3(0.1f, 0.0f, 0.0f));
		matrixs2 = glm::scale(matrixs2, glm::vec3(0.1f, 0.1f, 1.8f));
		cylinder3.setShader(&shaderDirectionLight);
		cylinder3.setProjectionMatrix(projection);
		cylinder3.setViewMatrix(view);
		cylinder3.render(matrixs2);
		//caja de pasajeros  brazo 1
		glm::mat4 matrix3 = glm::translate(matrixs2, glm::vec3(0.0f, 0.0f, 0.57f)); //caja pasajeros 
		glBindTexture(GL_TEXTURE_2D, textureID4);
		matrix3 = glm::rotate(matrix3, 1.5708f, glm::vec3(0.0f, 0.1f, 0.0f));
		matrix3 = glm::scale(matrix3, glm::vec3(0.2,2.5f,5.0f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.render(matrix3);
		//detalle brazo posterior 
		glm::mat4 matrix5 = glm::translate(matrixs2, glm::vec3(0.0f, 0.0f, -0.57f)); //caja pasajeros 
		glBindTexture(GL_TEXTURE_2D, textureID5);
		matrix5 = glm::rotate(matrix5, 1.5708f, glm::vec3(0.0f, 0.1f, 0.0f));
		matrix5 = glm::scale(matrix5, glm::vec3(0.2, 1.0f, 3.0f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.render(matrix5);
		// brazo anterior
		glBindTexture(GL_TEXTURE_2D, textureID3);
		matrixs2_1 = glm::rotate(matrixs2_1, 1.5708f, glm::vec3(0.1f, 0.0f, 0.0f));
		matrixs2_1 = glm::scale(matrixs2_1, glm::vec3(0.1f, 0.1f, 1.8f));
		cylinder4.setShader(&shaderDirectionLight);
		cylinder4.setProjectionMatrix(projection);
		cylinder4.setViewMatrix(view);
		cylinder4.render(matrixs2_1);
		//caja de pasajeros  brazo 2
		glm::mat4 matrix4 = glm::translate(matrixs2_1, glm::vec3(0.0f, 0.0f, 0.57f)); //caja pasajeros 
		glBindTexture(GL_TEXTURE_2D, textureID4);
		matrix4 = glm::rotate(matrix4, 1.5708f, glm::vec3(0.0f, 0.1f, 0.0f));
		matrix4 = glm::scale(matrix4, glm::vec3(0.2, 2.5f, 5.0f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.render(matrix4);
		//detalle brazo anterior
		glm::mat4 matrix6 = glm::translate(matrixs2_1, glm::vec3(0.0f, 0.0f, -0.57f)); //caja pasajeros 
		glBindTexture(GL_TEXTURE_2D, textureID5);
		matrix6 = glm::rotate(matrix6, 1.5708f, glm::vec3(0.0f, 0.1f, 0.0f));
		matrix6 = glm::scale(matrix6, glm::vec3(0.2, 1.0f, 3.0f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.render(matrix6);

		//---------			letrero del juego 
		glm::mat4 matrix7 = glm::translate(matrix0, glm::vec3(0.0f, 1.0f, 0.0f));
		glBindTexture(GL_TEXTURE_2D, textureID1);
		matrix7 = glm::rotate(matrix7, 1.5708f, glm::vec3(0.0f, 0.1f, 0.0f));
		matrix7 = glm::scale(matrix7, glm::vec3(0.1f, 2.5f, 0.1f));
		cylinder4.setShader(&shaderDirectionLight);
		cylinder4.setProjectionMatrix(projection);
		cylinder4.setViewMatrix(view);
		cylinder4.render(matrix7);

		glm::mat4 matrixs3 = glm::translate(matrix7, glm::vec3(0.0f, 0.6f, 0.0f)); //caja pasajeros 
		glBindTexture(GL_TEXTURE_2D, textureID6);
		matrixs3 = glm::rotate(matrixs3, 0.001f, glm::vec3(0.0f, 0.0f, 0.1f));
		matrixs3 = glm::scale(matrixs3, glm::vec3(4.5, 0.5f, 8.5f));
		box.setShader(&shaderDirectionLight);
		box.setProjectionMatrix(projection);
		box.setViewMatrix(view);
		box.render(matrixs3);
	
	
		




	
	



	
/*------------				MANEJO DE LA ILUMINACION			-------------------

Se manejan los eventos para mover izquierda, dercha , acercar y alejar.

*/


		// matriz de luz 
		glm::mat4 lightModelmatrix = glm::rotate(cubeModelMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
		lightModelmatrix = glm::translate(lightModelmatrix, glm::vec3(0.0f, 0.0f, -ratio));
		if (ilumina) {
			// Iluminaci�n direccional 

			shaderDirectionLight.turnOn();
			//se comentan las sigyuientes lineas para spotlight
			glUniform3fv(shaderDirectionLight.getUniformLocation("light.position"), 1, glm::value_ptr(glm::vec3(2.0f,0.0f,5.0)));
			glUniform3fv(shaderDirectionLight.getUniformLocation("light.direction"), 1, glm::value_ptr(glm::vec3(-0.3f, -1.0f, -0.2f)));
			//glUniform3fv(shaderDirectionLight.getUniformLocation("light.position"), 1, glm::value_ptr(camera->getPosition()));
			//se comenta para direccional  y se comenta nuevamente para spot
			glUniform3fv(shaderDirectionLight.getUniformLocation("light.direction"), 1, glm::value_ptr(camera->getFront())); //direcional
			glUniform3fv(shaderDirectionLight.getUniformLocation("viewPos"), 1, glm::value_ptr(camera->getPosition()));
			glUniform3f(shaderDirectionLight.getUniformLocation("light.ambient"), 0.2, 0.2, 0.2);
			glUniform3f(shaderDirectionLight.getUniformLocation("light.diffuse"), 0.2, 0.3, 0.6);
			glUniform3f(shaderDirectionLight.getUniformLocation("light.specular"), 0.5, 0.3, 0.2);
			glUniform3f(shaderDirectionLight.getUniformLocation("material.ambient"), 1.0, 0.2, 0.6);
			glUniform3f(shaderDirectionLight.getUniformLocation("material.diffuse"), 0.4, 0.5, 0.8);
			glUniform3f(shaderDirectionLight.getUniformLocation("material.specular"), 0.5, 0.3, 0.2);
			//definimos �ngulos para el spotlight se descomentan 
			//glUniform1f(shaderDirectionLight.getUniformLocation("light.cutOff"), glm::cos(glm::radians(5.0f))); 
			// disminuimos valores el cono se hace maspeque
			//glUniform1f(shaderDirectionLight.getUniformLocation("light.outerCutOff"), glm::cos(glm::radians(7.5f)));
			//modificamos los  valores de point ligth, mas peque�o el termino  cuadratico    
			//permite alejarse y que no se vea tanto la diferencia  de que se obscurece

			//glUniform1f(shaderDirectionLight.getUniformLocation("light.constant"), 1.0f); //distancias  de 400
			//glUniform1f(shaderDirectionLight.getUniformLocation("light.linear"), 0.007f);
			//glUniform1f(shaderDirectionLight.getUniformLocation("light.quadratics"), 0.0002f);
			//glUniform1f(shaderDirectionLight.getUniformLocation("material.shininess"), 32.0);
			//sphere2.render();
			//sphere2.setPosition(glm::vec3(-0.4, 0.5, 0.5));
			//sphere2.render();
			//cylinder2.setPosition(glm::vec3(-5.0, 0.0, 4.0));
			//cylinder2.render();
			//box.setPosition(glm::vec3(-5.0, 0.0, -9.0));
			//box.render();
			//PISO
			//box1.setPosition(glm::vec3(-5.0, -15.0, 0.0));
			//box1.render();
			//PARED LATERAL 1
			//box2.setPosition(glm::vec3(-20.0, 0.0, 0.0));
			//box2.render();
			//PARED LATERAL 2
			//box3.setPosition(glm::vec3(10.0, 0.0, 0.0));
			//box3.render();
			shaderDirectionLight.turnOff();
		}
		else {
			// Iluminaci�n

			shaderSpotLight.turnOn();
			//se comentan las sigyuientes lineas para spotlight
			//glUniform3fv(shaderSpotLight.getUniformLocation("light.position"), 1, glm::value_ptr(glm::vec3(2.0f,0.0f,5.0)));
			//glUniform3fv(shaderSpotLight.getUniformLocation("light.direction"), 1, glm::value_ptr(glm::vec3(-0.3f, -1.0f, -0.2f)));
			glUniform3fv(shaderSpotLight.getUniformLocation("light.position"), 1, glm::value_ptr(camera->getPosition())); //se comenta para direccional  y se comenta nuevamente para spot
			glUniform3fv(shaderSpotLight.getUniformLocation("light.direction"), 1, glm::value_ptr(camera->getFront())); //direcional
			glUniform3fv(shaderSpotLight.getUniformLocation("viewPos"), 1, glm::value_ptr(camera->getPosition()));
			glUniform3f(shaderSpotLight.getUniformLocation("light.ambient"), 0.2, 0.2, 0.2);
			glUniform3f(shaderSpotLight.getUniformLocation("light.diffuse"), 0.2, 0.3, 0.6);
			glUniform3f(shaderSpotLight.getUniformLocation("light.specular"), 0.5, 0.3, 0.2);
			glUniform3f(shaderSpotLight.getUniformLocation("material.ambient"), 1.0, 0.2, 0.6);
			glUniform3f(shaderSpotLight.getUniformLocation("material.diffuse"), 0.4, 0.5, 0.8);
			glUniform3f(shaderSpotLight.getUniformLocation("material.specular"), 0.5, 0.3, 0.2);
			//definimos �ngulos para el spotlight se descomentan 
			glUniform1f(shaderSpotLight.getUniformLocation("light.cutOff"), glm::cos(glm::radians(5.0f))); // disminuimos valores el cono se hace maspeque
			glUniform1f(shaderSpotLight.getUniformLocation("light.outerCutOff"), glm::cos(glm::radians(7.5f)));
			//modificamos los  valores de point ligth, mas peque�o el termino  cuadratico    
			//permite alejarse y que no se vea tanto la diferencia  de que se obscurece

			glUniform1f(shaderSpotLight.getUniformLocation("light.constant"), 1.0f); //distancias  de 325
			glUniform1f(shaderSpotLight.getUniformLocation("light.linear"), 0.014f);
			glUniform1f(shaderSpotLight.getUniformLocation("light.quadratics"), 0.0007f);
			glUniform1f(shaderSpotLight.getUniformLocation("material.shininess"), 32.0);
			//sphere2.render();
			//sphere2.setPosition(glm::vec3(-0.4, 0.5, 0.5));
			//sphere2.render();
			//cylinder2.setPosition(glm::vec3(-5.0, 0.0, 4.0));
			//cylinder2.render();



			shaderSpotLight.turnOff();

		}
		if (ilumina2) {
			// Iluminaci�n

			shaderPointLight.turnOn();
			//se comentan las sigyuientes lineas para spotlight
			glUniform3fv(shaderPointLight.getUniformLocation("light.position"), 1, glm::value_ptr(glm::vec3(2.0f,0.0f,5.0)));
			glUniform3fv(shaderPointLight.getUniformLocation("light.direction"), 1, glm::value_ptr(glm::vec3(-0.3f, -1.0f, -0.2f)));
			glUniform3fv(shaderPointLight.getUniformLocation("light.position"), 1, glm::value_ptr(camera->getPosition())); 
			//se comenta para direccional  y se comenta nuevamente para spot
			glUniform3fv(shaderPointLight.getUniformLocation("light.direction"), 1, glm::value_ptr(camera->getFront())); 
			//direcional
			glUniform3fv(shaderPointLight.getUniformLocation("viewPos"), 1, glm::value_ptr(camera->getPosition()));
			glUniform3f(shaderPointLight.getUniformLocation("light.ambient"), 0.2, 0.2, 0.2);
			glUniform3f(shaderPointLight.getUniformLocation("light.diffuse"), 0.2, 0.3, 0.6);
			glUniform3f(shaderPointLight.getUniformLocation("light.specular"), 0.5, 0.3, 0.2);
			glUniform3f(shaderPointLight.getUniformLocation("material.ambient"), 1.0, 0.2, 0.6);
			glUniform3f(shaderPointLight.getUniformLocation("material.diffuse"), 0.4, 0.5, 0.8);
			glUniform3f(shaderPointLight.getUniformLocation("material.specular"), 0.5, 0.3, 0.2);
			//definimos �ngulos para el spotlight se descomentan 
			//glUniform1f(shaderPointLight.getUniformLocation("light.cutOff"), glm::cos(glm::radians(5.0f))); 
			// disminuimos valores el cono se hace maspeque
			//glUniform1f(shaderPointLight.getUniformLocation("light.outerCutOff"), glm::cos(glm::radians(7.5f)));
			//modificamos los  valores de point ligth, mas peque�o el termino  cuadratico    
			//permite alejarse y que no se vea tanto la diferencia  de que se obscurece

			glUniform1f(shaderPointLight.getUniformLocation("light.constant"), 1.0f); //distancias  de 400
			glUniform1f(shaderPointLight.getUniformLocation("light.linear"), 0.007f);
			glUniform1f(shaderPointLight.getUniformLocation("light.quadratics"), 0.0002f);
			glUniform1f(shaderPointLight.getUniformLocation("material.shininess"), 32.0);
			//sphere2.render();
			//sphere2.setPosition(glm::vec3(-0.4, 0.5, 0.5));
			//sphere2.render();
			//cylinder2.setPosition(glm::vec3(-5.0, 0.0, 4.0));
			//cylinder2.render();

			shaderPointLight.turnOff();


		}
		
		glBindTexture(GL_TEXTURE_2D, 0);

		if (angle > 2 * M_PI)
			angle = 0.0;
		else
			angle += 0.001;

		
		sphere.setShader(&shaderColor);
		sphere.setColor(glm::vec3(0.4f, 0.3f, 0.6f));
		sphere.setProjectionMatrix(projection);
		sphere.setViewMatrix(view);
		sphere.setScale(glm::vec3(4.0f, 4.0f, 4.0f));
		sphere.enableWireMode();
		sphere.render(lightModelmatrix);

	


		// Se Dibuja el Skybox
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderCubeTexture.turnOn();
		GLuint cubeTextureId = shaderCubeTexture.getUniformLocation("skybox");
		glUniform1f(cubeTextureId, 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		sphere.setShader(&shaderCubeTexture);
		sphere.setProjectionMatrix(projection);
		sphere.setViewMatrix(glm::mat4(glm::mat3(view)));
		sphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));
		sphere.render();

		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);
		shaderCubeTexture.turnOff();

		glfwSwapBuffers(window);
	}
}




//--------------------------------------------------------------------------

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}


// para point light comenatmos linea 371y 372.