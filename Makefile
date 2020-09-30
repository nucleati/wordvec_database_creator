CC=g++
CFLAGS=-Wall --std=c++11
LDFLAGS=-lleveldb -lpthread

w2vToLevelDb: main.o w2v_bin_helper.o
	$(CC) $(CFLAGS) -o w2vToLevelDb main.o w2v_bin_helper.o $(LDFLAGS)
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
w2v_bin_helper.o:  w2v_bin_helper.cpp
	$(CC) $(CFLAGS) -c w2v_bin_helper.cpp
clean:
	rm main.o w2v_bin_helper.o w2vToLevelDb