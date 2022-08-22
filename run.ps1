$no_console = $true;

if($no_console){
	g++ main.cc engine.cc level.cc audio.cc game.cc game_elements.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include -mwindows  && ./build/main.exe
}else{
	g++ main.cc engine.cc level.cc audio.cc game.cc game_elements.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include -D NOTITLE  && ./build/main.exe
}