set -e
set -x

gcc -Wall -g main.c -o main -lm

./main
