#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  FILE* fichier = NULL;

 char* forme = malloc(11*sizeof(char));
 int i,j;

 fichier = fopen("pentomino.txt","r");

 if (fichier != NULL)
   {
     for (i=0;i<80;i++)
       {
	 fgets(forme,11,fichier);
	 printf("%s",forme);
       }
     fclose(fichier);
   }
 return 0;
}
