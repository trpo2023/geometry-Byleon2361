#Благодаря PHONY можно создавать файлы с имнем цели, т.е. all, clean и др.
# $^ список зависимостей
# $@ имя цели
# $< первая зависимость
# $? - Имена всех пререквизитов (разделенные пробелами), которые являются "более новыми", чем цель
# rcs означает replace, create, sort.
# ar — Создать библиотечные архивы
#APP_PATH - bin/geometry - исполняемый файл
#LIB_PATH - obj/src/geometry/geo.a
#LIB_OBJ - obj/src/libgeometry/geo.o
#APP_OBJ - obj/src/geometry/main.o
#DEPS - все файлы с расширением .d

APP_NAME = geometry
LIB_NAME = libgeometry

CFLAGS = -Wall 
CPPFLAGS = -I src -MMD

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src

APP_PATH = $(BIN_DIR)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a

SRC_EXT = c

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)

.PHONY: all clean run
all: $(APP_PATH) run clean

-include $(DEPS)

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ -lm

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ 
run:
	./$(APP_PATH)
#@-не показывает в командой строке
clean:
	@rm -f  $(APP_PATH) $(LIB_PATH) $(LIB_OBJECTS) $(APP_OBJECTS) $(DEPS)

