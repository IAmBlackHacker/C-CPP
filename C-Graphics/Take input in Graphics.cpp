#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#define MAX 200
using namespace std;
int inputg_int(int x,int y,char s[]="integer"){
    // for whole number pass argument s as "whole"
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
        outtextxy(x,y,"                                                                        ");
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
int main(){
    initwindow(1000,500,"");
    settextstyle(6,0,2);
    int m;
    char name[MAX],name2[MAX*2];
    setcolor(GREEN);
    outtextxy(10,100,"ENTER NUMBER : ");
    setcolor(RED);
    m=inputg_int(300,100);
    setcolor(GREEN);
    outtextxy(10,150,"ENTER STRING : ");
    setcolor(RED);
    strcpy(name,inputg_str(300,150));
    sprintf(name2,"You Enter int = %d ,str = %s",m,name);
    outtextxy(100,200,name2);
    getch();
    closegraph();
}
