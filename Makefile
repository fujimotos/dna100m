CC = gcc
CFLAGS = -O2 -Wall
TIME = /usr/bin/time -p
SIZE = 100000000

all: bench0 bench1 bench2 bench3

bench0: search0 data.txt
	$(TIME) ./search0 < data.txt | wc -l

bench1: search1 data.txt
	$(TIME) ./search1 < data.txt | wc -l

bench2: search2 data.txt
	$(TIME) ./search2 < data.txt | wc -l

bench3: search2 data.txt
	$(TIME) parallel --block 10M --pipepart -a data.txt ./search2 | wc -l

.PHONY: all bench0 bench1 bench2 bench3

data.txt: gendata
	./gendata | head -n $(SIZE) > $@

gendata: gendata.c
	$(CC) $(CFLAGS) -o $@ $^

search0: search0.c
	$(CC) $(CFLAGS) -o $@ $^

search1: search1.c
	$(CC) $(CFLAGS) -o $@ $^

search2: search2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f search0
	rm -f search1
	rm -f search2
