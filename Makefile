CXX=clang++
INCLUDES=-Iincludes/ -Itests/
CXXEXTRAS=-Wall -Wextra -Werror -pedantic
CXXFLAGS=-std=c++20 -g -fstandalone-debug

exec: bin/exec
tests: bin/tests

obj/item.o: src/item.cc #item: no dependencies
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -c -o $@ 

obj/room.o: src/room.cc obj/item.o #room: 1 dependency
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -c -o $@

obj/character.o: src/character.cc obj/item.o obj/room.o #character: 2 dependencies
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -c -o $@

obj/game.o: src/game.cc obj/item.o obj/character.o obj/room.o #game: 3 dependencies
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -c -o $@

obj/catch.o: tests/catch.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^ -o $@

bin/tests: tests/tests.cc obj/catch.o obj/character.o obj/item.o obj/room.o obj/game.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

bin/exec: ./src/driver.cc obj/character.o obj/item.o obj/room.o obj/game.o
	$(CXX) $(CXXFLAGS) $(CXXEXTRAS) $(INCLUDES) $^ -o $@

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/* obj/item.o obj/room.o obj/character.o obj/game.o