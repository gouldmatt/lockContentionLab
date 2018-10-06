#include <iostream>
#include <thread>
#include <mutex>
#include <atomic> 
#include <chrono>
using namespace std;

bool allThreadsCreated = false;
int passedCrit = 0; 
atomic<int> nextTicket;
atomic<int> nowServing; 
mutex m;

void spinner();
void method1();
void method2();
void method3();
void acquireTicket();
void releaseTicket(); 

int main(){
    chrono::steady_clock::time_point threadTimes[1000];
    double averageTime = 0; 

    //SETUP
    thread myThreads[1000];
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner);
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    allThreadsCreated = true;


    for(int i=0; i<1000; i++){
        myThreads[i].join();
        threadTimes[i] = chrono::steady_clock::now();
    }

    for(int j = 0; j < 1000; j++){
        averageTime += chrono::duration_cast<std::chrono::milliseconds>(threadTimes[j] - begin).count();
    }

    cout << endl << "average time in milleseconds: " << averageTime / 1000 << endl << endl; 
    
    return 0;
}

void spinner(){
    while(!allThreadsCreated){
        //cout << "Spinning...\n";
    } 

    method1();
    //method2();
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
    //METHOD 2 ARRAY Stuff
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

