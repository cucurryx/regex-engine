regex_engine: *.cc *.h
	g++ *.cc -c;rm test.o;g++ *.o -o regex_engine

test: *.cc *.h
	g++ *.cc -c;rm main.o;g++ *.o /usr/local/lib/libgtest.a -lpthread -o test

clean:
	rm -rf *.o;