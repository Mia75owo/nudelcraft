.DEFAULT_GOAL := start

SRC=src
OUT=out


# ========
# Programs
# ========

CC=clang
CC_flags=-ggdb3

LD=clang
LD_flags=-lGL -lglfw -lGLEW


# =====
# Files
# =====

# C ==========
C_SRCS=$(wildcard $(SRC)/*.c)
C_OBJS=$(subst $(SRC),$(OUT),$(C_SRCS:.c=.o))

# The name of the output file
TARGET=nudelcraft


# =====
# Rules
# =====

# C rules

$(OUT)/%.o: $(SRC)/%.c
	$(CC) $(CC_flags) -c $< -o $@

# Target rules

# The main file
$(OUT)/$(TARGET): $(C_OBJS)
	$(LD) $(LD_flags) $(C_OBJS) -o $@

compile: $(OUT)/$(TARGET)


# ===========
# Other rules
# ===========

clean:
	rm -rf $(OUT)/*

valgrind: compile
	valgrind --tool=memcheck --track-origins=yes ./$(OUT)/$(TARGET)

start: compile
	./$(OUT)/$(TARGET)
