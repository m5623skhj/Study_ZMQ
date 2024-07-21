@echo off

cd build/
cmake ..

if "%OS%"=="Windows_NT" (
	cmake --build . --config Debug
	cmake --build . --config Release
) else (
	make
)

echo.
echo "Build completed"
pause