#log_generator Makefile

CC = g++
CFLAGS = -Wall -Wextra

RMFLAGS = -f -v

TARGET = log_generator

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $^ -o $(TARGET)

clean:
	@$(RM) $(RMFLAGS) $(TARGET)