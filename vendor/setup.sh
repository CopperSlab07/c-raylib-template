# cd raylib && "$ZIG" build -Dplatform=rgfw -Draygui=true && cp -r zig-out ../../autogen/raylib && rm -rf zig-out .zig-cache && cd ../../
cd raylib && ../../../Tools/zig-x86_64-macos-0.17.0/zig build -Dplatform=glfw -Draygui=true && cp -r zig-out ../../autogen/raylib && rm -rf zig-out .zig-cache && cd ../../
