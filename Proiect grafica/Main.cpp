/*
* cone.c
* Programul demonstreaza utilizarea iluminarii in OpenGL
* Se deseneaza un con cu material de culoarea gri
* Obiectul este iluminat de o singura sursa de lumina
*/
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void myinit(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);
void CALLBACK deplasareStangaLauncher();
void CALLBACK deplasareDreaptaLauncher();
void CALLBACK launch();


/*  Se initializeaza proprietatile materialului, ale sursei de lumina
*  si ale modelului de iluminare
*/

const int numarParticule = 1000;
GLfloat pozXSursa = 60;
GLfloat pozYSursa = 60;
GLfloat pozZSursa = 60;
bool lansat = false;
bool seInalta = false;

GLfloat pozXLauncher = 0;
GLfloat pozYLauncher = -85;

GLfloat pozXFirework = 0;
GLfloat pozYFirework = -85;

class Particul {
	GLfloat x, y, z;
public:
	Particul() { x = 0; y = 0; z = 0; }
	Particul(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void mofificaX(GLfloat x) { this->x = x; }
	void mofificaY(GLfloat y) { this->y = y; }
	void mofificaZ(GLfloat z) { this->z = z; }
	void modificaCoordonate(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	void afiseaza() {
		glTranslatef(x, y, z);
		auxSolidSphere(0.5);
	}
};
Particul particule[numarParticule];
void CALLBACK deplasareStangaLauncher() {
	if (pozXLauncher>-55)
		pozXLauncher -= 1;
}

void CALLBACK deplasareDreaptaLauncher() {
	if (pozXLauncher<55)
		pozXLauncher += 1;
}

void CALLBACK launch() {
	pozXFirework = pozXLauncher;
	pozYFirework = pozYLauncher;
	lansat = true;
	seInalta = true;
}

void CALLBACK fireworks() {
	if (lansat && seInalta) {
		pozYFirework++;
		display();	
		Sleep(10);
		if (pozYFirework > 74) {
			seInalta = false;
			display();
			return;
		}				
	}
	if (lansat && !seInalta) {
		pozYFirework = pozYLauncher;
		pozXFirework = pozXLauncher;
		display();
		lansat = false;
	}	
}
/*void ConfigurareParticule() {
	//-------------------------------------------------------------
	particule[0].modificaCoordonate(pozXLauncher - 10, 75, 0);
	particule[1].modificaCoordonate(pozXLauncher - 9, 74, 0);
	particule[2].modificaCoordonate(pozXLauncher - 8, 73, 0);
	particule[3].modificaCoordonate(pozXLauncher - 7, 72, 0);
	particule[4].modificaCoordonate(pozXLauncher - -6, 73, 0);
	particule[5].modificaCoordonate(pozXLauncher - 5, 74, 0);
	particule[6].modificaCoordonate(pozXLauncher - 4, 75, 0);
	//-------------------------------------------------------------
	particule[7].modificaCoordonate(pozXLauncher - 1, 75, 0);
	particule[8].modificaCoordonate(pozXLauncher - 1, 74, 0);
	particule[9].modificaCoordonate(pozXLauncher - 1, 73, 0);
	particule[10].modificaCoordonate(pozXLauncher - 1, 72, 0);

	particule[11].modificaCoordonate(pozXLauncher, 75, 0);
	particule[12].modificaCoordonate(pozXLauncher + 1, 75, 0);

	particule[13].modificaCoordonate(pozXLauncher + 1, 74, 0);
	particule[14].modificaCoordonate(pozXLauncher, 73, 0);
	particule[15].modificaCoordonate(pozXLauncher + 1, 72, 0);
	//-------------------------------------------------------------
	particule[16].modificaCoordonate(pozXLauncher + 4, 75, 0);
	particule[17].modificaCoordonate(pozXLauncher + 4, 74, 0);
	particule[18].modificaCoordonate(pozXLauncher + 4, 73, 0);
	particule[19].modificaCoordonate(pozXLauncher + 4, 72, 0);
	particule[20].modificaCoordonate(pozXLauncher + 4, 71, 0);

	particule[21].modificaCoordonate(pozXLauncher + 5, 75, 0);
	particule[22].modificaCoordonate(pozXLauncher + 5, 73, 0);
	//-------------------------------------------------------------
	particule[23].modificaCoordonate(pozXLauncher + 11, 75, 0);
	particule[24].modificaCoordonate(pozXLauncher + 10, 74, 0);
	particule[25].modificaCoordonate(pozXLauncher + 9, 73, 0);
	particule[26].modificaCoordonate(pozXLauncher + 8, 72, 0);

	particule[27].modificaCoordonate(pozXLauncher + 12, 74, 0);
	particule[28].modificaCoordonate(pozXLauncher + 13, 73, 0);
	particule[29].modificaCoordonate(pozXLauncher + 14, 72, 0);
	particule[30].modificaCoordonate(pozXLauncher + 10, 73, 0);
	particule[31].modificaCoordonate(pozXLauncher + 11, 73, 0);
	//-------------------------------------------------------------
	particule[32].modificaCoordonate(pozXLauncher + 17, 75, 0);
	particule[33].modificaCoordonate(pozXLauncher + 17, 74, 0);
	particule[34].modificaCoordonate(pozXLauncher + 17, 73, 0);
	particule[35].modificaCoordonate(pozXLauncher + 17, 72, 0);

	particule[36].modificaCoordonate(pozXLauncher + 18, 72, 0);

	particule[37].modificaCoordonate(pozXLauncher + 19, 75, 0);
	particule[38].modificaCoordonate(pozXLauncher + 19, 74, 0);
	particule[39].modificaCoordonate(pozXLauncher + 19, 73, 0);
	particule[40].modificaCoordonate(pozXLauncher + 19, 72, 0);
	//-------------------------------------------------------------
	particule[41].modificaCoordonate(pozXLauncher + 25, 75, 0);
	particule[42].modificaCoordonate(pozXLauncher + 25, 74, 0);
	particule[43].modificaCoordonate(pozXLauncher + 25, 73, 0);
	particule[44].modificaCoordonate(pozXLauncher + 25, 71, 0);


	particule[45].modificaCoordonate(pozXLauncher + 26, 75, 0);
	particule[46].modificaCoordonate(pozXLauncher + 27, 75, 0);

	particule[47].modificaCoordonate(pozXLauncher + 26, 73, 0);
	particule[48].modificaCoordonate(pozXLauncher + 27, 73, 0);
	particule[49].modificaCoordonate(pozXLauncher + 27, 72, 0);

	particule[50].modificaCoordonate(pozXLauncher + 27, 71, 0);
	particule[51].modificaCoordonate(pozXLauncher + 26, 71, 0);
	particule[52].modificaCoordonate(pozXLauncher + 25, 71, 0);
}*/
void ConfigurareParticule() {
	int ct = 0;
	int n = 2;

	while (ct < numarParticule) {	
		for (int i = (-n / 2)*2; i < 0; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework + i, 75 + n + 1, 0);
		}
		for (int i = 2; i <= (n / 2)*2; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework + i, 75 + n + 1, 0);
		}

		for (int i = (-n / 2)*2; i < 0; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework - n - 1, 75 + i, 0);
		}
		for (int i = 2; i <= (n / 2)*2; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework - n - 1, 75 + i, 0);
		}
		//---------------
		for (int i = -n; i < 0; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework - i, 75 - n - 1, 0);
		}
		for (int i = 2; i <= n; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework - i, 75 - n - 1, 0);
		}

		for (int i = -n; i < 0; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework + n + 1, 75 - i, 0);
		}
		for (int i = 2; i <= n; i+=2) {
			if (ct == numarParticule)
				return;
			particule[ct++].modificaCoordonate(pozXFirework + n + 1, 75 - i, 0);
		}
		n += 2;
	}
	
	

}
void myinit(void)
{	// coeficientii de reflexie pentru reflexia ambientala 
	// si cea difuza sunt cei impliciti
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	/*  rflectanta speculara si exponentul de reflexie speculara
	nu sunt la valorile implicite (0.0)   */
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	// valori implicite pentru intensitatea sursei LIGHT0
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	/*  pozitia sursei nu are valori implicite */
	GLfloat light_position[] = { pozXSursa, pozYSursa, pozZSursa, 1 };

	GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	glEnable(GL_LIGHTING); // activare iluminare
	glEnable(GL_LIGHT0);	// activare sursa 0

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_COLOR_MATERIAL);
}

