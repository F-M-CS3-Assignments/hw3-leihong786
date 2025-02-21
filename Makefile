all:
    g++ -Wall -g TimeCode.cpp TimeCodeTests.cpp -o tct
run:
	./tct

try: all run