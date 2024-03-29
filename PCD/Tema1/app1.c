/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 1
 * 
 * < O aplicatie C, denumita app1.c in care sa exemplificati la alegere,
 *  utilizarea functiei getopt_long(). Aplicatia ar trebui
 *  sa accepte mai multe optiuni pe linia de comanda -f (--fisier ) si
 *  optional -c (--character ). Aplicatia va procesa optiunile folosind 
 *  getopt_long() si va extrage numele fisierului si o litera. 
 *  Daca nu este atribuit nici o litera afiseaza 0 daca este atribuit 
 *  numara cate litere sunt in text.
 * 
 * Probleme cu Segmentation Fault - nu ruleaza cu argument optional si primeste argumentul.
 *
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- daca argumentele obligarii au fost transmise
 * -- daca fisierul nu se poate deschide
 */


#include <stdio.h> /* utilizat pentru: fprintf */
#include <stdlib.h> /* utilizat pentru: EXIT_SUCCESS, EXIT_FAILURE, atoi */
#include <getopt.h> /* utilizat pentru optiunim multiple de pe linia de comanda*/
#include <unistd.h> /* utilizat pentru read, write */
#include <fcntl.h> /* utilizat pentru file descriptor*/
#include <string.h> /* utilizat pentru: strstr */
#include <errno.h> /* utilizat pentru tratarea erorilor*/


/*Definim si valorile lungi --file si --character*/
static struct option options[] = {
        {"fisier", required_argument, 0, 'f'},
        {"character", required_argument, 0, 'c'},
        {0,0,0,0}
    };

static void errorAndExit(char * msg)
{
    fprintf(stderr, " [%s:%d] ERROR: %d {%s}\n",__FILE__,__LINE__,errno,strerror(errno)); /*eroare cu numarul erorii si statusul acesteia*/
    exit(errno); 

}

int main(int argc, char *argv[]) 

{
    /*stocam variabilele pentru optiuni, numefisier,caracter si numarul de litere*/
    char opt;
    char *filename = NULL;
    char c='\0';
    int numara=0;

    /* Procesarea argumentelor */ 

    while ((opt = getopt_long(argc, argv, "f:c:",options,NULL)) != -1) {
        switch (opt) { /* switch in functie de optiunea primita ca si argument*/
            case 'f':
            {
                /*atribuire nume fisier*/
                filename = optarg;
                break;

            }
            case 'c':
            {
                c = optarg[0];
                break;
            }
            case '?':
                /*apel functie eroare*/
                errorAndExit("Invalid option!");
                return 1;
        }
    }

    /* Deschidem fisierul in modul scriere */
    int fd = open(filename, O_RDONLY , 0666);

    /* Tratam cazul in care fisierul nu poate fi deschis*/
    if (fd == -1) 
    {
        fprintf(stderr, "The file can't be opened");
        strerror(errno);
    }
     
    char buffer[1024]; /*buffer pentru continut*/
    ssize_t bytes_read; /* variabile pentru a stoca numarul de bytes cititi si scrisi*/
    
    
    /* Citire si scriere in fisier*/
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {

        /* trece prin fiecare byte citit si il prelucreaza*/
         for (int i = 0; i < bytes_read; ++i) {
            if (buffer[i] == c) 
            {   
                /*numara cate caractere sunt*/
                numara++;
            }
        }

    
       
      
    }
    if (bytes_read == -1) {

        fprintf(stderr, "Error reading the file");
        close(fd);
        return 1;
}


    printf("%d\n", numara);

    
    close(fd);
    return 0;
}

/*> Exemple de compilare si rulare a programului

$ gcc -g -o app1 app1.c
$ ./app1 -f test.txt -c e

file:               ->          
ce tema frumoasa                2

$ gcc -g -o app1 app1.c
$ ./app1 --file test.txt --character a


file:               ->          
ce tema frumoasa                3



*/
