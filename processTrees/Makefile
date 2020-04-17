
all: list numeric

clean: 
	rm -f list numeric

list: list_sub_file.c
	gcc -Wall -o list_sub_file list_sub_file.c

numeric: numeric_checker.c
	gcc -Wall -o numeric_checker numeric_checker.c
    
