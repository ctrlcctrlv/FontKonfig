CC=gcc
CXX=g++
MOC=moc
UIC=uic
INCLUDES=-I/usr/include/qt/QtCore -I/usr/include/qt/QtGui -I/usr/include/qt/QtWidgets -I/usr/include/qt -I/usr/include -I.
OPTIMIZE=0
CFLAGS=-g -fPIC -O$(OPTIMIZE)
CXXFLAGS=-g -fPIC -O$(OPTIMIZE) -std=c++11
LDFLAGS=-L/usr/lib/qt5 -L/usr/lib -lQt5Widgets -lQt5Gui -lQt5Core -lstdc++ -lfontconfig

.PHONY: all
all: FontKonfig

ui_fontkonfig.h: fontkonfig.ui
	$(UIC) $< -o $@

fontkonfig.moc: fontkonfig.h
	$(MOC) $< -o $@

FontKonfig: main.cpp fontkonfig.h fontkonfig.moc ui_fontkonfig.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) main.cpp -o $@ $(LDFLAGS)
