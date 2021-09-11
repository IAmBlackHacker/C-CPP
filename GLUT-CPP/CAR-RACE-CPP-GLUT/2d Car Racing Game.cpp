#include<windows.h>
#include<GL/glut.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#define SPD 50
using namespace std;
int i,q;
long int score = 0;//for score counting
int screen = 0;
bool collide = false;//check if car collide to make game over
char buffer[10];
float dtime=SPD;
int vehicleX = 200, vehicleY = 70;
int ovehicleX[4], ovehicleY[4];
int divx = 250, divy = 4, movd;

class BmpLoader{
    private:
        BITMAPFILEHEADER bfh;
        BITMAPINFOHEADER bih;
    public:
        unsigned char *textureData;
        int iWidth,iHeight;
        BmpLoader(const char* filename){
             FILE *file=0;
             file=fopen(filename,"rb");
             if(!file){
                cout<<".bmp file not found !";
             }
             fread(&bfh,sizeof(BITMAPFILEHEADER),1,file);
             if(bfh.bfType != 0x4D42){
                cout<<"Not Valid Bitmap File";
             }
             fread(&bih,sizeof(BITMAPINFOHEADER),1,file);
             if(bih.biSizeImage==0){
                bih.biSizeImage=bih.biHeight*bih.biWidth*3;
             }
             textureData=new unsigned char[bih.biSizeImage];
             fseek(file,(long)bfh.bfOffBits,SEEK_SET);
             fread(textureData,1,bih.biSizeImage,file);
             for(int i=0;i<bih.biSizeImage;i+=3){
                swap(textureData[i],textureData[i+2]);
             }
             iWidth = bih.biWidth;
             iHeight= bih.biHeight;
             fclose(file);
        }
        ~BmpLoader(){
            delete textureData;
        }
};
BmpLoader mycar("mycar.bmp");
BmpLoader othercar("othercar.bmp");
GLuint tex1,tex2;

void LoadTexture(int c){
    if(c==1){
        glGenTextures(1, &tex1);
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, tex1);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3 ,mycar.iWidth,mycar.iHeight,GL_RGB,GL_UNSIGNED_BYTE,mycar.textureData);
    }
    else{
        glGenTextures(1, &tex2);
        glColor3f(1,1,1);
        glBindTexture(GL_TEXTURE_2D, tex2);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3 ,othercar.iWidth,othercar.iHeight,GL_RGB,GL_UNSIGNED_BYTE,othercar.textureData);
    }

}
void drawText(char ch[],int xpos, int ypos)//draw the text for score and game over
{
    int numofchar = strlen(ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <= numofchar - 1; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[i]);//font used here, may use other font also
    }
}


void drawTextNum(char ch[],int numtext,int xpos, int ypos)//counting the score
{
    int len;
    int k;
    k = 0;
    len = numtext - strlen (ch);
    glLoadIdentity ();
    glRasterPos2f( xpos , ypos);
    for (i = 0; i <=numtext - 1; i++)
    {
        if ( i < len )
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,'0');
        else
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ch[k]);
            k++;
        }
    }
}


void ovpos()
{
    glClearColor(0,1,0,0); //GREEN BACKGOURND
    for(i = 0; i < 4; i++)
    {
        if(rand() % 2 == 0)
        {
            ovehicleX[i] = 200;
        }
        else
        {
            ovehicleX[i] = 300;
        }
        ovehicleY[i] = 1000 - i * 160;
    }
}


void drawRoad() //Drawing Road
{
    glBegin(GL_QUADS);
        glColor3f(0.3,0.3,0.3); //Colour of Road
        //set dimention
        glVertex2f(250 - 100, 500);
        glVertex2f(250 - 100, 0);
        glVertex2f(250 + 100, 0);
        glVertex2f(250 + 100, 500);
    glEnd();
}


