#include "./numbers.c"
#include "./count.c"

int main(){

	int x = number1(); 
	int y = number2();
	int i = count(&x, &y); 
	return 0;
}
