/*
 *
 * Michael Dunnegan and Jonah Fidel, September 25
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "list.h"

char** tokenify(const char *line, node *head) {

    char *str = strdup(line); // duplicate line
    
    // tells me how long to malloc the return array 
    int numWhiteSpaces = 0;
    for (int i = 0; i < strlen(line); i++){
        if (isspace(line[i])){
            numWhiteSpaces++;
        }
    }

    // we will be returning a pointer to an array of accepted values in str
    char **token_array = (char**) malloc(sizeof(char*) * numWhiteSpaces+5); // mallocing worst case scenario

    // token is first line???
    char *token = malloc(sizeof(char));

    // makes a token out of the first thing
    token = strtok(str, " \n\t");

    int token_index = 0; //sure

    // for each token in a line (line may have many tokens)
    while (token != NULL){

        // check if there is a # anywhere
        char *token_duplicate = strdup(token);

        for (int i = 0; i < strlen(token_duplicate); i++){
            if (token_duplicate[i] == '#'){ // terminate
                //printf("[deleted]\n%s", token_duplicate);
                token_duplicate[i] = '\0';

                // I dont think we want to return null here...

                return token_array; // right?
            } 


        }

        //token = strdup(token);
        token_array[token_index] = token;
        token_index++;
        token = strtok(NULL, " \n\t");
    }

    token_array[token_index] = NULL;
    return token_array;
}

void print_tokens(char *tokens) {
    int i = 0;
    while (tokens[i] != NULL) {
        printf("Token %d: %s\n", i+1, tokens[i]);
        i++;
    }
}

bool is_integer(const char *token){
    // this ain't working!
    if (sizeof(int) == sizeof(token)){
        //printf("token thats supposedly an int: \n");
        //printf(token);
        //printf("\n");
    }
}

void process_data(FILE *input_file) {

    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library functionope.  close it with the fclose()
    // built-in function

    // initialize a linked list
    // go through each element in the file
    // if element is strictly an int, add it to our linked list

    //node *head = NULL;

    char *line = malloc(101*sizeof(char));

    node *token_list = NULL;

    while(fgets(line, 100, input_file)!=NULL){
        //print_tokens(tokenify(line, &tokens));
        //printf(line);
        //printf(line);
        char **token = tokenify(line, &token_list);

        if (is_integer(*token)) {
            //printf(*token);
            //printf("\n");

            //list_append(*token_list, token); // pointer to pointer of head
        }

        /*
        * SINCE IS_INTEGER ISN'T WORKING, IM ADDING EVERYTHING TO THE LIST
        */
        printf("before list insert called:\n");
        list_insert(token_list, token); // causing a SEGFAULT HOLY ASS!!!!!

        /*
        * DONE ADDING EVERYTHING TO THE LIST
        */


    }
    printf("sup\n");
    print_list(token_list);
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
