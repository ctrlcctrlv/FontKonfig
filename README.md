# FontKonfig

This is just a silly little program to demonstrate Qt Designer.

It outputs the list of fonts `fontconfig` sees given a pattern.

## Building

```bash
make
```

or

```bash
moc fontkonfig.h -o fontkonfig.moc
uic fontkonfig.ui -o ui_fontkonfig.h
g++ -g -fPIC -O0 -std=c++11 -I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include/qt -I/usr/include -I. main.cpp -o FontKonfig -L/usr/lib/qt5 -L/usr/lib -lQt5Widgets -lQt5Gui -lQt5Core -lstdc++ -lfontconfig
```
