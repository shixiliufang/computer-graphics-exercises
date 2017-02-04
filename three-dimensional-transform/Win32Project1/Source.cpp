#include <glut.h>
#include <math.h>
#define GL_PI 3.1415f

GLfloat xRot = -35.0f;
GLfloat yRot = 15.0f;
GLfloat xMov = 0.0f;
GLfloat winW = 0.0f;
GLfloat winH = 0.0f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	glLoadIdentity();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f + xMov, 0.0f, 0.0f);
	glVertex3f(1.0f + xMov, 0.0f, 0.0f);
	glVertex3f(1.0f + xMov, 0.0f, 1.0f);
	glVertex3f(0.0f + xMov, 0.0f, 1.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f + xMov, 1.0f, 1.0f);
	glVertex3f(0.0f + xMov, 1.0f, 0.0f);
	glVertex3f(1.0f + xMov, 1.0f, 0.0f);
	glVertex3f(1.0f + xMov, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f + xMov, 0.0f, 0.0f);
	glVertex3f(1.0f + xMov, 0.0f, 0.0f);
	glVertex3f(1.0f + xMov, 1.0f, 0.0f);
	glVertex3f(0.0f + xMov, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0f + xMov, 0.0f, 1.0f);
	glVertex3f(0.0f + xMov, 0.0f, 1.0f);
	glVertex3f(0.0f + xMov, 1.0f, 1.0f);
	glVertex3f(1.0f + xMov, 1.0f, 1.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(1.0f + xMov, 0.0f, 0.0f);
	glVertex3f(1.0f + xMov, 0.0f, 1.0f);
	glVertex3f(1.0f + xMov, 1.0f, 1.0f);
	glVertex3f(1.0f + xMov, 1.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f + xMov, 0.0f, 0.0f);
	glVertex3f(0.0f + xMov, 0.0f, 1.0f);
	glVertex3f(0.0f + xMov, 1.0f, 1.0f);
	glVertex3f(0.0f + xMov, 1.0f, 0.0f);
	glEnd();

	glPopMatrix();
	glFlush();
}
void OnReshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

}
void OnMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xMov -= 0.1;
		glutPostRedisplay();
	}
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Cube");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(OnReshape);
	glutMouseFunc(OnMouse);

	SetupRC();

	glutMainLoop();
}