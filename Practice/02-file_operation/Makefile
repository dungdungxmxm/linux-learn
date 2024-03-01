SOURCE = file_sample.c
FLAGS += -lrt

all:
#	@gcc -c $(SOURCE) -o $(patsubst %.c,%, $(SOURCE))
	@gcc $(FLAGS) $(SOURCE)
clean:
	@rm -rf *.out *.exe *.elf $(patsubst %.c,%, $(SOURCE))