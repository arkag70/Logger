#pragma once
#include "sink.hpp"
#include "logConfig.hpp"

class JsonSink : public Sink{

    public:
        
        JsonSink():log_file{}{}

        void registerSink(std::string path){

            log_file = path;
            std::ofstream fout(log_file, std::ios::out);
            if(fout){
                fout << "{\n";
            }

        }

        void processMessage(LogInfo_t &info){

            
            std::ofstream fout(log_file, std::ios::app);
            if(fout){
                static bool firstJson = true;
                
                if(firstJson){
                
                    firstJson = false;
                    fout << "\t\"" << info.runnable_name << "\" :{\n";
                }
                else{

                    fout << ",\n\t\"" << info.runnable_name << "\" :{\n";
                }
                
                fout << "\t\t\"Timestamp\" : \"" << info.timestamp << "\",\n";
                fout << "\t\t\"Severity\" : \"" << Channels[info.severity] << "\",\n";
                fout << "\t\t\"file_name\" : \"" << info.file_name << "\",\n";
                fout << "\t\t\"line number\" : \"" << info.line_number << "\",\n";
                fout << "\t\t\"Thread ID\" : \"" << info.thread_id << "\",\n";
                fout << "\t\t\"Message\" : \"" << info.data << "\"";
                fout << "\n\t}";
            }
        }

        ~JsonSink(){

            std::ofstream fout{log_file, std::ios::app};
            if(fout){
                fout << "\n}\n";
                fout.close();
            }
        }

    private:

        std::string log_file;
};