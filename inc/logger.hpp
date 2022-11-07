#pragma once
#include <iostream>
#include <fstream>
#include <pthread.h>
#include <map>
#include <mutex>
#include "jsonSink.hpp"

class Logger{

    public:

        Logger():loginfo{}, log_file{}{
            loginfo.size = sizeof(LogInfo_t);
        };
        
        Logger(const Logger &src) = delete;
        Logger& operator=(const Logger &src) = delete;
        Logger(Logger &&src) = delete;
        Logger& operator=(Logger &&src) = delete;

        void registerLogger(SinkType type, const char *label = ""){

            loginfo.setLabel(label);

            log_file = std::string(__progname) + "_log.json";
            
            if(type == JSONSINK){
                sink = new JsonSink();
            }
            
            sink->registerSink(log_file);
        }

        template<typename... Args>
        void Fatal(int line, const char* src, const char* fmt, Args... args){

            log(line, src, fmt, args...);
        }

        template<typename... Args>
        void Error(const char* fmt, Args... args){
            log(fmt, args...);
        }

        template<typename... Args>
        void Warning(const char* fmt, Args... args){
            log(fmt, args...);
        }

        template<typename... Args>
        void Info(const char* fmt, Args... args){
            log(fmt, args...);
        }

        template<typename... Args>
        void Debug(const char* fmt, Args... args){
            log(fmt, args...);
        }

        template<typename... Args>
        void Trace(const char* fmt, Args... args){
            log(fmt, args...);
        }

        ~Logger(){
            delete sink;
            sink = nullptr;
        }

    private:
        
        LogChannel channel;
        LogInfo_t loginfo;
        std::string log_file{};
        std::mutex mtx;
        Sink *sink;

        template<typename... Args>
        void log(int line, const char *src, const char* fmt, Args... args){

            std::lock_guard<std::mutex> locker(mtx);
            
            loginfo.setTimestamp();
            loginfo.setThreadID();
            loginfo.severity = FATAL;
            loginfo.setFilename(src);
            loginfo.setLine(line);
            loginfo.setData(fmt, args...);

            sink->processMessage(loginfo);

        }
        


};

#define LOG_FATAL(FMT, ...) Fatal(__LINE__, __FILE__, FMT, __VA_ARGS__)
