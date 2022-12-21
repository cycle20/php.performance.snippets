set -e
set -x

gcc -std=gnu18 -fPIC -Wall  -c shared.c \
  && gcc -shared  -o libshared.so shared.o # \
#  && gcc  -o main main.c -lshared -lm -L.

# echo Run test "'main'"
# export LD_LIBRARY_PATH=.
# ./main
#

