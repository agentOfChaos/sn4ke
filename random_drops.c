#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <math.h>
#include "structures.h"
#include "prototypes.h"
#include "unicode_art.h"

void timerPortal(vars *varia)
{
    varia->gioco.nextportime=portal_min_delay+(rand()%(portal_max_delay-portal_min_delay));
}
void removepup(campo *dove, int indice)
{
    int cont;
    move(dove->powerup[indice].y+1,(dove->powerup[indice].x*2)+1);
    wprintw(stdscr,"  ");
    for (cont=indice; cont<dove->numpowerups-1; cont++)
        {
        dove->powerup[cont]=dove->powerup[cont+1];
        }
    dove->numpowerups--;
}
void droppup(vars *varia)
{
    int x,y,safe=0;
    if (varia->gioco.numpowerups<2)
        {
        do {
            x=rand()%varia->gioco.larg;
            y=rand()%varia->gioco.alt;
            safe++;
            } while (morsocoda(varia,x,y) && safe<2500);
        varia->gioco.powerup[varia->gioco.numpowerups].x=x;
        varia->gioco.powerup[varia->gioco.numpowerups].y=y;
        varia->gioco.numpowerups++;
        }
}
void mangiacibo(vars *varia)
{
    switch (varia->gamemode&0b1111)
        {
        case vanilla:
            varia->gioco.serpente.ate+=1;
        break;
        case doubled:
            varia->gioco.serpente.ate+=2;
        break;
        case exponential:
            varia->gioco.serpente.ate+=abs(pow(2,varia->gioco.serpente.keepexp));
            varia->gioco.serpente.keepexp++;
        break;
        case russian:
            if (rand()%6 == 0)
                {
                nuovoblast(varia,&(varia->gioco.serpente.sezioni[1]),varia->gioco.serpente.numsezioni-1);
                varia->gioco.serpente.numsezioni=1;
                regen_snacache(&(varia->gioco.serpente),varia->gioco.larg,varia->gioco.alt); // ricrea la cache delle collisioni
                }
            else varia->gioco.serpente.ate+=1;
        break;
        }
}
void drop_portal(vars *varia)
{
    int x,y,safe=0,nuovo,altro;
    if (varia->gioco.numportals==0)
        {
        do {
            x=rand()%varia->gioco.larg;
            y=rand()%varia->gioco.alt;
            safe++;
            } while (morsocoda(varia,x,y) && presopup(varia,x,y) && safe<2500);
        varia->gioco.portale[0].x=x;
        varia->gioco.portale[0].y=y;
        safe=0;
        do {
            x=rand()%varia->gioco.larg;
            y=rand()%varia->gioco.alt;
            safe++;
            } while (morsocoda(varia,x,y) && presopup(varia,x,y) && (presoportal(varia,x,y)==1) && safe<2500);
        varia->gioco.portale[1].x=x;
        varia->gioco.portale[1].y=y;
        varia->gioco.numportals=2;
        }
    else
        {
        nuovo=rand()%2;
        if (nuovo==0)altro=2;
        else altro=1;
        move(varia->gioco.portale[nuovo].y+1,(varia->gioco.portale[nuovo].x*2)+1);
        printw("  ");
        do {
            x=rand()%varia->gioco.larg;
            y=rand()%varia->gioco.alt;
            safe++;
            } while (morsocoda(varia,x,y) && presopup(varia,x,y) && (presoportal(varia,x,y)==altro) && safe<2500);
        varia->gioco.portale[nuovo].x=x;
        varia->gioco.portale[nuovo].y=y;
        }
    if (varia->gioco.serpente.portalcross!=0) // portal cut ouch!
        {
        nuovoblast(varia,&(varia->gioco.serpente.sezioni[varia->gioco.serpente.portalcross]),varia->gioco.serpente.numsezioni-varia->gioco.serpente.portalcross);
        varia->gioco.serpente.numsezioni=varia->gioco.serpente.portalcross;
        varia->gioco.serpente.portalcross=0;
        varia->gioco.serpente.ate=0;
        regen_snacache(&(varia->gioco.serpente),varia->gioco.larg,varia->gioco.alt); // ricrea la cache delle collisioni
        }
}
