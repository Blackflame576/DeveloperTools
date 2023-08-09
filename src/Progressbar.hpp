#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H
#include <iostream>
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
        void Update(float NetworkSpeed = 0,double Time = 0.0) {
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
            // cout << EndTime << endl;
            if (NetworkSpeed != 0) {
                string Speed = AutoConvert(NetworkSpeed);
                OutputStr = Output + " " + to_string(Process) + "% " + Speed;
            }
            else {
                OutputStr = Output + " " + to_string(Process) + "% ";
            }
            // cout << Time << endl;
            cout << "\r" << OutputStr << flush;
            LastSizeStr = OutputStr.size();
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
                ConvertedSpeed = to_string(NetworkSpeed) + " KB/s";
            }
            return ConvertedSpeed;
        }

        float convert_to_MB(float Value) {
            float NewValue = Value / 1024;
            NewValue = floor(NewValue * 100) / 100;
            return NewValue;
        }

        float convert_to_MBit(float Value) {
            float NewValue = Value * 0.008;
            NewValue = floor(NewValue * 100) / 100;
            return NewValue;
        }

        float convert_to_KBit(float Value) {
            float NewValue = Value * 8;
            NewValue = floor(NewValue * 100) / 100;
            return NewValue;
        }
};
#endif