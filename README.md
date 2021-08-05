# Utils CPP
Repository containing some utility frequnetly used inside different libraries' examples.

### Authors/Maintainers
- Bernardo Fichera (bernardo.fichera@epfl.ch)

### Available Utils
- File Manager
- Timer

### ToDo
- add memory monitoring (https://www.youtube.com/watch?v=sLlGEUO_EGE&t=239s and https://en.cppreference.com/w/cpp/types/alignment_of)

### Dependencies
This library depends on Eigen for loading files into Eigen matrices. For various utilities the library depends on Corrade utility library.
```sh
git clone https://github.com/mosra/corrade.git (git@github.com:mosra/corrade.git)
cd corrade && mkdir build && cmake .. && make && (sudo) make install
```

### Installation
Clone the repository including the submodules
```sh
git clone --recursive https://github.com/nash169/utils-cpp.git (git@github.com:nash169/utils-cpp.git)
```
**utils-cpp** relies on WAF compilation tool.
Arch provides an updated version of WAF exec in the standard repo
```sh
sudo pacman -S waf
```
For other distros it is better to download the latest version from the official website and move the executable in the library repo
```sh
wget 'https://waf.io/waf-2.0.21'
mv waf-2.0.19waf-2.0.19 waf && mv waf /path/to/utils-cpp
cd /path/to/kernel-lib
chmod +x waf
```
Compile and install using waf commands
```sh
waf (./waf) configure build
```
or
```sh
waf (./waf) configure && waf (./waf)
```
Install the library (optional)
```sh
(sudo) waf (./waf) install
```
If you want to make clean installation
```sh
(sudo) waf (./waf) distclean configure build install
```

#### Compilation options
In order to set the desired compiler define the environment variable CXX=<g++,clang++,icpc> (gnu, clang and intel compiler respectively).

It is highly recommended to compile with AVX support
```sh
waf (./waf) configure --optional-flags
```
Compile static library (default option)
```sh
waf (./waf) configure --static
```
Compile shared library
```sh
waf (./waf) configure --shared
```

### Examples
```sh
./build/src/examples/read_file
```