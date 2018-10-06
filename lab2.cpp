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
atomic<int> nextIndex; 
mutex m;
bool waitArray[1000];

void spinner();
void method1();
void method2();
void method3();
void acquireTicket();
void releaseTicket(); 

int main(){
    chrono::steady_clock::time_point threadTimes[1000];
    double averageTime = 0;  
    nextIndex = 0; 

    //SETUP
    thread myThreads[1000];
    for(int i=0; i<1000; i++){
        waitArray[i] = false; 
        myThreads[i] = thread(spinner);
    }

    waitArray[0] = true; 

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
     while(!(allThreadsCreated)){
        //cout << "Spinning...\n";
    } 
    //method1();
    method2();
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

    atomic<int> myIndex; 
    myIndex = nextIndex.fetch_add(1,memory_order_relaxed);

    while(waitArray[myIndex] == false){}

    //Critical section start
    passedCrit++;
    //Critical section end

    waitArray[myIndex +1] = true; 
}

void method3(){
    //METHOD 3 ticket lock

    acquireTicket();
    //Critical section start
    passedCrit++;
    //Critical section end

    releaseTicket(); 
}

void acquireTicket(){
    atomic<int> myTicket; 
    myTicket =  nextTicket.fetch_add(1,memory_order_relaxed); // -1 is to start at 0 
    while (myTicket != nowServing){} 

}
void releaseTicket(){
    nowServing.fetch_add(1,memory_order_relaxed); 
}

