DEPS = player.hpp game.hpp enemy.hpp
all_sources = main.cpp player.cpp game.cpp enemy.cpp
PlayGame : $(DEPS) $(all_objs)
	g++ -o TheDemonHunter main.cpp game.cpp player.cpp enemy.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
%.o : %.cpp $(DEPS)
	g++ -c $<
clean :
	rm TheDemonHunter