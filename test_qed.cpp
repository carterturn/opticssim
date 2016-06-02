#include "block.h"
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
#endif

	qed q = qed(tsvector(-2.5, -2.5, 0), tsvector(-2.5, 2.5, 0), 532e-3_mpf);

	line l = line(tsvector(2, 2, 0), tsvector(0, 0, 0.57), 5, 0.0, 0.0, cnst::c);
	line l2 = line(tsvector(2, -3, 0), tsvector(0, 0, -0.57), 5, 0.0, 0.0, cnst::c);

	vector<object*> objects = vector<object*>();
	objects.push_back(&l);
	objects.push_back(&l2);
	
	cout << q.calculate(objects, 0.1, 1) << "\n";
#ifdef GRAPHICS
	while(true){
		glClear(GL_COLOR_BUFFER_BIT);
		glEnable(GL_BLEND);

		glBegin(GL_LINES);

		glColor3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-10, 0, 0);
		glVertex3f(10, 0, 0);
		glVertex3f(0, -10, 0);
		glVertex3f(0, 10, 0);
		glVertex3f(0, 0, -10);
		glVertex3f(0, 0, 10);

		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
	
		l.draw();
		l2.draw();

		q.draw();

		glBegin(GL_POINTS);

		glColor3f(1.0f, 0.0f, 0.0f);

		glVertex3f(-2.5f, 0.0f, 0.0f);
		glVertex3f(2.5f, 0.0f, 0.0f);

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(50000);
	}

	glfwTerminate();
#endif

	return 0;
}
