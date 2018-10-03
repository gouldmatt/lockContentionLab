#include <iostream>
#include <thread>
#include <mutex>
#include <atomic> 
#include <time.h>
using namespace std;

bool all_threads_created = false;
int theDoor = 0; 
atomic<int> nextTicket;
atomic<int> nowServing; 

void spinner();
void method1();
void method2();
void method3();
void acquireTicket();
void releaseTicket(); 
double threadTimer(); 

int main(){
    thread timerThread; 
    double averageTime = 0; 

    //SETUP
    cout << "Making threads...\n";
    thread myThreads[1000];
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner);
    }

    all_threads_created = true;

    for(int i=0; i<1000; i++){
        myThreads[i].join();
    }

    cout << "Threads finished!\n";
    
    return 0;
}

void spinner(){
    while(!(all_threads_created)){
        //cout << "Spinning...\n";
    } 

    method1();
    method2();
    method3();
}

void method1(){
    //METHOD 1 PTHReAD shit
}

void method2(){
    //METHOD 2 ARRAY Stuff
}

void method3(){
    //METHOD 3 ticket lock

    acquireTicket();
    // critical section
    
    theDoor++; 

    releaseTicket(); 
}

void acquireTicket(){
    atomic<int> myTicket; 
    myTicket =  nextTicket.fetch_add(1,memory_order_relaxed);
    while (myTicket != nowServing){} 

}
void releaseTicket(){
    nowServing.fetch_add(1,memory_order_relaxed); 
}

double threadTimer(){
    
}