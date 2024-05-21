Компиляция mingw/cygwin в Windows:
g++ src/*.cpp src/club_logic/*.cpp src/utils/*.cpp -Iinclude/club_logic -Iinclude/utils -o task.exe

Пример запуска программы:
$ task.exe test.txt
