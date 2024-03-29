/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 3 
 * 
 * Implementati un scurt program C pentru demonstrarea utilizarii functiei execlp
 * 
 * Am tratat urmatoarele situatii limita care pot aparea in
 * contextul programului de mai jos :
 * -- daca aven eroare la fork
 * -- daca exec da fail atunci abort()
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[])

{   fprintf(stdout, "\t ========================\n");
    fprintf(stdout, "\t 1.6 EXECLP Example: curl \n");
    fprintf(stdout, "\t ========================\n");


    switch(fork()) 
    {
        case -1: /* error */

            exit(EXIT_FAILURE);

        case 0: /* child */
        {
            /* Folosim execve sa executam comanda /snap/bin/curl */             
            execlp("curl",/* programul direct */
            "curl",
            "file:///home/negrea/PCD/Tema3/index.html", /* path pt site */           
            (char*) NULL);
            

            perror("execlp");
        
            abort(); /* daca execv da fail , genereaza core dump */
        }
        default: /* parent */
           { 
            /* asteapta pana child termina executia*/
            wait(NULL);
           }
    }


  

}

/*> Exemple de compilare si rulare a programului

instalam sudo daca nu avem instalat in /snap
sudo snap install curl

daca exista which curl si aflam unde este path-ul pt curl

gcc -g -o app16 app16.c 
./app16
	 ========================
	 1.6 EXECLP Example: curl 
	 ========================
<!DOCTYPE html>
<html lang="en">
<head>

	<meta charset="UTF-8">
	<title>Tema3</title>
</head>

<body>
	<h1>Exemplu curl pentru tema 3</h1>
</body>
</html>


*/