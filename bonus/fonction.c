// #include<stdio.h>
// #include<stdbool.h>
// #include<stdlib.h>
// #include<time.h>
// #include<string.h>
// // #include"triabulle.h"

// void Affichage( int tab[], int n)
// { int i;
// printf("Le tableau apres le tri finale : \n");
// for(i=1;i<=n;i++)
// {
// printf(" %d | ",tab[i]);
// }
// printf("\n");
// }

// void permuter(int* a, int* b)
// {
// int c;
// c=*a; // 1
// *a=*b; // 1
// *b=c; // 1
// }
// int choixmultiple(int tab[], int n)
// { int i,choix;
// printf("Choisissez si vous voulez un tableau dans : \n1/Le pire cas tapez 1 \n2/Le meilleur cas tapez 2 \n3/Le moyen cas tapez 3 \n");
// scanf("%d",&choix);
// switch(choix)
// {
// case 1://pire cas
// {
// for(i=1;i<=n;i++)
// {
// tab[i]=n-i;
// }
// break;
// }
// case 2:// best case
// {
// for(i=1;i<=n;i++)
// {
// tab[i]=i;
// }
// break;
// }
// case 3:// moyen cas
// {
// for(i=1;i<=n;i++)
// {
// tab[i]=rand();
// }
// break;
// }
// }
// printf("Le tableau avant le tri : \n");
// for(i=1;i<=n;i++)
// {
// printf(" %d | ",tab[i]);
// }
// return tab;
// }

/*void continuer(){
int con;
printf("\n\nSi vous voulez continuez tapez sur 1\n");
scanf("%d",&con);
if(con==1){
main();
}
else {
return 0;
}
}*/
#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// #include"triabulle.h"

void Affichage( int tab[], int n)
{ int i;
printf("Le tableau apres le tri finale : \n");
for(i=1;i<=n;i++)
{
printf(" %d | ",tab[i]);
}
printf("\n");
}

void permuter(int* a, int* b)
{
int c;
c=*a; // 1
*a=*b; // 1
*b=c; // 1
}
int choixmultiple(int tab[], int n)
{ int i,choix;
printf("Choisissez si vous voulez un tableau dans : \n1/Le pire cas tapez 1 \n2/Le meilleur cas tapez 2 \n3/Le moyen cas tapez 3 \n");
scanf("%d",&choix);
switch(choix)
{
case 1://pire cas
{
for(i=1;i<=n;i++)
{
tab[i]=n-i;
}
break;
}
case 2:// best case
{
for(i=1;i<=n;i++)
{
tab[i]=i;
}
break;
}
case 3:// moyen cas
{
for(i=1;i<=n;i++)
{
tab[i]=rand();
}
break;
}
}
printf("Le tableau avant le tri : \n");
for(i=1;i<=n;i++)
{
printf(" %d | ",tab[i]);
}
return tab;
}