set -x
g++ -std=c++11 main.cpp -o cpusage-DBG -O0 -g -Wall
g++ -std=c++11 main.cpp -o cpusage -O3 -s -Wall
