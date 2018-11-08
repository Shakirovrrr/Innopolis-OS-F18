gcc -o copy.o -DBUF_SIZE=1024 -DSYNC copy.c
time ./copy.o ex2.c ex2.c.copy
rm ex2.c.copy copy.o