/*
 *
 * Jonah Fidel and Mike Dunnegan 9/28/14
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "list.h"

//this function was taken from lab02
char** tokenify(const char *s) {  
    char scopy[strlen(s) + 1];
    for (int i = 0; i < strlen(s) + 1; i++) {
        scopy[i] = s[i];  
        if (s[i] == '#'){
            scopy[i] = '\0';
        }
    }
    int track = 0; 
    char **arr = malloc(sizeof(char*) * (strlen(scopy) + 2));
    char *token = NULL;  
    char *temp; 
    
    token = strtok(scopy, " \t\n");
    while (token != NULL) {
        temp = strdup(token);
        arr[track] = temp;
        track++; 
        token = strtok(NULL, " \t\n");
    }
    arr[track] = NULL; 
    return arr; 
}

bool is_int(char *token) {
    if(!isdigit(token[0])) {
        if(token[0] != '-') {
            return false;
        }
        if(!isdigit(token[1])){
            return false;
        }
    }
    for(int i = 1; i < strlen(token); i++) {
        if(!isdigit(token[i])) { 
            return false;
        }
    }    
    return true;
}

void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function
    char *line = malloc(101*sizeof(char));

    node **token_list = malloc(sizeof(node)); 

    while(fgets(line, 100, input_file)!=NULL){
        char **tokens = tokenify(line);

        int i = 0; 
        while ((tokens[i]) != NULL){            
            if (is_int(tokens[i])){
                list_append(atoi(tokens[i]), token_list);
            } 
            i++;  
        }
    }

    list_sort(&token_list); 
    list_print(token_list);
    free(line);

    struct rusage usage;
    struct timeval user_time;
    struct timeval system_time;

    getrusage(RUSAGE_SELF, &usage);
    user_time = usage.ru_utime;
    system_time = usage.ru_stime;

    printf("User time: %f\n", (double)user_time.tv_sec+(double)user_time.tv_usec/1000000);
    printf("System time: %f\n", (double)system_time.tv_sec+(double)system_time.tv_usec/1000000); 

    free(token_list);
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