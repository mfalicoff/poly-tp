CXX=g++
CFLAGS=-g -m32 -Wall
LDFLAGS=-lm
RM=rm -f
TARGET=Tp4_Ex1
OBJECTS=Tp4_Ex1.o Rectangle.o Cylinder.o Rectangle_Perimeter.s Rectangle_Area.s Rectangle_Diagonal.s Cylinder_Perimeter.s Cylinder_Area.s Cylinder_BaseArea.s Cylinder_LateralArea.s Cylinder_Volume.s

.PHONY: clean

.cpp.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

.s.o:
	$(CXX) $(CFLAGS) -c -o $@ $<

all: Tp4_Ex1

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	$(RM) *.o $(TARGET)
