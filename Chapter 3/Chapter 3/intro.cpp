#include <iostream>
#include <thread>

using namespace std;

bool ShouldEndThread = false;
int ThreadVar = 0;

void HelloWorldThread() {
    while(!ShouldEndThread) {
        ThreadVar++;
        if(ThreadVar > 1000) ThreadVar = 0;
    }
}

int helloworld()
{
    cout << "Hello World!\n";
    char userInput;
    thread Hello(HelloWorldThread);

    Hello.join();

    return 0;
}
