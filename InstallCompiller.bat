@echo off
if %PROCESSOR_ARCHITECTURE% == AMD64 (
    powershell -Command "Invoke-WebRequest https://github.com/mstorsjo/llvm-mingw/releases/download/20231031/llvm-mingw-20231031-msvcrt-x86_64.zip -Outfile llvm-mingw-20231031-msvcrt-x86_64.zip"
    tar -xf llvm-mingw-20231031-msvcrt-x86_64.zip --directory C:\
    del llvm-mingw-20231031-msvcrt-x86_64.zip
    powershell -Command "Invoke-WebRequest https://git.rootprojects.org/attachments/33681b9d-0f51-4589-b29f-c050213df219 -Outfile pathman-v0.5.2-windows-amd64.zip"
    tar -xf pathman-v0.5.2-windows-amd64.zip --directory .\
    .\pathman-v0.5.2-windows-amd64.exe  add C:\llvm-mingw-20231031-msvcrt-x86_64\bin
    del .\pathman-v0.5.2-windows-amd64.exe
    del pathman-v0.5.2-windows-amd64.zip
) else (
    powershell -Command "Invoke-WebRequest https://github.com/mstorsjo/llvm-mingw/releases/download/20231031/llvm-mingw-20231031-ucrt-aarch64.zip -Outfile llvm-mingw-20231031-ucrt-aarch64.zip"
    tar -xf llvm-mingw-20231031-ucrt-aarch64.zip --directory C:\
    del llvm-mingw-20231031-ucrt-aarch64.zip
    powershell -Command "Invoke-WebRequest https://git.rootprojects.org/attachments/33681b9d-0f51-4589-b29f-c050213df219 -Outfile pathman-v0.5.2-windows-amd64.zip"
    tar -xf pathman-v0.5.2-windows-amd64.zip --directory .\
    .\pathman-v0.5.2-windows-amd64.exe  add C:\llvm-mingw-20231031-ucrt-aarch64\bin
    del .\pathman-v0.5.2-windows-amd64.exe
    del pathman-v0.5.2-windows-amd64.zip
)