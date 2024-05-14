# OuterJoin
Educational project with [googletest](https://github.com/google/googletest), [doxygen](https://github.com/doxygen/doxygen) and [boost asio](https://github.com/boostorg/asio).

## Build local Linux
```shell
sudo apt-get update && sudo apt-get install cmake libgtest-dev libboost-all-dev -y

cd OuterJoin
mkdir build && cd build

cmake ..

# build release
cmake --build . --config Release

# build deb-package
cmake --build . --target package
```

## Build local Windows
```shell
vcpkg install gtest boost-asio boost-system
vcpkg integrate install

cd OuterJoin
mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"

# build release
cmake --build . --config Release
```

## Tests
```shell
ctest
```
