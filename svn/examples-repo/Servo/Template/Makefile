CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

APPDIR = Application
HALDIR = HAL-Host

INCLUDEHAL = $(HALDIR)
INCLUDEAPP = $(APPDIR)

APPOBJS =		$(APPDIR)/main.o
HALOBJS =       $(HALDIR)/switch.o $(HALDIR)/beeper.o

LIBS =

TARGET =	Beeper.exe

$(TARGET):	$(APPOBJS) $(HALOBJS)
	$(CXX) -I$(INCLUDEHAL) -I$(INCLUDEAPP) -o $(TARGET) $(APPOBJS) $(HALOBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(APPOBJS) $(HALOBJS) $(TARGET)
