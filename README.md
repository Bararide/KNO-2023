# KNO-2023

компиляция происходит при помощи g++ и CMake в папке build, которая была добавлена после копирования репозитория проекта.

mkdir build & cd build
cmake ..

папка library добавляется в папку build

внутри файла Block_analysis.cpp нужно сменить путь до подключаемых внешних библиотек.

после компиляции для запуска проекта нужно написать:
make genome
./genome -in:in.txt

