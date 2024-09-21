#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265358979323846

// Variable to store the angle of the camera
GLfloat angle = 0.0;

// For the roof with high gloss factor
GLfloat roof_ambient[] = {0.25, 0.25, 0.25, 1.0};
GLfloat roof_diffuse[] = {0.4, 0.4, 0.4, 1.0};
GLfloat roof_specular[] = {0.774597, 0.774597, 0.774597, 1.0};
GLfloat roof_shininess[] = {100.0};

// For the walls with a matte reddish surface
GLfloat wall_ambient[] = {0.7, 0.0, 0.0, 1.0};
GLfloat wall_diffuse[] = {0.0, 0.0, 0.0, 1.0};
GLfloat wall_specular[] = {0.0, 0.0, 0.0, 1.0};
GLfloat wall_shininess[] = {1.0};

// For the green grass
GLfloat grass_ambient[] = {0.0, 0.3, 0.0, 1.0};
GLfloat grass_diffuse[] = {0.0, 0.5, 0.0, 1.0};
GLfloat grass_specular[] = {0.0, 0.0, 0.0, 1.0};
GLfloat grass_shininess[] = {1.0};

// Variable to store the angle of the spotlight
GLfloat spotlightAngle = .0;
// Flag to control the spotlight visibility
GLboolean isSpotlightOn = GL_TRUE;

// Sun parameters
GLfloat sun_radius = 2.0;
GLfloat sun_position_x = -50.0;
GLfloat sun_position_y = 0.0;
GLfloat sun_position_z = 0.0;

// Sunlight parameters
GLfloat sunlight_direction[] = {1.0, 0.0, 0.0};
GLfloat sunlight_diffuse_noon[] = {1.0, 1.0, 1.0, 1.0};
GLfloat sunlight_diffuse_sunset[] = {0.3, 0.3, 0.3, 1.0};

// Shading mode (smooth or flat)
GLboolean isSmoothShading = GL_TRUE;

// Observer position
GLfloat observer_position[] = {0.0, 0.0, 5.0, 1.0};

// Camera position
GLfloat camera_angle = 0.0;
GLfloat camera_radius = 70.0;

// Function to calculate the surface normal of a polygon
void calculateNormal(GLfloat* v1, GLfloat* v2, GLfloat* v3, GLfloat* normal) {
    GLfloat edge1[3];
    GLfloat edge2[3];
    edge1[0] = v2[0] - v1[0];
    edge1[1] = v2[1] - v1[1];
    edge1[2] = v2[2] - v1[2];
    edge2[0] = v3[0] - v1[0];
    edge2[1] = v3[1] - v1[1];
    edge2[2] = v3[2] - v1[2];
    normal[0] = edge1[1] * edge2[2] - edge1[2] * edge2[1];
    normal[1] = edge1[2] * edge2[0] - edge1[0] * edge2[2];
    normal[2] = edge1[0] * edge2[1] - edge1[1] * edge2[0];
    GLfloat length = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= length;
    normal[1] /= length;
    normal[2] /= length;
}

void init() {
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat white_light[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    // Set up the spotlight
    GLfloat spotlight_direction[] = {0.0, -1.0, 0.0};
    GLfloat spotlight_position[] = {-5.0, 10.0, 10.0, 1.0};
    GLfloat spotlight_cutoff = 30.0;

    glLightfv(GL_LIGHT1, GL_POSITION, spotlight_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlight_direction);
    glLightfv(GL_LIGHT1, GL_SPOT_CUTOFF, &spotlight_cutoff);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.0);

    // Set spotlight properties
    GLfloat spotlight_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlight_diffuse);

    // Enable the spotlight
    glEnable(GL_LIGHT1);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_radius * sin(camera_angle * PI / 180.0), 40.0, camera_radius * cos(camera_angle * PI / 180.0),
              0, 40, 0, 0, 1, 0);

    // Adjust spotlight properties
    GLfloat spotlight_cutoff = 300.0 * (GLfloat)w / (GLfloat)h;
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlight_cutoff);
}

