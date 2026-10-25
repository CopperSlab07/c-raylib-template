# cd raylib/src && make PLATFORM=PLATFORM_DESKTOP_RGFW CC="../../../../Tools/zig 0.17.0 cc" AR="../../../../Tools/zig 0.17.0 ar" && mv libraylib.a ../../../autogen/ && make clean && cd ../../
cd raylib/src && make PLATFORM=PLATFORM_DESKTOP_RGFW && mv libraylib.a ../../../autogen/ && make clean && cd ../../
