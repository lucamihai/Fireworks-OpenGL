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
#include <time.h>
#include <iostream>

using namespace std;

class Punct {
public:
	GLfloat x, y, z;
	Punct() {}
	Punct(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

const int numarParticule = 1000;
int p = 0;

GLfloat limitaInaltime = 50;

GLfloat limitaLauncherXNegativ = -75;
GLfloat limitaLauncherXPozitiv = 75;

GLfloat limitaInaltimeInferioaraParticule = -25;

GLdouble sizeParticul = 0.25;

const int puncteTraiectorie = 150;	//cate puncte vor fi definite pe traiectoria particulelor
									//cresterea valorii duce la o cadere mai "fluenta" 
									//dar si la o viteza redusa de cadere, datorita apelului functiei Sleep

Punct sursa(60, 60, 60);
Punct launcher(0, -85, 0);
Punct firework(0, -85, 0);
Punct origineParticule;		//punctul de unde pornesc particulele (de unde a explodat firework-ul)

//int punctCurent = 0;		//index pentru selectarea punctului din totalitatea punctelor parcurse de traiectoria particulelor

bool lansat = false;		//true daca a fost lansat un firework
bool seInalta = false;		//true daca firework-ul se inalta
bool part = false;			//true daca firework-ul a explodat si daca particulele mai au de parcurs traiectorile propii

void myinit(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);
void CALLBACK deplasareStangaLauncher();
void CALLBACK deplasareDreaptaLauncher();
void CALLBACK launch();


/*  Se initializeaza proprietatile materialului, ale sursei de lumina
*  si ale modelului de iluminare
*/



double bezier(double A,  // Start value
	double B,  // First control value
	double C,  // Second control value
	double D,  // Ending value
	double t)  // Parameter 0 <= t <= 1
{
	double s = 1 - t;
	double AB = A * s + B * t;
	double BC = B * s + C * t;
	double CD = C * s + D * t;
	double ABC = AB * s + CD * t;
	double BCD = BC * s + CD * t;
	return ABC * s + BCD * t;
}

GLfloat randomize(GLfloat n) {
	int decizie = rand() % 10;
	GLfloat limita = 0.75;
	GLfloat deviatie = 0;
	if (decizie >= 0 && decizie <= 4) {
		deviatie = (GLfloat)((rand() % 75) / 100.0);
	}
	if (decizie >= 5 && decizie <= 8) {
		deviatie = (GLfloat)((rand() % 75) / 100.0);
	}
	decizie = rand() % 2;
	if (decizie == 1) {
		deviatie = deviatie * -1;
	}

	return (n + deviatie);
}

double randomize(double n) {
	int decizie = rand() % 10;
	double limita = 0.75;
	double deviatie = 0;
	if (decizie >= 0 && decizie <= 4) {
		deviatie = (double)((rand() % 75) / 100.0);
	}
	if (decizie >= 5 && decizie <= 8) {
		deviatie = (double)((rand() % 75) / 100.0);
	}
	decizie = rand() % 2;
	if (decizie == 1) {
		deviatie = deviatie * -1;
	}

	return (n + deviatie);
}

class Particul {
	GLfloat x, y, z;	
public:
	int punctCurent = 0;
	Punct coordonate[puncteTraiectorie];

	Particul() { x = 0; y = 0; z = 0; }
	Particul(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void mofificaX(GLfloat x) { this->x = x; }
	void mofificaY(GLfloat y) { this->y = y; }
	void mofificaZ(GLfloat z) { this->z = z; }

	void generareBezier() {
		/*coordonate Bezier*/
		int i = 0;
		for (double t = 0; t <= 1; t += (1.0 / puncteTraiectorie)) {
			double distantaX = origineParticule.x - this->x;
			double finalX = this->x - (distantaX)*2.5;

			/*cout << "distantaX=" << distantaX << endl;
			cout << "x final=" << finalX << endl;*/

			double coordonataX = bezier(origineParticule.x, this->x, this->x, finalX, t);

			double coordonataY = bezier(limitaInaltime, this->y, this->y, limitaInaltimeInferioaraParticule, t);

			coordonate[i].x = randomize(coordonataX);
			coordonate[i].y = randomize(coordonataY);
			coordonate[i].z = 0;
			i++;
		}
	}

	void modificaCoordonate(GLfloat x, GLfloat y, GLfloat z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void goUrmatorulPunct() {
	
		/*x = coordonate[punctCurent].x;
		y = coordonate[punctCurent].y;
		z = coordonate[punctCurent].z;
		
		punctCurent++;*/

		x = coordonate[p].x;
		y = coordonate[p].y;
		z = coordonate[p].z;

		//cout << "x=" << x << " y=" << y << " z=" << z << endl;
		//cout << "origine.x=" << origineParticule.x << endl;
	}

	void afiseaza() {
		glPushMatrix();
			glTranslatef(x, y, z);
			auxSolidSphere(sizeParticul);
		glPopMatrix();
	}

	void dispersie() {
		x = randomize(x);
		y = randomize(y);
	}
};

Particul particule[numarParticule];

void CALLBACK deplasareStangaLauncher() {
	if (launcher.x>limitaLauncherXNegativ)
		launcher.x -= 1;
}

void CALLBACK deplasareDreaptaLauncher() {
	if (launcher.x<limitaLauncherXPozitiv)
		launcher.x += 1;
}

void CALLBACK launch() {
	if (!part) {
		firework.x = launcher.x;
		firework.y = launcher.y;
		lansat = true;
		seInalta = true;
	}
}

void CALLBACK fireworks() {
	if (lansat && seInalta) {
		firework.y++;
		display();	
		Sleep(10);
		if (firework.y == limitaInaltime) {
			origineParticule.x = firework.x;
			seInalta = false;
			display();
			return;
		}				
	}
	if (lansat && !seInalta) {		
		firework.x = launcher.x;
		firework.y = launcher.y;	
		//display();
		lansat = false;
		part = true;
	}	
	if (part) {		
		for (int i = 0; i < numarParticule; i++) {
			particule[i].goUrmatorulPunct();
		}	
		display();
		Sleep(10);
		p++;
		/*if (particule[0].punctCurent >= 50) {
			for (int i = 0; i < numarParticule; i++)
				particule[i].punctCurent = 0;
			part = false;
		}*/
		if (p >= puncteTraiectorie) {		
			p = 0;
			part = false;
			display();
		}
			
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
	GLfloat n = 2;

	GLfloat x = 0; GLfloat y = 0; GLfloat z = 0;

	while (ct < numarParticule) {	
		/*partea superioara*/
		for (GLfloat i = (-n / 2)*2; i < 0; i+=2) {
			/*jumatatea din stanga*/
			if (ct == numarParticule)
				return;
			x = firework.x + i;
			y = limitaInaltime + n + 1;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}
		for (GLfloat i = 2; i <= (n / 2)*2; i+=2) {
			/*jumatatea din dreapta*/
			if (ct == numarParticule)
				return;
			x = firework.x + i;
			y = limitaInaltime + n + 1;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}


		/*partea din stanga*/
		for (GLfloat i = (-n / 2)*2; i < 0; i+=2) {
			/*jumatatea de jos*/
			if (ct == numarParticule)
				return;
			x = firework.x - n - 1;
			y = limitaInaltime + i;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}
		for (GLfloat i = 2; i <= (n / 2)*2; i+=2) {
			/*jumatatea de sus*/
			if (ct == numarParticule)
				return;
			x = firework.x - n - 1;
			y = limitaInaltime + i;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}


		/*partea inferioara*/
		for (GLfloat i = -n; i < 0; i+=2) {
			/*jumatatea din dreapta*/
			if (ct == numarParticule)
				return;
			x = firework.x - i;
			y = limitaInaltime - n - 1;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}
		for (GLfloat i = 2; i <= n; i+=2) {
			/*jumatatea din stanga*/
			if (ct == numarParticule)
				return;
			x = firework.x - i;
			y = limitaInaltime - n - 1;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}


		/*partea din dreapta*/
		for (GLfloat i = -n; i < 0; i+=2) {
			/*jumatatea superioara*/
			if (ct == numarParticule)
				return;
			x = firework.x + n + 1;
			y = limitaInaltime - i;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}
		for (GLfloat i = 2; i <= n; i+=2) {
			/*jumatatea inferioara*/
			if (ct == numarParticule)
				return;
			x = firework.x + n + 1;
			y = limitaInaltime - i;
			particule[ct].modificaCoordonate(x, y, 0);
			particule[ct].dispersie();
			particule[ct].generareBezier();
			ct++;
		}
		n += 2;
	}
}

void myinit(void)
{	
	srand(time(NULL));
	// coeficientii de reflexie pentru reflexia ambientala 
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
	GLfloat light_position[] = { sursa.x, sursa.y, sursa.z, 0 };

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

	GLfloat light_position[] = { sursa.x, sursa.y, sursa.z, 1 };

	glEnable(GL_CULL_FACE);//activeaza eliminarea fetelor
	glCullFace(GL_BACK);//sunt eliminate fetele spate
	//inlocuiti cu GL_FRONT pentru fete fata

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	/*sfera - sursa lumina*/
	glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(sursa.x, sursa.y, sursa.z);
		glColor3f(1, 1, 0.48);
		auxSolidSphere(10);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	

	/*floor?*/
	glPushMatrix();
		glColor3f(0, 0.5, 0);
		glTranslatef(0, -95, 0);
		glScalef(25, 0.5, 0);
		auxSolidCube(10);
	glPopMatrix();

	/*launcher*/
	glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(launcher.x, launcher.y, 0);
		glScalef(1, 2, 1);
		glRotatef(30, 0, 1, 0);
		auxSolidCube(5);
	glPopMatrix();

	/*firework*/
	if (lansat) {	
		glPushMatrix();
			glTranslatef(firework.x, firework.y, 0);
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
			part = true;
			//lansat = true;
		}
	}
	if (part) {	
		//glPushMatrix();
			for (int i = 0; i < numarParticule; i++) {
				//glPushMatrix();
				particule[i].afiseaza();
				//glPopMatrix();
			}
		//glPopMatrix();
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
	auxInitPosition(0, 0, 1280, 720);
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
