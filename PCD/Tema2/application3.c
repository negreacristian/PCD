/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 2
 * 
 * < Scrieti un script C care implementeaza comanda ps. O implementare
 *  custom pentru aceasta comanda presupune, pentru cerinta actuala,
 *  ca intreaga lista de procese active pe sistem sa fie traversata si,
 *  pentru fiecare proces, afisat numele sau, precum si identificatorii 
 * sai (PID, PPID, GID, EGID, UID, EUID, respectiv identificatorul de grup).
 * Nu se vor folosi in implementare: apeluri de tipul system sau exec
 *  (trebuie sa va folositi de alte mijloace pentru a implementa manual aceasta functionalitate).
 *  Acolo unde folositi operatii I/O low-level, nu veti folosi alte apeluri sistem
 *  decat cele standard (open, write, read, close).
 * 
 * O sursa foarte utila pentru intelegerea si implementarea cerintei date: https://man7.org/linux/man-pages/man5/proc.5.html 
 * Indicatie. pentru cerinta 3, raportati-va la fisierul system `/proc`!
 *
 * 
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- daca argumentele obligarii au fost transmise
 * -- daca fisierul nu se poate deschide
 * -- daca nu se poate scrie in fisier
 * -- daca nu se poate citi caracterul de la tastatura
 * -- daca nu se poate schimba pointerul in fisier
 */

#include <stdio.h> /* librarie pentru input output*/
#include <unistd.h> /* folosim fork si sleep*/
#include <stdlib.h> /* librarie standard pt exit() */
#include <sys/wait.h> /* wait() la sistem*/
#include <signal.h> /* folosim pt kill() */

int main(int argc, char * argv[])
{
    pid_t child;
    long numChilds = strtol(argv[1], NULL, 10);
    
    if(numChilds <= 0 || argc != 2)
    {
        fprintf(stderr, "Usage: %s <num_childs>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int i;
    for(i = 0;i < numChilds;i ++)
    {
        child = fork();
        if(child < 0)
        {
            perror("Forking new child");
            exit(EXIT_FAILURE);
        }
        else if(child == 0)
        {
            fprintf(stdout, "Child no. %d [PID=%d, PPID=%d]\n", i, (int)getpid(), (int)getppid());
        }
        else
        {
            break;
        }
    }

    wait(NULL);


    exit(EXIT_SUCCESS);
}