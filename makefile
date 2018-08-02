all: load query print change clean data_writer

load: load.c header.h
	gcc -o load load.c header.c
query: query.c header.h
	gcc -o query query.c header.c
print: print.c header.h
	gcc -o print print.c header.c
change: change.c header.h
	gcc -o change change.c header.c
clean: clean.c header.h
	gcc -o clean clean.c header.c

data_writer: data_writer.c header.h
	gcc -o data_writer data_writer.c header.c

