CXX := g++
OBJDUMP := objdump
OBJCOPY := objcopy
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
INCLUDE_DIR := includes
NAME := programs
CFLAGS := -O2 -std=c++20 -Wall -Wextra -Wno-unknown-pragmas -Wno-unused-result
LDFLAGS := -O2
INCLUDES := -I$(INCLUDE_DIR)

C_SRCS := $(shell find . -name "*.c")
CPP_SRCS := $(shell find . -name "*.cpp")

C_OBJS := $(C_SRCS:%.c=$(OBJ_DIR)/%.c.o)
CPP_OBJS := $(CPP_SRCS:%.cpp=$(OBJ_DIR)/%.cpp.o)

OBJS := $(C_OBJS) $(CPP_OBJS) $(ASM_OBJS)

.PHONY: all clean debug run

all: clean $(BIN_DIR)/$(NAME)

$(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.c.o: %.c | $(OBJ_DIR)
	@echo "[cc] $<"
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.cpp.o: %.cpp | $(OBJ_DIR)
	@echo "[cxx] $<"
	@mkdir -p $(dir $@)
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR)/$(NAME): $(OBJS) | $(BIN_DIR)
	@echo "[ld] linking $(NAME)"
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

clean:
	@echo "[clean] removing $(BUILD_DIR)"
	@rm -rf $(BUILD_DIR)

debug: all
	@echo "[info] Debug build completed, product is in $(BIN_DIR)/$(NAME)"
	@echo "[objdump] Generating assembly dump..."
	$(OBJDUMP) -d $(BIN_DIR)/$(NAME) > $(BIN_DIR)/$(NAME).s
	@echo "[objcopy] Extracting debug info..."
	$(OBJCOPY) --only-keep-debug $(BIN_DIR)/$(NAME) $(BIN_DIR)/$(NAME).dbg
	@echo "[info] Debug files generated"

run: all
	@echo "[run] running $(BIN_DIR)/$(NAME)"
	@$(BIN_DIR)/$(NAME)