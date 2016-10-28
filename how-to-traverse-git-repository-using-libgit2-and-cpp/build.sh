set -x 

g++ src/main.cpp -o repo_basics-DBG -std=c++11 -O0 -Wall -I/usr/local/include -L/usr/local/lib -lgit2
g++ src/main.cpp -o repo_basics -std=c++11 -O3 -s -Wall -I/usr/local/include -L/usr/local/lib -lgit2
