# cd raylib && "$ZIG" build -Dplatform=rgfw -Draygui=true && cp -r zig-out ../../autogen/raylib && rm -rf zig-out .zig-cache && cd ../../
cd raylib && "$ZIG" build -Dplatform=glfw -Draygui=true && cp -r zig-out ../../autogen/raylib && rm -rf zig-out .zig-cache && cd ../../
