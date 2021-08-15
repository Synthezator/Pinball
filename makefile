CFLAGS = -g -Wall -o3
LDLIBS = -lm
BUILD_FOLDER = ./build

ping_pong_test:create_build_folder ping_pong_test.c
	gcc -c -o $(BUILD_FOLDER)/$@ ping_pong_test.c

gtk_gui:create_build_folder sample_gtk_gui.c
	gcc -c -o $(BUILD_FOLDER)/$@ sample_gtk_gui.c

create_build_folder: clean
	mkdir -p $(BUILD_FOLDER)

clean:
	rm -rvf $(BUILD_FOLDER)/*