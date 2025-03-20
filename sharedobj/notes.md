Specify at Linktime:
	gcc -shared shared.c
	mv a.out /usr/lib/libshared.so
	gcc main.c -l shared

Specify dynamically
	gcc main.c



