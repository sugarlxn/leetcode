# acm_template

刷题acm模式的输入输出模板

1. 首先修改`CmakeLists.txt` 中的`add_executable(<target> <source_file>)` 中的 source_file

2. 在`build` 目录下执行编译和运行
```shell
cd build
cmake ..
make
./<target>
```
