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
bool lockArray[1000];
int passedCrit = 0; 
atomic<int> nextTicket;
atomic<int> nowServing; 
atomic<int> nextIndex;
mutex m;
thread myThreads[1000];

void spinner(int i);
void method1();
void method2(int i);
void method3();
void acquireTicket();
void releaseTicket(); 
double threadTimer(); 

int main(){
    thread timerThread; 
    double averageTime = 0;
    nextIndex = 0;
    lockArray[0] = true;

    //SETUP
    cout << "Making threads...\n";
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner, i);
    }

    all_threads_created = true;

    for(int i=0; i<1000; i++){
        myThreads[i].join();
    }
    cout << "Passed through door: " << passedCrit << endl;
    cout << "Threads finished!\n";
    
    return 0;
}

void spinner(int i){
    while(!(all_threads_created)){
        //cout << "Spinning...\n";
    } 

    //method1();
    method2(i);
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

void method2(int i){
    //METHOD 2: spinlock using array
    
    while(!lockArray[i]){
        //maybe sleep here
        this_thread::sleep_for(chrono::nanoseconds(1));
    }

    //Critical section start
    //cout<<i<<endl;
    passedCrit++;
    cout<<passedCrit<<endl;
    //Critical section end
    lockArray[i] = false;
    lockArray[i+1] = true;    
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