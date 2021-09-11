#include<iostream>
using namespace std;
class hack
{
    private:
        int x;
        int y;
    public:
        hack(int a)
        {
            x=a;
            y=a*2;
        }
        int getx()
        {
            return x;
        }
        int gety()
        {
            return y;
        }
};
int main()
{
    hack n(10);
    cout<<n.getx()<<" "<<n.gety()<<endl;
    /*now you have to change value of the private members of class*/
    int *k=(int *)&n; //get address of x
    (*k)++;  //change the value of x
    k++;    //move to y
    (*k)+=7;  //change y
    cout<<n.getx()<<" "<<n.gety()<<endl;
}
