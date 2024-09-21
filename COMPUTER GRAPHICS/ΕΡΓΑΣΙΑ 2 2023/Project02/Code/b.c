#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define WIDTH 500
#define HEIGHT 500

GLfloat edge = 4.0; // αρχικό μήκος ακμής του κύβου
GLfloat scale = 1.0; 
GLfloat center[] = {0.0, 0.0, -80.0}; // κέντρο περιστροφής
GLfloat rotation_radius = 20.0; // ακτίνα περιστροφής
GLfloat axis[] = {1.0, 1.0, 1.0}; // άξονας περιστροφής
GLint angle = 0; // γωνία περιστροφής
GLuint squareList; // λίστα εμφάνισης για το τετράγωνο

// δηλώσεις συναρτήσεων
void init(void);
void display(void);
void reshape(int w, int h);
void update(int value);
void drawCube(void);
void drawSquare(GLfloat size);

int main(int argc, char** argv) {
    // αρχικοποίηση glut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Rotating Cube");

    // αρχικοποίηση OpenGL
    init();

    // δημιουργία της λίστας εμφάνισης για το τετράγωνο
    squareList = glGenLists(1);
    glNewList(squareList, GL_COMPILE);
    drawSquare(2.0);
    glEndList();

    // ρύθμιση των συναρτήσεων επανάκλησης
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(10, update, 0);

    // έναρξη του κύριου βρόχου
    glutMainLoop();
    return 0;
}

void init(void) {
    // ρύθμιση του χρώματος καθαρισμού σε λευκό
    glClearColor(1.0, 1.0, 1.0, 1.0);
    // ενεργοποίηση της δοκιμής βάθους
    glEnable(GL_DEPTH_TEST);
}
void display(void) {
    // καθαρισμός των buffers χρώματος και βάθους
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ρύθμιση του προβολικού πίνακα
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)WIDTH/(GLfloat)HEIGHT, 1.0, 1000.0);

    // ρύθμιση του πίνακα modelview
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // ρύθμιση της θέσης και του προσανατολισμού της κάμερας
    gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

    // μετάφραση στο κέντρο περιστροφής
    glTranslatef(center[0], center[1], center[2]);

    // περιστροφή γύρω από το κέντρο περιστροφής
    glRotatef(angle, axis[0], axis[1], axis[2]);

    // μετάφραση στην απόσταση ακτίνας περιστροφής
    glTranslatef(0.0, 0.0, -rotation_radius);

    // κλίμακα του κύβου
    glScalef(scale, scale, scale);

    // σχεδιάζει τον κύβο
    drawCube();

    // ανταλλαγή των buffers
    glutSwapBuffers();
}
void reshape(int w, int h) {
    // ρύθμιση της προβολής
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void update(int value) {
    static GLfloat scaleFactor = 1.0;
    static GLfloat scaleDir = 1.0;
    static GLint scaleSteps = 50;
    static GLint scaleCount = 0;

    // ενημέρωση της γωνίας
    angle = (angle + 1) % 360;

    // ενημέρωση της κλίμακας
    if (scaleCount == scaleSteps) {
        // αλλαγή της κατεύθυνσης κλίμακας
        scaleDir *= -1.0;
        scaleCount = 0;
    }
    scaleFactor += 0.01 * scaleDir;
    scaleCount++;

    // ρύθμιση του νέου παράγοντα κλίμακας
    scale = scaleFactor;

    // ξανασχεδιάζει τη σκηνή
    glutPostRedisplay();

    // ρύθμιση του χρονοδιακόπτη για την επόμενη ενημέρωση
    glutTimerFunc(10, update, 0);
}


void drawCube(void) {
    // ρύθμιση του χρώματος σε κόκκινο
    glColor3f(1.0, 0.0, 0.0);

    // σχεδιάζει την πρόσοψη
    glPushMatrix();
    glTranslatef(0.0, 0.0, edge/4.0);
    glCallList(squareList);
    glPopMatrix();

    // ρύθμιση του χρώματος σε πράσινο
    glColor3f(0.0, 1.0, 0.0);

    // σχεδιάζει την πίσω όψη
    glPushMatrix();
    glTranslatef(0.0, 0.0, -edge/4.0);
    glRotatef(180.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    // ρύθμιση του χρώματος σε μπλε
    glColor3f(0.0, 0.0, 1.0);

    // σχεδιάζει την επάνω όψη
    glPushMatrix();
    glTranslatef(0.0, edge/4.0, 0.0);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    glColor3f(1.0f, 0.5f, 0.0f);//Πορτοκαλί

    // σχεδιάζει την κάτω όψη
    glPushMatrix();
    glTranslatef(0.0, -edge/4.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 1.0f);//Μοβ

    // σχεδιάζει την αριστερή όψη
    glPushMatrix();
    glTranslatef(-edge/4.0, 0.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glCallList(squareList);
    glPopMatrix();

    glColor3f(0.5f, 1.0f, 1.0f);//Γαλάζιο

    // σχεδιάζει την δεξιά όψη
    glPushMatrix();
    glTranslatef(edge/4.0, 0.0, 0.0);
    glRotatef(-90.0, 0.0, 1.0, 0.0);
    glCallList(squareList);
    glPopMatrix();
}

void drawSquare(GLfloat size) {
    // σχεδιάζει ένα τετράγωνο με κέντρο την αρχή με το δεδομένο μέγεθος
    glBegin(GL_QUADS);
    glVertex3f(-size/2.0, -size/2.0, 0.0);
    glVertex3f(size/2.0, -size/2.0, 0.0);
    glVertex3f(size/2.0, size/2.0, 0.0);
    glVertex3f(-size/2.0, size/2.0, 0.0);
    glEnd();
}



