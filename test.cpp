#include <iostream>
#include <unistd.h>
#include "src/Progressbar.hpp"
using namespace std;

string DoneChar = "#";
string TodoChar = " ";
string StartChar = "[";
string EndChar = "]";
string output;
int n_char = 50;
int n_current = 0;
int process = 0;
// int n_done = 0;
ProgressBar bar;

// void UpdateProgressBar(string Speed) {
//         process += 1; 
//         // output = "";
//         output = "[";
//         for (int n = 0;n < n_done;n++) {
//             output = output + "#";
//             // cout << output << endl;
//         }
//         if (process % 2 == 0) {
//             output = output + "#";
//             n_done += 1;
//         }
        
//         if (n_char - n_done) {
//             for (int a = 0;a < (n_char - n_done);a++) {
//                 output +=" ";
//             }
//         }
//         output = output + "]";
//         // cout << n_done << endl;
//         // std::cout << "\rCompleted " << i << "%   " << std::flush;
//         std::cout << "\r" << output << " " << process << "%   " << Speed << std::flush;
// }

int main() {
    // for (int i = 0;i < 100;i++) {
    //     UpdateProgressBar();
    // }
    for (int i = 0; i < 100; i++) {
        int random = (std::rand()%20000)+1;
        // float time = random / i;
        // int t = random / i;
        bar.Update(random);
        // cout << t << endl;
        // string Speed = to_string(random) + " KB/s";
        // UpdateProgressBar(Speed);
        sleep(1);
    }

    // std::cout << "\rDone            " << std::endl;
    return 0;
}