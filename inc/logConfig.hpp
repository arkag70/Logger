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
    char data[5 * LOG_INFO_PARSE_MAX_NAME_SIZE];
    char timestamp[5 * LOG_INFO_PARSE_MAX_NAME_SIZE];
    uint16_t thread_id;
    uint16_t code;
    uint32_t severity;
    char label[2 * LOG_INFO_PARSE_MAX_NAME_SIZE];
    char file_name[6 * LOG_INFO_PARSE_MAX_NAME_SIZE];
    uint16_t line_number;
    uint32_t owner_pid;
    uint32_t flags;

    void setTimestamp(){
        std::time_t current_time = std::time(0);
        std::tm* timestamp_tm = std::localtime(&current_time);
        strftime(timestamp, 80, "%c", timestamp_tm);
    }

    void setThreadID(){
        thread_id = static_cast<uint16_t>(pthread_self());
    }

    void setFilename(const char *src){
        
        memcpy(file_name, src, strlen(src));
        file_name[strlen(src)] = '\0';
    }

    void setLabel(const char *l = ""){

        int len = strlen(l);

        if(len == 0){
            memcpy(label, __progname, strlen(__progname));
            label[strlen(__progname)] = '\0';
        }
        else{
            memcpy(label, l, len);
            label[len] = '\0';
        }
    }

    void setLine(int line){
        line_number = line;
    }

    template<typename... Args>
    void setData(const char* fmt, Args... args){
        sprintf(data, fmt, args...);
    }
};