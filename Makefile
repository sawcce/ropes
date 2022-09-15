main.c:
	clang ./main.c -o ./main.exe


#.PHONY: build main.c
build: main.c

#.PHONY: run
run:
	./main.exe


