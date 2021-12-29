src = $(wildcard ./src/*.c)
obj = $(patsubst ./src/%.c, ./obj/%.o, $(src))
inc_path=./inc

ALL:a.out

a.out:$(obj)
	gcc $^ -o a.out
	
./obj/%.o:./src/%.c
	gcc -c $< -o $@ -I $(inc_path)

clean:
	-rm -rf $(obj) a.out

.PHONY:clean ALL
