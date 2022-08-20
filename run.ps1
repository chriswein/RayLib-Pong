$no_console = $false;

if($no_console){
	g++ test.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include -mwindows  && ./build/main.exe
}else{
	g++ test.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include   && ./build/main.exe
}