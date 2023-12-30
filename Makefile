CC = g++
CFLAGS = -std=c++14 -O3
TARGET = sifas-dat

build:
	$(CC) $(CFLAGS) $(TARGET).cpp -o $(TARGET)

clean:
	$(RM) $(TARGET)