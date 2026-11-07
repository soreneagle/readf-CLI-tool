#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
    char word[42];
    unsigned count; // the count of the word
} WORD_T;

char buffer[BUFSIZE];
size_t total_words = 0;
size_t total_characters = 0; // used to keep track of characters read by fgets()

int main(int argc, char **argv) {
    if (argc != 2) { // argument count should be 2 
        printf("Usage: ./readf [file.ext]\n");
        return -1; // returns -1 indicating program encountered an error
    } 

    FILE *fp = fopen(argv[1], "r"); //opens argument 1 aka the filename to be opened
    if (fp == NULL) { // if the file pointer is NULL after attempting to open argv[1], print out that the file was not found
        printf("File Not Found");
    } 

    char Tbuffer[BUFSIZE]; // temporary buffer of size BUFSIZE 
    char *Dbuffer = NULL; // dynamic buffer to grow at every pass through of fgets

    while (fgets(Tbuffer, sizeof(Tbuffer), fp)) { // gets line from the file and fills buffer
        size_t chunk_length = strlen(Tbuffer);
        void *Temp = realloc(Dbuffer, (total_characters + chunk_length + 1)); // dynamically allocates the dbuffer by the total_characters read + the new chunk length + 1 for the null term.. '\0'
        
        if (Temp == NULL) { // checks to see if realloc succeeded in allocated memory
            return -1;
        } else { // if Temp != NULL, assing Dbuffer pointer to Temp pointer
            Dbuffer = Temp; // update Dbuffer with after a sucessful call because realloc might move memory to diff address
        }       

        memcpy(Dbuffer + total_characters, Tbuffer, chunk_length); // appends the chunk_length bytes from the temp buffer into the dynamic buffer after the previous stored characters

        total_characters += chunk_length; // gets the total characters that are in each chunk and updates it every loop iteration
        Dbuffer[total_characters] = '\0'; // adds a null terminator at the last index in the dynamic buffer
    }

    printf("%s\n", Dbuffer);

    free(Dbuffer); // frees the dynamic buffer in memory since we no longer need it
    fclose(fp); // close the file as we already read the contents
    return 0;
}