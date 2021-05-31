#include<bits/stdc++.h>
using namespace std;

class Seamaphore{
  public:
    int val;
    Seamaphore(int value){
        val=value;
    }  
};
int in=0,out=0;

//Buffer size
int n=10;
vector<int> buffer(n,-1);

Seamaphore mutex(0);
Seamaphore empty(n);
Seamaphore full(0);

bool wait(Seamaphore &s){
    s.val-=1;
}
void signal(Seamaphore &s){
    s.val+=1;
}

void producer(int item){
    while(empty.val<=0);
    wait(empty);
    while(mutex.val==0);
    wait(mutex);

    buffer[in]=item;
    cout<<item<<"inserted at index :"<<in<<endl;
    in=(in+1)%n;

    signal(mutex);
    signal(full);
}

void consumer(){
    while(full.val<=0);
    wait(full);
    while(mutex.val==0);
    wait(mutex);

    int remItem=buffer[out];
    buffer[out]=-1;
    cout<<remItem<<"values item removed from index :"<<out<<endl;
    out=(out+1)%n;

    signal(mutex);
    signal(empty);
}
int main(){
    producer(3);
    producer(4);

    consumer();
    consumer();
    
    return 0;
}