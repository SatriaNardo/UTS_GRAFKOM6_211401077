#include<GL/glut.h>
#include<cmath>

float carPositionX = 0.0f; // Posisi x mobil lingkaran
float carPositionY = -150.0f; // Posisi y mobil lingkaran
float radius = 64.0f; //radius mobil
float sunPositionX = 0.0f; // Posisi awal matahari
float colorG = 0.0f; //Buat gradiasi langit
float colorB = 0.2f;
float car2ndPositionX = -250.0f; //posisi x mobil
float car2ndPositionY = -60.0f;  //posisi y mobil

void drawCloud(float cloudX, float cloudY) {
    glColor3f(1.0, 1.0, 1.0); // Warna putih untuk awan
    int numSegments = 100;

    // Menggambar awan dengan beberapa lingkaran
    for (int i = 0; i < 3; i++) {
        glBegin(GL_POLYGON);
        for (int j = 0; j < numSegments; j++) {
            float theta = 2.0f * 3.1415926f * float(j) / float(numSegments);
            float x = cloudX + 20.0f * cosf(theta) + i * 20.0f;
            float y = cloudY + 10.0f * sinf(theta);
            glVertex2f(x, y);
        }
        glEnd();
    }
}
void drawCar(float carX, float carY) {
    // Menggambar bodi mobil
    glColor3f(1.0, 0.0, 0.0); // Warna merah
    glBegin(GL_QUADS);
    glVertex2f(carX - 35.0f, carY - 15.0f);
    glVertex2f(carX + 35.0f, carY - 15.0f);
    glVertex2f(carX + 25.0f, carY + 5.0f);
    glVertex2f(carX - 25.0f, carY + 5.0f);
    glEnd();

    // Menggambar roda depan mobil
    glColor3f(0.0, 0.0, 0.0); // Warna hitam
    glBegin(GL_POLYGON);
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = carX - 25.0f + 10.0f * cosf(theta);
        float y = carY - 20.0f + 10.0f * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Menggambar roda belakang mobil
    glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = carX + 25.0f + 10.0f * cosf(theta);
        float y = carY - 20.0f + 10.0f * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
}
void tampil() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_QUADS);
    // Menggambar Langit
    for (int i = 0; i <= 320; ++i) {
        glColor3f(0, 1 - i / 320.0 + colorG, 1.2 - i / 320.0 + colorB);
        glVertex2f(-320 + i * 2, 320);
        glVertex2f(320 + (i + 1) * 2, -320);
        glVertex2f(320 + (i + 1) * 2, -240);
        glVertex2f(-320 + i * 2, -240);
    }
    glEnd();
    glBegin(GL_QUADS);
    // Menggambar tanah
    for (int i = 0; i <= 320; ++i) {
        glColor3f(0.1, 0.2 + i / 2.0, i / 800.0);
        glVertex2f(-320 + i * 2, 0);
        glVertex2f(320 + (i + 1) * 2, 0);
        glVertex2f(320 + (i + 1) * 2, -240);
        glVertex2f(-320 + i * 2, -240);
    }
    glEnd();

    // Warna gunung (misalnya warna coklat)
    glColor3f(0.6, 0.4, 0.2);

    // Menggambar gunung kiri
    glBegin(GL_TRIANGLES);
    glVertex2f(-320, 0);  // Titik bawah kiri gunung kiri
    glVertex2f(-160, 90);  // Titik puncak gunung kiri
    glVertex2f(0, 0);  // Titik bawah kanan gunung kiri
    glEnd();

    // Menggambar gunung kanan
    glBegin(GL_TRIANGLES);
    glVertex2f(320, 0);  // Titik bawah kiri gunung kanan
    glVertex2f(160, 90);  // Titik puncak gunung kanan
    glVertex2f(0, 0);  // Titik bawah kanan gunung kanan
    glEnd();

    //buat jalan
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-150, -240);  // Titik bawah kiri
    glVertex2f(150, -240);  // Titik bawah kanan
    glVertex2f(40, 0);     // Titik atas kanan
    glVertex2f(-40, 0);    // Titik atas kiri
    glEnd();
    //buat jalan horizontal
    glBegin(GL_QUADS);
    glColor3f(0.5, 0.5, 0.5);
    glVertex2f(-320, -50);  // Titik bawah kiri
    glVertex2f(320, -50);  // Titik bawah kanan
    glVertex2f(320, -100);     // Titik atas kanan
    glVertex2f(-320, -100);    // Titik atas kiri
    glEnd();
    //Gambar Mobil dr sisi samping
    drawCar(car2ndPositionX, car2ndPositionY);
    // Menggambar tampilan mobil dengan menggunakan lingkaran
    glColor3f(1, 0, 0.5);
    glBegin(GL_POLYGON);
    int numSegments = 100;
    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(numSegments);
        float x = carPositionX + radius * cosf(theta);
        float y = carPositionY + radius * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();


    glColor3f(1.0, 1.0, 0.0); // Warna kuning
    glBegin(GL_POLYGON);
    int sunSegments = 100; // Jumlah segmen matahari
    
    for (int i = 0; i <= sunSegments; i++) {
        float angle = 2.0f * 3.1415926f * float(i) / float(sunSegments);
        float p = sunPositionX + 20.0f * cosf(angle);
        float q = 200 + 20.0f * sinf(angle);
        glVertex2f(p , q);
    }
    glEnd();
    drawCloud(-150, 180);
    drawCloud(200, 180);
    drawCloud(-220, 120);
    drawCloud(120, 210);
    drawCloud(-230, 210);
    drawCloud(220, 110);
    drawCloud(0, 150);
    glEnd();
    
    glFlush();

}



