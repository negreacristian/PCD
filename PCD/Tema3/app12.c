/**
 * Negrea Cristian
 * IR3 2024, subgrupa 4
 * Tema 3 
 * 
 * Implementati un scurt program C pentru demonstrarea utilizarii functiei execve
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
    fprintf(stdout, "\t 1.2 EXECVE Example: curl -o \n");
    fprintf(stdout, "\t ========================\n");


    switch(fork()) 
    {
        case -1: /* error */

            exit(EXIT_FAILURE);

        case 0: /* child */
        {
            /* Folosim execve sa executam comanda /snap/bin/curl */             
            execve("/snap/bin/curl",/* path-ul absolut*/
            (char *[]){
            "curl",
            "-o",
            "save.html",
           "file:///home/negrea/PCD/Tema3/index.html", /* path pt site */           
            (char*) NULL
            }, 
             (char *[]) {    /* vector de argumente , cast explicit la char * []*/
             "numesite=tema3",
             "numefisier=index.html",
             (char*) NULL 
                   });

            /* printam informatii despre eroare */
            perror("execve");
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

gcc -g -o app12 app12.c 
./app12
	 ========================
	 1.1 EXECVE Example: curl -o 
	 ========================
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100   156  100   156    0     0  1953k      0 --:--:-- --:--:-- --:--:-- 1953k

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