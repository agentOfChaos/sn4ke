#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include "structures.h"
#include "prototypes.h"
#include "unicode_art.h"

int presopup(vars *varia, int x, int y)
{
    int cont,num=varia->gioco.numpowerups;
    for (cont=0; cont<num; cont++)
        {
        if (varia->gioco.powerup[cont].x==x && varia->gioco.powerup[cont].y==y)
            {
            removepup(&(varia->gioco),cont);
            return 1;
            }
        }
    return 0;
}
inline int presoportal(vars *varia, int x, int y)
{
    if (x==varia->gioco.portale[0].x && y==varia->gioco.portale[0].y) return 1;
    if (x==varia->gioco.portale[1].x && y==varia->gioco.portale[1].y) return 2;
    return 0;
}
inline int presomuro(vars *varia, int x, int y)
{
    if (x<0 || x>=varia->gioco.larg || y<0 || y>=varia->gioco.alt) return 1;
    return 0;
}
inline int morsocoda(vars *varia, int x, int y)
{
    snake *serp=&(varia->gioco.serpente);
    if (x<0 || y<0 || x>=varia->gioco.larg || y>=varia->gioco.alt) return 0; // avoid segfault
    if (serp->cache[x][y]==1) return 1;
    return 0;
}
void calc_direz(int direz, int *newposx, int *newposy)
{
    switch(direz)
        {
        case 0:
            (*newposy)-=1;
        break;
        case 1:
            (*newposx)+=1;
        break;
        case 2:
            (*newposy)+=1;
        break;
        case 3:
            (*newposx)-=1;
        break;
        }
}
void fisica_serp(vars *varia) // very important function!
{
    int newposx,newposy,lastposx,lastposy,cont,port;
    snake *serp=&(varia->gioco.serpente);
    serp->direz=serp->scheduledir; // apply the scheduled route change
    newposx=serp->sezioni[0].x; // before
    newposy=serp->sezioni[0].y;
    if (serp->ai&assistedAI)
        {
        if (rotelle(varia,&newposx,&newposy,serp->direz)==0)calc_direz(serp->direz,&newposx,&newposy);
        }
    else
        {
        calc_direz(serp->direz,&newposx,&newposy);
        }
    // we have the new coordinates in newposx newposy
    if (morsocoda(varia,newposx,newposy)) gameover(varia,-1); // check loosing conditions
    else if (presomuro(varia,newposx,newposy)) gameover(varia,-2);
    else // didn't crash
        {
        if (varia->gamemode&portals) // if portal mode is active
            {
            port=presoportal(varia,newposx,newposy); // check if went through portal
            if (port!=0) // if yes
                {
                if (port==2)port=0; // get the id of the exit portal
                else port=1;
                newposx=varia->gioco.portale[port].x; // update the 'new coordinates'
                newposy=varia->gioco.portale[port].y;
                serp->portalcross=1; // initializes portal cross counter
                }
            if (serp->portalcross>0) // if is crossing portal
                {
                serp->portalcross++;
                if (serp->portalcross==serp->numsezioni)serp->portalcross=0; // reset the counter when done crossing
                }
            }
        if (morsocoda(varia,newposx,newposy)) gameover(varia,-1); // re-check loosing condition, in case a warp took place
        else if (presomuro(varia,newposx,newposy)) gameover(varia,-2);
        else
            {
            serp->cache[newposx][newposy]=1; // updates cache
            if (presopup(varia,newposx,newposy))mangiacibo(varia); // eats food (if any)
            for (cont=0; cont<serp->numsezioni; cont++)
                {
                lastposx=serp->sezioni[cont].x; // translates each module to the coordinates of the previous one
                serp->sezioni[cont].x=newposx;  // this model works great for navigating portals, too
                lastposy=serp->sezioni[cont].y;
                serp->sezioni[cont].y=newposy;
                newposx=lastposx;
                newposy=lastposy;
                }
            if (serp->ate>0) // if there are cells to grow
                {
                varia->score+=punto_base; // adds score
                serp->sezioni[serp->numsezioni].x=lastposx; // grows the new cell
                serp->sezioni[serp->numsezioni].y=lastposy;
                serp->numsezioni++;
                serp->ate--;
                }
            else // if there aren't, cleans the position where the tail used to be
                {
                move(lastposy+1,(lastposx*2)+1);
                serp->cache[lastposx][lastposy]=0; // updates cache
                printw("  ");
                }
            }
        }
    serp->scheduledir=serp->direz; // to avoid unexpected route changes
}
