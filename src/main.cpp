#include "logger.hpp"
#include <thread>

void calculate(int a, int b, Logger &logger){

    int add = a+b;
    logger.LOG_FATAL("Sum : %d", add);

    int sub = a-b;
    logger.LOG_FATAL("Diff : %d", add);

    int pro = a*b;
    logger.LOG_FATAL("Prod : %d", pro);

}

int main(){

    Logger logger{};
    logger.registerLogger(JSONSINK);
    
    const char *name = "Arka";
    int age{26};
    const char *place = "Kolkata";

    std::thread calc(calculate, 20, 15, std::ref(logger));

    calculate(10, 5, logger);


    logger.LOG_FATAL("Hello my name is %s", name);
    logger.LOG_FATAL("I am %d years old", age);
    logger.LOG_FATAL("I stay in %s", place);

    calc.join();




    return 0;
}
