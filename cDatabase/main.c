
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE  1024

typedef struct {
	char* cBuffer;
	size_t stBufferLen;
	size_t stInputLen;
}sInputBuffer;




/*Static allocation for input buffer, not thread safe and limits input len but prevents malloc related issues*/
sInputBuffer* sNewInputBufferStatic(){
	static sInputBuffer* input_buffer;
	static char cBuffer[MAX_BUFFER_SIZE];

	input_buffer->cBuffer= cBuffer;
	input_buffer->stBufferLen= MAX_BUFFER_SIZE;
	input_buffer->stInputLen= 0;
	
	return input_buffer;
}

/*Stack Allocation, define the fixed size within the stuct and return by value instead of pointer*/
sInputBuffer sNewInputBufferStack(){
	sInputBuffer input_buffer= {
		.stBufferLen = MAX_BUFFER_SIZE,
		.stInputLen = 0
	};
	return input_buffer;

}

/*Malloc Allocation, uses malloc to assign size to buffer, more dynamic than the other two but we don't know how big this is*/
sInputBuffer* sNewInputBufferMalloc(){
	sInputBuffer* input_buffer = (sInputBuffer*)malloc(sizeof(sInputBuffer));
	input_buffer->cBuffer = NULL;
	input_buffer->stBufferLen = 0;
	input_buffer->stInputLen = 0;
	return input_buffer;
}





/*nicitie's*/
void printprompt(){printf("db> ");}




int main(int argc, char* argv[]){
	sInputBuffer* input = sNewInputBufferMalloc();
}

