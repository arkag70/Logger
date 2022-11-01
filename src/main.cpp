#include "logger.hpp"

int main(){

    const char *name = "Arka";
    int age{26};
    const char *place = "Kolkata";
    Logger::Fatal("Hello my name is %s", name);
    Logger::Fatal("I am %d years old", age);
    Logger::Fatal("I stay in %s", place);
    // Logger::Error("Hello my name is :%s", name);
    // Logger::Warning("Hello my name is :%s", name);
    // Logger::Info("Hello my name is :%s", name);
    // Logger::Debug("Hello my name is :%s", name);
    // Logger::Trace("Size of enum :%d", sizeof(LogChannel));


    return 0;
}