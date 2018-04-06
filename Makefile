
RegexEngine: main.o nfa.o dfa.o regex_parser.o; g++ -std=c++11 *.o -o RegexEngine

main.o: main.cc nfa.o dfa.o regex_parser.o; g++ -std=c++11 main.cc -c

dfa.o: dfa.cc nfa.o regex_parser.o; g++ -std=c++11 dfa.cc -c

regex_parser.o: regex_parser.cc nfa.o; g++ -std=c++11 regex_parser.cc -c

nfa.o: nfa.cc; g++ -std=c++11 nfa.cc -c

clean:
    rm -rf *.o RegexEngine