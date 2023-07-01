#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime> 
#include <exception>
#include <filesystem>
#include <cmath>
#include <concepts>

using namespace std;

namespace Logger {
    // Инициализация переменных класса
    bool getFile = false;
    ofstream file;
    string PathFile = "";
    long size;
    long size_KB;
    long size_MB;
    long size_GB;
    long size_TB;
    ifstream get_file_size;
    long limit_size;
    char limit_value;
    const string DebugStr = "☑️[DEBUG]";
    const string ErrorStr = "❌[ERROR]";
    const string InfoStr = "🆗[INFO]";
    const string WarningStr = "⚠️[WARNING]";
    const string SuccessStr = "✅[SUCCESS]";

    class Logger
    {
        public:
            const string GetTime() {
                time_t     now = time(0);
                struct tm  tstruct;
                char       buf[80];
                tstruct = *localtime(&now);
                // for more information about date/time format
                strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
                return buf;
            }

            void Debug(string sentence) {
                auto time = GetTime();
                string text = DebugStr + "::[" + time + "]" + ":::" + sentence;
                if (getFile == true) {
                    WriteFile(PathFile,text);
                }
                else {
                    cout << text <<endl;
                }
            }
            void Info(string sentence) {
                auto time = GetTime();
                string text = InfoStr + "::[" + time + "]" + ":::" + sentence;
                if (getFile == true) {
                    WriteFile(PathFile,text);
                }
                else {
                    cout << text <<endl;
                }
            }

            void Error(string sentence) {
                auto time = GetTime();
                string text = ErrorStr + "::[" + time + "]" + ":::" + sentence;
                if (getFile == true) {
                    WriteFile(PathFile,text);
                }
                else {
                    cout << text << endl;
                }
            }
            
            void Warning(string sentence) {
                auto time = GetTime();
                string text = WarningStr + "::[" + time + "]" + ":::" + sentence;
                if (getFile == true) {
                    WriteFile(PathFile,text);
                }
                else {
                    cout << text << endl;
                }
            }

            void Success(string sentence) {
                auto time = GetTime();
                string text = SuccessStr + "::[" + time + "]" + ":::" + sentence;
                if (getFile == true) {
                    WriteFile(PathFile,text);
                }
                else {
                    cout << text << endl;
                }
            }

            Logger();
            ~Logger();
        
        private:
            /* data */
            void WriteFile(string filename,string sentence) {
                file.open(filename,ofstream::app);
                get_file_size.open(filename, ios::in | ios::binary);
                get_file_size.seekg(0,ios::end);
                size = get_file_size.tellg();
                get_file_size.close();
                file << sentence + "\n";
                size_KB = round(size / 1024);
                size_MB = round(size / pow(1024,2));
                size_GB = round(size / pow(1024,3));
                size_TB = round(size / pow(1024,4));
                file.close();
            }
        
    };
    Logger::Logger(/* args */)
    {
    }
    
    Logger::~Logger()
    {
    }
    
}