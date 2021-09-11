#include <iostream>
#include <string.h>
#include <ctime>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#define MAX 100
using namespace std;
COORD coord={0,0};
 void gotoxy(int x,int y)
 {
   coord.X=x;
 coord.Y=y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }
/*start of queue................................................*/
struct node {
    int info;
    node *next;
};

class Queue {
    private:
        node *front;
        node *rear;
    public:
        Queue();
        ~Queue();
        bool isEmpty();
        void enqueue(int);
        int dequeue();
        void display();

};

void Queue::display(){
    node *p = new node;
    p = front;
    if(front == NULL){
        cout<<"\nNothing to Display\n";
    }else{
        while(p!=NULL){
            cout<<endl<<p->info;
            p = p->next;
        }
    }
}

Queue::Queue() {
    front = NULL;
    rear = NULL;
}

Queue::~Queue() {
    delete front;
}

void Queue::enqueue(int data) {
    node *temp = new node();
    temp->info = data;
    temp->next = NULL;
    if(front == NULL){
        front = temp;
    }else{
        rear->next = temp;
    }
    rear = temp;
}

int Queue::dequeue() {
    node *temp = new node();
    int value;
    if(front == NULL){
        cout<<"\nQueue is Emtpty\n";
    }else{
        temp = front;
        value = temp->info;
        front = front->next;
        delete temp;
    }
    return value;
}

bool Queue::isEmpty() {
    return (front == NULL);
}
/*end of queue..................................................*/

/*function to find number of digit for desired outout in table*/
int digit(int n)
{
    int k=0;
    while(n)
    {
        n=n/10;
        k++;
    }
    return k;
}
/*function to display table.....................................*/
void DisplayTable(int vertex,char Hr[50][50],char Vr[50][50])
{
    int dig;
    cout<<endl;
   for(int i=1;i<=vertex;i++)
    {
        if(i==1)
            cout<<char(201);
        else
            cout<<char(204);
        for(int n=0;n<vertex;n++)
        {
            for(int m=0;m<8;m++)
            {
                if(Hr[i-1][n])
                    cout<<char(205);
                else
                    cout<<" ";
                    //cout<<char(196);
            }
            if(n==vertex-1)
            {
                if(i==1)
                    cout<<char(187);
                else
                    cout<<char(185);
            }
            else
            {
                if(i==1)
                    cout<<char(203);
                else
                    cout<<char(206);
            }
        }

        cout<<endl<<char(186)<<"  ";
        for(int k=1;k<=vertex;k++)
        {
            cout<<k+vertex*(i-1)<<"   ";
            dig=digit(k+vertex*(i-1));
            while(5-dig)
            {
                cout<<" ";
                dig++;
            }
            if(Vr[i-1][k-1])
                cout<<"\b\b"<<char(186)<<"  ";
            else
                cout<<" ";
                //cout<<"\b\b"<<char(179)<<"  ";
        }
        cout<<endl;
        if(i==vertex)
            cout<<char(200);

    }
    for(int n=0;n<vertex;n++)
    {
            for(int m=0;m<8;m++)
                    cout<<char(205);
            if(n==vertex-1)
            {
                cout<<char(188);
            }
            else
            {
                cout<<char(202);
            }
    }
}
/*end of function to display table.............................................................*/

class Graph {
    private:
        int n; ///vertices
        int **A; ///edges between two vertices
    public:
        Graph(int size = 2);
        ~Graph();
        bool isConnected(int, int);
        void addEdge(int u, int v);
        void BFS(int ,int);
};

Graph::Graph(int size) {
    int i, j;
    if (size < 2) n = 2;
    else n = size;
    A = new int*[n*n];
    for (i = 0; i < n*n; ++i)
        A[i] = new int[n*n];
    for (i = 0; i < n*n; ++i)
        for (j = 0; j < n*n; ++j)
            A[i][j] = 0;
}

