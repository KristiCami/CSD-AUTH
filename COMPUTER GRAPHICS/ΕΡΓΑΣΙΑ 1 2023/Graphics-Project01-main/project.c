#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int mouseX, mouseY; // μεταβλητές για την αποθήκευση της τρέχουσας θέσης του ποντικιού
int popupMenu; // μεταβλητή για την αποθήκευση του αναγνωριστικού του αναδυόμενου μενού
int numIterations = 15000; // Δηλώσει numIterations ως καθολική μεταβλητή και αρχικοποιήστε το σε 15000
int colorMode=0; // μεταβλητή για την αποθήκευση της τρέχουσας λειτουργίας χρώματος (0 = μονόχρωμο, 1 = τυχαίο χρώμα)
int numVertices=5; // μεταβλητή για την αποθήκευση του αριθμού των κορυφών του πολυγώνου (5 ή 6)

// λειτουργία χειρισμού συμβάντων του ποντικιού
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseX = x;
        mouseY = y;
    }
}

// λειτουργία χειρισμού του αναδυόμενου μενού
void menu(int value) {
    switch(value) {
        case 0:
            exit(0); // Κλείστε το πρόγραμμα
            break;
        case 1:
            numIterations = 8000; // Αλλάξτε τον αριθμό των επαναλήψεων σε 8000
            glutPostRedisplay(); // Επισημάνετε το τρέχον παράθυρο ότι πρέπει να επανεμφανιστεί
            break;
        case 2:
            colorMode = 1 - colorMode; // Εναλλαγή λειτουργίας χρώματος
            glutPostRedisplay(); //Επισημάνετε το τρέχον παράθυρο ότι πρέπει να επανεμφανιστεί
            break;
        case 3:
            // Αλλάξτε τον αριθμό των κορυφών σε 6
            numVertices = 6;
            glutPostRedisplay(); // Επισημάνετε το τρέχον παράθυρο ότι πρέπει να επανεμφανιστεί
            break;
        case 4:
            // Αλλάξτε τον αριθμό των κορυφών σε 5
            numVertices = 5;
            glutPostRedisplay(); // Επισημάνετε το τρέχον παράθυρο ότι πρέπει να επανεμφανιστεί
            break;
    }
}

// λειτουργία χειρισμού συμβάντων κίνησης του ποντικιού
void motion(int x, int y) {
    int dx = x - mouseX; //υπολογισμος τησ νεας θεσεις απο την προηγουμενη
    int dy = y - mouseY;

    glMatrixMode(GL_MODELVIEW);
    glTranslatef(dx, -dy, 0); // μεταφράστε τη σκηνή με τη διαφορά στη θέση του ποντικιού

    mouseX = x;
    mouseY = y;

    glutPostRedisplay(); // Επισημάνετε το τρέχον παράθυρο ότι πρέπει να επανεμφανιστεί
}

void myinit(void)
{
    /* Ενεργοποίηση ανάμειξης και ορισμός λευκού χρώματος φόντου */
    glEnable(GL_BLEND);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    
    /* Ορίστε το χρώμα του σχεδίου σε μαύρο */
    glColor3f(0.0, 0.0, 0.0);

    /* Enable smooth shading */
    glShadeModel(GL_SMOOTH);

    /* Ενεργοποιήστε την ομαλή σκίαση */
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /* Ρύθμιση προβολής */
    /* 500 x 500 παράθυρο με προέλευση κάτω αριστερά */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0); // στήνει μια ορθογραφική προβολή
    glMatrixMode(GL_MODELVIEW);    
}

void display(void)
{
    /* Καθορίστε έναν τύπο δεδομένων σημείου*/
    typedef GLfloat point2[2];
    
    /* Ορίστε τις κορυφές του πενταγώνου και του εξαγώνου */
    point2 vertices5[5] = {
        {250.0, 450.0},
        {72.0, 292.0},
        {178.0, 88.0},
        {322.0, 88.0},
        {428.0, 292.0}
    };

    point2 vertices6[6] = {
        {250.0, 450.0},
        {108.0, 382.0},
        {108.0, 118.0},
        {250.0, 50.0},
        {392.0, 118.0},
        {392.0, 382.0}
    };

    point2 *vertices = NULL;
    
    /* Επιλέξτε τις κορυφές που θα χρησιμοποιήσετε με βάση τον τρέχοντα αριθμό κορυφών */
    if (numVertices == 5) {
        vertices = vertices5;
    } else if (numVertices == 6) {
        vertices = vertices6;
    }
    
    int i, j, k;
    point2 p = {250.0, 250.0}; /* Ένα αυθαίρετο αρχικό σημείο */
    
    /* Καθαρίστε το παράθυρο*/
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* Υπολογίστε και σχεδιάστε αριθμητικά νέα σημεία */
    for (k = 0; k < numIterations; k++) {
        j = rand() % numVertices; /*Επιλέξτε μια κορυφή τυχαία*/

        /* Υπολογίστε το σημείο το ένα τρίτο της διαδρομής προς την κορυφή */
        GLfloat r = 1.0 / 3.0;

        /* Υπολογίστε το νέο σημείο παρεμβάλλοντας μεταξύ του τρέχοντος σημείου και της επιλεγμένης κορυφής */
        p[0] = r * p[0] + (1 - r) * vertices[j][0]; 
        p[1] = r * p[1] + (1 - r) * vertices[j][1];
        
        /* Plot new point */
        glBegin(GL_POINTS);
            if (colorMode == 1) { // Εάν είναι ενεργοποιημένη η λειτουργία τυχαίου χρώματος, ορίστε το χρώμα σε μια τυχαία τιμή
                glColor3f((GLfloat) rand() / RAND_MAX, (GLfloat) rand() / RAND_MAX, (GLfloat) rand() / RAND_MAX);
            }
            glVertex2fv(p); // Σχεδιάστε το νέο σημείο χρησιμοποιώντας το τρέχον χρώμα
        glEnd();
    }
    
    /* Αποστολή όλων των αποτελεσμάτων στην εμφάνιση*/
    glFlush();

    glutSwapBuffers(); //Προσθέστε αυτήν τη γραμμή για να ενεργοποιήσετε τη διπλή προσωρινή αποθήκευση
}

int main(int argc, char** argv)
{
    srand(time(NULL)); // Δημιουργήστε τη γεννήτρια τυχαίων αριθμών

    /* Εκκινήστε τη βιβλιοθήκη GLUT */
    glutInit(&argc, argv);

    /* Ρυθμίστε το παράθυρο */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Project01");

    /* Καταχωρίστε τις λειτουργίες επανάκλησης */
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);

    /* Δημιουργήστε το αναδυόμενο μενού */
    popupMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Toggle random coloring", 2);
    glutAddMenuEntry("Change points to 8000", 1);
    glutAddMenuEntry("Change number of vertices to 6", 3); // new option
    glutAddMenuEntry("Change number of vertices to 5", 4); // new option
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    /* Εκκινήστε το OpenGL */
    myinit();

    /* Εισαγάγετε τον κύριο βρόχο συμβάντος
     */
    glutMainLoop();

    return 0;
}
