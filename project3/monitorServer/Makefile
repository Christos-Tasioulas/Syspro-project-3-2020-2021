# sample Makefile that you can quickly adapt to your needs
# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11 -pthread

# set the name of the executable file to compile here
program=monitorServer

# list object files needed to compile the program
objects=main.o Handle.o CyclicBuffer.o List.o Free.o GetHost.o Sockets.o Threads.o Directory.o File.o Stats.o BloomFilter.o VirusBloom.o SkipList.o VirusSkip.o CitizenRecord.o CitizenVirus.o IsValid.o InputManager.o

# arguments to run the program
# args = -m 5 -b 50 -c 10 -s 4096 -i input_dir -t 3

# this makes the program. It's the first rule so it will be executed if you give just 'make'
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program)

# list .h dependencies for each .o (dependency on .c is automatically set by make!)
main.o : Handle.h
Handle.o : Handle.h Interface.h
Directory.o : Interface.h
File.o : Interface.h
IsValid.o : Interface.h
InputManager.o : Interface.h
Free.o : Interface.h
GetHost.o : Interface.h
Sockets.o : Interface.h
Threads.o : Interface.h
CitizenRecord.o : CitizenRecord.h
CitizenVirus.o : CitizenVirus.h
List.o : List.h
BloomFilter.o : BloomFilter.h
VirusBloom.o : VirusBloom.h
SkipList.o : SkipList.h
VirusSkip.o : VirusSkip.h
Stats.o : Stats.h
CyclicBuffer.o : CyclicBuffer.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'. Sometimes useful to avoid rewriting long commands.
run: $(program)
	./$(program) $(args)	

valgrind: $(program)
	valgrind --track-origins=yes --trace-children=yes ./$(program) $(args)