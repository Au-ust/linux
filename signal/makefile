.PHONY:all
all: myprocess.exe mykill.exe
myprocess.exe:myprocess.c
	gcc -o $@ $^ 
mykill.exe:mykill.c
	gcc -o $@ $^ 
.PHONY:clear
clear:
	rm -rf mykill.exe myprocess.exe