void drawDivider()//patch drawn in middle of road
{
    glLoadIdentity();
    glTranslatef(0, movd, 0);
    for(i = 1; i <= 10; i++)
    {
        glColor3f(0.9, 0.9, 0.9);
        glBegin(GL_QUADS);
            glVertex2f(divx  - 5, divy * 15 * i + 18);
            glVertex2f(divx  - 5, divy * 15 * i - 18);
            glVertex2f(divx  + 5, divy * 15 * i - 18);
            glVertex2f(divx  + 5, divy * 15 * i + 18);
        glEnd();
    }
    glLoadIdentity();
}
void drawVehicle()//car for racing (mycar)
{
    glPointSize(10.0);
    glBindTexture(GL_TEXTURE_2D, tex1);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(vehicleX - 25, vehicleY + 40);
    glTexCoord2i(0, 1); glVertex2i(vehicleX - 25, vehicleY - 40);
    glTexCoord2i(1, 1); glVertex2i(vehicleX + 25, vehicleY - 40);
    glTexCoord2i(1, 0); glVertex2i(vehicleX + 25, vehicleY + 40);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
  //  GLuint image = loadBMP_custom("./my_texture.bmp");
 }

void drawOVehicle()//other cars
{

    for(i = 0; i < 4; i++)
    {
    glPointSize(10.0);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0); glVertex2i(ovehicleX[i] - 25, ovehicleY[i] + 40);
    glTexCoord2i(0, 1); glVertex2i(ovehicleX[i] - 25, ovehicleY[i] - 40);
    glTexCoord2i(1, 1); glVertex2i(ovehicleX[i] + 25, ovehicleY[i] - 40);
    glTexCoord2i(1, 0); glVertex2i(ovehicleX[i] + 25, ovehicleY[i] + 40);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    ovehicleY[i] = ovehicleY[i] - 8;

    if(ovehicleY[i] > vehicleY - 25 - 25 && ovehicleY[i] < vehicleY + 25 + 25 && ovehicleX[i] == vehicleX) //COLLIDE CONDITION
    {
        PlaySound("cbreak.wav", NULL, SND_ASYNC|SND_FILENAME);
        collide = true;
    }

    if(ovehicleY[i] < -25) // CAR REST CONDITION
    {
        if(rand() % 2 == 0)
        {
            ovehicleX[i] = 200;
        }
        else
        {
            ovehicleX[i] = 300;
        }
        ovehicleY[i] = 600;
    }
    }
}

void Specialkey(int key, int x, int y)//allow to use navigation key for movement of car
{
    switch(key)
    {
        case GLUT_KEY_UP:
             for(i = 0; i <4; i++)
             {
              ovehicleY[i] = ovehicleY[i] - 10;
             }
             movd = movd - 20;
             break;
        case GLUT_KEY_DOWN:
             for(i = 0; i <4; i++)
             {
              ovehicleY[i] = ovehicleY[i] + 10;
             }
             movd = movd + 20;
             break;
        case GLUT_KEY_LEFT:
             vehicleX = 200;
        //    vehicleX-=10;
                     break;
        case GLUT_KEY_RIGHT:
             vehicleX = 300;
            //vehicleX+=10;
                     break;

    }
    glutPostRedisplay();
}

void Normalkey(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 13: //ENTER KEY
            if(screen==0 || screen==2){
                screen=1;
            }
            else if(screen==1){
                score=0;
                dtime=SPD;
                PlaySound("cstart.wav", NULL, SND_ASYNC|SND_FILENAME);
                screen=3;
            }
            else if(screen==3 && collide){
                collide=false;
                ovpos();
                screen=1;
            }
            break;
        case 32: //SPACE
            if(screen==1){
                screen=2;
            }
            else if(screen==3){
                glColor3f(0.5,0.2,0.2);
                drawText("GAME PAUSED", 360,305);
                PlaySound("none.wav",NULL, SND_ASYNC|SND_FILENAME);
                //mciSendString("pause MY_SND",NULL,0,NULL);
                glutSwapBuffers();
                screen=4;
            }
            else if(screen==4){
                PlaySound("cspeed.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
                screen=3;
            }
            break;
        case 27: //ESC KEY
            exit(0);
    }
}