void updateSunPosition() {
    // Update sun position along a semicircular path
    GLfloat path_radius = 50.0;
    GLfloat path_center_x = 0.0;
    GLfloat path_center_y = 0.0;
    GLfloat path_center_z = 0.0;
    GLfloat sun_angle = angle * PI / 180.0;
    sun_position_x = path_center_x + path_radius * sin(sun_angle);
    sun_position_y = path_center_y + path_radius * cos(sun_angle);
    sun_position_z = path_center_z;

    // Update sunlight direction based on sun position
    sunlight_direction[0] = (sun_position_x - path_center_x) / path_radius;
    sunlight_direction[1] = (sun_position_y - path_center_y) / path_radius;
    sunlight_direction[2] = (sun_position_z - path_center_z) / path_radius;
}

void calculateSunlightDiffuse() {
    // Calculate sunlight's diffuse reflectance based on sun position
    GLfloat light_diffuse[4];
    if (sun_position_x >= 0) {
        GLfloat t = sun_position_x / 50.0; // Normalized position in range [0, 1]
        light_diffuse[0] = t * sunlight_diffuse_noon[0] + (1 - t) * sunlight_diffuse_sunset[0];
        light_diffuse[1] = t * sunlight_diffuse_noon[1] + (1 - t) * sunlight_diffuse_sunset[1];
        light_diffuse[2] = t * sunlight_diffuse_noon[2] + (1 - t) * sunlight_diffuse_sunset[2];
        light_diffuse[3] = 1.0;
    } else {
        light_diffuse[0] = sunlight_diffuse_sunset[0];
        light_diffuse[1] = sunlight_diffuse_sunset[1];
        light_diffuse[2] = sunlight_diffuse_sunset[2];
        light_diffuse[3] = 1.0;
    }

    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
}

void drawGrass() {
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0, 0.0); // Set the surface normal for the grass

    // Set the material properties for the grass
    glMaterialfv(GL_FRONT, GL_AMBIENT, grass_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, grass_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, grass_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, grass_shininess);

    // Draw the grass quad
    glVertex3f(-50.0f, 0.0f, 50.0f);
    glVertex3f(50.0f, 0.0f, 50.0f);
    glVertex3f(50.0f, 0.0f, -50.0f);
    glVertex3f(-50.0f, 0.0f, -50.0f);
    glEnd();
}

void drawWalls() {
    // Calculate surface normals for the walls
    GLfloat normal[3];

    // Set the material properties for the walls
    glMaterialfv(GL_FRONT, GL_AMBIENT, wall_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wall_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, wall_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, wall_shininess);

    glBegin(GL_QUADS);
    if (isSmoothShading) {
        glShadeModel(GL_SMOOTH); // Use smooth shading
    } else {
        glShadeModel(GL_FLAT); // Use flat shading
    }

    // Front wall
    GLfloat v1[] = {-5.0f, 0.0f, 10.0f};
    GLfloat v2[] = {5.0f, 0.0f, 10.0f};
    GLfloat v3[] = {5.0f, 10.0f, 10.0f};
    GLfloat v4[] = {-5.0f, 10.0f, 10.0f};
    calculateNormal(v1, v2, v3, normal);
    glNormal3fv(normal);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v4);

    // Right wall
    GLfloat v5[] = {5.0f, 0.0f, 10.0f};
    GLfloat v6[] = {5.0f, 0.0f, -10.0f};
    GLfloat v7[] = {5.0f, 10.0f, -10.0f};
    GLfloat v8[] = {5.0f, 10.0f, 10.0f};
    calculateNormal(v5, v6, v7, normal);
    glNormal3fv(normal);
    glVertex3fv(v5);
    glVertex3fv(v6);
    glVertex3fv(v7);
    glVertex3fv(v8);

    // Back wall
    GLfloat v9[] = {5.0f, 0.0f, -10.0f};
    GLfloat v10[] = {-5.0f, 0.0f, -10.0f};
    GLfloat v11[] = {-5.0f, 10.0f, -10.0f};
    GLfloat v12[] = {5.0f, 10.0f, -10.0f};
    calculateNormal(v9, v10, v11, normal);
    glNormal3fv(normal);
    glVertex3fv(v9);
    glVertex3fv(v10);
    glVertex3fv(v11);
    glVertex3fv(v12);

    // Left wall
    GLfloat v13[] = {-5.0f, 0.0f, -10.0f};
    GLfloat v14[] = {-5.0f, 0.0f, 10.0f};
    GLfloat v15[] = {-5.0f, 10.0f, 10.0f};
    GLfloat v16[] = {-5.0f, 10.0f, -10.0f};
    calculateNormal(v13, v14, v15, normal);
    glNormal3fv(normal);
    glVertex3fv(v13);
    glVertex3fv(v14);
    glVertex3fv(v15);
    glVertex3fv(v16);

    glEnd();
}

