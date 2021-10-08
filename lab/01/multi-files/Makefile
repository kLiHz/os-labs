main: hello.o functions.o
	cc -o main hello.o functions.o

hello.o: hello.c functions.h
	cc -c hello.c

functions.o: functions.c functions.h
	cc -c functions.c

clean:
	rm main hello.o functions.o
