#include "logger.hpp"
#include <thread>

void calculate(int a, int b){

    int add = a+b;
    LOG_FATAL("Sum : %d", add);

    int sub = a-b;
    LOG_FATAL("Diff : %d", add);

    int pro = a*b;
    LOG_FATAL("Prod : %d", pro);

}

int main(){

    Logger::registerLogger();
    
    const char *name = "Arka";
    int age{26};
    const char *place = "Kolkata";

    std::thread calc(calculate, 20, 15);

    calculate(10, 5);


    LOG_FATAL("Hello my name is %s", name);
    LOG_FATAL("I am %d years old", age);
    LOG_FATAL("I stay in %s", place);

    calc.join();




    return 0;
}
