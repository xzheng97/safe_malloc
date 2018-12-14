CC=gcc
SCAN_BUILD_DIR = scan-build-out
EXE=output

all: advanced_testcase4.o 537malloc.o range_tree.o linkedlist.o
	$(CC) -o $(EXE) advanced_testcase4.o 537malloc.o range_tree.o linkedlist.o

# main.c is your testcase file name
advanced_testcase4.o: advanced_testcase4.c
	$(CC) -Wall -Wextra -c advanced_testcase4.c

# Include all your .o files in the below rule
obj: 537malloc.o range_tree.o linkedlist.o

537malloc.o: 537malloc.c 537malloc.h range_tree.h linkedlist.h
	$(CC) -Wall -Wextra -g -O0 -c 537malloc.c linkedlist.c

range_tree.o: range_tree.c range_tree.h linkedlist.h
	$(CC) -Wall -Wextra -g -O0 -c range_tree.c linkedlist.c

linkedlist.o: linkedlist.c linkedlist.h
	$(CC) -Wall -Wextra -g -O0 -c linkedlist.c
clean:
	-rm *.o $(EXE)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html
