all: ./bin/SquaryBeginning object

./bin/SquaryBeginning: main.o function.o
	gcc -o ./bin/SquaryBeginning function.o ./obj/main.o /Library/Frameworks/SDL2.framework/Versions/A/SDL2

main.o: ./source/main.c
	gcc -c ./source/main.c -I/Library/Frameworks/SDL2.framework/Versions/A/Headers

function.o: ./source/function.c
	gcc -c ./source/function.c -I/Library/Frameworks/SDL2.framework/Versions/A/Headers

object:
	rm -rf *o

clean:
	rm -rf *o ./bin/SquaryBeginning

