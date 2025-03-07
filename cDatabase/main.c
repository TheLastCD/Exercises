
#include <i386/endian.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

/* Static Max input buffersize */
#define MAX_BUFFER_SIZE  1024




/* Define error codes */
#define BUFFER_EXCEEDED_ERROR -1
#define LINE_READ_ERROR -10
#define STATEMENT_EXEC_FAILURE -20

/* Define Columns Sizes */
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255






/* Enums */
typedef enum{
	META_SUCCESS,
	META_UNKNOWN
}eMetaCommand;


typedef enum {
	STATE_INSERT,
	STATE_SELECT,
	STATE_SYNTAX_ERROR,
	STATE_UNKNOWN
}eStatementTypes;



/* Structs */

//define Row struct
typedef struct{
	uint32_t iID;
	char cUname[COLUMN_USERNAME_SIZE];
	char cEmail[COLUMN_EMAIL_SIZE];
}sRow;



typedef struct {
	char* cBuffer;
	size_t stBufferLen;
	size_t stInputLen;
}sInputBuffer;


typedef struct{
	eStatementTypes type;
	sRow sRowInsert; // only applicable to isert function
}sStatement;


/* Define Row sizes and Offsets */
/* Row breakdown (from original Tutorial):
 *	Column	size	offset
 *
 *	iID	4	0
 *	cUname	32	4
 *	cEmail	255	36
 *	total	291
 *
 * Each Row consumes 291 Bytes  
 * */

#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
const uint32_t ID_SIZE = size_of_attribute(sRow, iID);
const uint32_t USERNAME_SIZE = size_of_attribute(sRow, cUname);
const uint32_t EMAIL_SIZE = size_of_attribute(sRow, cEmail);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;





/* Static allocation for input buffer, not thread safe and limits input len but prevents malloc related issues*/
sInputBuffer* sNewInputBufferStatic(){
	static sInputBuffer input_buffer;
	static char cBuffer[MAX_BUFFER_SIZE];

	input_buffer.cBuffer= cBuffer;
	input_buffer.stBufferLen= MAX_BUFFER_SIZE;
	input_buffer.stInputLen= 0;
	
	return &input_buffer;
}

/* Stack Allocation, define the fixed size within the stuct and return by value instead of pointer as memory is free'd after lifecycle*/
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





/* Command Handling */

eMetaCommand McDoCommand(sInputBuffer* input_buffer){
	if (strcmp(input_buffer->cBuffer, ".exit") == 0) {
		//vCloseInputBuffer(input_buffer); //Comment out if using Stack or Static methods memory
		exit(EXIT_SUCCESS);
	}
	else{
		return META_UNKNOWN;
	}
}

void vReturnStatementType(sInputBuffer* input_buffer, sStatement* statement){
	if(strncmp(input_buffer->cBuffer, "insert", 6) == 0){
		statement->type = STATE_INSERT;
		int iArgs = sscanf(input_buffer->cBuffer, "insert %d %s %s", &(statement->sRowInsert.iID), statement->sRowInsert.cUname, statement->sRowInsert.cEmail);
		if(iArgs < 3){
			statement->type = STATE_SYNTAX_ERROR;
		}
	}

	else if(strcmp(input_buffer->cBuffer, "select") == 0){
		statement->type = STATE_SELECT;
	}
	else{
		statement->type = STATE_UNKNOWN;
	}

}

//PrepareResult prepare_statement(sInputBuffer* input_buffer, sStatement* statement) {
//  if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
//    statement->type = STATEMENT_INSERT;
//    return PREPARE_SUCCESS;
//  }
//  if (strcmp(input_buffer->buffer, "select") == 0) {
//   statement->type = STATEMENT_SELECT;
//    return PREPARE_SUCCESS;
//  }
//  return PREPARE_UNRECOGNIZED_STATEMENT;
//}



/* Executing Commands */

void vExecCommand(sStatement* statement){
	switch(statement->type){
		case(STATE_UNKNOWN):
			printf("Unrecognized keyword \n");
			break;
		case(STATE_SYNTAX_ERROR):
			printf("Syntax Error \n");
		case(STATE_INSERT):
			printf("Do an Insert \n");
			break;
		case(STATE_SELECT):
			printf("Do an Select \n");
			break;
	}
}

int iDoInsert(){
	return STATEMENT_EXEC_FAILURE;
}

/* Row de/Serialise logic */
/* In C11 or higher can us memcpy_s but as im compiling on Mac OS the headaches of getting that working is not worth it for a small change in a example*/
void vSerialiseRow(sRow* vSource, void* destination) {
	memcpy(destination + ID_OFFSET, &(vSource->iID), ID_SIZE);
	memcpy(destination + USERNAME_OFFSET, &(vSource->cUname), USERNAME_SIZE);
	memcpy(destination + EMAIL_OFFSET, &(vSource->cEmail), EMAIL_SIZE);
}

void vDeserialiseRow(void* vSource, sRow* destination) {
	memcpy(&(destination->iID), vSource + ID_OFFSET, ID_SIZE);
	memcpy(&(destination->cUname), vSource + USERNAME_OFFSET, USERNAME_SIZE);
	memcpy(&(destination->cEmail), vSource + EMAIL_OFFSET, EMAIL_SIZE);
}

/* implementation using memmove, better tham memcpy as it solves memory overlapping issues, however it is slower and overlapping is probably not a concern here */
void vSerialiseRowMM(sRow* vSource, void* destination) {
	memmove(destination + ID_OFFSET, &(vSource->iID), ID_SIZE);
	memmove(destination + USERNAME_OFFSET, &(vSource->cUname), USERNAME_SIZE);
	memmove(destination + EMAIL_OFFSET, &(vSource->cEmail), EMAIL_SIZE);
}
void vDeserialiseRowMM(void* vSource, sRow* destination) {
	memmove(&(destination->iID), vSource + ID_OFFSET, ID_SIZE);
	memmove(&(destination->cUname), vSource + USERNAME_OFFSET, USERNAME_SIZE);
	memmove(&(destination->cEmail), vSource + EMAIL_OFFSET, EMAIL_SIZE);
}

/*nicitie's*/
void printprompt(){printf("db> ");}


/* Exec Main */
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
		
		/* execute any meta commands */
		else if (input_buffer->cBuffer[0]== '.') {
			switch (McDoCommand(input_buffer)) {
				case(META_SUCCESS):
					continue;
				case(META_UNKNOWN):
					printf("Unrecognized command '%s'\n", input_buffer->cBuffer);
					continue;
			}
		} 
		else{
			sStatement statement;
			vReturnStatementType(input_buffer, &statement);
			vExecCommand(&statement);
			//if(statement.type == STATE_UNKNOWN){
			//	printf("retry Unrecognized keyword at start of '%s'.\n",input_buffer->cBuffer);
			//}
		};

//		else {
//			printf("Unrecognized command '%s'.\n", input_buffer->cBuffer);
//		}


		}
}


