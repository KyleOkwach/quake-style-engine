.PHONY: compile build run clean

compile: build run

out:
	@mkdir -p out

build: out
	@echo "Building the SDL game..."
	@gcc ./src/*.c \
		./src/backend/*.c \
		./src/backend/sdl/*.c \
		./src/core/*.c \
		./src/core/utils/*.c \
		./src/core/systems/*.c \
		./src/game/*.c \
		-lSDL3 \
		-o ./out/boomer_shooter.exe || (echo "Build failed!"; exit 1)

run: ./out/boomer_shooter.exe
	@echo "Running the SDL game..."
	@./out/boomer_shooter.exe

clean:
	@rm -rf ./out/boomer_shooter.exe