
@rmdir /S /Q msvs
@mkdir msvs
@cd msvs
C:\DOS\bin\cmake -G"Visual Studio 10 2010" .. -DCMAKE_BUILD_TYPE=Release
C:\DOS\bin\cmake --build . --config "Release" --target "ALL_BUILD"
@cd ..

@rmdir /S /Q codeblock
@mkdir codeblock
@cd codeblock
C:\DOS\bin\cmake -G "CodeBlocks - MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Release
C:\DOS\bin\cmake --build . --config "Release"
@cd ..

@rmdir /S /Q mingw
@mkdir mingw
@cd mingw
C:\DOS\bin\cmake -G "MinGW Makefiles" .. -DCMAKE_BUILD_TYPE=Release
C:\DOS\bin\cmake --build . --config "Release"
@cd ..
