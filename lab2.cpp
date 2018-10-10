#include <iostream>
#include <thread>
#include <mutex>
#include <atomic> 
#include <time.h>

using namespace std;

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
    passedCrit = 0;
    chrono::steady_clock::time_point threadTimes[100];
    double averageTime = 0;
    nextIndex = 0;
    lockArray[0] = true;

    //SETUP 
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner, i);
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    all_threads_created = true;

    for(int i=0; i<1000; i++){
        myThreads[i].join();
        threadTimes[i] = chrono::steady_clock::now();
    }

    for(int j = 0; j < 1000; j++){
        averageTime += chrono::duration_cast<std::chrono::milliseconds>(threadTimes[j] - begin).count();
    }

    //cout << endl << endl <<  averageTime / 1000 << endl << endl; 

    cout << endl << endl << "passed crit. : " << passedCrit << endl << endl; 

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
    while(!lockArray[i]){}
    
    //Critical section start
    passedCrit++;
    //Critical section end

    lockArray[i] = false;
    
    if(i != 999){
        lockArray[i+1] = true;    
    }

    cout << passedCrit << " " ; 
    cout << i << endl;
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

