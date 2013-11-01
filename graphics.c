#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include <string.h>
#include "structures.h"
#include "prototypes.h"
#include "unicode_art.h"

char speed_str[num_speedset][20]={"grandma speed   ","slow speed      ","normal speed    ","high speed      ","supersonic speed"};

wchar_t *drawsez(punto prima, punto qui, punto dopo)
{
    int alfa=0,beta=0;
    if (prima.y<qui.y && prima.x==qui.x)alfa=0;
    else if (prima.y==qui.y && prima.x>qui.x)alfa=1;
    else if (prima.y>qui.y && prima.x==qui.x)alfa=2;
    else alfa=3;

    if (dopo.y>qui.y && dopo.x==qui.x)beta=0;
    else if (dopo.y==qui.y && dopo.x<qui.x)beta=1;
    else if (dopo.y<qui.y && dopo.x==qui.x)beta=2;
    else beta=3;

    return snakebody2x[alfa][beta];
}
wchar_t *drawtail(punto prima, punto qui)
{
    int alfa=0;
    if (prima.y<qui.y && prima.x==qui.x)alfa=0;
    else if (prima.y==qui.y && prima.x>qui.x)alfa=1;
    else if (prima.y>qui.y && prima.x==qui.x)alfa=2;
    else alfa=3;

    return tail2x[alfa];
}
void bordino(vars *varia)
{
    int cont;
    if (varia->colori)attron(COLOR_PAIR(color_wall));
    for (cont=0; cont<(varia->gioco.larg*2)+2; cont++)
        {
        move(0,cont);
        printw("%lc",wall);
        move(varia->gioco.alt+1,cont);
        printw("%lc",wall);
        }
    for (cont=1; cont<(varia->gioco.alt)+2; cont++)
        {
        move(cont,0);
        printw("%lc",wall);
        move(cont,(varia->gioco.larg*2)+1);
        printw("%lc",wall);
        }
    if (varia->colori)attroff(COLOR_PAIR(color_wall));
}
void bordino_safe(vars *varia)
{
    int cont;
    if (varia->colori)attron(COLOR_PAIR(color_wall));
    for (cont=0; cont<(varia->gioco.larg*2)+2; cont++)
        {
        move(0,cont);
        printw("%lc",wall_safe);
        move(varia->gioco.alt+1,cont);
        printw("%lc",wall_safe);
        }
    for (cont=1; cont<(varia->gioco.alt)+2; cont++)
        {
        move(cont,0);
        printw("%lc",wall_safe);
        move(cont,(varia->gioco.larg*2)+1);
        printw("%lc",wall_safe);
        }
    if (varia->colori)attroff(COLOR_PAIR(color_wall));
}
void grafica_stillosa(vars *varia, int drawserp)
{
    int cont;
    snake *serp=&(varia->gioco.serpente);
    bordino(varia);
    move(0,0);
    printw("Punteggio: %d",varia->score);
    if ((varia->gamemode&portals)!=0)
        {
        for (cont=0; cont<varia->gioco.numportals; cont++)
            {
            move(varia->gioco.portale[cont].y+1,(varia->gioco.portale[cont].x*2)+1);
            if (varia->colori) attron(COLOR_PAIR(color_portal(cont)));
            wprintw(stdscr,"%ls",icon_portale[cont]);
            if (varia->colori) attroff(COLOR_PAIR(color_portal(cont)));
            }
        }
    for (cont=0; cont<varia->gioco.numpowerups; cont++)
        {
        move(varia->gioco.powerup[cont].y+1,(varia->gioco.powerup[cont].x*2)+1);
        if (varia->colori)attron(COLOR_PAIR(color_food));
        wprintw(stdscr,"%ls",pwup);
        if (varia->colori)attroff(COLOR_PAIR(color_food));
        }
    if (drawserp)
        {
        move((serp->sezioni[0].y)+1,(serp->sezioni[0].x*2)+1);
        printw("%lc%lc",head2x[serp->ciclo_anim][serp->direz][0],head2x[serp->ciclo_anim][serp->direz][1]);
        if (varia->colori)attron(COLOR_PAIR(color_snake));
        for (cont=1; cont<serp->numsezioni-1; cont++)
            {
            move(serp->sezioni[cont].y+1,(serp->sezioni[cont].x*2)+1);
            printw("%lc%lc",*drawsez(serp->sezioni[cont-1],serp->sezioni[cont],serp->sezioni[cont+1]),*(drawsez(serp->sezioni[cont-1],serp->sezioni[cont],serp->sezioni[cont+1])+1));
            }
        if (serp->numsezioni>1)
            {
            move(serp->sezioni[serp->numsezioni-1].y+1,(serp->sezioni[serp->numsezioni-1].x*2)+1);
            printw("%lc%lc",*drawtail(serp->sezioni[serp->numsezioni-2],serp->sezioni[serp->numsezioni-1]),*(drawtail(serp->sezioni[serp->numsezioni-2],serp->sezioni[serp->numsezioni-1])+1));
            }
        if (varia->colori)attroff(COLOR_PAIR(color_snake));
        }
    else
        {
        move((serp->sezioni[0].y)+1,(serp->sezioni[0].x*2)+1);
        printw("  ");
        for (cont=1; cont<serp->numsezioni-1; cont++)
            {
            move(serp->sezioni[cont].y+1,(serp->sezioni[cont].x*2)+1);
            printw("  ");
            }
        if (serp->numsezioni>1)
            {
            move(serp->sezioni[serp->numsezioni-1].y+1,(serp->sezioni[serp->numsezioni-1].x*2)+1);
            printw("  ");
            }
        }
    move(varia->gioco.alt+1,(varia->gioco.larg*2)+1);
}
wchar_t *safe_sez(wchar_t *from)
{
    long posiz;
    posiz=(long)from;
    posiz+=((long)snakebody2x_safe-(long)snakebody2x); // bypass annoyng pointer algebra and get things done
    return (wchar_t *) posiz;
}
wchar_t *safe_tail(wchar_t *from)
{
    long posiz;
    posiz=(long)from;
    posiz+=((long)tail2x_safe-(long)tail2x); // bypass annoyng pointer algebra and get things done
    return (wchar_t *) posiz;
}
void grafica_sicura(vars *varia, int drawserp)
{
    int cont;
    wchar_t *base;
    snake *serp=&(varia->gioco.serpente);
    bordino_safe(varia);
    move(0,0);
    printw("Punteggio: %d",varia->score);
    if ((varia->gamemode&portals)!=0)
        {
        for (cont=0; cont<varia->gioco.numportals; cont++)
            {
            move(varia->gioco.portale[cont].y+1,(varia->gioco.portale[cont].x*2)+1);
            if (varia->colori) attron(COLOR_PAIR(color_portal(cont)));
            wprintw(stdscr,"%ls",icon_portale_safe[cont]);
            if (varia->colori) attroff(COLOR_PAIR(color_portal(cont)));
            }
        }
    for (cont=0; cont<varia->gioco.numpowerups; cont++)
        {
        move(varia->gioco.powerup[cont].y+1,(varia->gioco.powerup[cont].x*2)+1);
        if (varia->colori)attron(COLOR_PAIR(color_food));
        wprintw(stdscr,"%ls",pwup_safe);
        if (varia->colori)attroff(COLOR_PAIR(color_food));
        }
    if (drawserp)
        {
        move((serp->sezioni[0].y)+1,(serp->sezioni[0].x*2)+1);
        printw("%lc%lc",head2x_safe[serp->ciclo_anim][serp->direz][0],head2x_safe[serp->ciclo_anim][serp->direz][1]);
        if (varia->colori)attron(COLOR_PAIR(color_snake));
        for (cont=1; cont<serp->numsezioni-1; cont++)
            {
            base=safe_sez(drawsez(serp->sezioni[cont-1],serp->sezioni[cont],serp->sezioni[cont+1]));
            move(serp->sezioni[cont].y+1,(serp->sezioni[cont].x*2)+1);
            printw("%lc%lc",*(base),*(base+1));
            }
        if (serp->numsezioni>1)
            {
            base=safe_tail(drawtail(serp->sezioni[serp->numsezioni-2],serp->sezioni[serp->numsezioni-1]));
            move(serp->sezioni[serp->numsezioni-1].y+1,(serp->sezioni[serp->numsezioni-1].x*2)+1);
            printw("%lc%lc",*(base),*(base+1));
            }
        if (varia->colori)attroff(COLOR_PAIR(color_snake));
        }
    else
        {
        move((serp->sezioni[0].y)+1,(serp->sezioni[0].x*2)+1);
        printw("  ");
        for (cont=1; cont<serp->numsezioni-1; cont++)
            {
            move(serp->sezioni[cont].y+1,(serp->sezioni[cont].x*2)+1);
            printw("  ");
            }
        if (serp->numsezioni>1)
            {
            move(serp->sezioni[serp->numsezioni-1].y+1,(serp->sezioni[serp->numsezioni-1].x*2)+1);
            printw("  ");
            }
        }
    move(varia->gioco.alt+1,(varia->gioco.larg*2)+1);
}
void grafica(vars *varia, int drawserp)
{
    if (varia->safe_graph)grafica_sicura(varia,drawserp);
    else grafica_stillosa(varia,drawserp);
}
void overlay_scritta(vars *varia)
{
    int cont,offsetx,alt,offsetop;
    if (varia->gameover==0)
        {
        alt=5;
        offsetop=((varia->gioco.alt-alt)/2)-scritta_devia;
        offsetx=(varia->gioco.larg*2-strlen(scritta_pausa[0]))/2;
        for (cont=0; cont<alt; cont++)
            {
            move(offsetop+cont+1,offsetx+1);
            printw("%s",scritta_pausa[cont]);
            }
        }
    else if (varia->gameover<0)
        {
        alt=5;
        offsetop=((varia->gioco.alt-alt)/2)-scritta_devia;
        offsetx=(varia->gioco.larg*2-strlen(scritta_gameover[0]))/2;
        for (cont=0; cont<alt; cont++)
            {
            move(offsetop+cont+1,offsetx+1);
            printw("%s",scritta_gameover[cont]);
            }
        }
    else if (varia->gameover==1)
        {
        alt=5;
        offsetop=((varia->gioco.alt-alt)/2)-scritta_devia;
        offsetx=(varia->gioco.larg*2-strlen(scritta_titolo[0]))/2;
        for (cont=0; cont<alt; cont++)
            {
            move(offsetop+cont+1,offsetx+1);
            printw("%s",scritta_titolo[cont]);
            }
        }
    else if (varia->gameover==2)
        {
        alt=5;
        offsetop=((varia->gioco.alt-alt)/2)-scritta_devia;
        offsetx=(varia->gioco.larg*2-strlen(scritta_congrats[0]))/2;
        for (cont=0; cont<alt; cont++)
            {
            move(offsetop+cont+1,offsetx+1);
            printw("%s",scritta_congrats[cont]);
            }
        }
}
void delete_scritta(vars *varia)
{
    int cont,x,offsetx,alt,offsetop;
    if (varia->gameover>=0)
        {
        alt=5;
        offsetop=((varia->gioco.alt-alt)/2)-scritta_devia;
        offsetx=(varia->gioco.larg*2-strlen(scritta_pausa[0]))/2;
        for (cont=0; cont<alt; cont++)
            {
            for (x=0; x<strlen(scritta_pausa[cont]); x++)
                {
                move(offsetop+cont+1,offsetx+x+1);
                printw(" ");
                }
            }
        }
}
void titlescreen_leftpanel(vars *varia)
{
    int offsetop=((varia->gioco.alt-5)/2)+7;
    int left=1;
    move(offsetop,left);
    attron(A_UNDERLINE);
    printw("S");
    attroff(A_UNDERLINE);
    printw("tart the game (classic mode)");
    move(offsetop+1,left);
    printw("start the game (");
    attron(A_UNDERLINE);
    printw("D");
    attroff(A_UNDERLINE);
    printw("ouble mode)");
    move(offsetop+2,left);
    printw("start the game (");
    attron(A_UNDERLINE);
    printw("R");
    attroff(A_UNDERLINE);
    printw("ussian mode)");
    move(offsetop+3,left);
    printw("start the game (");
    attron(A_UNDERLINE);
    printw("E");
    attroff(A_UNDERLINE);
    printw("xponential mode)");
    move(offsetop+4,left);
    attron(A_UNDERLINE);
    printw("Q");
    attroff(A_UNDERLINE);
    printw("uit the game");
}
void titlescreen_rightpanel(vars *varia)
{
    int offsetop=((varia->gioco.alt-5)/2)+7;
    int left=(varia->gioco.larg*2)+2-7-22;
    move(offsetop,left);
    if (varia->colori)
        {
        printw("I colori sono supportati.");
        }
    else
        {
        printw("I colori non sono supportati.");
        }
    move(offsetop+1,left);
    printw("%lc ",tickbox[(varia->gamemode&portals ? 1 : 0)]);
    printw("toggle ");
    attron(A_UNDERLINE);
    printw("P");
    attroff(A_UNDERLINE);
    printw("ortals");
    move(offsetop+2,left);
    printw("%lc %s <",speed_icon[varia->speed],speed_str[varia->speed]);
    attron(A_UNDERLINE);
    printw("C");
    attroff(A_UNDERLINE);
    printw("hange>");
    move(offsetop+3,left);
    if (varia->gioco.serpente.ai==noAI)
        {
        printw("Attiva AI   (");
        attron(A_UNDERLINE);
        printw("L");
        attroff(A_UNDERLINE);
        printw("azy mode)");
        }
    else if (varia->gioco.serpente.ai==assistedAI)
        {
        printw("AI attivata (");
        attron(A_UNDERLINE);
        printw("L");
        attroff(A_UNDERLINE);
        printw("azy mode)");
        }
    move(offsetop+4,left);
}
