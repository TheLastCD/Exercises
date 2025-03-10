echo "Building..."
gcc -c -Os -fno-ident -fno-asynchronous-unwind-tables -fno-stack-protector -fomit-frame-pointer -o shell.o shell.c
as sys.S -o sys.o
ld -o init shell.o sys.o --entry main -z noexecstack

echo "Cleaning..."
rm shell.o sys.o
