CC=gcc

all:
	${CC} -O2 -o pdfsearch pdfsearch.c `pkg-config --cflags --libs  glib-2.0 gio-2.0 cairo poppler-glib` -pthread 

# Requires a bebug build
memchk:
	valgrind  --leak-check=full --track-origins=yes --show-leak-kinds=all ./pdfsearch "pdf.pdf" ""

clean:
	rm -f ./pdfsearch