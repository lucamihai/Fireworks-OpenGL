/*
Programul afiseaza un patrat pe care il translateaza 
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <GL/glut.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);


static GLfloat x=0;

static GLfloat y=0;
static alfa = 0;


void myinit () {
    glClearColor(1.0, 1.0, 1.0, 1.0);
	
}


void CALLBACK MutaStanga(void)
{
	x=x-10;
	alfa += 90;
}

void CALLBACK MutaDreapta(void)
{
	x=x+10;
}

void CALLBACK MutaSus(void)
{
	y=y+10;
}

void CALLBACK MutaJos(void)
{
	y=y-10;
}

void CALLBACK rot_z_up(AUX_EVENTREC * event){
	alfa -= 90;
}

void CALLBACK rot_z_down(AUX_EVENTREC * event){
	alfa += 90;
}

void CALLBACK display (void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity ();

	glTranslatef(x, 0, 0.0);
	glTranslatef(1, y, 0.0);

	glRotatef(300, 0, 0, 1);
	


	glBegin(GL_QUADS);
		
		glColor3f (1.0, 0.0, 0.0);
		glVertex2f(0, 0);
		glColor3f (1.0, 1.0, 0.0);
		glVertex2f(0, 100.0);
		glColor3f (0.0, 0.0, 1.0);
		glVertex2f(100, 100.0);
		glColor3f (0.0, 1.0, 0.0);
		glVertex2f(100, 0);

	glEnd();

	glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(100, 100);
		glColor3f(1.0, 1.0, 0.0);
		glVertex2f(100, 200.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(200, 200.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(200, 100);
	glEnd();

	auxWireSphere(10);

    glFlush();
}



void CALLBACK myReshape(GLsizei w, GLsizei h)	
{
    if (!h) 
		return;
    glViewport(0, 0, w, h);	
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)		
    glOrtho (-160.0, 160.0, 160.0*(GLfloat)h/(GLfloat)w, 
        -160.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else 
    glOrtho (-160.0*(GLfloat)w/(GLfloat)h, 
        160.0*(GLfloat)w/(GLfloat)h, -160.0, 160.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, 600, 400);
    auxInitWindow ("Un patrat care se translateaza pe axa x");
    myinit ();
	auxKeyFunc (AUX_LEFT, MutaStanga);
	auxKeyFunc (AUX_RIGHT, MutaDreapta);
	auxKeyFunc (AUX_UP, MutaSus);
	auxKeyFunc (AUX_DOWN, MutaJos);

	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);
	
    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
