/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Laboratorul 2
 * 
 * < Scrieti un script C in care un proces creeaza 7 procese copil.
 *  Procesul in cauza va astepta terminarea celui de-al treilea proces creat,
 *  dupa care va cere terminarea executiei tuturor celorlalte procese.
 *
 * 
 * 
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * daca copilul nu a fost creat 
 * daca a primit si alte argumente error
 */
#include <stdio.h> /* librarie pentru input output*/
#include <unistd.h> /* folosim fork si sleep*/
#include <stdlib.h> /* librarie standard pt exit() */
#include <sys/wait.h> /* wait() la sistem*/
#include <signal.h> /* folosim pt kill() */

int main(int argc,char* argv[])
{
    /* varibila pentru ID si setam numarul de procese copil */
    pid_t child;
    long numChilds = 7; 
    
    if(argc > 1)
    {
        perror("Nu e nevoie de argumente");
        exit(EXIT_FAILURE);
    }
    int i; /* index */
    pid_t third_child_pid = 0; /* variabila pentru a seta PID ul celui de al treilea proces*/

    for(i = 0; i <=numChilds; ++i)
    {
        child = fork(); /* creaza proces si verifica daca a fost creat */
        if(child < 0)
        {
            perror("Forking new child");
            exit(EXIT_FAILURE);
        }
        else if(child == 0) /* proces copil afisare detalii*/
        {
            printf("Child no. %d [PID=%d, PPID=%d]\n", i + 1, (int)getpid(), (int)getppid());

            sleep(5); /* sleep ca sa putem vedea ce se intampla */
  
            exit(EXIT_SUCCESS); 
        }
        else 
        {   
            /* verifica daca e al treilea copil */
            if(i == 2) 
            {
                third_child_pid = child; 
                /* salveaza ID pentru al treilea copil*/
                /* asteapta sa termina al treilea copil */
                waitpid(third_child_pid, NULL, 0); 
                printf("Third child terminated. Now will terminate other children.\n");
            }
        }
    }

    for(i = 0; i <=numChilds; ++i) /*verifica in toate procesele copil */
    {
        if(child > 0 && i != 2) 
        {
            kill(child, SIGKILL); /* termina toate procesele */
            waitpid(child, NULL, 0); 
        }
    }

    exit(EXIT_SUCCESS); /* termina procesul parinte*/
}



/*> Exemple de compilare si rulare a programului


gcc -g -o app1 APP1.c 

 ./app1

Child no. 1 [PID=115713, PPID=115712]
Child no. 2 [PID=115714, PPID=115712]
Child no. 3 [PID=115715, PPID=115712]

wait and then

Third child terminated. Now will terminate other children.
Child no. 4 [PID=115718, PPID=115712]
Child no. 5 [PID=115719, PPID=115712]
Child no. 6 [PID=115720, PPID=115712]
Child no. 7 [PID=115721, PPID=115712]

./app1 3
Nu e nevoie de argumente

*/


