#include<iostream>
#include<pthread.h>
#include<windows.h>
#include<stdlib.h>
using namespace std;
pthread_mutex_t write_mutex,read_mutex;
int readers=0;
void write(){
    int i=rand()%1000;
    cout<<"\n     Writer is Writing wait ...("<<i<<" ms)\n";
    Sleep(i);
}
void read(){
    int i=rand()%1000;
    if(readers>1)
    cout<<"\n     "<<readers<<" Readers are reading wait ...("<<i<<" ms)\n";
    else
    cout<<"\n     "<<readers<<" Reader is reading wait ...("<<i<<" ms)\n";
    Sleep(i);
}
void *Writer(void *ptr){
    while(true){
        cout<<"\nWriter trying to access writing ...\n";
        pthread_mutex_lock(&write_mutex);
        write();
        cout<<"\nWriting complete\n";
        pthread_mutex_unlock(&write_mutex);
    }
}
void *Reader(void *ptr){
    while(true){
        pthread_mutex_lock(&read_mutex);
        readers++;
        if(readers==1){
            pthread_mutex_lock(&write_mutex);
        }
        pthread_mutex_unlock(&read_mutex);
        read();
        pthread_mutex_lock(&read_mutex);
        readers--;
        if(readers==0){
            pthread_mutex_unlock(&write_mutex);
        }
        pthread_mutex_unlock(&read_mutex);
    }
}
int main(){
    int nr,nw;
    cout<<"Enter Number of readers[int] : ";
    cin>>nr;
    cout<<"Enter Number of writer[int] : ";
    cin>>nw;

    pthread_t r[nr],w[nw];

    pthread_mutex_init(&write_mutex,NULL);
    pthread_mutex_init(&read_mutex,NULL);

    for(int i=0;i<nw;i++){
        if(pthread_create(&w[i],NULL,Writer,NULL)){
            cout<<"\n Error in Writing!";
            exit(-1);
        }
    }
    for(int i=0;i<nr;i++){
        if(pthread_create(&r[i],NULL,Reader,NULL)){
            cout<<"\n Error in reading!";
            exit(-1);
        }
    }

    for(int i=0;i<nw;i++){
        pthread_join(w[i],NULL);
    }
    for(int i=0;i<nr;i++){
        pthread_join(r[i],NULL);
    }

    pthread_mutex_destroy(&write_mutex);
    pthread_mutex_destroy(&read_mutex);
}