void drawRoof() {
    // Calculate surface normals for the roof
    GLfloat normal[3];

    // Set the material properties for the roof
    glMaterialfv(GL_FRONT, GL_AMBIENT, roof_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, roof_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, roof_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, roof_shininess);

    glBegin(GL_TRIANGLES);
    if (isSmoothShading) {
        glShadeModel(GL_SMOOTH); // Use smooth shading
    } else {
        glShadeModel(GL_FLAT); // Use flat shading
    }

    // Front roof
    GLfloat v1[] = {-5.0f, 10.0f, 10.0f};
    GLfloat v2[] = {5.0f, 10.0f, 10.0f};
    GLfloat v3[] = {0.0f, 20.0f, 0.0f};
    calculateNormal(v1, v2, v3, normal);
    glNormal3fv(normal);
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v3);

    // Back roof
    GLfloat v4[] = {5.0f, 10.0f, -10.0f};
    GLfloat v5[] = {-5.0f, 10.0f, -10.0f};
    GLfloat v6[] = {0.0f, 20.0f, 0.0f};
    calculateNormal(v4, v5, v6, normal);
    glNormal3fv(normal);
    glVertex3fv(v4);
    glVertex3fv(v5);
    glVertex3fv(v6);

      // Left roof side
    GLfloat v7[] = {-5.0f, 10.0f, -10.0f};
    GLfloat v8[] = {-5.0f, 10.0f, 10.0f};
    GLfloat v9[] = {0.0f, 20.0f, 0.0f};
    calculateNormal(v7, v8, v9, normal);
    glNormal3fv(normal);
    glVertex3fv(v7);
    glVertex3fv(v8);
    glVertex3fv(v9);

    // Right roof side
    GLfloat v10[] = {5.0f, 10.0f, 10.0f};
    GLfloat v11[] = {5.0f, 10.0f, -10.0f};
    GLfloat v12[] = {0.0f, 20.0f, 0.0f};
    calculateNormal(v10, v11, v12, normal);
    glNormal3fv(normal);
    glVertex3fv(v10);
    glVertex3fv(v11);
    glVertex3fv(v12);

    glEnd();
}

void drawSun() {
    glPushMatrix();
    glTranslatef(sun_position_x, sun_position_y, sun_position_z);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(sun_radius, 20, 20);
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camera_radius * sin(camera_angle * PI / 180.0), 40.0, camera_radius * cos(camera_angle * PI / 180.0),
              0, 40, 0, 0, 1, 0);

    calculateSunlightDiffuse();

    // Draw the grass
    drawGrass();

    // Draw the walls
    drawWalls();

    // Draw the roof
    drawRoof();

    // Draw the sun
    drawSun();

    glutSwapBuffers();
}

void keyboard(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            camera_angle -= 5.0;
            if (camera_angle < 0.0)
                camera_angle += 360.0;
            break;
        case GLUT_KEY_RIGHT:
            camera_angle += 5.0;
            if (camera_angle >= 360.0)
                camera_angle -= 360.0;
            break;
        case GLUT_KEY_UP:
            camera_radius += 1.0;
            break;
        case GLUT_KEY_DOWN:
            camera_radius -= 1.0;
            if (camera_radius < 0.0)
                camera_radius = 0.0;
            break;
    }
    glutPostRedisplay();
}

void update(int value) {
    angle += 0.1;
    if (angle >= 360.0)
        angle -= 360.0;

    updateSunPosition();
    glutPostRedisplay();
    glutTimerFunc(2, update, 0);
}

void menu(int option) {
    switch (option) {
        case 1:
            isSpotlightOn = !isSpotlightOn;
            if (isSpotlightOn)
                glEnable(GL_LIGHT1);
            else
                glDisable(GL_LIGHT1);
            break;
        case 2:
            isSmoothShading = !isSmoothShading;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D House with Lighting");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(10, update, 0);

    glutCreateMenu(menu);
    glutAddMenuEntry("Toggle Spotlight", 1);
    glutAddMenuEntry("Toggle Shading", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
