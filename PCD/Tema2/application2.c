/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 2
 * 
 * < mbunatatiti aplicatia de la punctul 1,
 *  pentru a putea permite si o optiune -s sau –subprocesses,
 *  care primeste ca si valoare asociata un numar pozitiv intreg,
 *  si creaza urmatoarea ierarhie de procese:

 * 
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * 

 * -- daca argumentele obligarii au fost transmise
 * -- daca valoare este diferita de 0 si pozitiva
 * -- daca este un numar incorect de argumente mai mare sau mai mic
 * -- daca optiunile sunt incorecte
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
    int subnumber;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct args *arguments = state->input;
    long int val,val2;
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

        /* Luam numarul subproceselor */
        case 's':
        
            /* Verificam daca numarul e de tip int */
            val2 = strtol(arg, &endptr, 10); /* facem conversie in longint*/

            /* verificam daca e pozitiv */
            if (*endptr != '\0' || val2 <= 0) { 
                argp_error(state, "Numar invalid de procese sau valoare invalida ");
            }
            arguments->subnumber = (int)val2;
            break;

        default:
        /* If unknown option, exit. */
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp_option options[] = {
    {"processes", 'p', "PROCESSES", 0, "Numarul de procese ce trebuie create", 0},
    {"subprocesses", 's', "SUBPROCESSES", 0, "Numarul de subprocese ce trebuie create", 0},
    {0}
};

static struct argp argp = {
    .options = options,
    .parser = parse_opt,
    .args_doc = " ",
    .doc = "Creaza un numar de procese si un numar de subprocese fiecarui proces creat",
};

int main(int argc, char * const argv[])
{
    struct args arguments;
    pid_t parentB,parent0,child;
  

    /* Initializam argumentul cu 0*/
    arguments.number = 0;
    arguments.subnumber=0;

    /* Verifcam numarul de argumente de pe linia de comanda */
    if (argc < 4) { 
        fprintf(stderr, "Prea putine argumente \n");
        return 1;
    }

    /* parsam argumentele */
    if (argp_parse(&argp, argc, (char **)argv, 0, 0, &arguments) != 0) {
        fprintf(stderr, "Erroare la parsare argumentelor \n");
        return 1;
    }

     /*procesul  A */
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
            child=fork();
            if(child< 0 )
            {
            /* Eroare la fork*/
            perror("Fork failed");
            exit(EXIT_FAILURE);

            }    else if (child== 0) 
                {
                /* Aici scriem fiecare proces copil din piaptan*/
                printf("Proces[%d] PID %d PPID %d\n", i, (int)getpid(), (int)getppid());
                
                
                for (int j = 1; j <=arguments.subnumber; ++j) {
                child = fork();
                if(child < 0)
                {
                      /* Eroare la fork*/
                    perror("Fork failed");
                    exit(EXIT_FAILURE);
                } else if (child == 0) 
                {
                    /* Suntem în subproces */
                    printf("Subproces[%d.%d] PID %d PPID %d\n", i, j, (int)getpid(), (int)getppid());
                    exit(EXIT_FAILURE);
                } else 
                {
                    wait(NULL); /* Așteptăm terminarea subprocesului */
                  
                }
                }
                exit(EXIT_FAILURE);
            }
            wait(NULL);
            }
        exit(EXIT_FAILURE); /* Procesul 0 se termina  */
        }
        wait(NULL); /* procesul B asteapta terminarea procesului 0*/
        exit(EXIT_FAILURE);
    } else {

        wait(NULL); /* Așteptăm să se termine procesul B */
       
        
    }
    
    return EXIT_SUCCESS;
}

/*> Exemple de compilare si rulare a programului

gcc -g -o app2 application2.c 

./app2 -p 3 -s 2

Proces[A] PID 14465 PPID 13756
ProceD 14467 PPID 14466
Proces[1] PID 1s[B] PID 14466 PPID 14465
Proces[0] PI4468 PPID 14467
Subproces[1.1] PID 14469 PPID 14468
Subproces[1.2] PID 14470 PPID 14468
Proces[2] PID 14471 PPID 14467
Subproces[2.1] PID 14472 PPID 14471
Subproces[2.2] PID 14473 PPID 14471
Proces[3] PID 14474 PPID 14467
Subproces[3.1] PID 14475 PPID 14474
Subproces[3.2] PID 14476 PPID 14474

./app2 --processes 3 -subprocesses 3

Proces[A] PID 14477 PPID 13756
Proces[B] PID 14478 PPID 14477
Proces[0] PID 14479 PPID 14478
Proces[1] PID 14480 PPID 14479
Subproces[1.1] PID 14481 PPID 14480
Subproces[1.2] PID 14482 PPID 14480
Subproces[1.3] PID 14483 PPID 14480
Proces[2] PID 14484 PPID 14479
Subproces[2.1] PID 14485 PPID 14484
Subproces[2.2] PID 14486 PPID 14484
Subproces[2.3] PID 14487 PPID 14484
Proces[3] PID 14488 PPID 14479
Subproces[3.1] PID 14489 PPID 14488
Subproces[3.2] PID 14490 PPID 14488
Subproces[3.3] PID 14491 PPID 14488

./app2 -p 3 
Prea putine argumente 

./app2 -p 3 -s 2 p
app2: Too many arguments

./app2 --processes 5 --subprocesses 2 
Proces[A] PID 111795 PPID 111498
Proces[B] PID 111796 PPID 111795
Proces[0] PID 111797 PPID 111796
Proces[1] PID 111798 PPID 111797
Subproces[1.1] PID 111799 PPID 111798
Subproces[1.2] PID 111800 PPID 111798
Proces[2] PID 111801 PPID 111797
Subproces[2.1] PID 111802 PPID 111801
Subproces[2.2] PID 111803 PPID 111801
Proces[3] PID 111804 PPID 111797
Subproces[3.1] PID 111805 PPID 111804
Subproces[3.2] PID 111806 PPID 111804
Proces[4] PID 111807 PPID 111797
Subproces[4.1] PID 111808 PPID 111807
Subproces[4.2] PID 111809 PPID 111807
Proces[5] PID 111810 PPID 111797
Subproces[5.1] PID 111811 PPID 111810
Subproces[5.2] PID 111812 PPID 111810

*/