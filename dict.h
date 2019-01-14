#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#define HASHSIZE 3169
#define MAXLEN 46



typedef struct node{
char data[MAXLEN];
struct node *link;
}llist;

llist *hashtable[HASHSIZE];



int totalwords =0;



int get_bucket(char* str){
int i,sum=0;
int len=strlen(str);
for(i=0;i<len;i++)
sum+=str[i];
return sum%HASHSIZE;
}



void load_dictionary()
{
int i, n;
char word[MAXLEN];
for(i=0;i<HASHSIZE;i++)
hashtable[i]=NULL;
FILE *dict;
dict=fopen("wordsEn.txt","r");
if(dict==NULL)
printf("Error while loading dictionary \n");
else{
while(fscanf(dict,"%s",word)!=EOF){
llist *newnode;
newnode=(llist*)malloc(sizeof(*newnode));
newnode->link=NULL;
strcpy(newnode->data, word);
n=get_bucket(word);
if(hashtable[n]==NULL)
hashtable[n]=newnode;
else{
newnode->link=hashtable[n];
hashtable[n]=newnode;
}
totalwords++;
}}
fclose(dict);
}


void unloaddictionary(){
int i;
for(i=0;i<HASHSIZE;i++){
llist* pos=hashtable[i];
while(pos!=NULL){
llist* temp=pos;
pos=pos->link;
free(temp);
}}
}



int size(){
return totalwords;
}


bool spell_check(char *str){
int i,n,len=strlen(str);
llist *temp;
char word[MAXLEN];
for(i=0;i<len;i++){
if(isupper(str[i]))
word[i]=tolower(str[i]);
else
word[i]=str[i];
}
word[len]='\0';
n=get_bucket(word);
temp=hashtable[n];
while(temp!=NULL){
if(strcmp(temp->data,word)==0)
return true;
temp=temp->link;
}
return false;
}



