# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this repo is

A personal WSL scratch workspace for practicing C++ (LeetCode problems, STL internals, concurrency, build systems) plus assorted Python scripts and Jupyter notebooks. There is no single application and no test suite — it is a collection of dozens of independent, self-contained mini-projects. Documentation, comments, and commit messages are written in Chinese.

## Layout

- Numbered directories (`1smart_pointer` … `35nanobindpy`): one standalone C++ exercise each, typically a single `main.cpp`/`*.cpp` plus its own `CMakeLists.txt`. The number is just creation order; new exercises continue the sequence.
- `src/` + `include/` + `output/`: the "quick scratch" area built by the top-level Makefile. `src/main.cpp` is the default playground file.
- `script/`: Python scratch scripts (matplotlib plotting, PIL); `script/main.py` is the entry point for `make runpy`.
- `book_practice/1concurrency_in_action/`: exercises from *C++ Concurrency in Action*, same one-dir-per-topic CMake layout.
- `acm_template/`: ACM-style stdin/stdout I/O templates; to build one, edit the source file named in `add_executable()` in its `CMakeLists.txt`.
- `cmake_ws/`: a small CMake workspace example with its own `build/` dir.
- `notebooks/`: Jupyter notebooks.

## Building and running

Two build paths coexist:

**Top-level Makefile** (scratch area only — compiles everything under `src/` into `output/main`):
```bash
make run    # build src/*.cpp with g++ -std=c++17 and run output/main
make runpy  # run script/main.py with python3
make clean
```

**Per-directory CMake** (each numbered exercise):
```bash
cd <exercise_dir>
mkdir -p build && cd build
cmake .. && make
./<target>           # target name is defined in that dir's CMakeLists.txt
```
Ninja also works: `cmake -S . -B build -G Ninja && cd build && ninja` (see `34ninja_build/readme.md`).

The standard per-exercise `CMakeLists.txt` pattern: `cmake_minimum_required(VERSION 3.10)`, `CMAKE_CXX_STANDARD 17`, single `add_executable`. Follow it when adding a new exercise directory.

**Exception — `35nanobindpy`** is a Python extension module (nanobind + scikit-build-core), built with uv instead of plain CMake:
```bash
cd 35nanobindpy
uv sync
uv run python main.py
```

## Conventions

- C++17 throughout (`-std=c++17 -Wextra -g` in the Makefile, `CMAKE_CXX_STANDARD 17` in CMake).
- Each new topic/exercise gets its own numbered directory with its own `CMakeLists.txt`; add an entry to the directory list in `README.md`.
- Exercises that read input keep sample data in `in.txt`/`out.txt` next to `main.cpp` (see `28graph`, `31dijkstra`).
