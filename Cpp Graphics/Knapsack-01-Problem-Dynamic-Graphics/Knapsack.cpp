#include<iostream>
#include<conio.h>
#include<graphics.h>
#include<windows.h>
#include<vector>
#include<stdio.h>
#define MAX 200
using namespace std;
int inputg_int(int x,int y,char s[]="integer"){
    char ch;
    char name[MAX];
    int i=0;
    int sign=1;
    do{
        ch=getch();
        if(int(ch)==8){
                if(i>0)
            name[--i]='\0';
        else
            sign=1;
        }
        if(int(ch)>=48 && int(ch)<=57){
                name[i++]=ch;
                name[i]='\0';
                if(name[0]=='0')i--;
        }
        outtextxy(x,y,"                                                                                                   ");
        if(((ch=='-' && i==0) || sign==-1) && s!="whole"){
            outtextxy(x,y,"-");
            sign=-1;
        }
        outtextxy(x+20,y,name);
    }while(int(ch)!=13 && int(ch)!=32);
    if(s=="whole")
        sign=1;
    return atoi(name)*sign;
}

char * inputg_str(int x,int y){
    char ch;
    char name[MAX];
    int i=0;
    do{
        ch=getch();
        if(int(ch)==8){
                if(i>0)
            name[--i]='\0';
        }
        else if(int(ch)!=13){
                name[i++]=ch;
                name[i]='\0';
                if(name[0]=='0')i--;
        }
        outtextxy(x,y,"                                                                                             ");
        outtextxy(x,y,name);
    }while(int(ch)!=13);
    return name;
}
struct unit{
    int weight;
    int value;
};
int knapsack(int W,vector <struct unit> w,int n){
    char name[MAX];
    int i, j;
    int K[n+1][W+1];
    if(W<5){
        setcolor(RED);
        outtextxy(100,100,"TABLE");
        setcolor(YELLOW);
        for(i=0;i<n;i++){
            sprintf(name,"%d(%d)",w[i].weight,w[i].value);
            outtextxy(20,225+25*i,name);
        }
    }
    for (i = 0; i <= n; i++)
    {
       for (j = 0; j <= W; j++)
       {
           if (i==0 || j==0)
               K[i][j] = 0;
           else if (w[i-1].weight <= j)
                 K[i][j] = max(w[i-1].value + K[i-1][j-w[i-1].weight],  K[i-1][j]);
           else
                 K[i][j] = K[i-1][j];
           if(i!=0){
                sprintf(name,"%d",K[i][j]);
                setcolor(BLUE);
           }
           else{
                sprintf(name,"%d",j);
                setcolor(YELLOW);
           }

           if(W<5){
           delay(50);
           outtextxy(200+150*j,200+25*i,name);
           }
       }
    }
    return K[n][W];
}
void outlist(int x,int y,vector <struct unit> w){
    char name[MAX];
    for(int i=0;i<w.size();i++){
        setcolor(BLUE);
        sprintf(name,"%d",w[i].weight);
        outtextxy(x,y+25*i,name);
        setcolor(YELLOW);
        sprintf(name,"%d",w[i].value);
        outtextxy(x+120,y+25*i,name);
    }
}
int main(){
    vector <struct unit> w;
    int W,i;
    char name[MAX];
    initwindow(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN),"Huffman Code");
    PlaySound(TEXT("hurd.wav"),NULL,SND_ASYNC);
    settextstyle(1,0,10);
    while(!kbhit()){
        sprintf(name,"hc2 (%d).gif",(i++)%91+1);
        readimagefile(name,0,0,getmaxx(),getmaxy());
        setcolor(i%10+1);
        outtextxy(100,300,"KnapSack Code");
    }
    getch();
    settextstyle(1,0,3);
    cleardevice();
    readimagefile("back1.jpg",0,0,getmaxx(),getmaxy());
    setcolor(GREEN);
    outtextxy(100,100,"ENTER TOTAL WEIGHT : ");
    setcolor(RED);
    W=inputg_int(600,100);
    cleardevice();
    readimagefile("back1.jpg",0,-100,getmaxx(),200);
    readimagefile("sbt.jpg",getmaxx()-295,getmaxy()-95,getmaxx()-15,getmaxy()-35);
    while(true){
        setcolor(GREEN);
        outtextxy(300,200,"ENTER WEIGHT : ");
        outtextxy(300,300,"ENTER VALUE  : ");
        setcolor(RED);
        if(kbhit()){
                struct unit temp;
                temp.weight=inputg_int(800,200);
                temp.value=inputg_int(800,300);
                w.push_back(temp);
                outtextxy(600,200,"                                                                                                       ");
                outtextxy(600,300,"                                                                                                       ");
                setcolor(GREEN);
                outtextxy(10,100,"WHT  VAL");
                outlist(10,130,w);
        }
        POINT P;
        GetCursorPos(&P);
        if(P.x>getmaxx()-300 && P.y>getmaxy()-200){
            setcolor(BLUE);
            rectangle(getmaxx()-300,getmaxy()-100,getmaxx()-10,getmaxy()-30);
            if(GetAsyncKeyState(VK_LBUTTON)){
                break;
            }
        }
        else{
            setcolor(BLACK);
            rectangle(getmaxx()-300,getmaxy()-100,getmaxx()-10,getmaxy()-30);
        }
    }
    cleardevice();
    delay(150);
    int result=knapsack(W,w,w.size());
    if(W<5)
        getch();
    readimagefile("back.jpg",0,0,getmaxx(),getmaxy());
    sprintf(name,"%d",result);
    settextstyle(1,0,10);
    if(result){
        outtextxy(300,280,"RESULT");
        outtextxy(500,400,name);
    }
    else{
        setcolor(RED);
        outtextxy(10,400,"Invalid Inputs");
    }
    getch();
    closegraph();
}
