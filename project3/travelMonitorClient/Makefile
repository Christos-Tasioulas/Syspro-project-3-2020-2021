# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11

# set the name of the executable file to compile here
program=travelMonitorClient

# list object files needed to compile the program
objects=main.o Handle.o Directory.o List.o Free.o Child.o GetHost.o Sockets.o BloomFilter.o VirusBloom.o IsValid.o InputManager.o TravelRequest.o

# arguments to run the program
args = -m 5 -b 50 -c 10 -s 64 -i input_dir -t 3

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
main.o : Handle.h
Handle.o : Handle.h Interface.h
Directory.o : Interface.h
IsValid.o : Interface.h
InputManager.o : Interface.h
Free.o : Interface.h
Child.o : Interface.h
GetHost.o : Interface.h
Sockets.o : Interface.h
List.o : List.h
BloomFilter.o : BloomFilter.h
VirusBloom.o : VirusBloom.h
TravelRequest.o : TravelRequest.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) $(args)	

valgrind: $(program)
	valgrind --track-origins=yes --trace-children=yes ./$(program) $(args)