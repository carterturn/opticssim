#include "concavespheremirror.h"
#include "source.h"
#include <iostream>
#include <vector>

#ifdef GRAPHICS
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char * argv[]){
	// Seed rand()
	srand((unsigned)time(NULL));

#ifdef GRAPHICS
	// Make window
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(1000, 1000, "Util Test", NULL, NULL);

	if(!window){
		cout << "Window creation failed\n";
		return -1;
	}

	glfwMakeContextCurrent(window);
	glOrtho(-10, 10, -10, 10, -10, 10);
#endif

	concavespheremirror s = concavespheremirror(tsvector(), 15, 9, tsvector(0, 0, 0));
	
	vector<object*> objects;
	objects.push_back(&s);

	source src = source(tsvector(50, 0, 0), 10);

#ifdef GRAPHICS
	while(true){
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_LINES);

		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-10, 0, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(0, -10, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(0, 0, -10);
		glVertex3f(0, 0, 10);

		glEnd();

		glColor3f(1.0f, 0.0f, 0.0f);

		glBegin(GL_POINTS);

		tsvector(0, 2, 0).draw();
		tsvector(1, 0, 0).draw();
		tsvector(0.1, 1, 0).draw();
		tsvector(0.5, 0, 0.6).draw();
		tsvector(0, 2.5, 0.5).draw();
		
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
	
		s.draw();
		src.draw();
		src.radiate(objects, 2);

		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(50000);
	}

	glfwTerminate();
#endif

	return 0;
}