void init()
{
    /*glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void display()
{
    if(screen == 0)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);//up body
        glColor3f(1,0.1,0);
        glVertex2f(800, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 600);
        glVertex2f(800, 600);
        glEnd();
        glColor3f(1,1,1);
        drawText("WELCOME", 170, 290);
        drawText("DRIVE A CAR", 170, 250);
        drawText("Press Enter To Continue ...", 170, 150);
        glutSwapBuffers();
    }
    else if(screen == 1)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);//up body
        glColor3f(1,0.1,0);
        glVertex2f(800, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 600);
        glVertex2f(800, 600);
        glEnd();
        glColor3f(1,1,1);
        drawText("CONTROLS", 170, 360);
        drawText("UP      = Accelerate", 170, 320);
        drawText("LEFT    = Move Left", 170, 280);
        drawText("RIGHT   = Move Right", 170, 240);
        drawText("ESC     = QUIT", 170, 200);
        drawText("Press Space to see About", 170, 150);
        drawText("Press Enter To Continue ...", 170, 120);
        glutSwapBuffers();
    }
    else if(screen == 2){
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_QUADS);//up body
        glColor3f(1,0.1,0);
        glVertex2f(800, 0);
        glVertex2f(0, 0);
        glVertex2f(0, 600);
        glVertex2f(800, 600);
        glEnd();
        glColor3f(1,1,1);
        drawText("ABOUT", 170, 360);
        drawText("LOKESH BHOYAR CSE15 15075028", 170, 320);
        drawText("YADUL RAGHAV CSE15 15074015", 170, 280);
        drawText("LALIT MANDLOI CSE15 15075026", 170, 240);
        drawText("RAGHWENDRA MEENA CSE15 15075039", 170, 200);
        drawText("Enter to continue ...", 170, 160);
        glutSwapBuffers();
    }
    else if(screen==3)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        if(!collide){
            drawRoad();
            drawDivider();
            drawVehicle();
            drawOVehicle();
            movd = movd - 16;
            if(movd < - 60)
            {
                movd = 0;
            }
            score = score + 1;
            if(score==15){
                PlaySound("cspeed.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
            }
            glColor3f(1,0,0);
            drawText("Score:", 360,455);
            sprintf(buffer,"%d",score);
            glColor3f(0,0,1);
            drawTextNum(buffer, 6, 420,455);
            glColor3f(1,0,0);
            drawText("Speed:", 360,415);
            sprintf(buffer,"%d km/hr ",int(300-dtime*5));
            glColor3f(0,0,1);
            drawTextNum(buffer, 12, 420,415);
            glColor3f(1,0,0);
            drawText("Press Space for", 360,375);
            drawText("            PLAY/PAUSE", 360,355);

            glutSwapBuffers();
            if(score%100==0){
                dtime-=1; //this will increase speed of car
                if(dtime<0){
                    dtime=0;
                }
            }
            Sleep(dtime);
        }
        else
        {
            glColor3f(1,0,0);
            drawText("Game Over", 200,350);
            glColor3f(0,0,0);
            drawText("Final Score:", 200,310);
            sprintf(buffer,"%d",score);
            drawTextNum(buffer, 6, 260,310);
            drawText("Press Enter to Main Menu ...", 200,270);
            glutSwapBuffers();
        }
    }
    else{
    }
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowPosition(10,50);
    glutInitWindowSize(800,600);
    glutCreateWindow("SUPER FAST DRIVING");
    ovpos();
    LoadTexture(1);
    LoadTexture(2);
    init();
    glutDisplayFunc(display);
	glutSpecialFunc(Specialkey);
    glutKeyboardFunc(Normalkey);
    glutIdleFunc(display);
    glutMainLoop();
}
