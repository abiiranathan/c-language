vector: main.c
	gcc -Wall -ggdb3 -o vector main.c -lvec -L .

lib: vec.h vec.c
	gcc -c -Wall -Werror -std=c99 -fPIC -shared -L . -o libvec.so vec.c

valg:
	valgrind -s --leak-check=full ./vector 

clean:
	rm -f *.so *.o vector