    //DDA Algorithm for Line calculation
#include<lokesh.h>
#define round(x) ((int)(x+0.5))
using namespace std;
void header(char name[],int x=550){
    line(10,10,getmaxx()-10,10);
    line(14,14,getmaxx()-14,14);
    line(14,80,getmaxx()-14,80);
    line(10,84,getmaxx()-10,84);
    line(10,10,10,84);
    line(getmaxx()-10,10,getmaxx()-10,84);
    line(14,14,14,80);
    line(getmaxx()-14,14,getmaxx()-14,80);
    outtextxy(x,40,name);
}
double graph_point(double g1,double g2,double point,double max_point,char axis='x'){ /* if axis 'x' then g1(min x) and g2(max x) point is x ans max_point is max of x similary for axis='y'*/
    if(max_point<=g2-g1){
        point+=g1;
    }
    else{
        point=point*(g2-g1)/(max_point)+g1;
    }
    if(axis=='x'){
        return point;
    }
    return g1+g2-point;
}
int main(){
    initwindow(1530,760,"DDA Algorithm for Line view");
    char temp[MAX];

    /*for(int i=0;true;i++){
        settextstyle(i,0,4);
        outtextxy(100,100*(i%4)+100,"RAM RAM");
        getch();
    }*/
    settextstyle(4,0,2);
    header("DDA Algorithm for Line view");
    // Actual code
    outtextxy(480,150,"------------- Enter First Point -------------");
    outtextxy(600,180,"X : ");
    outtextxy(600,210,"Y : ");
    outtextxy(460,260,"------------- Enter Second Point -------------");
    outtextxy(600,290,"X : ");
    outtextxy(600,320,"Y : ");
    int x1=inputg_int(650,180);
    int y1=inputg_int(650,210);
    int x2=inputg_int(650,290,"whole");
    int y2=inputg_int(650,320,"whole");

    cleardevice();
    //print information
    header("DDA Algorithm for Line view");
    sprintf(temp,"Point1 : (%d,%d)  Point2 : (%d,%d)",x1,y1,x2,y2);
    outtextxy(380,120,temp);
    if(x1-x2!=0)
    sprintf(temp,"Slope of line : %f",(float)(y2-y1)/(float)(x2-x1));
    else
    sprintf(temp,"Slope of line : infinite");
    outtextxy(380,160,temp);
    //make axis
    setfillstyle(10,1);
    bar(100,200,1400,700);
    outtextxy(40,420,"Y");
    outtextxy(750,720,"X");
    outtextxy(90,700,"0");
    int maxx=max(max(x1,x2),1300),maxy=max(max(y1,y2),500);
    sprintf(temp,"%d",maxx);
    outtextxy(1360,720,temp);
    sprintf(temp,"%d",maxy);
    settextstyle(4,1,2);
    outtextxy(70,250,temp);
    settextstyle(4,0,2);
    line(100,200,100,700);
    line(100,700,1400,700);

    //recalculate x1,y1,x2,y2 in ratio of maxx,maxy

    x1=graph_point(100,1400,x1,maxx,'x');
    x2=graph_point(100,1400,x2,maxx,'x');
    y1=graph_point(200,700,y1,maxy,'y');
    y2=graph_point(200,700,y2,maxy,'y');
    setcolor(YELLOW);
    circle(x1,y1,5);
    circle(x2,y2,5);
    setcolor(RED);
    line(100,y1,x1,y1);
    line(100,y2,x2,y2);
    line(x1,y1,x1,700);
    line(x2,y2,x2,700);

    //algorithm
    double dx=x2-x1,dy=y2-y1,steps,x=x1,y=y1;
    if(abs(dx)>abs(dy)){
        steps=abs(dx);
    }
    else{
        steps=abs(dy);
    }
    dx/=steps;
    dy/=steps;
    for(int i=0;i<steps;i++){
        x=x+dx;
        y=y+dy;
        putpixel(round(x),round(y),WHITE);
    }
    //End of Actual code
    getch();
    closegraph();
}


