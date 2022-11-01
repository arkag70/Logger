#include <iostream>
#include <fstream>
#include <cstdint>
#include <ctime>
#include <pthread.h>
#include <map>
#include <filesystem>
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

    void getFilename(){
        sprintf(file_name, "%s", __progname);
    }

    template<typename... Args>
    void getData(const char* fmt, Args... args){
        sprintf(data, fmt, args...);
    }
};

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

        template<typename... Args>
        static void Fatal(const char* fmt, Args... args){


            getInstance().loginfo.getTimestamp();
            getInstance().loginfo.getThreadID();
            getInstance().loginfo.severity = FATAL;
            getInstance().loginfo.getFilename();
            getInstance().loginfo.getData(fmt, args...);

            getInstance().log(fmt, args...);
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
        std::map<std::string, int> file_records{};

        Logger():loginfo{}{
            loginfo.size = sizeof(LogInfo_t);
        };
        
        ~Logger(){
            std::string logfile_name = std::string(loginfo.file_name) + "_log.json";
            std::ofstream fout;

            if(std::filesystem::exists(logfile_name)){
                fout.open(logfile_name, std::ios::app);
            }
            else{
                fout.open(logfile_name, std::ios::out);
            }
            if(fout){
                fout << "\n]";
                fout.close();
            }
        }

        template<typename... Args>
        void log(const char* fmt, Args... args){

            std::string logfile_name = std::string(loginfo.file_name) + "_log.json";
            std::ofstream fout;

            if(std::filesystem::exists(logfile_name)){
                fout.open(logfile_name, std::ios::app);
            }
            else{
                fout.open(logfile_name, std::ios::out);
            }
            if(fout){
                file_records[logfile_name]++;

                if(file_records[logfile_name] == 1){
                    fout << "[\n\t{\n";
                }
                else{
                    fout << ",\n\t{\n";
                }
                fout << "\t\t\"Timestamp\" : \"" << loginfo.timestamp << "\",\n";
                fout << "\t\t\"Severity\" : \"" << Channels[loginfo.severity] << "\",\n";
                fout << "\t\t\"file_name\" : \"" << loginfo.file_name << "\",\n";
                fout << "\t\t\"Thread ID\" : \"" << loginfo.thread_id << "\",\n";
                fout << "\t\t\"Message\" : \"" << loginfo.data << "\"";
                fout << "\n\t}";

                fout.close();
            }
        }
        


};