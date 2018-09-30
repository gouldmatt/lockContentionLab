#include <iostream>
#include <thread>
using namespace std;

bool all_threads_created = false;

void spinner(){
    while(!(all_threads_created)){
        cout << "Spinning...\n";
    }
}

int main(){
    //SETUP
    cout << "Making threads...\n";
    thread myThreads[1000];
    for(int i=0; i<1000; i++){
        myThreads[i]=thread(spinner);
    }

    for(int i=0; i<1000; i++){
        myThreads[i].join();
    }
    //thread t1(spinner);
    //t1.join();
    cout << "thread finished\n";
    
    return 0;
}
