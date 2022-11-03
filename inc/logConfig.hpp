#pragma once
#include <ctime>
#include <string>
#include <cstring>
#include <cstdint>
extern char *__progname;

#define LOG_INFO_PARSE_MAX_NAME_SIZE 30

enum LogChannel{
    TRACE = 0, DEBUG, INFO, WARNING, ERROR, FATAL
};

std::string Channels[] = {
    "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
};

struct LogInfo_t{
    uint32_t size;
    uint16_t sequence_number;
    uint16_t data_size;
    char data[LOG_INFO_PARSE_MAX_NAME_SIZE];
    char timestamp[LOG_INFO_PARSE_MAX_NAME_SIZE];
    uint16_t thread_id;
    uint16_t code;
    uint32_t severity;
    char runnable_name[LOG_INFO_PARSE_MAX_NAME_SIZE];
    char file_name[2 * LOG_INFO_PARSE_MAX_NAME_SIZE];
    uint16_t line_number;
    uint32_t owner_pid;
    uint32_t flags;

    void getTimestamp(){
        std::time_t current_time = std::time(0);
        std::tm* timestamp_tm = std::localtime(&current_time);
        strftime(timestamp, 80, "%c", timestamp_tm);
    }

    void getThreadID(){
        thread_id = static_cast<uint16_t>(pthread_self());
    }

    void getFilename(const char *src){
        
        memcpy(file_name, src, strlen(src));
        file_name[strlen(src)] = '\0';
    }

    void getRunnable(){

        sprintf(runnable_name, "%s", __progname);
    }

    void getLine(int line){
        line_number = line;
    }

    template<typename... Args>
    void getData(const char* fmt, Args... args){
        sprintf(data, fmt, args...);
    }
};