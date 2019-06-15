#include <stdlib.h>
#include <glut.h>
#include <iostream>

using namespace std;

int tableArray[8][8] = 
{ 
		{-1,-2,-3,-4,-5,-3,-2,-1},
		{-6,-6,-6,-6,-6,-6,-6,-6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{1, 2, 3, 4, 5, 3, 2, 1}
};

int tableArray2[8][8] = {
		{-1,-2,-3,-4,-5,-3,-2,-1},
		{-6,-6,-6,-6,-6,-6,-6,-6},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{6, 6, 6, 6, 6, 6, 6, 6},
		{1, 2, 3, 4, 5, 3, 2, 1}
};

void drawBS(double x, double y);
void drawWS(double x, double y);
void drawBorderS(double x, double y);

void fill()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			tableArray[i][j] = tableArray2[i][j];
		}
	}
}

void clearWindow() {

	glClearColor(0, 0.3, 0.7, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100,100,-100,100);
}



//board drawing

void drawChessBoard() {

	double x = -90, y = 90;

	drawBorderS(x, y);

	int c = 1;

	for (double y = 80; y >= -70; y -= 20) {
		for (double x = -80; x <= 70; x += 20) {
			if (c % 2 != 0) {
				drawWS(x, y);
			}
			else {
				drawBS(x, y);
			}
			c ++;
		}

		c ++;

	}

	
	double x1 = -74, y1 = 83;
	double x2 = -86, y2 = 70;
	char c1 = 'A';
	char c2 = '1';

	glColor3f(1, 1, 0.5);
	for (int i = 1; i < 9; i++) {
		glRasterPos2f(x1, y1);
		x1 += 20;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)(c1++));


		glRasterPos2f(x2, y2);
		y2 -= 20;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)(c2++));

	}

	/*x1 = -0.74; y1 = -0.86;
	x2 = 0.9; y2 = 0.7;
	c1 = 'A'; c2 = '1';
	for (int i = 1; i < 9; i++) {
		//whiteSquare();
		glRasterPos2f(x1, y1);
		x1 += 0.2;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)(c1++));

		glRasterPos2f(x2, y2);
		y2 -= 0.2;
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)(c2++));

	}*/
}

void drawBorderS(double x, double y) {
	glColor3f(0.3, 0.1, 0.05);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(y, y);
	glVertex2f(y, x);
	glVertex2f(x, x);
	glEnd();
}

void drawBS(double x, double y) {
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 20, y);
	glVertex2f(x + 20, y - 20);
	glVertex2f(x, y - 20);
	glEnd();
}

void drawWS(double x, double y) {
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(x, y);
	glVertex2f(x + 20 , y);
	glVertex2f(x + 20, y-20);
	glVertex2f(x, y-20);
	glEnd();
}

//circle algorithm

void plot(double x, double y)
{
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}


//puts 8 points

void drawEight(double a, double b, double x2, double y2)
{
	plot(a + x2, b + y2);
	plot(a - x2, b + y2);
	plot(a + x2, b - y2);
	plot(a - x2, b - y2);
	plot(a + y2, b + x2);
	plot(a - y2, b + x2);
	plot(a + y2, b - x2);
	plot(a - y2, b - x2);
}

//function for drawing circle
void midpoint(double a, double b, double r)
{
	double x = 0;
	double y = r;
	drawEight(a, b, x, y);

	double p = 1 - r;

	while (x < y)
	{

		x+=0.01;

		drawEight(a, b, x, y);

		if (p < 0)
		{
			p += 2 * x + 1;
		}

		else
		{
			y-=0.01;
			p += 2 * (x - y) + 1;
		}

	}
}

float t = 0, i = 0, j = 0, k = 0;

GLfloat s = 1.0, p = 1.0, isdown = 0;

int xtranslate = 20, ytranslate = -20, xsum = 0, ysum = 0, arrayElement = 0, currentX, currentY, nextX, nextY;

//choosing color

void color()
{
	if (arrayElement > 0)
	{
		glColor3f(0.5, 0.5, 0.5);
	}
	else {
		glColor3f(0.6, 0.6, 0.3);
	}
}

//figures

