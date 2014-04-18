CPPFLAGS = `wx-config --cppflags` -fopenmp -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP 
LDLIBS = `wx-config --libs` -fopenmp
CXX = g++

SOURCES = CApp.cpp CAquarium.cpp CDecorTreasure.cpp CFish.cpp \
		CFishBeta.cpp CFishDory.cpp CFishNemo.cpp CFrame.cpp \
		CItem.cpp 


OBJS = CApp.o CAquarium.o CDecorTreasure.o CFish.o \
		CFishBeta.o CFishDory.o CFishNemo.o CFrame.o \
		CItem.o 


all: Aquarium


Aquarium: $(OBJS)
	$(CXX) $^ $(LDLIBS) -o$@

include $(subst .cpp,.d,$(SOURCES))

%.d: %.cpp
	$(CXX) -M $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

clean:
	rm -f *.o *.d
