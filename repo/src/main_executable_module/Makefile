CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic
LIBS_DIR = ../data_libs
BUILD_DIR = ../../build

SRC = main_executable_module.c
COMMON_LIBS = $(LIBS_DIR)/data_io.c $(LIBS_DIR)/data_stat.c $(LIBS_DIR)/decision.c
ALL_LIBS = $(COMMON_LIBS) $(LIBS_DIR)/data_process.c

TARGET = $(BUILD_DIR)/Quest_3
STATIC_TARGET = $(BUILD_DIR)/Quest_4
DYNAMIC_TARGET = $(BUILD_DIR)/Quest_5

STATIC_LIB = $(BUILD_DIR)/data_stat.a
DYNAMIC_LIB = $(BUILD_DIR)/data_process.so

.PHONY: all clean rebuild build_with_static build_with_dynamic

all: $(TARGET)

$(TARGET): $(SRC) $(ALL_LIBS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBS_DIR) $(SRC) $(ALL_LIBS) -lm -o $(TARGET)

clean:
	rm -f $(TARGET) $(STATIC_TARGET) $(DYNAMIC_TARGET) $(STATIC_LIB) $(DYNAMIC_LIB) $(BUILD_DIR)/*.o

rebuild: clean all

# --- Bonus Quest 4: data_stat built as a static library ---
$(BUILD_DIR)/data_stat.o: $(LIBS_DIR)/data_stat.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBS_DIR) -c $(LIBS_DIR)/data_stat.c -o $(BUILD_DIR)/data_stat.o

$(STATIC_LIB): $(BUILD_DIR)/data_stat.o
	ar rcs $(STATIC_LIB) $(BUILD_DIR)/data_stat.o

build_with_static: $(STATIC_LIB)
	$(CC) $(CFLAGS) -I$(LIBS_DIR) $(SRC) $(LIBS_DIR)/data_io.c $(LIBS_DIR)/data_process.c \
		$(LIBS_DIR)/decision.c $(STATIC_LIB) -lm -o $(STATIC_TARGET)

# --- Bonus Quest 5: data_process built as a dynamic library ---
$(DYNAMIC_LIB): $(LIBS_DIR)/data_process.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(LIBS_DIR) -fPIC -shared $(LIBS_DIR)/data_process.c -lm -o $(DYNAMIC_LIB)

build_with_dynamic: $(DYNAMIC_LIB)
	$(CC) $(CFLAGS) -DUSE_DYNAMIC_LIB -I$(LIBS_DIR) $(SRC) $(COMMON_LIBS) \
		$(DYNAMIC_LIB) -Wl,-rpath,'$$ORIGIN' -lm -o $(DYNAMIC_TARGET)