void drawRook()
{
	//
	//glColor3f(0.6, 0.6, 0.3);

	color();

	glBegin(GL_QUADS);
	glVertex2f(-75, 76);
	glVertex2f(-73, 76);
	glVertex2f(-73, 74);
	glVertex2f(-75, 74);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-71, 76);
	glVertex2f(-69, 76);
	glVertex2f(-69, 74);
	glVertex2f(-71, 74);
	glEnd();

	glBegin(GL_QUADS);
	glVertex2f(-67, 76);
	glVertex2f(-65, 76);
	glVertex2f(-65, 74);
	glVertex2f(-67, 74);
	glEnd();
		
	glBegin(GL_QUADS);
	glVertex2f(-75, 74);
	glVertex2f(-65, 74);
	glVertex2f(-65, 72);
	glVertex2f(-75 , 72);
	glEnd();


	glBegin(GL_QUADS);
	
	glVertex2f(-67 , 72 );
	glVertex2f(-73 , 72);
	glVertex2f(-74 , 68 );
	glVertex2f(-66 , 68 );
	
	glEnd();

	glBegin(GL_QUADS);
	
	glVertex2f(-76 , 68 );
	glVertex2f(-64 , 68 );
	glVertex2f(-64 , 64 );
	glVertex2f(-76 , 64);
	glEnd();
}

void drawPawn()
{
	
	//glColor3f(0.6, 0.6, 0.3);

	color();

	midpoint(-70, 74, 2);

	glBegin(GL_QUADS);

	glVertex2f(-67, 72);
	glVertex2f(-73, 72);
	glVertex2f(-74, 68);
	glVertex2f(-66, 68);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-76, 68);
	glVertex2f(-64, 68);
	glVertex2f(-64, 64);
	glVertex2f(-76, 64);
	glEnd();
}

void drawKnight()
{
	//
	//glColor3f(0.6, 0.6, 0.3);
	
	color();

	glBegin(GL_QUADS);
	glVertex2f(-75, 77);
	glVertex2f(-65, 77);
	glVertex2f(-65, 73);
	glVertex2f(-75, 73);
	glEnd();


	glBegin(GL_POLYGON);

	glVertex2f(-75, 73);
	glVertex2f(-72, 73);
	
	glVertex2f(-66, 69);
	glVertex2f(-67, 68);
	glVertex2f(-75, 68);
	
	

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-76, 68);
	glVertex2f(-64, 68);
	glVertex2f(-64, 64);
	glVertex2f(-76, 64);
	glEnd();
}

void drawBishop()
{
	//
	//glColor3f(0.6, 0.6, 0.3);
	
	color();

	glBegin(GL_TRIANGLES);
	glVertex2f(-70, 77);
	glVertex2f(-65, 73);
	glVertex2f(-75, 73);
	glEnd();


	glBegin(GL_QUADS);

	glVertex2f(-68, 73);
	glVertex2f(-72, 73);
	glVertex2f(-72, 67);
	glVertex2f(-68, 67);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-76, 67);
	glVertex2f(-64, 67);
	glVertex2f(-64, 64);
	glVertex2f(-76, 64);
	glEnd();
}

void drawKing()
{
	//glColor3f(0.6, 0.6, 0.3);

	color();

	midpoint(-70,76,2);
	midpoint(-70, 76, 1.5);
	midpoint(-70, 76, 1);

	glBegin(GL_TRIANGLES);
	glVertex2f(-73.5, 74);
	glVertex2f(-73.5, 79);
	glVertex2f(-70, 75);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex2f(-66.5, 74);
	glVertex2f(-66.5, 79);
	glVertex2f(-70, 75);
	glEnd();
	
	
	


	glBegin(GL_QUADS);

	glVertex2f(-66, 74);
	glVertex2f(-74, 74);
	glVertex2f(-74, 67);
	glVertex2f(-66, 67);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-76, 67);
	glVertex2f(-64, 67);
	glVertex2f(-64, 63);
	glVertex2f(-76, 63);
	glEnd();
}

void drawQueen() {

	//glColor3f(0.6, 0.6, 0.3);
	color();
	midpoint(-70, 78, 1);

	glBegin(GL_QUADS);

	glVertex2f(-66, 77);
	glVertex2f(-74, 77);
	glVertex2f(-72, 74);
	glVertex2f(-68, 74);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-68, 74);
	glVertex2f(-72, 74);
	glVertex2f(-74, 67);
	glVertex2f(-66, 67);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(-76, 67);
	glVertex2f(-64, 67);
	glVertex2f(-64, 63);
	glVertex2f(-76, 63);
	glEnd();
}

//Positions



