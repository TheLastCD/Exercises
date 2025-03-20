Companion to a smallest possible distro configuration:
	https://www.youtube.com/watch?v=u2Juz5sQyYQ


initial compilation of c and asm code commands:
	gcc -c -Os -fno-ident -fno-asynchronous-unwind-tables -fno-stack-protector -fom
it-frame-pointer -o shell.o shell.c
	as sys.S
	ld -o init shell.o a.out --entry main -z noexecstack
	
converting the out compiled code into an archive
	echo init | cpio -H newc -o > init.cpio

adding it to the kernel:
	in linux dir
	make isoimage FDARGS="initrd=/init.cpio" FDINITRD=~/linux/userspace/init.cpio

Adding statically copiled modules:
	echo init >> files
	echo .. >> files
	echo files | cpio -H newc -o > init.cpio
