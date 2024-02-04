executeLinux:
	gcc -Wall -std=c11 ./Src/*.c -lSDL2 -lSDL2_ttf -o SpaceDanceLinux
	./SpaceDanceLinux
	rm SpaceDanceLinux

executeWindows:
	gcc -std=c11 ./Src/main.c ./Src/menu.c ./Src/gameLoop.c  -Wall -mwindows -lmingw32 -lSDL2 -lSDL2_ttf -o SpaceDanceWindows
	.\SpaceDanceWindows
	del "SpaceDanceWindows.exe"

buildLinux:
	gcc -Wall -std=c11 ./Src/*.c -lSDL2 -lSDL2_ttf -o SpaceDanceLinux

buildWindows:
	gcc -std=c11 ./Src/main.c ./Src/menu.c ./Src/gameLoop.c  -Wall -mwindows -lmingw32 -lSDL2 -lSDL2_ttf -o SpaceDanceWindows
