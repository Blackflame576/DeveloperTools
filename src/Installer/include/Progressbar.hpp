#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <iostream>
#include <cmath>
#include <math.h>
#include <sstream>
#include <iomanip>

using namespace std;

string doneSymbol = "#";
string todoSymbol = " ";
string startSymbol = "[";
string endSymbol = "]";
string Output;
int maxSymbols = 25;
int Process;
int n_done = 0;
string EmptyStr;
int LastSizeStr;
string OutputStr;

class ProgressBar {
    
    public:
        void Update(float NetworkSpeed = 0,float DownloadedSize = 0.0,float TotalSize = 0.0) {
            Process += 1;
            Output = startSymbol;
            for (int i = 0; i < n_done; i++) {
                Output += doneSymbol;
            }
            if (Process % 4 == 0) {
                Output += doneSymbol;
                n_done += 1;
            }
            if (maxSymbols - n_done) {
                for (int i = 0;i < (maxSymbols - n_done); i++) {
                    Output += todoSymbol;
                }
            }
            Output += endSymbol;
            EmptyStr = "";
            for (int i = 0;i < LastSizeStr;i++) {
                EmptyStr += todoSymbol;
            }
            cout << "\r" << EmptyStr << flush;
            OutputStr = Output + " " + to_string(Process) + "%  ";
            if (DownloadedSize != 0.0 && NetworkSpeed != 0 && TotalSize != 0.0) {
                string Speed = AutoConvertSpeed(NetworkSpeed);
                OutputStr = OutputStr + AutoConvertSize(DownloadedSize) + " / " + AutoConvertSize(TotalSize) + " | " + Speed;
            }
            else if (NetworkSpeed != 0) {
                string Speed = AutoConvertSpeed(NetworkSpeed);
                OutputStr += Speed;
            }
            else if (DownloadedSize != 0.0 && TotalSize != 0.0) {
                OutputStr += AutoConvertSize(DownloadedSize);
            }
            cout << "\r" << OutputStr << flush;
            LastSizeStr = OutputStr.size();
        }
        void ResetAll() {
            Process = 0;
            LastSizeStr = 0;
            OutputStr = "";
            EmptyStr = "";
            Output = "";
            n_done = 0;
        }

    private:
        string round(float value) {
            // Print value to a string
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << value;
            std::string str = ss.str();
            // Ensure that there is a decimal point somewhere (there should be)
            if(str.find('.') != std::string::npos)
            {
                // Remove trailing zeroes
                str = str.substr(0, str.find_last_not_of('0')+1);
                // If the decimal point is now the last character, remove that as well
                if(str.find('.') == str.size()-1)
                {
                    str = str.substr(0, str.size()-1);
                }
            }
            return str;
        }

        string AutoConvertSpeed(float NetworkSpeed) {
            string ConvertedSpeed;
            NetworkSpeed = convert_to_KB(NetworkSpeed);
            if (NetworkSpeed >= 1024) {
                ConvertedSpeed = round(convert_to_MB(NetworkSpeed))  + " MB/s";
            }
            else if (convert_to_KB(NetworkSpeed) < 1) {
                ConvertedSpeed = round(convert_to_KBit(NetworkSpeed)) + " KBit/s";
            }
            else {
                ConvertedSpeed = round(NetworkSpeed) + " KB/s";
            }
            return ConvertedSpeed;
        }

        string AutoConvertSize(float Size) {
            string ConvertedSize;
            Size = convert_to_KB(Size);
            if (Size >= 1024) {
                ConvertedSize = round(convert_to_MB(Size))  + " MB";
            }
            else if(convert_to_MB(Size) >= 1024) {
                ConvertedSize = round(convert_to_GB(Size)) + " GB";
            }
            else {
                ConvertedSize = round(Size) + " KB";
            }
            return ConvertedSize;
        }

        float convert_to_MB(float Value) {
            float NewValue = Value / 1024;
            return NewValue;
        }

        float convert_to_KB(float Value) {
            float NewValue = Value / 1024;
            return NewValue;
        }

        float convert_to_GB(float Value) {
            float NewValue = Value / 1024;
            return NewValue;
        }

        float convert_to_MBit(float Value) {
            float NewValue = Value * 0.008;
            return NewValue;
        }

        float convert_to_KBit(float Value) {
            float NewValue = Value * 8;
            return NewValue;
        }
};
#endif