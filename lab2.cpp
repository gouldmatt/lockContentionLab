#include <iostream>
#include <thread>
#include <mutex>
#include <atomic> 
#include <time.h>

using namespace std;
/* void threadfunc(){
    cout << "Threading\n";
}
int main(){
    thread t1(threadfunc);
    cout << "making a thread\n";
    t1.join();
    return 0;
} */

bool all_threads_created = false;
int passedCrit = 0; 
atomic<int> nextTicket;
atomic<int> nowServing; 
mutex m;
thread myThreads[1000];

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
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner);
    }

    all_threads_created = true;

    for(int i=0; i<1000; i++){
        myThreads[i].join();
    }
    cout << passedCrit << endl;
    cout << "Threads finished!\n";
    
    return 0;
}

void spinner(){
    while(!(all_threads_created)){
        //cout << "Spinning...\n";
    } 

    method1();
    //method1();
    //method3();
}

void method1(){
    //METHOD 1: all threads race for the lock (mutex lock)

    m.lock();
    //Critical section start
    passedCrit++;
    //Critical section end
    m.unlock();
}

void method2(){
    //METHOD 2: spinlock using array

    bool lock[1000];
    lock[0] = true;
    for(int i=0; i<1000; i++){
        //check corresponding element in lock array

        //spin the thread on its corresponding lock array element
        while(!lock[i]){

        }

    }
    
}

void method3(){
    //METHOD 3 ticket lock

    acquireTicket();
    // critical section
    
    passedCrit++; 

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
    return 1;
}