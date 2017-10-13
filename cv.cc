#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>

namespace {
    std::condition_variable cv;
    std::mutex mutex;
    const int UPPER_BOUND = 10000;
    int value = 0;
}

void even() {
    while ( value < UPPER_BOUND ) {
        std::unique_lock<std::mutex> lock( mutex );
        if ( value % 2 != 0 ) {
            cv.notify_all();
            cv.wait( lock, [&](){ return value % 2 == 0; } );
        }

        if( value > UPPER_BOUND )
            break;
        std::cout << "thread 1: " << value++ << std::endl;
    }
    cv.notify_all();
}

void odd() {
    while ( value < UPPER_BOUND ) {
        std::unique_lock<std::mutex> lock( mutex );
        if ( value % 2 != 1 ) {
            cv.notify_all();
            cv.wait( lock, [&](){ return value % 2 == 1; } );
        }

        if( value > UPPER_BOUND )
            break;

        std::cout << "thread 2: " << value++ << std::endl;
    }
    cv.notify_all();
}

int main( void ) {
    std::thread first( even );
    std::thread second( odd );

    first.join();
    second.join();
}
