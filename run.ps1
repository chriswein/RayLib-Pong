$no_console = $false;
$build_bin = $false;
$build_wasm = $true;

if($build_bin){
	if($no_console){
		g++ main.cc engine.cc level.cc audio.cc game.cc game_elements.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include -mwindows -D NOTITLE && ./build/main.exe;
	}else{
		g++ main.cc engine.cc level.cc audio.cc game.cc game_elements.cc -o ./build/main.exe -O1 -Wall -std=c++17 -Wno-missing-braces -L ./lib -lraylib -lopengl32 -lgdi32 -lwinmm -I ./include -D NOTITLE  && ./build/main.exe;
	}
}

if($build_wasm) {
	emcc -o ./build/game.html .\main.cc engine.cc level.cc audio.cc game.cc game_elements.cc  ./lib/wasm/libraylib.a -O1 -I./include -L lraylib -s USE_GLFW=3 -DPLATFORM_WEB -sLLD_REPORT_UNDEFINED --preload-file assets
}

# --embed-file ./assets/hit.wav 