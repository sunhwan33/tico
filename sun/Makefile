CC = gcc
TARGET = tico
OBJECTS = ticoSimulator.c tico.c

.PHONY : all
all : tico

tico :
CFLAGS = -Wall -W
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	clear

# convert :
# CFLAGS = -W -Wall
# $(TARGET) : $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $^
# 	clear
# 	./tico convert.txt

# average : 
# CFLAGS = -W -Wall
# $(TARGET) : $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $^
# 	clear
# 	./tico average.txt

# mode : 
# CFLAGS = -W -Wall
# $(TARGET) : $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $^
# 	clear
# 	./tico mode.txt

# GCD : 
# CFLAGS = -W -Wall
# $(TARGET) : $(OBJECTS)
# 	$(CC) $(CFLAGS) -o $@ $^
# 	clear
# 	./tico GCD.txt

.PHONY: clean
clean: 
	rm -rf tico
	rm -rf tico.o
	rm -rf ticoSimulator.o
	clear