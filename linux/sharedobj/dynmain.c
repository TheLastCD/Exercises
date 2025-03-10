#include <dlfcn.h>
void hello ();


void main(){
	void* handle = dlopen("libhello.so",RTLD_NOW);
	void(*helloFunc)(void) = dlsym(handle, "hello");
	helloFunc();
}
