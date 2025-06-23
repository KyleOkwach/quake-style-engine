.PHONY: compile build run clean

compile: build run

out:
	@mkdir -p out

build: out
	@echo "Building the SDL game..."
	@gcc ./src/*.c \
		./src/platform/*.c \
		-lSDL3 \
		-o ./out/sdl_game.exe || (echo "Build failed!"; exit 1)

run: ./out/sdl_game.exe
	@echo "Running the SDL game..."
	@./out/sdl_game.exe

clean:
	@rm -rf ./out/sdl_game.exe