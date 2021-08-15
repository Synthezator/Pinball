CFLAGS = -g -Wall -o3
LDLIBS = -lm
BUILD_FOLDER = ./build

arg_test: create_build_folder
	gcc -o $(BUILD_FOLDER)/$@ args_test.c

create_build_folder: clean
	mkdir -p $(BUILD_FOLDER)

clean:
	rm -rvf $(BUILD_FOLDER)/*