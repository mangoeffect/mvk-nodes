# MVK Lines Detection

mvk-lines-detection(machine vision lines detection) 2d points line fitting methods implement. Is a module for [MVK](https://github.com/mangosroom/machine-vision-algorithms-library)

# About The Project

## How to Build

### Requirements

- OpenCV 3.x or later
- C++11 or later
- CMake 3.14 or later

#### Windows

```bash
# 1. Download the source code
git clone https://github.com/mangosroom/mvk_line_fitting.git

# 2. CMake generate the Visual Studio solution
cd mvk_line_fitting
mkdir build
cmake -S ./ -B ./build -G "Visual Studio 16 2019" # x64 default
# cmake -S ./ -B ./build -G "Visual Studio 16 2019" -A Win32

# 3. Build
cmake --build build --config Debug
cmake --build build --config Release
```

### Linux

```bash
# 1. Download the source code
git clone https://github.com/mangosroom/mvk_line_fitting.git

# 2. CMake generate the Visual Studio solution
cd mvk_line_fitting
mkdir build
cmake -S ./ -B ./build -G 

# 3. Build
cmake --build build --config Debug
cmake --build build --config Release
```

# Usage

# Roadmap

| Method | State | Introduction | Remarks |
| ----   | ----  | ------ | ------ |
| Regresion | Completed | - | - |
| Huber | - | - | - |
| Tukey | - | - | - |
| Racsac | - | - | - |
| Orthogonal | - | - | - |

# License

[Apache License 2.0](https://github.com/mangosroom/mvk_line_fitting/blob/main/LICENSE)









