/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Laboratorul 1
 * 
 * < Program C care primeste o optiune -f / --file pe linia de comanda
 *  (argument asociat obligatoriu) si deschide fisierul in modul scriere.
 *  Scriptul va inlocui toate aparitiile unui c1 citit de la STDIN cu
 *  c2 citit de pe linia de comanda, aferent optiunii -c2 / --character2. >
 *  + optiunea -l / --lines  cu valoarea n asociata 
 *    va afisa primele n linii din fisierul modificat
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- daca argumentele obligarii au fost transmise
 * -- daca fisierul nu se poate deschide
 * -- daca nu se poate scrie in fisier
 * -- daca nu se poate citi caracterul de la tastatura
 * -- daca nu se poate schimba pointerul in fisier
 */


#include <stdio.h> /* utilizat pentru: fprintf */
#include <stdlib.h> /* utilizat pentru: EXIT_SUCCESS, EXIT_FAILURE, atoi */
#include <getopt.h> /* utilizat pentru optiunim multiple de pe linia de comanda*/
#include <unistd.h> /* utilizat pentru read, write */
#include <fcntl.h> /* utilizat pentru file descriptor*/
#include <string.h> /* utilizat pentru: strstr */
#include <errno.h> /* utilizat pentru tratarea erorilor*/


/*Definim si valorile lungi --file si --character2*/
static struct option options[] = {
        {"file", required_argument, 0, 'f'},
        {"character2", required_argument, 0, 'c'},
        {"lines", required_argument, 0, 'l'},
        {0,0,0,0}
    };

static void errorAndExit(char * msg)
{
    fprintf(stderr, " [%s:%d] ERROR: %d {%s}\n",__FILE__,__LINE__,errno,strerror(errno)); /*eroare cu numarul erorii si statusul acesteia*/
    exit(errno); 

}

int main(int argc, char *argv[]) 

{
    /*stocam variabilele pentru optiuni, numefisier, caracterul de pe linia de comanda si cel de la STDIN*/
    char opt;
    char *filename = NULL;
    char c1;
    char c2; 
    int lines = 0;


    /* Procesarea argumentelor */ 

    while ((opt = getopt_long(argc, argv, "f:c:l:",options,NULL)) != -1) {
        switch (opt) { /* switch in functie de optiunea primita ca si argument*/
            case 'f':
            {
                /*atribuire nume fisier*/
                filename = optarg;
                break;

            }
            case 'c':
            {
                /*atribuire caracter ce v-a inlocuii*/    
                c2 = optarg[0];
                break;
            }
            case 'l':
            {
                lines = atoi(optarg);  /* convetim in int*/
                break;
            }

            case '?':
                /*apel functie eroare*/
                errorAndExit("Invalid option!");
                return 1;
        }
    }

    /* Deschidem fisierul in modul scriere */
    int fd = open(filename, O_RDWR | O_CREAT);

    /* Tratam cazul in care fisierul nu poate fi descris*/
    if (fd == -1) 
    {
        fprintf(stderr, "The file can't be opened");
        strerror(errno);
    }

    /* Citim caracterul c1 de la STDIN si afisam eroare daca nu este posibil*/

    if (read(STDIN_FILENO, &c1, 1) != 1) 
    {
        perror("Error reading character");
        close(fd);
        return 1;
    }

   
    
    char buffer[1024]; /*buffer pentru continut*/
    ssize_t bytes_read,bytes_written; /* variabile pentru a stoca numarul de bytes cititi si scrisi*/
    off_t offset; /* pointer in fisier*/
    
    /* Citire si scriere in fisier*/
   while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {

        /* trece prin fiecare byte citit si il prelucreaza*/
         for (int i = 0; i < bytes_read; ++i) {
            if (buffer[i] == c1) 
            {   
                /* inlocuieste caracterele de la STDIN cu caracterul de pe linia de comanda*/
                buffer[i] = c2;
            }
        }
        /* muta pointerul in fisier inapoi unde a fost citit*/
        offset = lseek(fd, -bytes_read, SEEK_CUR);
        if (offset == -1) {
             perror("Error seeking file");
             close(fd);
             return 1;
    }
         /* scrie in fisier bufferul modificat*/
        if (write(fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(fd);
            return 1;
       }

     
    }
    if (lines > 0) 
    {
    lseek(fd, 0, SEEK_SET);  /* muta pointerul la inceput*/

    char lineBuffer[1024]; 
    int lineCount = 0; /*numaram linilie*/

   /*citim linile si le afisam*/
    while (lineCount < lines && (bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {

        for (int i = 0; i < bytes_read && lineCount < lines; ++i) {
            /*afisam caracter cu caracter la STDOUT*/
            write(STDOUT_FILENO, &buffer[i], 1);
            /*daca e linie noua incrementam*/
            if (buffer[i] == '\n') {
                lineCount++;
            }
        }
    }
}
    close(fd);
    return 0;
}

/*> Exemple de compilare si rulare a programului

$ gcc -g -o app2 Negrea_Cristian_app2.c
$ ./app2 -f test.txt -c e -l 2
a

file:               ->          file changed:
ce                               ce 
tema                             teme 
frumoasa                         frumoese

STDOUT:
ce 
teme

$ gcc -g -o app1 Negrea_Cristian_app1.c
$ ./app1 --file test.txt --character2 a --lines 3
h

file:               ->          file changed:
ce                              ce 
tema                            teha  
frumoasa                        fruhoasa

STDOUT:
ce
teha
fruhoasa

*/
