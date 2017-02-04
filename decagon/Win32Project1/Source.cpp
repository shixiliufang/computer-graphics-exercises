#include <windows.h>
#include <glut.h>

void fun()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	
	/*glVertex2f(3.1f, -9.5f);		// coordinates too big
	glVertex2f(-3.1f, -9.5f);
	glVertex2f(-8.1f, -5.9f);
	glVertex2f(-10.0f, 0.0f);
	glVertex2f(-8.1f, 5.9f);
	glVertex2f(-3.1f, 9.5f);
	glVertex2f(3.1f, 9.5f);
	glVertex2f(8.1f, 5.9f);
	glVertex2f(10.0f, 0.0f);
	glVertex2f(8.1f, -5.9f);*/	

	glVertex2f(0.15f, -0.5f);
	glVertex2f(-0.15f, -0.5f);
	glVertex2f(-0.4f, -0.3f);
	glVertex2f(-0.5f, 0.0f);
	glVertex2f(-0.4f, 0.3f);
	glVertex2f(-0.15f, 0.5f);
	glVertex2f(0.15f, 0.5f);
	glVertex2f(0.4f, 0.3f);
	glVertex2f(0.5f, 0.0f);
	glVertex2f(0.4f, -0.3f);

	glEnd();
	glFlush();
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(350, 350);
	glutInitWindowPosition(300, 150);
	glutCreateWindow("Decagon");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glutDisplayFunc(fun);
	glutMainLoop();
	return 0;
}