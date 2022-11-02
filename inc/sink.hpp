#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "logConfig.hpp"

class Sink{

    public:
        
        virtual void registerSink(std::string path) = 0;
        virtual void processMessage(LogInfo_t &info) = 0;
        
        Sink(const Sink &src) = delete;
        Sink(const Sink &&src) = delete;
        Sink& operator=(const Sink &src) = delete;
        Sink& operator=(const Sink &&src) = delete;

        Sink(){}
        ~Sink(){}
    
    private:

};