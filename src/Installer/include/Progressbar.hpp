#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

string doneSymbol = "#";
string todoSymbol = " ";
string startSymbol = "[";
string endSymbol = "]";
string Output;
int maxSymbols = 50;
int Process;
int n_done = 0;
string EmptyStr;
int LastSizeStr;
string OutputStr;

class ProgressBar {
    
    public:
        void Update(float NetworkSpeed = 0,float TotalDownloaded = 0.0) {
            Process += 1;
            Output = startSymbol;
            for (int i = 0; i < n_done; i++) {
                Output += doneSymbol;
            }
            if (Process % 2 == 0) {
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
            if (TotalDownloaded != 0.0 && NetworkSpeed != 0) {
                string Speed = AutoConvert(NetworkSpeed);
                OutputStr = OutputStr + to_string(TotalDownloaded) + " | " + Speed;
            }
            else if (NetworkSpeed != 0) {
                string Speed = AutoConvert(NetworkSpeed);
                OutputStr += Speed;
            }
            else if (TotalDownloaded != 0.0) {
                OutputStr += to_string(TotalDownloaded);
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
        string AutoConvert(float NetworkSpeed) {
            string ConvertedSpeed;
            if (NetworkSpeed >= 1024) {
                ConvertedSpeed = to_string(convert_to_MB(NetworkSpeed))  + " MB/s";
            }
            else if (NetworkSpeed < 1) {
                ConvertedSpeed = to_string(convert_to_KBit(NetworkSpeed)) + " KBit/s";
            }
            else {
                ConvertedSpeed = to_string(static_cast<int>(NetworkSpeed)) + " KB/s";
            }
            return ConvertedSpeed;
        }

        int convert_to_MB(float Value) {
            int NewValue = (int)(Value / 1024);
            return NewValue;
        }

        int convert_to_MBit(float Value) {
            int NewValue = (int)(Value * 0.008);
            return NewValue;
        }

        float convert_to_KBit(float Value) {
            int NewValue = (int)(Value * 8);
            return NewValue;
        }
};
#endif