Graph::~Graph() {
    for (int i = 0; i < n; ++i)
    delete [] A[i];
    delete [] A;
}

bool Graph::isConnected(int u, int v) {
    return (A[u-1][v-1] == 1);
}

void Graph::addEdge(int u, int v) {
    A[u-1][v-1] = A[v-1][u-1] = 1;
}
bool validE(int a,int b,int nv)
{
    int m=0,n=0;

        if(a<nv*nv)
            m=1;
        if(b<nv*nv)
            n=1;

    if(a==b)
        m=0;
    if(n&m)
        return true;
    else
        return false;
}
void Graph::BFS(int s,int bd=0)
{
    char ch,hr[50][50],vr[50][50],Key[]="yynnynnyyynyyyyynyyynnynnyynnynyynyyynyyynnyyyynnynyyyyyynny";
    int kkk=0,VERT[n*n],v,fdist;
    for(int i=0;i<50;i++)
        for(int k=0;k<50;k++)
    {
        hr[i][k]=vr[i][k]=1;
    }
    Queue Q;
    bool *visit    = new bool [n*n+1];
    bool *explored = new bool[n*n+1];
    int   dist[n*n+5];
    char  path[n*n+5][n*n*5],fpath[n*n*5];
    for (int i = 1; i <= n*n+1; ++i)
    {
        explored[i] = false;
        visit[i]    = false;
        dist[i]     = 0;
        strcpy(path[i],"");
    }
    Q.enqueue(s);
    explored[s] = true;
    sprintf(path[s],"1:");
    /*cout << s << " : " << endl;*/
    cout<<"Enter Edge Information.............\n";
    DisplayTable(n,hr,vr);
    strcpy(fpath,"");
    while (!Q.isEmpty())
    {
         v = Q.dequeue();
         visit[v]=true;
            if(v-n>0 && !isConnected(v,v-n) && (!explored[v-n] || !visit[v-n])) /*up ********************************************************/
            {
                cout<<"\n\n\nIs Node "<<v<<" connected to node "<<v-n<<" (Yes(y)/No(Other Key)) : ";
                cout<<"                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                if(bd)
                {
                    cout<<Key[kkk];
                    ch=Key[kkk++];
                }
                else
                    ch=getche();
                if(ch=='y'||ch=='Y')
                {
                   // Arr[v->info-vertex]=tmpnode;
                   // Q.enqueue(tmpnode);
                    hr[int(v/(n+0.1))][(v-1)%n]=0;
                    /*if(v->dist + 1 < tmpnode->dist || tmpnode->dist==0)
                    {
                    tmpnode->dist=v->dist+1;
                    tmpnode->path=new char [tmpnode->dist*5];
                    sprintf(tmpnode->path,"%s%d:",v->path,v->info-vertex);
                    }*/
                    if(dist[v] + 1 < dist[v-n] || dist[v-n]==0)
                    {
                        dist[v-n]=dist[v]+1;
                        sprintf(path[v-n],"%s%d:",path[v],v-n);
                    }
                    if(validE(v,v-n,n) && !explored[v-n])
                    {
                        addEdge(v,v-n);
                        Q.enqueue(v-n);
                        explored[v-n] = true;
                    }
                }
                /*else
                {
                    Arr[v->info]->up=tmp;
                }*/
                gotoxy(0,0);
                cout<<"Enter Edge Information.............\n";
                DisplayTable(n,hr,vr);
            }
            if((v-1)%n>0 && !isConnected(v,v-1) && (!explored[v-1] || !visit[v-1])) /*left ********************************************************/
            {
                cout<<"\n\n\nIs Node "<<v<<" connected to node "<<v-1<<" (Yes(y)/No(Other Key)) : ";
                cout<<"                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                if(bd)
                {
                    cout<<Key[kkk];
                    ch=Key[kkk++];
                }
                else
                    ch=getche();
                if(ch=='y'||ch=='Y')
                {
                   // Arr[v->info-vertex]=tmpnode;
                   // Q.enqueue(tmpnode);
                    vr[int(v/(n+0.1))][(v-2)%n]=0;
                    /*if(v->dist + 1 < tmpnode->dist || tmpnode->dist==0)
                    {
                    tmpnode->dist=v->dist+1;
                    tmpnode->path=new char [tmpnode->dist*5];
                    sprintf(tmpnode->path,"%s%d:",v->path,v->info-vertex);
                    }*/
                    if(dist[v] + 1 < dist[v-1] || dist[v-1]==0)
                    {
                        dist[v-1]=dist[v]+1;
                        sprintf(path[v-1],"%s%d:",path[v],v-1);
                    }
                    if(validE(v,v-1,n) && !explored[v-1])
                    {
                        addEdge(v,v-1);
                        Q.enqueue(v-1);
                        explored[v-1] = true;
                    }
                }
                gotoxy(0,0);
                cout<<"Enter Edge Information.............\n";
                DisplayTable(n,hr,vr);
            }
            if((v+1)%n!=1 && !isConnected(v,v+1) && (!explored[v+1] || !visit[v+1] ))      /*right*********************************************************/
            {
                cout<<"\n\n\nIs Node "<<v<<" connected to node "<<v+1<<" (Yes(y)/No(Other Key)) : ";
                cout<<"                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                if(bd)
                {
                    cout<<Key[kkk];
                    ch=Key[kkk++];
                }
                else
                    ch=getche();
                if(ch=='y'||ch=='Y')
                {
                   // Arr[v->info-vertex]=tmpnode;
                   // Q.enqueue(tmpnode);
                    vr[int(v/(n+0.1))][(v-1)%n]=0;
                    /*if(v->dist + 1 < tmpnode->dist || tmpnode->dist==0)
                    {
                    tmpnode->dist=v->dist+1;
                    tmpnode->path=new char [tmpnode->dist*5];
                    sprintf(tmpnode->path,"%s%d:",v->path,v->info-vertex);
                    }*/
                    if(dist[v] + 1 < dist[v+1] || dist[v+1]==0)
                    {
                        dist[v+1]=dist[v]+1;
                        sprintf(path[v+1],"%s%d:",path[v],v+1);
                    }
                    if(validE(v,v+1,n) && !explored[v+1])
                    {
                        addEdge(v,v+1);
                        Q.enqueue(v+1);
                        explored[v+1] = true;
                    }
                }
                gotoxy(0,0);
                cout<<"Enter Edge Information.............\n";
                DisplayTable(n,hr,vr);
            }
            if((v+n)<=n*n && !isConnected(v,v+n) && (!explored[v+n] || !visit[v+n]))  /*down*************************************************/
            {
                cout<<"\n\n\nIs Node "<<v<<" connected to node "<<v+n<<" (Yes(y)/No(Other Key)) : ";
                cout<<"                    \b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b";
                if(bd)
                {
                    cout<<Key[kkk];
                    ch=Key[kkk++];
                }
                else
                    ch=getche();
                if(ch=='y'||ch=='Y')
                {
                   // Arr[v->info-vertex]=tmpnode;
                   // Q.enqueue(tmpnode);
                    hr[int((v+n)/(n+0.1))][(v-1)%n]=0;
                    /*if(v->dist + 1 < tmpnode->dist || tmpnode->dist==0)
                    {
                    tmpnode->dist=v->dist+1;
                    tmpnode->path=new char [tmpnode->dist*5];
                    sprintf(tmpnode->path,"%s%d:",v->path,v->info-vertex);
                    }*/
                    if(dist[v] + 1 < dist[v+n] || dist[v+n]==0)
                    {
                        dist[v+n]=dist[v]+1;
                        sprintf(path[v+n],"%s%d:",path[v],v+n);
                    }
                    if(validE(v,v+n,n) && !explored[v+n])
                    {
                        addEdge(v,v+n);
                        Q.enqueue(v+n);
                        explored[v+n] = true;
                    }

                }
                gotoxy(0,0);
                cout<<"Enter Edge Information.............\n";
                DisplayTable(n,hr,vr);
            }
            /*if (isConnected(v, w) && !explored[w])
            {
                Q.enqueue(w);
                explored[w] = true;
            }*/
            if(v+n==n*n )
            {
                fdist=dist[v+n];
                sprintf(fpath,"%s",path[v+n]);
            }
            else if(v+1==n*n)
            {
                fdist=dist[v+1];
                sprintf(fpath,"%s",path[v+1]);
            }

        }//end of while loop

        if(dist!=0)
        {
            cout <<"\n\n\nShortest Distance is "<<fdist<<" Unit.                                                                       \n And Shortest path is ";
            for(int i=0;i<strlen(fpath)-1;i++)
            {
                if(fpath[i]==':')
                    cout<<" -> ";
                else
                    cout<<fpath[i];
            }
        }
        else
            cout<<"\n\n\n          Sorry There is no path found......................!";
    delete [] explored;
}

