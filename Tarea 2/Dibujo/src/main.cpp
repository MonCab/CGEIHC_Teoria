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

//Instancia del objeto shader
Shader shader;

GLuint VBO, VAO, EBO;
GLuint VBO2, VAO2, EBO2;
GLuint VBO3, VAO3, EBO3;
GLuint VBO4, VAO4, EBO4;

typedef struct {
	float XYZ[3];
	float RGB[3];
} Vertex;

int screenWidth;
int screenHeight;

GLFWwindow * window;

bool exitApp = false;
int lastMousePosX;
int lastMousePosY;

double deltaTime;

int option = 0;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroyWindow();
void destroy();
bool processInput(bool continueApplication = true);

void marioGrande();
void marioZorro();
void marioRana();
void marioBota();

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

	//Esta parte es para indicarle que funciones se van a ejecutar cuando suceda un evento
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

	//Inicializar los shader de vertices y fragmento
	//Los atributos son las rutas relativas de los archivos donde están
	//	almacenados los shaders.
	//El primer nombre del archivo es el shader de vertices
	//	y el segundo el shader de fragmento
	shader.initialize("../../Shaders/basic.vs", "../../Shaders/basic.fs");

	marioGrande();
	marioZorro();
	marioRana();
	marioBota();
}

void marioGrande() {
	// This is for the render with index element
	Vertex vertices[] =
	{
		{ { 1.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 1.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,  // First Triangle
		0, 2, 3,   // Second Triangle
		4, 5, 6,
		4, 6, 7
	};

	const size_t bufferSize = sizeof(vertices);
	const size_t vertexSize = sizeof(vertices[0]);
	const size_t rgbOffset = sizeof(vertices[0].XYZ);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// This is for the render with index element
	glGenBuffers(1, &EBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
		(GLvoid*)rgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void marioZorro() {
	// This is for the render with index element
	Vertex vertices[] =
	{
		{ { 1.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 1.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,  // First Triangle
		0, 2, 3,   // Second Triangle
		4, 5, 6,
		4, 6, 7
	};

	const size_t bufferSize = sizeof(vertices);
	const size_t vertexSize = sizeof(vertices[0]);
	const size_t rgbOffset = sizeof(vertices[0].XYZ);

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	// This is for the render with index element
	glGenBuffers(1, &EBO2);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
		(GLvoid*)rgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void marioRana() {
	// This is for the render with index element
	Vertex vertices[] =
	{	
		//Negro
		{ { 1.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//0
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//1
		{ { 2.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//2
		{ { 1.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//3
		{ { 13.0f, 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//4
		{ { 13.0f, 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//5
		{ { 2.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//6
		{ { 8.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//7
		{ { 9.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//8
		{ { 9.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//9
		{ { 8.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//10
		{ { 12.0f, 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//11
		{ { 13.0f, 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//12
		{ { 12.0f, 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//13
		{ { 3.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//14
		{ { 3.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//15
		{ { 2.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//16
		{ { 5.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//17
		{ { 8.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//18
		{ { 5.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//19
		{ { 12.0f, 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//20
		{ { 9.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//21
		{ { 1.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//22
		{ { 2.0f , 4.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//23
		{ { 1.0f , 4.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//24
		{ { 6.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//25
		{ { 7.0f , 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//26
		{ { 7.0f , 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//27
		{ { 6.0f , 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//28
		{ { 10.0f, 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//29
		{ { 11.0f, 3.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//30
		{ { 11.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//31
		{ { 10.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//32
		{ { 0.0f , 4.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//33
		{ { 1.0f , 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//34
		{ { 0.0f , 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//35
		{ { 3.0f , 5.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//36
		{ { 4.0f , 5.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//37
		{ { 4.0f , 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//38
		{ { 3.0f , 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//39
		{ { 6.0f , 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//40
		{ { 4.0f , 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//41
		{ { 9.0f , 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//42
		{ { 10.0f, 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//43
		{ { 9.0f , 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//44
		{ { 11.0f, 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//45
		{ { 16.0f, 6.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//46
		{ { 16.0f, 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//47
		{ { 11.0f, 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//48
		{ { 17.0f, 7.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//49
		{ { 17.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//50
		{ { 16.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//51
		{ { 2.0f , 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//52
		{ { 2.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//53
		{ { 1.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//54
		{ { 7.0f , 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//55
		{ { 8.0f , 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//56
		{ { 8.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//57
		{ { 7.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//58
		{ { 10.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//59
		{ { 11.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//60
		{ { 11.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//61
		{ { 10.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//62
		{ { 14.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//63
		{ { 19.0f, 8.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//64
		{ { 19.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//65
		{ { 14.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//66
		{ { 12.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//67
		{ { 15.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//68
		{ { 15.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//69
		{ { 12.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//70
		{ { 18.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//71
		{ { 20.0f, 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//72
		{ { 20.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//73
		{ { 18.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//74
		{ { 3.0f , 9.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//75
		{ { 3.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//76
		{ { 2.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//77
		{ { 5.0f , 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//78
		{ { 5.0f , 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//79
		{ { 3.0f , 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//80
		{ { 6.0f, 10.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//81
		{ { 7.0f, 12.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//82
		{ { 6.0f, 12.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//83
		{ { 9.0f, 10.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//84
		{ { 11.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//85
		{ { 9.0f , 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//86
		{ { 13.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//87
		{ { 14.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//88
		{ { 14.0f, 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//89
		{ { 13.0f, 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//90
		{ { 19.0f, 10.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//91
		{ { 20.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//92
		{ { 19.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//93
		{ { 6.0f, 16.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//94
		{ { 5.0f, 16.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//95
		{ { 11.0f, 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//96
		{ { 12.0f, 11.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//97
		{ { 12.0f, 16.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//98
		{ { 11.0f, 16.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//99
		{ { 10.0f, 13.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//100
		{ { 11.0f, 15.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//101
		{ { 10.0f, 15.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//102
		{ { 12.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//103
		{ { 13.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//104
		{ { 13.0f, 16.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//105
		{ { 14.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//106
		{ { 15.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//107
		{ { 15.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//108
		{ { 14.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//109
		{ { 16.0f, 12.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//110
		{ { 19.0f, 13.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//111
		{ { 16.0f, 13.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//112
		{ { 17.0f, 13.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//113
		{ { 17.0f, 15.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//114
		{ { 16.0f, 15.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//115
		{ { 13.0f, 15.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//116
		{ { 16.0f, 17.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//117
		{ { 13.0f, 17.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//118
		{ { 17.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//119
		{ { 18.0f, 14.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//120
		{ { 18.0f, 17.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//121
		{ { 17.0f, 17.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//122
		{ { 7.0f, 16.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//123
		{ { 7.0f, 18.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//124
		{ { 6.0f, 18.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//125
		{ { 8.0f , 18.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//126
		{ { 8.0f, 19.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//127
		{ { 7.0f, 19.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//128
		{ { 17.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//129
		{ { 16.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//130
		{ { 9.0f, 19.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//131
		{ { 9.0f, 22.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//132
		{ { 8.0f, 22.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },//133
		{ { 11.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//134
		{ { 12.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//135
		{ { 12.0f, 21.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//136
		{ { 11.0f, 21.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//137
		{ { 13.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//138
		{ { 14.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//139
		{ { 14.0f, 21.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//140
		{ { 13.0f, 21.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//141
		{ { 15.0f, 19.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//142
		{ { 16.0f, 22.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//143
		{ { 15.0f, 22.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//144
		{ { 10.0f, 22.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//145
		{ { 10.0f, 23.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//146
		{ { 9.0f , 23.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//147
		{ { 13.0f, 23.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//148
		{ { 14.0f, 23.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//149
		{ { 14.0f, 24.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//150
		{ { 12.0f, 24.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//151
		{ { 14.0f, 22.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//152
		{ { 15.0f, 24.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//153
		{ { 14.0f, 24.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//154
		{ { 14.0f, 23.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//155
		{ { 13.0f, 24.0f, 0.0f } , { 0.0f, 0.0f, 0.0f } },//156
		//Rosa 1
		{ { 11.0f, 1.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//157
		{ { 12.0f, 1.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//158
		{ { 12.0f, 2.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//159
		{ { 11.0f, 2.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//160
		{ { 16.0f,11.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//161
		{ { 19.0f,11.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//162
		{ { 19.0f,12.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//163
		{ { 16.0f,12.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//164
		{ { 10.0f,20.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//165
		{ { 11.0f,20.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//166
		{ { 11.0f,22.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//167
		{ { 10.0f,22.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//168
		{ { 11.0f,21.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//169
		{ { 12.0f,21.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//170
		{ { 12.0f,23.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//171
		{ { 11.0f,23.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//172
		{ { 14.0f,20.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//173
		{ { 15.0f,20.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//174
		{ { 15.0f,22.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//175
		{ { 14.0f,22.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//176
		{ { 13.0f,21.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//177
		{ { 14.0f,21.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//178
		{ { 14.0f,23.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//179
		{ { 13.0f,23.0f, 0.0f } , { 0.89f, 0.71f, 0.54f } },//180
		//Rosa 2
		{ { 10.0f, 1.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//181
		{ { 11.0f, 1.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//182
		{ { 11.0f, 2.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//183
		{ { 10.0f, 2.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//184
		{ { 12.0f, 8.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//185
		{ { 14.0f, 8.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//186
		{ { 14.0f, 9.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//187
		{ { 12.0f, 9.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//188
		{ { 12.0f,10.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//189
		{ { 13.0f,10.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//190
		{ { 13.0f,11.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//191
		{ { 12.0f,11.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//192
		{ { 16.0f,11.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//193
		{ { 16.0f,12.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//194
		{ { 13.0f,12.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//195
		{ { 15.0f,12.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//196
		{ { 16.0f,14.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//197
		{ { 15.0f,14.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//198
		{ { 14.0f,12.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//199
		{ { 14.0f,14.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//200
		{ { 13.0f,14.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//201
		{ { 15.0f,10.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//202
		{ { 19.0f,10.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//203
		{ { 19.0f,11.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//204
		{ { 15.0f,11.0f, 0.0f } , { 0.84f, 0.55f, 0.29f } },//205
		//Rosa 3
		{ { 9.0f , 1.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//206
		{ { 10.0f, 1.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//207
		{ { 10.0f, 2.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//208
		{ { 9.0f , 2.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//209
		{ { 11.0f, 7.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//210
		{ { 16.0f, 7.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//211
		{ { 16.0f, 8.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//212
		{ { 11.0f, 8.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//213
		{ { 10.0f, 8.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//214
		{ { 12.0f, 8.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//215
		{ { 12.0f, 9.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//216
		{ { 10.0f, 9.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//217
		{ { 11.0f, 9.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//218
		{ { 12.0f,11.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//219
		{ { 11.0f,11.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//220
		{ { 13.0f,11.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//221
		{ { 13.0f,14.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//222
		{ { 12.0f,14.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//223
		{ { 14.0f,10.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//224
		{ { 15.0f,10.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//225
		{ { 15.0f,11.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//226
		{ { 14.0f,11.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//227
		{ { 15.0f, 9.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//228
		{ { 18.0f, 9.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//229
		{ { 18.0f,10.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//230
		{ { 16.0f,14.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//231
		{ { 16.0f,15.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//232
		{ { 13.0f,15.0f, 0.0f } , { 0.89f, 0.38f, 0.24f } },//233
		//Verde 1
		{ { 6.0f , 1.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//234
		{ { 8.0f , 1.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//235
		{ { 8.0f , 2.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//236
		{ { 6.0f , 2.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//237
		{ { 5.0f , 4.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//238
		{ { 6.0f , 4.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//239
		{ { 6.0f , 6.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//240
		{ { 5.0f , 6.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//241
		{ { 4.0f , 5.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//242
		{ { 5.0f , 5.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//243
		{ { 4.0f , 6.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//244
		{ { 8.0f ,15.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//245
		{ { 9.0f ,15.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//246
		{ { 9.0f ,17.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//247
		{ { 8.0f ,17.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//248
		{ { 10.0f,17.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//249
		{ { 10.0f,18.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//250
		{ { 9.0f ,18.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//251
		{ { 9.0f , 4.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//252
		{ { 10.0f, 4.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//253
		{ { 10.0f, 6.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//254
		{ { 9.0f , 6.0f, 0.0f } , { 0.53f, 0.74f, 0.14f } },//255
		//Verde 3
		{ { 2.0f , 1.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//256
		{ { 4.0f , 1.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//257
		{ { 4.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//258
		{ { 2.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//259
		{ { 3.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//260
		{ { 5.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//261
		{ { 5.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//262
		{ { 3.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//263
		{ { 2.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//264
		{ { 3.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//265
		{ { 3.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//266
		{ { 2.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//267
		{ { 1.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//268
		{ { 2.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//269
		{ { 2.0f , 8.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//270
		{ { 1.0f , 8.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//271
		{ { 3.0f , 6.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//272
		{ { 4.0f , 6.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//273
		{ { 4.0f ,11.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//274
		{ { 3.0f ,11.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//275
		{ { 6.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//276
		{ { 6.0f ,11.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//277
		{ { 5.0f ,11.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//278
		{ { 6.0f ,12.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//279
		{ { 5.0f ,12.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//280
		{ { 6.0f , 9.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//281
		{ { 7.0f , 9.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//282
		{ { 7.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//283
		{ { 4.0f , 7.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//284
		{ { 7.0f , 7.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//285
		{ { 7.0f , 8.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//286
		{ { 4.0f , 8.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//287
		{ { 6.0f , 6.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//288
		{ { 8.0f , 6.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//289
		{ { 8.0f , 7.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//290
		{ { 6.0f , 7.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//291
		{ { 7.0f , 3.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//292
		{ { 8.0f , 3.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//293
		{ { 8.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//294
		{ { 9.0f , 2.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//295
		{ { 9.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//296
		{ { 8.0f , 4.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//297
		{ { 10.0f, 8.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//298
		{ { 10.0f, 9.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//299
		{ { 8.0f , 9.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//300
		{ { 10.0f,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//301
		{ { 8.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//302
		{ { 9.0f ,10.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//303
		{ { 9.0f ,13.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//304
		{ { 7.0f ,13.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//305
		{ { 7.0f ,12.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//306
		{ { 7.0f ,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//307
		{ { 6.0f ,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//308
		{ { 8.0f ,13.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//309
		{ { 10.0f,13.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//310
		{ { 10.0f,14.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//311
		{ { 8.0f ,14.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//312
		{ { 9.0f ,14.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//313
		{ { 10.0f,15.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//314
		{ { 9.0f ,15.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//315
		{ { 11.0f,15.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//316
		{ { 11.0f,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//317
		{ { 10.0f,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//318
		{ { 13.0f,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//319
		{ { 13.0f,17.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//320
		{ { 11.0f,17.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//321
		{ { 8.0f ,16.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//322
		{ { 8.0f ,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//323
		{ { 7.0f ,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//324
		{ { 9.0f ,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//325
		{ { 9.0f ,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//326
		{ { 8.0f ,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//327
		{ { 10.0f,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//328
		{ { 10.0f,22.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//329
		{ { 9.0f ,22.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//330
		{ { 11.0f,22.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//331
		{ { 11.0f,23.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//332
		{ { 10.0f,23.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//333
		{ { 10.0f,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//334
		{ { 12.0f,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//335
		{ { 12.0f,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//336
		{ { 13.0f,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//337
		{ { 13.0f,21.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//338
		{ { 12.0f,21.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//339
		{ { 13.0f,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//340
		{ { 16.0f,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//341
		{ { 16.0f,19.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//342
		{ { 15.0f,17.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//343
		{ { 16.0f,17.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//344
		{ { 15.0f,18.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//345
		{ { 16.0f,15.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//346
		{ { 17.0f,15.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//347
		{ { 17.0f,17.0f, 0.0f } , { 0.32f, 0.44f, 0.2f } },//348
		//Verde 2
		{ { 4.0f , 1.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//349
		{ { 6.0f , 1.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//350
		{ { 6.0f , 2.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//351
		{ { 4.0f , 2.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//352
		{ { 5.0f , 3.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//353
		{ { 6.0f , 3.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//354
		{ { 6.0f , 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//355
		{ { 5.0f , 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//356
		{ { 3.0f , 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//357
		{ { 5.0f , 5.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//358
		{ { 3.0f , 5.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//359
		{ { 4.0f , 8.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//360
		{ { 7.0f , 8.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//361
		{ { 7.0f , 9.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//362
		{ { 4.0f , 9.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//363
		{ { 6.0f , 9.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//364
		{ { 6.0f ,10.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//365
		{ { 4.0f ,10.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//366
		{ { 7.0f , 7.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//367
		{ { 9.0f , 7.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//368
		{ { 9.0f , 8.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//369
		{ { 8.0f , 6.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//370
		{ { 10.0f, 6.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//371
		{ { 10.0f, 7.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//372
		{ { 8.0f , 7.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//373
		{ { 8.0f , 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//374
		{ { 9.0f , 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//375
		{ { 9.0f , 6.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//376
		{ { 9.0f , 3.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//377
		{ { 10.0f, 3.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//378
		{ { 10.0f, 4.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//379
		{ { 7.0f ,13.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//380
		{ { 8.0f ,13.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//381
		{ { 8.0f ,16.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//382
		{ { 7.0f ,16.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//383
		{ { 8.0f ,14.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//384
		{ { 9.0f ,14.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//385
		{ { 9.0f ,15.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//386
		{ { 8.0f ,15.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//387
		{ { 10.0f,15.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//388
		{ { 10.0f,17.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//389
		{ { 9.0f ,17.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//390
		{ { 8.0f ,17.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//391
		{ { 9.0f ,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//392
		{ { 8.0f ,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//393
		{ { 10.0f,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//394
		{ { 10.0f,19.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//395
		{ { 9.0f ,19.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//396
		{ { 10.0f,16.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//397
		{ { 11.0f,16.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//398
		{ { 11.0f,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//399
		{ { 11.0f,17.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//400
		{ { 15.0f,17.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//401
		{ { 815.0f,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//402
		{ { 12.0f,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//403
		{ { 13.0f,18.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//404
		{ { 13.0f,19.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//405
		{ { 12.0f,19.0f, 0.0f } , { 0.44f, 0.53f, 0.11f } },//406
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,  // First Triangle
		0, 2, 3,   // Second Triangle
		1, 4, 5,
		1, 5, 6,
		7, 8, 9,
		7, 9, 10,
		11, 5, 12,
		11, 12, 13,
		2, 14, 15,
		2, 15, 16,
		17, 10, 18,
		17, 18, 19,
		9, 13, 20,
		9, 20, 21,
		22, 16, 23,
		22, 23, 24,
		25, 26, 27,
		25, 27, 28,
		29, 30, 31,
		29, 31, 32,
		33, 24, 34,
		33, 34, 35,
		36, 37, 38, 
		36, 38, 39,
		38, 28, 40,
		38, 40, 41,
		42, 43, 32,
		42, 32, 44,
		45, 46, 47,
		45, 47, 48,
		47, 49, 50, 
		47, 50, 51,
		34, 52, 53,
		34, 53, 54,
		55, 56, 57,
		55, 57, 58,
		59, 60, 61,
		59, 61, 62,
		63, 64, 65,
		63, 65, 66,
		67, 68, 69,
		67, 69, 70,
		71, 72, 73, 
		71, 73, 74,
		53, 75, 76,
		53, 76, 77,
		76, 78, 79,
		76, 79, 80,
		81, 58, 82,
		81, 82, 83,
		84, 61, 85,
		84, 85, 86,
		87, 88, 89,
		87, 89, 90,
		91, 73, 92,
		91, 92, 93,
		79, 83, 94,
		79, 94, 95,
		96, 97, 98,
		96, 98, 99,
		100, 85, 101,
		100, 101, 102,
		103, 104, 105,
		103, 105, 98,
		106, 107, 108,
		106, 108, 109,
		110, 93, 111,
		110, 111, 112,
		112, 113, 114,
		112, 114, 115,
		116, 115, 117,
		116, 117, 118,
		119, 120, 121, 
		119, 121, 122,
		94, 123, 124,
		94, 124, 125,
		124, 126, 127,
		124, 127, 128,
		117, 122, 129,
		117, 129, 130,
		127, 131, 132,
		127, 132, 133,
		134, 135, 136,
		134, 136, 137,
		138, 139, 140,
		138, 140, 141,
		142, 130, 143,
		142, 143, 144,
		132, 145, 146,
		132, 146, 147,
		136, 141, 148,
		125, 148, 149,
		146, 149, 150,
		146, 150, 151,
		152, 144, 153,
		152, 153, 154,
		148, 155, 154,
		148, 154, 156,
		157, 158, 159,
		157, 159, 160,//
		157, 158, 159,
		157, 159, 160,
		161, 162, 163,
		161, 163, 164,
		165, 166, 167,
		165, 167, 168,
		169, 170, 171, 
		169, 171, 172,
		173, 174, 175,
		173, 175, 176,
		177, 178, 179,
		177, 179, 180,//
		206, 207, 208,
		206, 208, 209,
		210, 211, 212,
		210, 212, 213,
		214, 215, 216, 
		214, 216, 217,
		218, 216, 219,
		218, 219, 220,
		219, 221, 222,
		219, 222, 223,
		224, 225, 226, 
		224, 226, 227, 
		228, 229, 230,
		228, 230, 225,
		222, 231, 232,
		222, 232, 233,//
		234, 235, 236,
		234, 236, 237,
		238, 239, 240,
		238, 240, 241,
		242, 243, 241,
		242, 241, 244,
		245, 246, 247,
		245, 247, 248,
		247, 249, 250,
		247, 250, 251,
		252, 253, 254,
		252, 254, 255,//
		256, 257, 258,
		256, 258, 259,
		260, 261, 262,
		260, 262, 263,
		264, 265, 266,
		264, 266, 267,
		268, 269, 270,
		268, 270, 271,
		272, 273, 274,
		272, 274, 275,
		266, 276, 277,
		266, 277, 275,
		278, 277, 279,
		278, 279, 280,
		281, 282, 283,
		281, 283, 276,
		284, 285, 286,
		284, 286, 287,
		288, 289, 290,
		288, 290, 291,
		292, 293, 290,
		292, 290, 285,
		294, 295, 296,
		294, 296, 297,
		286, 298, 299,
		286, 299, 282,
		300, 299, 301,
		300, 301, 302,
		283, 303, 304,
		283, 304, 305,
		279, 306, 307,
		279, 307, 308,
		309, 310, 311,
		309, 311, 312,
		313, 311, 314,
		313, 314, 315,
		314, 316, 317,
		314, 317, 318,
		317, 319, 320,
		317, 320, 321,
		307, 322, 323,
		307, 323, 324,
		323, 325, 326,
		323, 326, 327,
		326, 328, 329,
		326, 329, 330,
		329, 331, 332,
		329, 332, 333,
		334, 335, 336,
		334, 336, 328,
		336, 337, 338,
		336, 338, 339,
		340, 341, 342,
		340, 342, 337,
		343, 344, 341,
		343, 341, 345,
		346, 347, 348,
		346, 348, 344,//
		349, 350, 351,
		349, 351, 352,
		353, 354, 355,
		353, 355, 356,
		357, 356, 358,
		357, 358, 359,
		360, 361, 362,
		360, 362, 363,
		363, 364, 365,
		363, 365, 366,
		367, 368, 369,
		367, 369, 361,
		370, 371, 372,
		370, 372, 373,
		374, 375, 376,
		374, 376, 370,
		377, 378, 379,
		377, 379, 375,
		380, 381, 382,
		380, 382, 383,
		384, 385, 386,
		384, 386, 387,
		386, 388, 389,
		386, 389, 390,
		391, 390, 392,
		391, 392, 393,
		392, 394, 395,
		392, 395, 396,
		397, 398, 399,
		397, 399, 394,
		400, 401, 402,
		400, 402, 399,
		403, 404, 405,
		403, 405, 406
	};

	const size_t bufferSize = sizeof(vertices);
	const size_t vertexSize = sizeof(vertices[0]);
	const size_t rgbOffset = sizeof(vertices[0].XYZ);

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);
	// This is for the render with index element
	glGenBuffers(1, &EBO3);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
		(GLvoid*)rgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void marioBota() {
	// This is for the render with index element
	Vertex vertices[] =
	{
		{ { 1.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 1.0f , 2.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 0.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 13.0f, 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
		{ { 2.0f , 1.0f , 0.0f } , { 0.0f, 0.0f, 0.0f } },
	};

	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 2,  // First Triangle
		0, 2, 3,   // Second Triangle
		4, 5, 6,
		4, 6, 7
	};

	const size_t bufferSize = sizeof(vertices);
	const size_t vertexSize = sizeof(vertices[0]);
	const size_t rgbOffset = sizeof(vertices[0].XYZ);

	glGenVertexArrays(1, &VAO4);
	glGenBuffers(1, &VBO4);
	// This is for the render with index element
	glGenBuffers(1, &EBO4);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO4);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, vertices, GL_STATIC_DRAW);

	// This is for the render with index element
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO4);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
		(GLvoid*)rgbOffset);

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
	shader.destroy();

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &VBO3);
	glDeleteBuffers(1, &VBO4);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &EBO2);
	glDeleteBuffers(1, &EBO3);
	glDeleteBuffers(1, &EBO4);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteVertexArrays(1, &VAO3);
	glDeleteVertexArrays(1, &VAO4);
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
		case GLFW_KEY_UP:
			if (option == 3)
				option = 0;
			else
				option = option + 1;
			break;
		case GLFW_KEY_DOWN:
			if (option == 0)
				option = 3;
			else
				option = option - 1;
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
	while (psi) {
		psi = processInput(true);
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		//Este método es para activar los shaders que deseamos utilizar
		shader.turnOn();

		glm::mat4 projection = glm::ortho(-1.0f, 21.0f, -1.0f, 25.0f, 0.1f, 10.0f);
		GLuint locPoj = shader.getUniformLocation("projection");
		glUniformMatrix4fv(locPoj, 1, GL_FALSE, glm::value_ptr(projection));

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -1.0));
		GLuint locView = shader.getUniformLocation("view");
		glUniformMatrix4fv(locView, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, 12.0f, 0.0f));
		GLuint locModel = shader.getUniformLocation("model");
		glUniformMatrix4fv(locPoj, 1, GL_FALSE, glm::value_ptr(projection));


		if (option == 0) {
			glBindVertexArray(VAO);
			// This is for the render with index element
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (GLuint *)0);
		}
		else if (option == 1){
			glBindVertexArray(VAO2);
			// This is for the render with index element
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (GLuint *)0);
		}
		else if (option == 2) {
			glBindVertexArray(VAO3);
			// This is for the render with index element
			glDrawElements(GL_TRIANGLES, 594, GL_UNSIGNED_INT, (GLuint *)0);
		}
		else {
			glBindVertexArray(VAO4);
			// This is for the render with index element
			glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (GLuint *)0);
		}
		
		glBindVertexArray(0);

		//Este metodo es para desactivar el uso del shader
		shader.turnOff();

		glfwSwapBuffers(window);
	}
}

int main(int argc, char ** argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}

