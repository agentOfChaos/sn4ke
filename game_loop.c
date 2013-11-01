#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncursesw/curses.h>
#include "structures.h"
#include "prototypes.h"
#include "unicode_art.h"

int speed_setting[num_speedset]={200,155,110,90,60};

void game_loop(vars *varia)
{
    int itimer=0;
    int atimer=0;
    int ptimer=0;
    int blaster=0;
    while (!varia->quit)
        {
        game_step(varia,&itimer,&atimer,&ptimer,&blaster);
        if (varia->paused)game_pause_loop(varia,(varia->gameover<0 ? 1 : 0));
        }
}
void game_step(vars *varia, int *itimer, int *atimer, int *ptimer, int *blaster)
{
    int speed;
    comandi(varia);
    if (!varia->quit)
        {
        speed=speed_setting[varia->speed];
        if ((*itimer) >= speed)
            {
            fisica_serp(varia);
            checkwin(varia);
            (*itimer)=0;
            }
        if ((*atimer) >=animspeed)
            {
            if (varia->gioco.serpente.ciclo_anim==0)varia->gioco.serpente.ciclo_anim=1;
            else varia->gioco.serpente.ciclo_anim=0;
            (*atimer)=0;
            }
        if ((*ptimer) >= (varia->gioco.nextportime*1000))
            {
            if ((varia->gamemode&portals)!=0)
                {
                timerPortal(varia);
                drop_portal(varia);
                }
            (*ptimer)=0;
            }
        droppup(varia);
        grafica(varia,1);
        blastanim(varia,blaster);
        refresh();
        (*itimer)+=delay;
        (*atimer)+=delay;
        (*ptimer)+=delay;
        usleep(1000*delay);
        }
}
void game_pause_loop(vars *varia, int blink)
{
    int btimer=0;
    while (varia->paused)
        {
        game_pause_step(varia,&btimer,blink);
        if (varia->quit) break;
        }
    if (varia->gameover!=0)
        {
        free(varia->board.entry);
        }
    delete_scritta(varia);
}
void game_pause_step(vars *varia, int *btimer,int blink)
{
    int tblink=800;
    if (blink)
        {
        if ((*btimer)<tblink/2) grafica(varia,0);
        else if ((*btimer)>=tblink/2) grafica(varia,1);
        }
    else grafica(varia,1);
    overlay_scritta(varia);
    if (varia->gameover!=0)
        {
        move(1,1);
        if (varia->gameover==-1)printw("Ti sei morso la coda! ");
        else if (varia->gameover==-2)printw("Ti sei schiantato! ");
        else if (varia->gameover==2)printw("Hai vinto la partita! ");
        else printw("Fine della partita! ");
        printw("| q per chiudere | r per ricominciare");
        if (varia->game_insane&game_save_cheat)
            {
            move(2,1);
            printw("File salvataggi corrotto! Recupero backup..");
            }
        if (varia->game_insane&game_save_cheat_badly)
            {
            printw(" assente / corrotto. D'oh!");
            }
        scrivi_punteggi((varia->gioco.alt/2)+4-scritta_devia,(((varia->gioco.larg*2)+2)/2)-14,leaderboard_size,varia);
        }
    if ((*btimer)>=tblink)(*btimer)=0;
    refresh();
    comandi_pausa(varia);
    (*btimer)+=delay;
    usleep(1000*delay);
}
void title_loop(vars *varia)
{
    while (varia->paused)
        {
        game_title_step(varia);
        if (varia->quit) break;
        }
}
void game_title_step(vars *varia)
{
    comandi_titolo(varia);
    move(0,0);
    printw(versionstring);
    overlay_scritta(varia);
    titlescreen_leftpanel(varia);
    titlescreen_rightpanel(varia);
    refresh();
    usleep(1000*delay);
}
