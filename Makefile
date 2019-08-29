TARGET := malloc.exe laa.exe filemap.exe
CC := i686-w64-mingw32-gcc

all: $(TARGET)

malloc.exe: malloc.c
	$(CC) -o $@ $^

laa.exe: malloc.c
	$(CC) -Wl,--large-address-aware -o $@ $^

filemap.exe: filemap.c
	$(CC) -Wl,--large-address-aware -o $@ $^