void loadPosition()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			xsum += 20;
			arrayElement = tableArray[i][j];
			if (tableArray[i][j] == 0) {
				glTranslatef(xtranslate, 0, 0);
				continue;
			}
			else 
			if (abs(tableArray[i][j]) == 6) {

				drawPawn();
				glTranslatef(xtranslate, 0, 0);

			} else if (abs(tableArray[i][j]) == 1) {

				drawRook();
				glTranslatef(xtranslate, 0, 0);

			}
			else if (abs(tableArray[i][j]) == 2) {

				drawKnight();
				glTranslatef(xtranslate, 0, 0);

			}
			else if (abs(tableArray[i][j]) == 3) {

				drawBishop();
				glTranslatef(xtranslate, 0, 0);

			}
			else if (abs(tableArray[i][j]) == 4) {

				drawQueen();
				glTranslatef(xtranslate, 0, 0);
			}
			else if (abs(tableArray[i][j]) == 5) {

				drawKing();
				glTranslatef(xtranslate, 0, 0);
			}
		}

		glTranslatef(-xsum, ytranslate, 0);
		xsum = 0;
	}
	glTranslatef(0, -(8 * ytranslate), 0);
}

/*void moveRook(int value)
{
	
	if (i < 7 && j == 0)
	{
		i++;
		t += 0.2;
		s += 0.02;
		p = s;
		isdown = 0;
	}
	else if(i == 7 && j < 7) {
		j++;
		k -= 0.2;
		s -= 0.02;
		p = s;
		isdown = 0;
	}
	else if (j == 7 && i > 0)
	{
		i--;
		t -= 0.2;
		s += 0.02;
		p = s;
		isdown = 1;
	}
	else if (i == 0 && j >= 1)
	{
		j--;
		k += 0.2;
		s -= 0.02;
		p = s;
		isdown = 1;
	}
	
	
	glutPostRedisplay();
	glutTimerFunc(600, moveRook, 0);
	
}*/

void keyBoard(unsigned char key, int x, int y) {
	if (key == 'r')
	{
		fill();
		glutPostRedisplay();
	}
}

void myMouse(int button, int status, int x, int y) {

	int mainX = x / 65 - 1;
	int mainY = y / 65 - 1;

	if (button == GLUT_LEFT_BUTTON)
	{
		if (status == GLUT_DOWN) {
			currentX = mainX;
			currentY = mainY;
			cout << "FIRST values : \n x:" << currentX << "\n y:" << currentY << endl;
		}
		else if (status == GLUT_UP)
		{
			nextX = mainX;
			nextY = mainY;
			cout << "Second values : \n x:" << nextX << "\n y:" << nextY << endl;
			if (tableArray[currentY][currentX] > 0 && tableArray[nextY][nextX] < 0 ||
				tableArray[currentY][currentX] < 0 && tableArray[nextY][nextX] > 0 ||
				tableArray[nextY][nextX] == 0
				) {
				tableArray[nextY][nextX] = 0;
				int valuexchange = tableArray[currentY][currentX];
				tableArray[currentY][currentX] = tableArray[nextY][nextX];
				tableArray[nextY][nextX] = valuexchange;
			}
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++) {
					cout << tableArray[i][j] << " ";
				}
				cout << endl;
			}

			glutPostRedisplay();
		}
	}
}

void myDisplay() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	drawChessBoard();
	glMatrixMode(GL_MODELVIEW);
	/*glTranslatef(0.5, 0.5, 0);
	glRotatef(30.0, 0, 0, 1);
	glTranslatef(-0.5, -0.5, 0);
	
	
	
	glPushMatrix();
		
		
		
		glLoadIdentity();
		glTranslatef(t * p, k * p, 0);
		if (isdown == 0) {
			
			glTranslatef(0.5, 0.5, 0);
			glScalef(s, s, 0);
			glTranslatef(-0.5, -0.5, 0);
		}
		else {
			glTranslatef(-0.5, -0.5, 0);
			glScalef(s, s, 0);
			glTranslatef(0.5, 0.5, 0);
			
		}
		drawRook();
	
		glPopMatrix();*/
		//drawRook();
		//drawKnight();
		//drawBishop();
		//drawKing();
		//drawQueen();
		//drawPawn();
	glPushMatrix();

	loadPosition();

	glPopMatrix();

	glutSwapBuffers();


}


int main(int* args, char** argv)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(650, 650);
	glutInitWindowPosition(20, 20);
	glutCreateWindow("Chessboard");
	clearWindow();
	glutDisplayFunc(myDisplay);
	//glutTimerFunc(600,moveRook,0);
	glutKeyboardFunc(keyBoard);
	//glutSpecialFunc(process_SHIFT);
	glutMouseFunc(myMouse);



	glutMainLoop();

	return 0;
}
