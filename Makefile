.PHONY: compile build run clean

compile: build run

out:
	@mkdir -p out

build: out
	@echo "Building the SDL game..."
	@gcc ./src/*.c \
		./src/platform/*.c \
		./src/platform/sdl/*.c \
		./src/engine/renderer/*.c \
		-lSDL3 \
		-o ./out/boomer_shooter.exe || (echo "Build failed!"; exit 1)

run: ./out/boomer_shooter.exe
	@echo "Running the SDL game..."
	@./out/boomer_shooter.exe

clean:
	@rm -rf ./out/boomer_shooter.exe