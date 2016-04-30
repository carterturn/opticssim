#include "block.h"
#include <iostream>

#ifdef GRAPHICS
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <unistd.h>
#endif

using namespace std;

int main(int argc, char * argv[]){

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

	block b = block(tsvector(), tsvector(1, 5, 1), tsvector(0, 0, 0), 1.0, 0.0);

	cout << b.inside(tsvector(0.5, 2, 0)) << "\n";
	cout << b.inside(tsvector(1, 2.5, 0)) << "\n";
	cout << b.inside(tsvector(0.5, 2.5, 0)) << "\n";
	cout << b.inside(tsvector(0.5, 0, 0.6)) << "\n";
	cout << b.inside(tsvector(0, 2.5, 0.5)) << "\n";

	tsvector target = tsvector(0.5, 0, 0.5);
	tsvector a = b.get_reflected(target);
	cout << a.x.get_d() << ", " << a.y.get_d() << ", " << a.z.get_d() << "\n";

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

		glColor3f(0.0f, 1.0f, 0.0f);
	
		b.draw();

		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 1.0f);

		(target + tsvector(0.1, 0, 0)).draw();
		a.draw();

		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
		usleep(50000);
	}

	glfwTerminate();
#endif

	return 0;
}
