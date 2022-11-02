#pragma once
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <map>
#include <filesystem>
#include "logConfig.hpp"
#include "jsonSink.hpp"

class Logger{

    public:
        
        Logger(const Logger &src) = delete;
        Logger& operator=(const Logger &src) = delete;
        Logger(Logger &&src) = delete;
        Logger& operator=(Logger &&src) = delete;

        static Logger& getInstance(){
            
            static Logger instance;
            return instance;
        }

        static void registerLogger(){
            std::string logFile = getInstance().log_file = std::string(__progname) + "_log.json";
            getInstance().jsink.registerSink(logFile);
        }

        template<typename... Args>
        static void Fatal(int line, const char* src, const char* fmt, Args... args){

            getInstance().log(line, src, fmt, args...);
        }

        template<typename... Args>
        static void Error(const char* fmt, Args... args){
            getInstance().log(fmt, args...);
        }

        template<typename... Args>
        static void Warning(const char* fmt, Args... args){
            getInstance().log(fmt, args...);
        }

        template<typename... Args>
        static void Info(const char* fmt, Args... args){
            getInstance().log(fmt, args...);
        }

        template<typename... Args>
        static void Debug(const char* fmt, Args... args){
            getInstance().log(fmt, args...);
        }

        template<typename... Args>
        static void Trace(const char* fmt, Args... args){
            getInstance().log(fmt, args...);
        }

    private:
        
        LogChannel channel;
        LogInfo_t loginfo;
        std::string log_file{};
        JsonSink jsink;


        Logger():loginfo{}, log_file{}{
            loginfo.size = sizeof(LogInfo_t);
        };
        
        ~Logger(){
            
        }

        template<typename... Args>
        void log(int line, const char *src, const char* fmt, Args... args){

            loginfo.getTimestamp();
            loginfo.getThreadID();
            loginfo.severity = FATAL;
            loginfo.getFilename(src);
            loginfo.getLine(line);
            loginfo.getRunnable();
            loginfo.getData(fmt, args...);
            std::string logfile_name = std::string(loginfo.runnable_name) + "_log.json";

            jsink.processMessage(loginfo);

        }
        


};

#define LOG_FATAL(FMT, ...) Logger::Fatal(__LINE__, __FILE__, FMT, __VA_ARGS__)
