/**
* @file         task2.cpp
* @brief       	This is the main driver program which calls the CastelJau Algorithm program    
* @author       Shreeya, Gunpreet and Sriram
* @include      freeglut libraries like <GL/glut.h> to implement OpenGL functions and custom header files
*/
#include <GL/glut.h>
# include <iostream>
#include<bits/stdc++.h>
#include "bezier1.h"


using namespace std;

///Window
int win;
///input for mouse function
int input = 0;
///variable for mouse-menu
int mid;

///Structure for control points
Point control_point[150];
///Temporary structure
Point arr[150];
///Total number of control points
int total_controlpoints = 0;
///Initial value of x
int x_prev  = 0;
///Initial value of y
int y_prev  = 0;

/**
* @fn           add_control_point()
* @brief        function for adding the control points
* @param  		x represents x coordinate of control point , y represents y coordinate of control point
* @return type  void
*/
void add_control_point(int x, int y) {
	control_point[total_controlpoints].x = x; 
	control_point[total_controlpoints].y = y;
	total_controlpoints++;
}


/**
* @fn           del_control_point()
* @brief        function for deleting the control points
* @param  		x represents x coordinate of control point , y represents y coordinate of control point
* @return type  void
*/
void del_control_point(int x, int y) {

	for (int i = 0; i < total_controlpoints; i++) {
		if (abs(x - control_point[i].x) < 15 && abs(control_point[i].y - y) < 15) {
			for (int j = i; j < total_controlpoints - 1; j++) {
				control_point[j].x = control_point[j + 1].x;
				control_point[j].y = control_point[j + 1].y;
			}
			total_controlpoints--;
			break;
		}
	}
}

/**
* @fn           draw_curve()
* @brief        function for drawing (plotting points) Bezier curve
* @param  		h represents height of window
* @return type  void
*/
void draw_curve(int h){

	for (int i = 0; i < 1000; ++i)
	{
		if (total_controlpoints < 1){
			break;
		}

				
		float t = (float)i/999.0 ;

		Point p;
		p = CastelJau(t,total_controlpoints,control_point,arr);

		glPointSize(2.0f);

		glBegin(GL_POINTS);
			int x = p.x;
			int y = p.y;
			glColor3f(0.8, 0, 0);
			glVertex2i(x, h - y);
		glEnd();
	}
}
 
/**
* @fn           draw_controlpoints()
* @brief        function for drawing (plotting points) Control Points
* @param  		h represents height of window
* @return type  void
*/
void draw_controlpoints(int h){

	glPointSize(5.0f);
	glBegin(GL_POINTS);
		for (int i = 0; i < total_controlpoints; i++)
		{
			int x = control_point[i].x;
			int y = control_point[i].y;

			glColor3f(0, 0, 1);
			glVertex2i(x, h - y);
		}
	glEnd();
}
/**
* @fn           display()
* @brief        function that calls the other function to construct the scene
* @parameters   void
* @return type  void
*/
void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT); // clear display window

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const double w = glutGet(GLUT_WINDOW_WIDTH);
	const double h = glutGet(GLUT_WINDOW_HEIGHT);

	gluOrtho2D(0.0, w, 0.0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw_curve(h);
	draw_controlpoints(h);
	glFlush();
}





/**
* @fn           mymouse()
* @brief        function that is called by glutMouseFunc (Handles mouse actions)
* @parameters   button : which button is pressed, state : state of button
*				x,y : coordinates of mouse
* @return type  void
*/
void mymouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (input == 1) {
			add_control_point(x, y);
		}
		else if (input == 2) {
			del_control_point(x, y);
		}
		else if (input == 3) {

			x_prev  = x;
			y_prev  = y;
			
		}
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		
		for (int i = 0; i < total_controlpoints; i++) {
			if (abs(x_prev  - control_point[i].x) < 10 && abs(control_point[i].y - y_prev ) < 10) {
				control_point[i].x = x;
				control_point[i].y = y;
				break;
			}
		}
		

	}


	glutPostRedisplay();
}


/**
* @fn           mykeyboard()
* @brief        function that is called by glutKeyboardFunc (Handles keyboard actions)
* @parameters  	key: the key pressed, x,y : coordinates of mouse
* @return type  void
*/
void mykeyboard(unsigned char key, int x, int y) {
	if(key=='d'){
		del_control_point(x, y);
	}
	else if(key=='a'){
		add_control_point(x,y);
	}
	else if (key=='m') {

			x_prev  = x;
			y_prev  = y;
			
		}
	else if (key == 'q'){
		glutDestroyWindow(win);
		exit(0);
	}
}



/**
* @fn           reshape()
* @brief        function that reshapes window
* @parameters  	x,y : coordinates of width, heigh
* @return type  void
*/
void reshape(int x, int y) {

	/* define the viewport transformation */
	glViewport(0, 0, x, y);

}


/**
* @fn           specify_menu()
* @brief        function that initializes menu
* @parameters   option represents which menu is chosen
* @return type  void
*/
void specify_menu(int option) {
	if (option == 0) {
		glutDestroyWindow(win);
		exit(0);
	}
	else {
		input = option;
	}
	glutPostRedisplay();
}

/**
* @fn           create_menu()
* @brief        function that creates menu
* @parameters   void
* @return type  void
*/
void create_menu(void) {

	mid = glutCreateMenu(specify_menu);
	glutAddMenuEntry("Point Addition", 1);
	glutAddMenuEntry("Point Deletion", 2);
	glutAddMenuEntry("Point Movement", 3);
	glutAddMenuEntry("Quit Window", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/**
* @fn           Init
* @brief        function that initializes the opengl window parameters
* @parameters   void
* @return type  void
*/
void Init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);				// Set clear color to white 
    glColor3f(1.0, 1.0, 1.0);						// Set fill color to black 
    glViewport(0, 0, 1080, 900);
    glMatrixMode(GL_PROJECTION); 				//Initialize Projection Matrix
    glLoadIdentity();
    gluOrtho2D(0, 1080, 0, 900);
}

/**
* @fn           main
* @brief        driver function 
* @parameters   string whose first character is number of nodes in graph and rest is preorder traversal of tree
* @return type  int
*/

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1200, 800);

	win = glutCreateWindow("Assignment 3"); 
	Init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(mykeyboard);
	glutMouseFunc(mymouse);
	
	create_menu();

	glutMainLoop();
	return 0;
}