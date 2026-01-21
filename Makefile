CC = gcc
CFLAGS = -Wall
PTHREAD = -pthread
LIBS = -lm

PROGRAM_A = programA
PROGRAM_B = programB

WORKERS = MT25010_Part_B_cpu.c MT25010_Part_B_mem.c MT25010_Part_B_io.c

all: $(PROGRAM_A) $(PROGRAM_B)

$(PROGRAM_A): MT25010_Part_A_Program_A.c $(WORKERS)
	$(CC) $(CFLAGS) MT25010_Part_A_Program_A.c $(WORKERS) $(LIBS) -o $(PROGRAM_A)

$(PROGRAM_B): MT25010_Part_A_Program_B.c $(WORKERS)
	$(CC) $(CFLAGS) MT25010_Part_A_Program_B.c $(WORKERS) $(LIBS) $(PTHREAD) -o $(PROGRAM_B)

clean:
	rm -f $(PROGRAM_A) $(PROGRAM_B)
