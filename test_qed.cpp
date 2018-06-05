#include "line.h"
#include "qed.h"
#include "constant.h"
#include <vector>
#include <iostream>

#ifdef GRAPHICS
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char * argv[]){

	cnst::precision = 1.0_mpf;

#ifdef GRAPHICS
	glfwInit();
	GLFWwindow * window = glfwCreateWindow(1000, 1000, "Util Test", NULL, NULL);

	if(!window){
		cout << "Window creation failed\n";
		return -1;
	}

	glfwMakeContextCurrent(window);
	glOrtho(-10, 10, -10, 10, -10, 10);
	// glEnable(GL_BLEND);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

	qed q = qed(tsvector(-4, 0, 0), tsvector(4, 0, 0), 532e-4_mpf);

	line l = line(tsvector(1, 2, 0), tsvector(0, 0, 1.57), 3);
	line l2 = line(tsvector(-1, -2, 0), tsvector(0, 0, 1.57), 3);

	vector<object*> objects = vector<object*>();
	objects.push_back(&l);
	objects.push_back(&l2);

	q.calculate(objects, 0.02, 2);
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

	
		q.draw();

		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);

		l.draw();
		l2.draw();

		glColor3f(1.0f, 0.0f, 0.0f);

		glVertex3f(-2.5f, 0.0f, 0.0f);
		glVertex3f(2.5f, 0.0f, 0.0f);

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(1000000);
	}

	glfwTerminate();
#endif

	return 0;
}
