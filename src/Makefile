CXX=g++
CXXFLAGS=-std=c++0x -Wall

ifeq ($(mode),debug)
	CXXFLAGS+= -g
else ifeq ($(mode),profile)
	CXXFLAGS+= -pg
else
	CXXFLAGS+= -O3
endif

LDFLAGS=-lpng -lpthread -lboost_iostreams -lboost_system -lboost_filesystem -lboost_program_options

OBJECTS=util.o $(addprefix mc/, cache.o chunk.o nbt.o pos.o region.o world.o) $(addprefix render/, config.o image.o manager.o render.o textures.o tile.o)
TEST_OBJECTS=$(addprefix test/, test_image.o test_nbt.o test_pos.o test_tile.o)

all: $(OBJECTS) mapcrafter testtextures #test
clean:
	rm -rf mapcrafter mapcrafter.o testtextures testtextures.o $(OBJECTS)
	
mapcrafter: mapcrafter.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o mapcrafter mapcrafter.o $(OBJECTS) $(LDFLAGS)
testtextures: testtextures.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o testtextures testtextures.o $(OBJECTS) $(LDFLAGS)

test: test/test_all.cpp $(TEST_OBJECTS) $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o test/test_all -I. test/test_all.cpp $(TEST_OBJECTS) $(OBJECTS) $(LDFLAGS) -lboost_unit_test_framework

runtest: test
	cd test && ./test_all --log_level=test_suite
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

mc/cache.o: mc/cache.cpp mc/pos.h mc/chunk.h mc/region.h mc/world.h
mc/chunk.o: mc/chunk.cpp mc/nbt.h mc/pos.h
mc/nbt.o: mc/nbt.cpp
mc/pos.o: mc/pos.cpp
mc/region.o: mc/region.cpp mc/pos.h mc/chunk.h
mc/world.o: mc/world.cpp mc/pos.h mc/chunk.h mc/region.h

render/config.o: render/config.cpp
render/image.o: render/image.cpp
render/manager.o: render/manager.cpp mc/cache.h mc/pos.h mc/chunk.h mc/region.h mc/world.h render/render.h
render/render.o: render/render.cpp  mc/pos.h mc/cache.h render/config.h render/textures.h render/tile.h
render/textures.o: render/textures.cpp render/image.o
render/tile.o: render/tile.cpp mc/pos.h mc/chunk.h mc/cache.h

test/test_image.o: test/test_image.cpp render/image.h
test/test_nbt.o: test/test_nbt.cpp mc/nbt.h
test/test_pos.o: test/test_pos.cpp mc/pos.h
test/test_tile.o: test/test_tile.cpp render/tile.h