void wrt(char name[])
{
    for(long int i=0;i<strlen(name);i++)
    {
        cout<<name[i];
        Sleep(1);
    }
}
int rd()
{
    int ch,m=0;
    do
    {
        ch=getch()-48;
       // cout<<getch();
        if(ch<=9 && ch>=0)
            {cout<<ch;m=m*10+ch;}
        else if(ch==-40 && m>0)
        {
            m=m/10;
            cout<<"\b \b";
        }
    }while((ch!=-35 && ch!=-16) || m==0);
    return m;
}

int main()
{
    int nv,a,b,VERT[MAX],ne,bd;
    char name[MAX+100],ch;
    do
    {
        system("cls");
            bd=0;
            cout<<"\nWant default Maze(Yes(y)/No(Other)) : ";
            ch=getche();
        if(ch=='y'||ch=='Y')
        {
            bd=1;
            nv=6;
        }
        else
        {
            wrt("\n\nENTER NUMBER OF VERTICES IN ROW: ");
            do{
                nv=rd();
                if(!(nv>1 && nv <MAX))
                {
                    while(nv)
                    {
                        cout<<"\b \b";
                        nv=nv/10;
                    }
                }
              }while(!(nv>1 && nv <MAX));
        }
    Graph g(nv);
    wrt("\n\n\n               MATRIX OF"); cout<<nv<<"x"<<nv; wrt(" VERTICES SUCCESSFULLY CREATED....... ");
    for(int i=0;i<nv*nv;i++)
    {
        VERT[i]=i;
      /*  if(!validV(VERT[i],i,VERT))
        {
            cout<<"\b\b\b\b    \b\b\b\b";
            i--;
            while(VERT[i]!=0)
            {
                cout<<"\b \b";
                VERT[i]=VERT[i]/10;
            }
        }*/
    }
   /* system("cls");

    wrt("\nENTER ");cout<<ne;wrt(" EDGES(E) : { ");
    for(int i=0;i<ne;i++)
    {
        cout<<"("; a=rd(); cout<<","; b=rd(); cout<<")";
        if(i!=ne-1)
            cout<<" , ";
        else cout<<" }";
        if(validE(a,b,nv,VERT))
            g.addEdge(a,b);
        else
        {
            cout<<"\b\b\b\b\b\b      \b\b\b\b\b\b";
            i--;
            while(a!=0)
            {
                cout<<"\b \b";
                a=a/10;
            }
            while(b!=0)
            {
                cout<<"\b \b";
                b=b/10;
            }
        }
    }*/
        system("cls");
        g.BFS(1,bd);
        cout<<"\n\n\n                    Want to Continue(y/n).....";
        ch=getch();
    }while(tolower(ch)=='y');
}
