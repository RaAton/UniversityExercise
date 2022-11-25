arm-linux-gnueabihf-gcc  -static -ggdb3 $*
qemu-arm -g 12345 a.out &
gdb-multiarch -q --nh -ex 'set architecture arm' -ex 'file a.out' -ex 'target remote localhost:12345'
