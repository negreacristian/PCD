/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 1
 * 
 * < Realizati o aplicatie C, denumita app3.c in care sa exemplificati,
 *  la alegere, utilizarea functiilor si facilitatilor library-ului argparse.
 *  Aplicatia ar trebui sa accepte mai multe optiuni pe linia de comanda
 *  (stabilite si definite de voi), iar la unele din acestea, sa necesite o valoare,
 *  in timp ce la altele, sa nu necesite neaparat o valoare.
 *  Aplicatia va procesa optiunile folosind functiile din library-ul argparse
 *  si va extrage valorile asociate acestora, efecutand o procesare utila asupra acestora.
 * 
 * Probleme la rulare, optiuni nerecunoscute
 *
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- daca argumentele obligarii au fost transmise
 * -- daca fisierul nu se poate deschide sau nu a fost specificat
 */

#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/* Keep the arguments values here. */
struct args {
    char *file;
    int number;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct args *arguments = state->input;
    /* Check the option */
    switch (key) {
        case 'i':
        /* Get the file. */
            arguments->file = arg;
            break;

        case 'n':
        /* Get the value to search. */
            arguments->number = atoi(arg);
            break;

        default:
        /* If unknown option, exit. */
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp_option options[] = {
    {"file", 'f', "FILE", 0, "The input file", 0},
    {"number", 'n', "NUMBER", 0, "Number to search", 0},
    {0}
};

static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = " ",
    .doc = "Program too check value in file",
};

int main(int argc, char * const argv[])
{
    struct args arguments;

    /* Initialise the arguments. */
    arguments.file = NULL;

    /* Parsing the arguments */
    argp_parse(&argp, argc, (char**)argv, 0, 0, &arguments);
    
    /* Input file checking*/
    if(arguments.file == NULL){
        printf("Input file not specified.\n");
        return 1;

    }

    /* Open input file*/
    FILE *file=fopen(arguments.file,"r");

    /* Make sure that it is opened*/
    if (file == NULL){

        printf("Error opening file %s",arguments.file);
    }

    /* Check in file if the number given is found */
    int number;
    int found = 0;

    while (fscanf(file, "%d", &number) != EOF) 
    {
        if (number == arguments.number) 
        {
            /*if found it will print this n times it will be found*/
            printf("Number %d exists in the file.\n", arguments.number);
            found = 1;
            break;
        }
    }
   

    fclose(file);

    /* If not found */
    if (found==0) 
    {
        printf("Number %d does not exist in the file.\n", arguments.number);
    }

    return EXIT_SUCCESS;
}
/*> Exemple de compilare si rulare a programului

$ gcc -g -o app3 app3.c
$ ./app3 -f test.txt -n 3

file:               ->          
tema1                Number 3 does not exist in the file

$ gcc -g -o app1 app1.c
$ ./app3 -f test.txt -n 3


file:               ->          
ce tema frumoasa 3               Number 3 exists in the file



*/
