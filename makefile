CPP=g++

CORE=tsvector.cpp constant.cpp
QED=photon.cpp clock.cpp vector2d.cpp
OBJECT=object.cpp block.cpp sphere.cpp convexsphere.cpp concavesphere.cpp

TESTS := $(shell ls test_*.cpp)

CFLAGS=--std=c++0x

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	INCLUDES=-I/usr/include
	LINKS=-L/usr/lib64 -lgmp
	ifeq ($(GRAPHICS),1)
		LINKS=-L/usr/lib64 -lgmp -lGL -lglfw -lftgl
		CFLAGS=-DGRAPHICS=1 --std=c++0x
	endif
endif
ifeq ($(UNAME_S),Darwin)
	INCLUDES=-I/usr/local/Cellar/glfw3/3.1.2/include -I/opt/X11/include
	LINKS=-L/usr/local/Cellar/glfw3/3.1.2/lib -lgmp
	ifeq ($(GRAPHICS),1)
		LINKS=-L/usr/local/Cellar/glfw3/3.1.2/lib -lgmp -lglfw3
		CFLAGS=-DGRAPHICS=1 -framework OpenGl --std=c++0x
	endif
endif

build: $(CORE) $(QED) $(OBJECT)
	$(CPP) -c -fPIC $(CORE) $(INCLUDES) $(LINKS) $(CFLAGS)
	$(CPP) -c -fPIC $(OBJECT) $(INCLUDES) $(LINKS) $(CFLAGS)
	$(CPP) -c -fPIC $(QED) $(INCLUDES) $(LINKS) $(CFLAGS)
	$(foreach test,$(TESTS),$(CPP) $(test) -o $(test).out *.o $(INCLUDES) $(LINKS) $(CFLAGS);)
clean:
	for file in $$(ls *.o); do rm $$file; done
	for file in $$(ls *.so); do rm $$file; done
	for file in $$(ls *.gch); do rm $$file; done
	for file in $$(ls test_*.out); do rm $$file; done
