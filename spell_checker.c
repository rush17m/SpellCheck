#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>
#include"dict.h"

typedef struct node1{
int pos;
char data[46];
struct node1 *link;
}*misspelled;

misspelled first, ptr=NULL;



void main(){
int j=0,k=0;
char i;
char filename[50], wordindoc[46];
load_dictionary();
printf("Enter name of file to be spell checked (Ensure it is a .txt file)\n");
scanf("%s",filename);
strcat(filename,".txt");
FILE *fptr=fopen(filename,"r");
if(fptr==NULL){
printf("Error opening document to be spell checked \n");
exit(0);}
for(i=fgetc(fptr);i!=EOF;i=fgetc(fptr)){
if(isalpha(i)){
wordindoc[j]=i;
j++;}
else if(i=='\''){
i=fgetc(fptr);
if(i=='s')
continue;
else if(isspace(i)){
wordindoc[j]='\0';
k++;
if((spell_check(wordindoc))==false){
misspelled temp;
temp=(misspelled)malloc(sizeof(*temp));
temp->pos=k;
strcpy(temp->data,wordindoc);
temp->link=NULL;
if(first)
ptr->link=temp;
else
first=temp;
ptr=temp;
}
j=0;}

else{
wordindoc[j]=i;
j++;
}
}
else if(isdigit(i)){
while((i=fgetc(fptr))!=EOF && !isspace(i));
j=0;
}
else if(j>0){
wordindoc[j]='\0';
k++;
if((spell_check(wordindoc))==false){
misspelled temp;
temp=(misspelled)malloc(sizeof(*temp));
temp->pos=k;
strcpy(temp->data,wordindoc);
temp->link=NULL;
if(first)
ptr->link=temp;
else
first=temp;
ptr=temp;
}
j=0;}}
fclose(fptr);
printf("\nWords Missplled: \nIndex\tWord\n");
if(ptr==NULL)
printf("No misspelled words.\n");
else
{
misspelled temp=first;
while(temp!=NULL){
printf("%d\t%s\n",temp->pos,temp->data);
temp=temp->link;
}}
unloaddictionary();
}