void CALLBACK display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*sfera - sursa lumina*/
	glPushMatrix();
		glTranslatef(pozXSursa, pozYSursa, pozZSursa);
		glColor3f(1, 1, 0);
		auxSolidSphere(10);
	glPopMatrix();

	/*launcher*/
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(pozXLauncher, pozYLauncher, 0);
		glScalef(1, 2, 1);
		glRotatef(30, 0, 1, 0);
		auxSolidCube(5);
	glPopMatrix();

	/*firework*/
	
	if (lansat) {	
		glPushMatrix();
			glTranslatef(pozXFirework, pozYFirework, 0);
			auxSolidSphere(2.5);
		glPopMatrix();

		if (!seInalta) {
			glPushMatrix();
			ConfigurareParticule();
			for (int i = 0; i < numarParticule; i++) {
				glPushMatrix();
				particule[i].afiseaza();
				glPopMatrix();
			}
			glPopMatrix();
		}
		
			
		//pozYFirework++;
		//Sleep(100);
	}
	
	glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-100, 100, -100*(GLfloat)h / (GLfloat)w,
			100*(GLfloat)h / (GLfloat)w, -100, 100);
	else
		glOrtho(-100*(GLfloat)w / (GLfloat)h,
			100*(GLfloat)w / (GLfloat)h, -100, 100, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
	auxInitPosition(0, 0, 640, 480);
	auxInitWindow("Waterworks :D");
	myinit();
	auxKeyFunc(AUX_LEFT, deplasareStangaLauncher);
	auxKeyFunc(AUX_RIGHT, deplasareDreaptaLauncher);
	auxKeyFunc(AUX_UP, launch);
	auxReshapeFunc(myReshape);
	auxIdleFunc(fireworks);

	auxMainLoop(display);
	return(0);
}
