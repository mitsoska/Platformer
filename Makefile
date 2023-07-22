# Returns all c files nested or not in $(1)
define collect_sources
	$(shell find $(1) -name '*.cpp')
endef

SOURCES = $(call collect_sources, src)
OBJECTS = $(patsubst %.cpp, objects/%.o, $(SOURCES))

LD_FLAGS = `pkg-config --libs sdl2 SDL2_image SDL2_mixer SDL2_ttf`

all: build run

build: $(OBJECTS)
	@echo "[Makefile] Creating the executable"
	@g++ $^ -o bin $(LD_FLAGS)

run:
	@# Running with a default of two players
	@./bin 2

objects/%.o: %.cpp
	@# Making sure that the directory already exists before creating the object
	@mkdir -p $(dir $@)

	@echo "[Makefile] Building $@"
	@g++ -c $< -o $@

