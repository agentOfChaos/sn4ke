#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include <math.h>
#include <locale.h>
#include "structures.h"
#include "unicode_art.h"
#include "prototypes.h"
#include "unicode_art.h"

vars globali;
int crea_snacache(char ***board, int maxx, int maxy)
{
    int cont,r;
    (*board)=(char **)malloc(sizeof(char*)*maxx);
    if ((*board)==NULL) return 0;
    for (cont=0; cont<maxx; cont++)
        {
        (*board)[cont]=(char*)malloc(sizeof(char)*maxy);
        if ((*board)[cont]==NULL)
            {
            for (r=0; r<=cont; r++) free((*board)[cont]);
            return 0;
            }
        }
    return 1;
}
void blank_snacache(char **board, int maxx, int maxy)
{
    int x,y;
    for (x=0; x<maxx; x++)
        {
        for (y=0; y<maxy; y++)
            {
            board[x][y]=0;
            }
        }
}
void dump_snacache(char **board, int maxx, int maxy)
{
    int x,y;
    for (y=0; y<maxy; y++)
        {
        for (x=0; x<maxx; x++)
            {
            printw("%d",board[x][y]);
            }
        printw("\n");
        }
}
void regen_snacache(snake *chi, int maxx,int maxy)
{
    int cont;
    blank_snacache(chi->cache,maxx,maxy);
    for (cont=0; cont<chi->numsezioni; cont++)chi->cache[chi->sezioni[cont].x][chi->sezioni[cont].y]=1;
}
void kill_snacache(char ***board)
{
    free(*board);
    (*board)=NULL;
}
int creaserpente(snake *chi,int startx,int starty,int maxx,int maxy)
{
    chi->direz=0;
    chi->scheduledir=0;
    chi->numsezioni=1;
    chi->portalcross=0;
    chi->ate=0;
    chi->keepexp=0;
    chi->sezioni=(punto*)malloc(sizeof(punto)*maxx*maxy);
    if (chi->sezioni==NULL) return -1;
    if (!crea_snacache(&(chi->cache),maxx,maxy))return -1;
    chi->sezioni[0].x=startx;
    chi->sezioni[0].y=starty;
    regen_snacache(chi,maxx,maxy);
    return 1;
}
int creacampo(campo *dove)
{
    dove->numpowerups=0;
    dove->numportals=0;
    dove->toblast=NULL;
    dove->powerup=(punto*)malloc(sizeof(punto)*dove->larg*dove->alt);
    if (dove->powerup==NULL) return -1;
    if (creaserpente(&(dove->serpente),dove->larg/2,dove->alt/2,dove->larg,dove->alt)<=0) return -2;
    return 1;
}
void start_gioco(vars *varia)
{
    int ret;
    ret=creacampo(&(varia->gioco));
    if (ret==-1)
        {
        printw("Creazione del campo fallita\n");
        exit(-1);
        }
    else if (ret==-2)
        {
        printw("Creazione del serpente fallita\n");
        exit(-2);
        }
    varia->score=0;
    varia->quit=0;
    varia->game_insane=0;
    varia->paused=0;
    varia->gameover=0;
    varia->gioco.nextportime=0;
}
void end_gioco(vars *varia)
{
    kill_snacache(&(varia->gioco.serpente.cache));
    free(varia->gioco.serpente.sezioni);
    free(varia->gioco.powerup);
}
void init_colori(vars *varia)
{
    if (has_colors() == FALSE)
        {
        varia->colori=0;
        }
    else
        {
        varia->colori=1;
        start_color();
        init_pair(color_portal(0), COLOR_RED, COLOR_BLACK);
        init_pair(color_portal(1), COLOR_BLUE, COLOR_BLACK);
        init_pair(color_wall, COLOR_YELLOW, COLOR_BLACK);
        init_pair(color_snake, COLOR_GREEN, COLOR_BLACK);
        init_pair(color_food, COLOR_MAGENTA, COLOR_BLACK);

        }
}
void startNcurses(int *larg, int *alt)
{
    initscr();
	clear();
	//cbreak();
    timeout(0);
    noecho();
    keypad (stdscr, TRUE);
    getmaxyx(stdscr,*alt,*larg);
    if ((*larg)%2!=0)(*larg)--;
    if ((*alt)%2!=0)(*alt)--;
    (*larg)=(*larg)-2;
    (*alt)=(*alt)-2;
    (*larg)=(*larg)/2;
}
void endNcurses()
{
    endwin();
}
void riprova(vars *varia)
{
    varia->paused=0;
    varia->quit=0;
    varia->score=0;
    varia->gameover=0;
    varia->gioco.numportals=0;
    varia->gioco.nextportime=0;
    varia->gioco.numpowerups=0;
    varia->gioco.toblast=NULL;
    varia->gioco.serpente.numsezioni=1;
    varia->gioco.serpente.sezioni[0].x=varia->gioco.larg/2;
    varia->gioco.serpente.sezioni[0].y=varia->gioco.alt/2;
    regen_snacache(&(varia->gioco.serpente),varia->gioco.larg,varia->gioco.alt);
    varia->gioco.serpente.ate=0;
    varia->gioco.serpente.portalcross=0;
    varia->gioco.serpente.keepexp=0;
    clear();
    refresh();
}
void checkwin(vars *varia)
{
    if (varia->gioco.serpente.numsezioni==(varia->gioco.larg*varia->gioco.alt))
        {
        gameover(varia,2);
        }
}
int copyfile(char *source,char *dest)
{
    FILE *from;
    FILE *to;
    char ch;
    from=fopen(source,"rb");
    if (from==NULL) return 0;
    to=fopen(dest,"wb");
    if (to==NULL)
        {
        fclose(from);
        return 0;
        }
    while (!feof(from))
        {
        ch=fgetc(from);
        if (ch!=EOF) fputc(ch,to);
        }
    fclose(from);
    fclose(to);
    return 1;
}
int emptyfile(char *filename)
{
    FILE *chi;
    chi=fopen(filename,"w");
    if (chi==NULL) return 0;
    fclose(chi);
    return 1;
}
void gameover(vars *varia, int causa)
{
    int ret,ret2;
    varia->paused=1;
    varia->gameover=causa;
    ret=open_savefile(&(varia->board),mainSaveFile);
    if (ret==-3)
        {
        varia->game_insane+=game_save_cheat;
        ret2=copyfile(backupSaveFile,mainSaveFile); // ricarica da backup
        if (ret2!=0)
            {
            ret=open_savefile(&(varia->board),mainSaveFile);
            if (ret==-3) // anche il backup è corrotto
                {
                varia->game_insane+=game_save_cheat_badly;
                remove(mainSaveFile);
                remove(backupSaveFile);
                }
            }
        else // no backup :(
            {
            varia->game_insane+=game_save_cheat_badly;
            remove(mainSaveFile);
            open_savefile(&(varia->board),mainSaveFile);
            }
        update_savefile(varia->playername,varia->score,mainSaveFile,varia);
        copyfile(mainSaveFile,backupSaveFile); // salva backup
        }
    else
        {
        update_savefile(varia->playername,varia->score,mainSaveFile,varia);
        copyfile(mainSaveFile,backupSaveFile); // salva backup
        }
    free(varia->board.entry);
    open_savefile(&(varia->board),mainSaveFile);
}
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"it_IT.UTF-8"); // in primis
    srand(time(NULL)); // caos!
    startNcurses(&(globali.gioco.larg),&(globali.gioco.alt)); // inizializza ncurses
    snprintf(globali.playername,maxnome,"%s",getenv("USER")); // salva il nome del giocatore (max 10 char)
    init_colori(&globali); // attiva i colori
    globali.speed=2;
    globali.gioco.serpente.ai=noAI;
    globali.safe_graph=0;
    if (!parse_cmdline(argc,argv,&globali))
        {
        start_gioco(&globali); // inizializza le var di gioco
        globali.gameover=1;
        globali.paused=1;
        title_loop(&globali); // schermata titolo
        globali.paused=0;
        globali.gameover=0;
        }
    else start_gioco(&globali); // inizializza le var di gioco
    atexit(endNcurses); // eseguita automaticamente all'uscita
    clear();
    //dump_snacache(globali.gioco.serpente.cache,globali.gioco.larg,globali.gioco.alt); refresh(); sleep(3);
    refresh();
    game_loop(&globali); // loop di gioco
    end_gioco(&globali); // libera la memoria
    return 0;
}
