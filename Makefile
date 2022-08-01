# https://www.youtube.com/watch?v=PiFUuQqW-v8&ab_channel=Competer
# $@ replaced by name of target
# $< replaced by name of first prerequisite
# $^ replaced by names of all prerequisites

COMPILER = g++
RMDIR = rm -rdf
RM = rm -f

DEP_FLAGS = -M -MT $@ -MT $(BIN_PATH)/$(*F).o -MP -MF $@

FLAGS = -std=c++11 -Wall -pedantic -Wextra -Wno-unused-parameter -Werror=init-self

DFLAGS = -ggdb -O0 -DDEBUG

INC_PATH = include
SRC_PATH = src
TEST_PATH = tests
BIN_PATH = bin
DEP_PATH = dep

CPP_FILES = $(wildcard $(SRC_PATH)/*.cpp)
INC_FILES = $(wildcard $(INC_PATH)/*.hpp)
TEST_FILES = $(wildcard $(TEST_PATH)/*.cpp)
ALL_FILES = $(filter-out $(SRC_PATH)/main.cpp $(SRC_PATH)/menu.cpp, $(CPP_FILES))
ALL_FILES := $(ALL_FILES) $(filter-out $(INC_PATH)/main.hpp $(INC_PATH)/menu.hpp, $(INC_FILES))
ALL_FILES := $(ALL_FILES) $(TEST_FILES)
FILE_NAMES = $(sort $(notdir $(CPP_FILES:.cpp=)) $(notdir $(INC_FILES:.h=)))
DEP_FILES = $(addprefix $(DEP_PATH)/,$(addsuffix .d,$(FILE_NAMES)))
OBJ_FILES = $(addprefix $(BIN_PATH)/,$(notdir $(CPP_FILES:.cpp=.o)))

EXEC = vigenere

# Windows setup
ifeq ($(OS),Windows_NT)
RMDIR = rd /s /q
RM = del /q

FLAGS += -mwindows
DFLAGS += -mconsole

EXEC := $(EXEC).exe
endif
# End Windows setup

.PRECIOUS: $(DEP_FILES)
.PHONY: release debug clean folders help

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(COMPILER) -o $@ $^ $(FLAGS)

$(BIN_PATH)/%.o: $(DEP_PATH)/%.d | folders
	$(COMPILER) $(INC_PATHS) $(addprefix $(SRC_PATH)/,$(notdir $(<:.d=.cpp))) -c $(FLAGS) -o $@

$(DEP_PATH)/%.d: $(SRC_PATH)/%.cpp | folders
	$(COMPILER) $(INC_PATHS) $< $(DEP_FLAGS) $(FLAGS)

release: FLAGS += $(RFLAGS)
release: $(EXEC)

debug: FLAGS += $(DFLAGS)
debug: $(EXEC)

test: FLAGS += $(DFLAGS)
test:
	$(COMPILER) $(ALL_FILES) -o $@ $^ $(FLAGS)

clean:
	$(RMDIR) $(DEP_PATH)
	$(RMDIR) $(BIN_PATH)
	$(RM) $(EXEC)
	$(RM) test

folders:
ifeq ($(OS), Windows_NT)
	@if NOT exist $(DEP_PATH) (mkdir $(DEP_PATH))
	@if NOT exist $(BIN_PATH) (mkdir $(BIN_PATH))
	@if NOT exist $(INC_PATH) (mkdir $(INC_PATH))
	@if NOT exist $(SRC_PATH) (mkdir $(SRC_PATH))
else
	@mkdir -p $(DEP_PATH) $(BIN_PATH) $(INC_PATH) $(SRC_PATH)
endif

help:
ifeq ($(OS), Windows_NT)
	echo.
endif
	@echo Available targets:
	@echo - release: Build the release version
	@echo - debug: Build the debug version
	@echo - test: Build the test files
	@echo - clean: Cleans generated files
	@echo - folders: Generates project directories
	@echo - help: Show help
ifeq ($(OS), Windows_NT)
	echo.
endif
