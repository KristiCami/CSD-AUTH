//Bιβλιοθήκες
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500

// Καθολικές μεταβλητές
GLfloat edge = 4.0; // αρχικό μήκος πλευράς του κύβου
GLfloat scale = 1.0; // αρχικός παράγοντας κλίμακας για τον κύβο
GLfloat center[] = {0.0, 0.0, -100.0}; // κέντρο περιστροφής
GLfloat axis[] = {1.0, 1.0, 1.0}; // άξονας περιστροφής
GLint angle = 0; // γωνία περιστροφής
GLuint squareList; // λίστα εμφάνισης για το τετράγωνο

// Πρωτότυπα συναρτήσεων
void init(void);
void display(void);
void reshape(int w, int h);
void update(int value);
void drawCube(void);
void drawSquare(GLfloat size);

int main(int argc, char** argv) {
    // Αρχικοποίηση glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Rotating Cube");

    // Αρχικοποίηση OpenGL
    init();

    // Δημιουργία λίστας εμφάνισης για το τετράγωνο
    squareList = glGenLists(1);
    glNewList(squareList, GL_COMPILE);
    drawSquare(2.0);
    glEndList();

    // Ορισμός των συναρτήσεων επανάκλησης
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, update, 0);

    // Έναρξη κύριου βρόχου
    glutMainLoop();
    return 0;
}

void init(void) {
    // Ορισμός του χρώματος καθαρισμού στο λευκό
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // Ενεργοποίηση δοκιμής βάθους
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    // Καθαρισμός των buffer χρώματος και βάθους
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Ορισμός του πίνακα προβολής
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspectRatio = (GLfloat)WIDTH/(GLfloat)HEIGHT;
    GLfloat orthoSize = 150.0f; // Προσαρμογή αυτής της τιμής για το μέγεθος της ορθογραφικής προβολής
    glOrtho(-orthoSize * aspectRatio, orthoSize * aspectRatio, -orthoSize, orthoSize, 1.0, 1000.0);

    // Ορισμός του πίνακα modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Ορισμός της θέσης και του προσανατολισμού της κάμερας
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    // Μετάφραση στο κέντρο περιστροφής
    glTranslatef(center[0], center[1], center[2]);

    // Περιστροφή γύρω από το κέντρο περιστροφής
    glRotatef(angle, axis[0], axis[1], axis[2]);

    // Κλίμακα του κύβου
    GLfloat modifiedScale = scale * 4.0; 
    glScalef(modifiedScale, modifiedScale, modifiedScale);

    // Σχεδίαση του κύβου
    drawCube();

    // Ανταλλαγή των buffer
    glutSwapBuffers();
}

void reshape(int w, int h) {
    // Ορισμός του viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void update(int value) {
    static GLfloat scaleFactor = 1.0;
    static GLfloat scaleDir = 1.0;
    static GLint scaleSteps = 50;
    static GLint scaleCount = 0;

    // Ενημέρωση της γωνίας
    angle = (angle + 1) % 360;

    // Ενημέρωση της κλίμακας
    if (scaleCount == scaleSteps) {
        // αλλαγή της κατεύθυνσης κλίμακας
        scaleDir *= -1.0;
        scaleCount = 0;
    }
    scaleFactor += 0.01 * scaleDir;
    scaleCount++;

    // Ορισμός του νέου παράγοντα κλίμακας
    scale = scaleFactor;

    // Ανακατασκευή της σκηνής
    glutPostRedisplay();

    // Ορισμός του χρονοδιακόπτη για την επόμενη ενημέρωση
    glutTimerFunc(10, update, 0);
}

void drawCube(void) {
    // Ορισμός του χρώματος σε κόκκινο
    glColor3f(1.0, 0.0, 0.0);

    // Σχεδίαση της πρόσοψης
    glPushMatrix();
    glTranslatef(0.0, 0.0, edge/4.0);
    glCallList(squareList);
    glPopMatrix();

    // Ορισμός του χρώματος σε πράσινο
    glColor3f(0.0, 1.0, 0.0);

    // Σχεδίαση της οπίσθιας πρόσοψης
    glPushMatrix();
    glTranslatef(0.0, 0.0, -edge/4.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    // Ορισμός του χρώματος σε μπλε
    glColor3f(0.0, 0.0, 1.0);

    // Σχεδίαση της επιφάνειας κορυφής
    glPushMatrix();
    glTranslatef(0.0, edge/4.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    // Ορισμός του χρώματος σε Πορτοκαλί
    glColor3f(1.0f, 0.5f, 0.0f); 

    // Σχεδίαση της κάτω επιφάνειας
    glPushMatrix();
    glTranslatef(0.0, -edge/4.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    // Ορισμός του χρώματος σε Μωβ
    glColor3f(1.0f, 0.0f, 1.0f); 

    // Σχεδίαση της αριστερής επιφάνειας
    glPushMatrix();
    glTranslatef(-edge/4.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    // Ορισμός του χρώματος σε Κυανό
    glColor3f(0.5f, 1.0f, 1.0f);

    // Σχεδίαση της δεξιάς επιφάνειας
    glPushMatrix();
    glTranslatef(edge/4.0, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    }

    void drawSquare(GLfloat size) {
    // Σχεδίαση ενός τετραγώνου με κέντρο το σημείο (0,0,0) και δοσμένο μέγεθος
    glBegin(GL_QUADS);
    glVertex3f(-size/2.0, -size/2.0, 0.0);
    glVertex3f(size/2.0, -size/2.0, 0.0);
    glVertex3f(size/2.0, size/2.0, 0.0);
    glVertex3f(-size/2.0, size/2.0, 0.0);
    glEnd();
    }

