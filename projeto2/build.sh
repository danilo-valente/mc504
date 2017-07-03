NEW_FS=$1

fusermount -u mnt
gcc -Wall $NEW_FS.c -lcurl `pkg-config fuse --cflags --libs` -o $NEW_FS
./$NEW_FS mnt -f
