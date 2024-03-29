/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 3 
 * 
 * Implementati un scurt program C pentru demonstrarea utilizarii functiei execvp
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
    fprintf(stdout, "\t 1.3 EXECVP Example: curl -o \n");
    fprintf(stdout, "\t ========================\n");


    switch(fork()) 
    {
        case -1: /* error */

            exit(EXIT_FAILURE);

        case 0: /* child */
        {
            /* Folosim execve sa executam comanda /snap/bin/curl */             
            execvp("curl",/* doar numele de program*/
            (char *[]){
            "curl",
            "-o",
            "save.html",
           "file:///home/negrea/PCD/Tema3/index.html", /* path pt site */           
            (char*) NULL
                   });

            /* printam informatii despre eroare */
            perror("execvp");
            abort(); /* daca execv da fail , genereaza core dump */
        }
        default: /* parent */
           { 
            /* asteapta pana child termina executia*/
            wait(NULL);
           }
    }


    exit(EXIT_SUCCESS);

}

/*> Exemple de compilare si rulare a programului

instalam sudo daca nu avem instalat in /snap
sudo snap install curl

daca exista which curl si aflam unde este path-ul pt curl

gcc -g -o app13 app13.c 
./app13

	 ========================
	 1.1 EXECVP Example: curl -o 
	 ========================
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   156  100   156    0     0  1586k      0 --:--:-- --:--:-- --:--:-- 1586k


si salveaza intr-un fisier save.html ce este in index.html:

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