#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"fonction.h"
void TriGnome(int tab[], int n){
int i , temp ,z;
i=1;
while (i <= n)
{
    if (i == 1 || tab[i - 1] <= tab[i]){

    i++;
}
else
{
    temp = tab[i-1];
    tab[i - 1] = tab[i];
    tab[i] = temp;
    printf("Le tableau apres permutation : \n");
    for(z=1;z<=n;z++)
    {
        printf(" %d |",tab[z]);
    }
    printf("\n");
    i = i - 1;
}
}
}
int gnome()
{
int z, e, i, n, choix;
clock_t t1, t2;
float delta;
long int *tab;
printf("Donner n\n");
scanf("%d",&n);
tab= malloc(n*sizeof(long int *));
choixmultiple(tab, n);
printf("\n\n");
t1=clock();
TriGnome(tab, n);
t2=clock();
printf("\n");
delta =(t2-t1)/CLOCKS_PER_SEC;
Affichage(tab, n);

printf("complexity O");

printf("\nLe temps d'execution = %f secondes pour n = %d",delta,n);

return 0;
}
