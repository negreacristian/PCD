/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 2
 * 
 * < Scrieti un script C care va crea urmatoarea ierarhie de procese,
 *  pentru n numar natural nenul, primit pe linia de comanda.
 *  Scriptul va primi valoarea lui p care va fi asociata optiunii -p sau –processes.
 * 
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * 

 * -- daca argumentele obligarii au fost transmise
 * -- daca valoare este diferita de 0 si pozitiva
 * -- daca este un numar incorect de argumente mai mare sau mai mic
 * -- daca optiunea e incorecta
 * -- daca exista erori la creare fork-urilor
 */


#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Pastram argumentele intr-un struct */
struct args {
    int number;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct args *arguments = state->input;
    long int val;
    char *endptr;

    /* Verificam argumentele  */
    switch (key) {
        /* Luam numarul proceselor */
        case 'p':
        
            /* Verificam daca numarul e de tip int */
            val = strtol(arg, &endptr, 10); /* facem conversie in longint*/

            /* verificam daca e pozitiv */
            if (*endptr != '\0' || val <= 0) { 
                argp_error(state, "Numar invalid de procese sau valoare invalida ");
            }
            arguments->number = (int)val;
            break;

        default:
        /* If unknown option, exit. */
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp_option options[] = {
    {"processes", 'p', "PROCESSES", 0, "Numarul de procese ce trebuie create", 0},
    {0}
};

static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = " ",
    .doc = "Creaza un numar de procese",
};

int main(int argc, char * const argv[])
{
    struct args arguments;
    pid_t parentB,parent0;
  

    /* Initializam argumentul cu 0*/
    arguments.number = 0;

    /* Verifcam numarul de argumente de pe linia de comanda */
    if (argc < 2) { 
        fprintf(stderr, "Prea putine argumente \n");
        return 1;
    }

    /* parsam argumentele */
    if (argp_parse(&argp, argc, (char **)argv, 0, 0, &arguments) != 0) {
        fprintf(stderr, "Erroare la parsare argumentelor \n");
        return 1;
    }

    /* Procesul A*/
    printf("Proces[A] PID %d PPID %d\n", (int)getpid(),(int)getppid());

    parentB = fork();
    if (parentB < 0) {
        /* Eroare la fork*/
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (parentB == 0) {
       /* Procesul B*/

        printf("Proces[B] PID %d PPID %d\n", (int)getpid(),(int)getppid());
        
        parent0=fork();

        if(parent0 < 0 )
        {
            /* Eroare la fork*/
            perror("Fork failed");
            exit(EXIT_FAILURE);

        } else if(parent0 == 0 )
        {
            /* Procesul 0*/

            printf("Proces[0] PID %d PPID %d\n", (int)getpid(),(int)getppid());

            for (int i = 1 ;i <=arguments.number; ++i) {
            if (fork() == 0) {
                /* Aici scriem fiecare proces copil din piaptan*/
                printf("Proces[%d] PID %d PPID %d\n", i, (int)getpid(), (int)getppid());
                exit(EXIT_FAILURE);
                
            }
            wait(NULL);
            }
        exit(EXIT_FAILURE); /* Procesul 0 se termina */  
        }
        wait(NULL); /* procesul B asteapta terminarea procesului 0*/
        exit(EXIT_FAILURE);
    } else {

        wait(NULL); /* Așteptăm să se termine procesul B */ 
       
        
    }
    
    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului

gcc -g -o app1 application1.c 


./app1 -p 5
Proces[A] PID 13673 PPID 13268
Proces[B] PID 13674 PPID 13673
Proces[0] PID 13675 PPID 13674
Proces[1] PID 13676 PPID 13675
Proces[2] PID 13677 PPID 13675
Proces[3] PID 13678 PPID 13675
Proces[4] PID 13679 PPID 13675
Proces[5] PID 13680 PPID 13675

./app1 --processes 3

Proces[A] PID 13659 PPID 13268
Proces[B] PID 13660 PPID 13659
Proces[0] PID 13661 PPID 13660
Proces[1] PID 13662 PPID 13661
Proces[2] PID 13663 PPID 13661
Proces[3] PID 13664 PPID 13661

./app1 -processes 
app1: Numar invalid de procese sau valoare invalida 

./app1 -processes -2
app1: Numar invalid de procese sau valoare invalida 

./app1 -p 5 a b 
app1: Too many arguments

./app1 --processes 5 5
app1: Too many arguments
*/