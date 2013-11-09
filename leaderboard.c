#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <wchar.h>
#include <unistd.h>
#include "structures.h"
#include "unicode_art.h"
#include "prototypes.h"
#include "unicode_art.h"

void trimN(char *riga)
{
    int lung=strlen(riga);
    if (riga[lung-1]=='\n')
        riga[lung-1]='\0';
}
int parse_saveline(leaderboard *board, char *line)
{
    int val;
    board->entry[board->numentry].nome[0]='\0';
    val=sscanf(line,"%s%d%s",&(board->entry[board->numentry].nome),&(board->entry[board->numentry].score),&(board->entry[board->numentry].flags));
    board->numentry++;
    return (val==3);
}
int contarighe(FILE *dove)
{
    char ch;
    int ret=0;
    while (!feof(dove))
        {
        ch=fgetc(dove);
        if (ch=='\n')ret++;
        }
    fseek(dove,0,SEEK_SET);
    return ret;
}
void md5_4_humans(MD5_CTX *c, char* stringa)
{
    unsigned char digest[MD5_DIGEST_LENGTH];
    int i;
    MD5_Final(digest,c);
    for(i = 0; i < 16; ++i)
        sprintf(&stringa[i*2], "%02x", (unsigned int)digest[i]);
}
void printgameflags(vars *varia, char *str)
{
    switch (varia->gamemode&0b1111)
        {
        case vanilla: sprintf(str,"s");
        break;
        case doubled: sprintf(str,"d");
        break;
        case exponential: sprintf(str,"e");
        break;
        case russian: sprintf(str,"r");
        break;
        }
    if ((varia->gamemode&portals)!=0)
        {
        sprintf(&(str[strlen(str)]),"p");
        }
    if (varia->gioco.serpente.ai&assistedAI)
        {
        sprintf(&(str[strlen(str)]),"l");
        }
    sprintf(&(str[strlen(str)]),"%d",varia->speed);
    if (varia->gameover==2)
        {
        sprintf(&(str[strlen(str)]),"k");
        }
}
int update_savefile(char nome[maxnome], int score, char *filename,vars *varia)
{
    FILE *apri;
    MD5_CTX c;
    char nuovo=0;
    int cont;
    char buff[1024];
    char flags[scoreflags];
        flags[0]='\0';
    char nuovo5[hexmd5];
        nuovo5[0]='\0';
    apri=fopen(filename,"r");
    if (apri==NULL){apri=fopen(filename,"w"); nuovo=1;}
    if (apri==NULL)return 0;
    else
        { // aggiungi la nuova entry al file
        if (nuovo==1)
            { // riserva posto al md5
            for (cont=0; cont<hexmd5-1; cont++)fprintf(apri,"0");
            fprintf(apri," %s\n",lolstring);
            }
        else
            {
            fclose(apri);
            apri=fopen(filename,"a");
            }
        printgameflags(varia,flags);
        fprintf(apri,"%s\t%d\t%s\n",nome,score,flags);
        fclose(apri);
        MD5_Init(&c);
        apri=fopen(filename,"r");
        fgets(buff,1024,apri); // prima riga, ignorata
        buff[0]='\0';
        fgets(buff,1024,apri); //legge il file e crea il nuovo md5
        trimN(buff);
        if (feof(apri))MD5_Update(&c,buff,strlen(buff)*sizeof(char));
        while (!feof(apri)) // mi aspetto ultimo carattere= newline
            {
            MD5_Update(&c,buff,strlen(buff)*sizeof(char));
            buff[0]='\0';
            fgets(buff,1024,apri);
            trimN(buff);
            }
        fclose(apri);
        MD5_Update(&c,salt,strlen(salt)*sizeof(char));
        md5_4_humans(&c,nuovo5);
        apri=fopen(filename,"r+");
        fprintf(apri,"%s",nuovo5);
        fclose(apri);
        return 1;
        }
}
int comparaz(const void *a, const void *b)
{
    punteggio *uno=(punteggio *) a;
    punteggio *due=(punteggio *) b;
    return (uno->score<due->score);
}
void sort_punteggi(leaderboard *board)
{
    qsort(board->entry,board->numentry,sizeof(punteggio),comparaz);
}
void scrivi_punteggi(int top, int left, int num, vars *varia)
{
    int cont;
    move(top+cont,left);
    printw("Punteggi migliori:");
    for (cont=varia->board.curr; cont<varia->board.curr+num && cont<varia->board.numentry; cont++)
        {
        move(top+cont+1-varia->board.curr,left);
        printw("%3d)%11s %5d %6s",cont+1,varia->board.entry[cont].nome,varia->board.entry[cont].score,varia->board.entry[cont].flags);
        }
}
void printNexit(vars *varia, int num)
{
    int ret;
    end_gioco(varia);
    endNcurses();
    ret=open_savefile(&(varia->board),mainSaveFile);
    if (ret==-3)
        {
        printf("File salvataggi corrotto!\n");
        }
    else if (ret)
        {
        just_print(varia,num);
        }
    else
        {
        printf("Errore.\n");
        }
    free(varia->board.entry);
    exit(0);
}
void just_print(vars *varia, int num)
{
    int cont;
    printf("Punteggi migliori:\n");
    for (cont=varia->board.curr; cont<varia->board.curr+num && cont<varia->board.numentry; cont++)
        {
        printf("%3d)\t%11s\t%5d\t%6s\n",cont+1,varia->board.entry[cont].nome,varia->board.entry[cont].score,varia->board.entry[cont].flags);
        }
}
int open_savefile(leaderboard *board, char *filename)
{
    FILE *apri;
    int letti=0;
    int numrighe;
    char buff[1024];
    char primo[hexmd5];
    char test[hexmd5];
    MD5_CTX c;
    apri=fopen(filename,"r");
    if (apri==NULL)
        {
        board->numentry=0;
        return 0;
        }
    else
        {
        numrighe=contarighe(apri);
        board->numentry=0;
        board->entry=(punteggio *)malloc(sizeof(punteggio)*(numrighe-1));
        if (board->entry==NULL)
            {
            fclose(apri);
            return -1;
            }
        fgets(buff,1024,apri); // prima riga = checksum
        trimN(buff); // rimuove il carattere \n in fondo
        if (strlen(buff)<=(hexmd5-1))strcpy(primo,buff);
        else sscanf(buff,"%s",primo);

        MD5_Init(&c);
        fgets(buff,1024,apri);
        trimN(buff);
        if (feof(apri))
            {
            MD5_Update(&c,buff,strlen(buff)*sizeof(char));
            if (!parse_saveline(board,buff))
                {
                return -2;
                }
            }
        while (!feof(apri))
            {
            MD5_Update(&c,buff,strlen(buff)*sizeof(char));
            if (!parse_saveline(board,buff))
                {
                return -2;
                }
            fgets(buff,1024,apri);
            trimN(buff);
            }
        fclose(apri);
        MD5_Update(&c,salt,strlen(salt)*sizeof(char));
        md5_4_humans(&c,test);
        if (strcmp(test,primo)!=0)
            {
            free(board->entry);
            board->entry=NULL;
            board->numentry=0;
            return -3;
            }
        board->curr=0;
        sort_punteggi(board);
        return 1;
        }
}
