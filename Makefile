CC = gcc
TARGET = suntico
OBJECTS = sunticoSimulator.c suntico.c

.PHONY : all
all : suntico

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
	rm -rf app
	rm -rf app.o
	clear