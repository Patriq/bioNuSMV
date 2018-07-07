How to compile NuSMV in Windows:
--------------------------------
The following procedure was performed under Windows 10 as of 2018-06-25

* Install [MSYS2](https://www.msys2.org/) and follow their installing instructions
* Open MSYS2 Shell and run:
    * `pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-toolchain`
    * `pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-make mingw-w64-x86_64-python2`

* Download:
    * https://sourceforge.net/projects/gnuwin32/files/patch/2.5.9-7/patch-2.5.9-7-bin.zip
    * https://sourceforge.net/projects/gnuwin32/files/bison/2.4.1/bison-2.4.1-dep.zip
    * https://sourceforge.net/projects/gnuwin32/files/bison/2.4.1/bison-2.4.1-bin.zip
    * https://sourceforge.net/projects/gnuwin32/files/flex/2.5.4a-1/flex-2.5.4a-1-bin.zip

* Extract and drag everything to `C:/msys64/mingw64/` (or wherever you installed MSYS)

* Open a cmd.exe with administrator and run:
    * `cd` to your user directory
    * `git clone https://github.com/ptgm/NuSMV-a.git`
    * `cd NuSMV-a`
    * `set PATH=C:\msys64\mingw64\bin;%PATH%`
    * `set CC=gcc`
    * `cd NuSMV/`
    * `mkdir build`
    * `cd build`
    * `cmake  -G "MinGW Makefiles" -DENABLE_STATIC_LINK=ON ..`
    * `mingw32-make`
    * `robocopy \msys64\mingw64\bin .\bin libgcc_s_seh-1.dll libstdc++-6.dll libwinpthread-1.dll`

The last step is needed because I was unable to static link `libstdc++` and `libgcc`.

If you have a better way to do this please submit a pull request. I am pretty sure this process probably isn't the best but it was a mashup of their original instructions and a lot of Google browsing.