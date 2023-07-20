#include <iostream>

string OS_NAME;

void Build() {
  system("cmake  . ");
  system ("cmake --build  . ");
  system("cd build");
  if (OS_NAME == "Linux") {
    system ("cd Linux");
  }
  else if (OS_NAME == "macOS") {
    system("cd macOS");
  }
  else if (OS_NAME == "Windows") {
    system("cd Windows");
  }
}

int main() {
  #if defined(__linux__) 
     OS_NAME = "Linux";
  #elif __APPLE__
     OS_NAME = "macOS";
  #elif _WIN_32
     OS_NAME = "Windows";
  #endif
  Build();
}
