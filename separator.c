#include        <stdio.h>
#include        <stdlib.h>
#include        <unistd.h>
#include        <pthread.h>
#include 	<string.h>

//  PURPOSE:  To tell the length of char arrays.
const  int  		MAX_LINE = 256;

struct  		Word
{
    char* 		textPtr_;
    struct  Word* 	nextPtr_;
};

struct  Word*  		obtainCommaSeparatedList( const char* string) {
    char*  		charRun  	= strchr(string, ','); // pointer to next comma
    size_t 		wordLength;
    size_t              length          = strlen(string);
    struct  Word*       ret        = (struct Word*)malloc(sizeof(struct Word));
    char* 		stringRem;

    if (charRun != NULL) {
        charRun  	+= 1;
        wordLength 	= (charRun - string - 1);
        stringRem   = (char*)malloc(length - wordLength);
        strncpy(stringRem, charRun, (length - wordLength + 1));
    } else {
        wordLength 	= length;
        stringRem  	= string;
    }

    char* 		wordText 	= (char*)malloc(wordLength+1);
    strncpy(wordText, string, wordLength);
    ret->textPtr_ = wordText;

    if (charRun == NULL) {
        ret->nextPtr_ = NULL ;
        free(wordText);
        free(stringRem);
        return(ret);
    } else {
        ret->nextPtr_ = obtainCommaSeparatedList(stringRem); // the remainder of the string
    }
    return(ret);
}

void 		printCommaSeparatedList(const struct Word* list) {
    printf("\"%s\" \n", list->textPtr_);
    if (list->nextPtr_ == NULL)
        return;
    printCommaSeparatedList(list->nextPtr_);
}

void 		freeCommaSeparatedList(struct Word* list) {
    if (list->nextPtr_ == NULL) {
        free(list->textPtr_);
        return;
    }
    free(list->textPtr_);
    freeCommaSeparatedList(list->nextPtr_);
    free(list->nextPtr_);
}

int main () {
    char 	  	line[MAX_LINE];
    char*  	  	cPtr;
    char* 	 	charRun;
    struct  Word*  	splitList;
    char* 		initChar;
    char* 		commaChar;

    printf("Enter a line of text: ");
    fgets(line, MAX_LINE, stdin);

    cPtr  	= strchr(line,'\n');

    if (cPtr != NULL) {
        *cPtr = '\0';
        splitList 	= obtainCommaSeparatedList(line);
        printCommaSeparatedList(splitList);
        freeCommaSeparatedList(splitList);
    } else {
        printf("Invalid string entered; program terminating. \n");
        printf("Enter something longer next time \n");
    }

    return(EXIT_SUCCESS);
}
