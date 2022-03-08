# Utils Library
Repository containing some utility frequently used inside different libraries.

### Authors/Maintainers
- Bernardo Fichera (bernardo.fichera@epfl.ch)

### Available Utils
- File Manager
- Timer
- Realtime checker
- Derivative checker

### ToDo
- add memory allocation monitoring (https://en.cppreference.com/w/cpp/types/alignment_of)

### Dependencies
This library depends on **Eigen** linear algebra library to load data into *Eigen* vectors/matrices. For various utilities the library depends on **Corrade** utility library.

*Corrade* installation:
```sh
git clone https://github.com/mosra/corrade.git (git@github.com:mosra/corrade.git)
cd corrade && mkdir build && cmake .. && make && (sudo) make install
```
*Eigen* installation:
```sh
git clone https://gitlab.com/libeigen/eigen.git (git@gitlab.com:libeigen/eigen.git)
cd eigen && mkdir build && cmake .. && (sudo) make install
```

### Installation
Clone the repository including the submodules
```sh
git clone --recursive https://github.com/nash169/utils-lib.git (git@github.com:nash169/utils-lib.git)
```
**utils-lib** relies on WAF compilation tool.
Arch provides an updated version of WAF exec in the standard repo
```sh
sudo pacman -S waf
```
For other distros it is better to download the latest version from the official website and move the executable in the library repo
```sh
wget 'https://waf.io/waf-2.0.23'
mv waf-2.0.23 waf && mv waf /path/to/utils-lib
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
If you want to make a clean installation
```sh
(sudo) waf (./waf) distclean configure build install
```

#### Compilation options
In order to set the desired compiler define the environment variable CXX=<g++,clang++,icpc> (gnu, clang and intel compiler respectively).

It is highly recommended to compile with AVX support
```sh
waf (./waf) configure --release
```
Compile static library (default option)
```sh
waf (./waf) configure --static
```
Compile shared library
```sh
waf (./waf) configure --shared
```
Define a specific installation path
```sh
waf (./waf) configure --prefix=/path/to/install/folder
```

### Examples
Once the library is compiled all the examples can be found in
```sh
./build/src/examples/
```
