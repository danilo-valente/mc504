CC := gcc
MNT := ./mnt
MNAME := qotdfs
LIBS := `pkg-config fuse --cflags --libs`

.PHONY: build clean

all: build mount

umount:
	fusermount -u $(MNT)

mount:
	mkdir -p $(MNT)
	./$(MNAME) $(MNT) -f

build:
	$(CC) -Wall qotdfs.c $(LIBS) -o $(MNAME)

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c $(MNAME)