void keyboardFunc(unsigned char key, int x, int y) {
    switch (key) {
    case 'A':
    case 'a':
        if (carPositionX != -40.0f)
        {
            carPositionX -= 10.0f; // Geser mobil ke kiri
        } break;
    case 'D':
    case 'd':
        if (carPositionX != 40.0f)
        {
            carPositionX += 10.0f; // Geser mobil ke kanan
        } break;
    case 'W':
    case 'w':
        if (radius != 0.0f)
        {
            carPositionY += 10.0f; // geser mobil kedepan
            radius -= 4.0f;
        } break;
    case 'S':
    case 's':
        if (carPositionY != -240.0f)
        {
            carPositionY -= 10.0f; // geser mobil kebelakang
            radius += 4.0f;
        } break;
    }

    glutPostRedisplay(); // Meminta tampilan untuk diperbarui
}
void specialKey(int key,  int x, int y) { 
    switch (key) {
    case GLUT_KEY_LEFT:
        car2ndPositionX -= 10.0f; // Geser mobil ke kiri
        break;
    case GLUT_KEY_RIGHT:
        car2ndPositionX += 10.0f; // Geser mobil ke kanan 
        break;
    case GLUT_KEY_UP:
        if (car2ndPositionY < -40)
        {
            car2ndPositionY += 5.0f; // geser mobil kedepan
        } break;
    case GLUT_KEY_DOWN:
        if (car2ndPositionY > -60.0f)
        {
            car2ndPositionY -= 5.0f; // geser mobil kebelakang
        } break;
    }
    glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y) {
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Klik kiri, geser matahari ke kanan
        sunPositionX += 10.0f;
        colorG += 0.03125;
        colorB += 0.03125;
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Klik kanan, geser matahari ke kiri
        sunPositionX -= 10.0f;
        colorG -= 0.03125;
        colorB -= 0.03125;
    }

    glutPostRedisplay(); // Meminta tampilan untuk diperbarui
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Primitive Drawing");
    glClearColor(0.49, 0.8, 0.89, 1.0);
    gluOrtho2D(-320, 320, -240, 240);
    glutDisplayFunc(tampil);
    glutKeyboardFunc(keyboardFunc); // Menambahkan fungsi keyboard
    glutSpecialFunc(specialKey);
    glutMouseFunc(mouseFunc); // Menambahkan fungsi mouse
    glutMainLoop();
    return 0;
}
