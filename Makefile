TARGET := malloc.exe laa.exe
CC := i686-w64-mingw32-gcc

all: $(TARGET)

malloc.exe: malloc.c
	$(CC) -o $@ $^

laa.exe: malloc.c
	$(CC) -Wl,--large-address-aware -o $@ $^

