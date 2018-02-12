#include <bits/stdc++.h>
#include <GLUT/glut.h>
#define GLUT_DISABLE_ATEXIT_HACK

//the color is red
GLfloat color[] = {1.0, 0.0, 0.0, 1.0};

//light position
GLfloat lightpos[] = {1200.0, 150.0, -500.0, 1.0};

//main func
void idle(void){
    glutPostRedisplay();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 320, 240); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //viewing angle
    gluPerspective(30.0, 300.0 / 300.0, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //set viewpoint
    gluLookAt(150.0, 100.0, -200.0, // Camera coordinate
              0.0, 0.0, 0.0,        // gazing point coordinate
              0.0, 1.0, 0.0);       // the screen, Vector pointing up 

    //set light
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    //set material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
    glutSolidCube(40.0);

    glutSwapBuffers();
}

void Init(){
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);                          // Initialization
    glutInitWindowPosition(100, 100);               // Window position
    glutInitWindowSize(300, 300);                   // Window size
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);   // Display mode & RGBA mode & doube buffer mode
    glutCreateWindow("offline sample program");     // Program show  windowname
    glutDisplayFunc(display);                       // Display callback
    glutIdleFunc(idle);                             // Idle callback
    Init();                                         // Next Func
    glutMainLoop();                                 // Loop processing
    return 0;
}
