all:

	g++ -Wall -g TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa
	g++ -Wall -g TimeCode.cpp PaintDryTimer.cpp -o pdt

run:
	./tct
	./nasa

run-pdt:
	./pdt

try: all run