# Programowanie obiektowe w C++

All excercises are from:
[ROSALIND](https://rosalind.info/problems/tree-view/)

### Dependencies:
- [Boost regex](https://github.com/boostorg/regex)
- [LIBCURL](https://github.com/curl/curl)

##### Installation:
For arch based users:
```shell
sudo pacman -Ss boost
sudo pacman -Ss libcurl
```
For debian-based distro users:
```shell
sudo apt install libboost-regex-dev
sudo apt install libcurl4-gnutls-dev
```

### How to run

C++20 is required to compile
```shell
make
./rosSolver -d
```

```shell
./rosSolver --help
Rosalind solutions
Allows to see my rosalind progress
 Usage:         |        [options]
  -h, --help            Show help message
  -d, --default         allows to run program with predefined inputs
  -i                    first input file to be provided
  -I                    second input file to be provided
```

> Don't mind chaotic makefile

