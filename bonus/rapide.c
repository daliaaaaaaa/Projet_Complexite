#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include"fonction.h"
// premiere position du pivot
int partitionner(int tab[], int first, int last, int n)
{

int pivot =first;
int i = first;
int j = last;

while (i < j)
{
    while(tab[i] <= tab[pivot]&& i < last)
    i++;
    while(tab[j] > tab[pivot] && j> first)
    j--;
    if(i < j)
    {
        permuter(&tab[i], &tab[j]);
        i++;
        j--;
    }
}

if (j != first)
permuter(&tab[pivot], &tab[j]);
return j;

}

// premiere position du pivot
void triRapide(int tab[], int first, int last,int n)
{
int i, j;
if(first < last)
{
    j=partitionner(tab, first, last, n);
    triRapide(tab, first, j - 1, n);
    printf("La recursivite dans la partie droite du tableau : \n");
    for(i=1;i<= n;i++)
    {
        printf(" %d | ",tab[i]);
    }
    printf("\n");
    triRapide(tab, j + 1, last, n);
    printf("La recursivite dans la partie gauche du tableau : \n");
    for(i=1;i<= n;i++)
    {
        printf(" %d | ",tab[i]);
    }
    printf("\n");
}
}
///////////////////////////////////////////////
// derniere position du pivot
int partitionnerlast(int tab[], int first, int last, int n)
{

int pivot = last;
int i = first;
int j = last;

while (i < j)
{
    while(tab[i] <= tab[pivot] && i < last)
    i++;
    while(tab[j] > tab[pivot] && j> first)
    j--;
    if(i < j)
    {
        permuter(&tab[i], &tab[j]);
    }


}
if (j != last)
permuter(&tab[pivot], &tab[j]);
return j;

}

// derniere position du pivot
void triRapidelast(int tab[], int first, int last,int n)
{
int i, j;
if(first < last)
{
    j=partitionnerlast(tab, first, last, n);
    triRapidelast(tab, first, j - 1, n);
    printf("La recursivite dans la partie droite du tableau : \n");
    for(i=1;i<= n;i++)
    {
        printf(" %d | ",tab[i]);
    }
    printf("\n");
    triRapidelast(tab, j + 1, last, n);
    printf("La recursivite dans la partie gauche du tableau : \n");
    for(i=1;i<= n;i++)
    {
        printf(" %d | ",tab[i]);
    }
    printf("\n");
}
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////
// position aleatoire du pivot
/*int partitionnerrand(int tab[], int first, int last, int n)
{

int pivot = rand()%n;
int i = first;
int j = last;
printf("Le pivot = %d : \n",pivot);
while (i < j)
{
    while(tab[i] <= tab[pivot] && i < last)
    i++;
    while(tab[j] > tab[pivot] && j> first)
    j--;
    if(i < j)
    {
        permuter(&tab[i], &tab[j]);
        i++;
        j--;
    }
}
if (j != pivot)
permuter(&tab[pivot], &tab[j]);

return j;

}*/
////////////////////////////////////////////////////

int partitionn(int tab[], int first, int last)
{
int pivot = tab[first];
int i = first - 1, j = last + 1;
while (1) {
    do {
        i++;
    }
    while (tab[i] < pivot);
    do {
    j--;
    }
    while (tab[j] > pivot);
        if (i >= j)
    return j;

    int temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}
}


int partitionner_r(int tab[], int first, int last ,int n)
{
srand(time(0));
int random = first + rand() % (last - first);
int temp = tab[random];
tab[random] = tab[first];
tab[first] = temp;
return partitionn(tab, first, last);
}

// position aleatoire du pivot
void triRapiderand(int tab[], int first, int last,int n)
{
int i, j;
if(first < last)
{
    j=partitionner_r(tab, first, last, n);
    triRapiderand(tab, first, j - 1, n);
    triRapiderand(tab, j + 1, last, n);
    printf("\n");
}
}
///////////////////////////////////////////////////////////
int rapide()
{
int n, i,choix;
clock_t t1,t2;
float delta;
long int *tab;
printf("Donner n\n");
scanf("%d",&n);
tab= malloc(n*sizeof(long int *));

choixmultiple(tab, n);
printf("\n\n");

printf("Choisissez si vous voulez un pivot dans : \n1/La premiere position du tableau 1 \n2/La derniere position du tableau 2 \n3/une position aleatoire 3 \n");
scanf("%d",&choix);
switch(choix)
{
case 1:
{ t1=clock();
triRapide(tab, 1, n, n);// premiere position du pivot
t2=clock();
break;
}
case 2:
{
t1=clock();
triRapidelast(tab, 1, n, n);
t2=clock();
break;
}
case 3:
{
t1=clock();
triRapiderand(tab, 1, n, n);
t2=clock();
break;
}
}

printf("\n");
delta =(t2-t1)/CLOCKS_PER_SEC;
Affichage(tab, n);
printf("\nLe temps d'execution = %f secondes pour n = %d",delta,n);

return 0;
}
