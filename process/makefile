src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))
out = $(patsubst ./obj/%.o, ./out/%, $(obj))
inc_path=./inc

ALL:$(out)

$(out):./out/%:./obj/%.o
	gcc $< -o $@
	
./obj/%.o:./src/%.c
	gcc -c $< -o $@ -I $(inc_path) -Wall -g -std=c99

clean:
	-rm -rf $(obj) $(out)

.PHONY:clean ALL
