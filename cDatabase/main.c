
#include <i386/endian.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE  1024




/* Define error codes */
#define BUFFER_EXCEEDED_ERROR -1
#define LINE_READ_ERROR -10



typedef struct {
	char* cBuffer;
	size_t stBufferLen;
	size_t stInputLen;
}sInputBuffer;




/* Static allocation for input buffer, not thread safe and limits input len but prevents malloc related issues*/
sInputBuffer* sNewInputBufferStatic(){
	static sInputBuffer input_buffer;
	static char cBuffer[MAX_BUFFER_SIZE];

	input_buffer.cBuffer= cBuffer;
	input_buffer.stBufferLen= MAX_BUFFER_SIZE;
	input_buffer.stInputLen= 0;
	
	return &input_buffer;
}

/* Stack Allocation, define the fixed size within the stuct and return by value instead of pointer*/
sInputBuffer sNewInputBufferStack(){
	sInputBuffer input_buffer= {
		.stBufferLen = MAX_BUFFER_SIZE,
		.stInputLen = 0
	};
	return input_buffer; //return the full struct not pointer as memory will be deallocated after lifecycle ends

}

/* Malloc Allocation, uses malloc to assign size to buffer, more dynamic than the other two but we don't know how big this is*/
sInputBuffer* sNewInputBufferMalloc(){
	sInputBuffer* input_buffer = (sInputBuffer*)malloc(sizeof(sInputBuffer));
	input_buffer->cBuffer = NULL;
	input_buffer->stBufferLen = 0;
	input_buffer->stInputLen = 0;
	return input_buffer;
}


/* Input Handling */
int vReadInput(sInputBuffer* input_buffer){
	size_t stByteRead = getline(&(input_buffer->cBuffer),&(input_buffer->stBufferLen),stdin);

	// this should be enough to bprevent an overflow, more accurately i could us fgets but i'll experiment with that later
	if (stByteRead >= MAX_BUFFER_SIZE){return BUFFER_EXCEEDED_ERROR;} //handle buffer overflow

	else if(stByteRead <=0){return LINE_READ_ERROR;}

	//removing trailing new line 
	input_buffer->stInputLen = stByteRead -1;
	input_buffer->cBuffer[stByteRead-1]=0;
	//input_buffer->cBuffer[input_buffer->stInputLen] = '\0';
	return 0;
}

void vCloseInputBuffer(sInputBuffer* input_buffer){
	free(input_buffer->cBuffer); //need to deallocate this first as if not it can cause memory leaks
	free(input_buffer);
}



/*nicitie's*/
void printprompt(){printf("db> ");}




int main(int argc, char* argv[]){
	//sInputBuffer* input_buffer = sNewInputBufferMalloc();
	//
	sInputBuffer input_struct = sNewInputBufferStack();
	sInputBuffer* input_buffer = &input_struct;
	for(;;){
		printprompt();
		int iReturnCode = vReadInput(input_buffer);
		if (iReturnCode == BUFFER_EXCEEDED_ERROR){
			printf("Reading Input error: '%d'.\n",iReturnCode); //manage errors return codes
		}
		if (strcmp(input_buffer->cBuffer, ".exit") == 0) {
			//vCloseInputBuffer(input_buffer);//comment out if using static or stack assigning, this is handled by program
			exit(EXIT_SUCCESS);
		} else {
			printf("Unrecognized command '%s'.\n", input_buffer->cBuffer);
		}


	

	}
}

