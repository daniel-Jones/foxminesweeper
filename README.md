![image](https://danieljon.es/media/minesweep1.png)

Simple Minesweeper written in C++ using the fox toolkit.

You need FOX http://www.fox-toolkit.org/. On arch you can install the 'fox' package.

Compile:

```
cmake CMakeLists.txt
make
```

binary is in bin/

Right click on a tile to flag it.

Currently whe na game ends you need to restart the program for a new one.

You can change the width, height and mine count in the MainWindow constructor, not added to the gui yet.
