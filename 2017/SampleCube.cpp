#define GLFW_INCLUDE_GLU
#include <iostream>
#include <GLFW/glfw3.h>
#define width 1280
#define height 960

static GLFWwindow*  window;

static const GLdouble CubeVertex[][3] = {
	{ 0.0, 0.0, 0.0 },
	{ 1.0, 0.0, 0.0 },
	{ 1.0, 1.0, 0.0 },
	{ 0.0, 1.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ 1.0, 0.0, 1.0 },
	{ 1.0, 1.0, 1.0 },
	{ 0.0, 1.0, 1.0 }
};

static const GLint CubeFace[][4] = {
	{ 0, 1, 2, 3 },
	{ 1, 5, 6, 2 },
	{ 5, 4, 7, 6 },
	{ 4, 0, 3, 7 },
	{ 4, 5, 1, 0 },
	{ 3, 2, 6, 7 }
};

static const GLdouble CubeNormal[][3] = {
	{ 0.0, 0.0,-1.0 },
	{ 1.0, 0.0, 0.0 },
	{ 0.0, 0.0, 1.0 },
	{ -1.0, 0.0, 0.0 },
	{ 0.0,-1.0, 0.0 },
	{ 0.0, 1.0, 0.0 }
};

static const GLfloat CubeMaterial[] = { 0.8, 0.35, 0.4, 1.0 };
static const GLfloat LightColor[] = { 0.2, 0.2, 0.8, 1.0 };
static const GLfloat Lightpos0[] = { 0.0, 3.0, 5.0, 1.0 };
static const GLfloat Lightpos1[] = { 5.0, 3.0, 0.0, 1.0 };


static void DrawCube()
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, CubeMaterial);

	glBegin(GL_QUADS);
	for (size_t i = 0; i < 6; ++i)
	{
		glNormal3dv(CubeNormal[i]);
		for (size_t j = 0; j < 4; ++j)
		{
			glVertex3dv(CubeVertex[CubeFace[i][j]]);
		}
	}
	glEnd();
}

int main()
{

	if (glfwInit() == GL_FALSE)
	{
		std::cerr << "Error initilize GLFW" << std::endl;
		exit(EXIT_FAILURE);
		return 1;
	}

	window = glfwCreateWindow(width, height, "SampleCube", NULL, NULL);

	if (window == NULL)
	{
		std::cerr << "Error create GLFW window." << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
		return 1;
	}

	glfwMakeContextCurrent(window);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightColor);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightColor);
	// #82ffe6 is HTML color
	glClearColor(0.509f, 1.0f, 0.901f, 1.0f);

	while (glfwWindowShouldClose(window) == GL_FALSE)
	{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();


		int now_width, now_height;
		glfwGetFramebufferSize(window, &now_width, &now_height);
		glViewport(0, 0, now_width, now_height);
		gluPerspective(30.0, (double)now_width / (double)now_height, 1.0, 100.0);
		glTranslated(0.0, 0.0, -2.0);
		gluLookAt(3.0, 5.0, 4.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glLightfv(GL_LIGHT0, GL_POSITION, Lightpos0);
		glLightfv(GL_LIGHT1, GL_POSITION, Lightpos1);

		DrawCube();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
