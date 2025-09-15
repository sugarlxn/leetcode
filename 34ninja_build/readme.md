# how to use ninja-build with cmake

first, write donw your c++ project with CMakeLists.txt 

then, using cmake create ninja build files
```shell
cmake -S . -B build -G Ninja
```
指定-S为源码目录，-B为生成的build目录，-G指定生成ninja文件

finnally, 进入build目录 使用ninja 对项目进行编译
```shell
cd build
ninja
```
