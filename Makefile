CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++20 -Werror


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

Dominion:  Player.o TreasureCard.o Card.o KingdomCard.o VictoryCard.o main.o Jeux.o Plateau.o Reserve.o GameCommand.o
	$(CXX) $^ -o $@ $(LDFLAGS)

.PHONY: run clean

run: Dominion


clean:
	rm -f *.o *~ *.core
