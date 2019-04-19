FILES=image_operations.h image_operations.c fs_operations.c fs_operations.h main.c
OBJS=$(FILES:.c=.o)
ARCHIVE=libcont.a
EXE=cont
FLAGS=-std=c99 -pthread -lm

all: $(OBJS) archive
	gcc $(OBJS) -o $(EXE) $(FLAGS)

.c.o:
	gcc -c $< -o $@ $(FLAGS)

archive:
	ar rcs $(ARCHIVE) $(OBJS)