#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/curses.h>
#include <wchar.h>
#include "structures.h"
#include "blast_anim.h"
#include "prototypes.h"
#include "unicode_art.h"

void blastanim(vars *varia, int *counter)
{
    int fase=(*counter)/blastspeed;
    int blastlung=varia->gioco.blastlung;
    if (varia->gioco.toblast!=NULL)
        {
        if (fase<blastlung)
            {
            move((varia->gioco.toblast+fase)->y+1,((varia->gioco.toblast+fase)->x*2)+1);
            printw("%ls",explo);
            }
        else if (fase<(blastlung*2))
            {
            move((varia->gioco.toblast+fase-blastlung)->y+1,((varia->gioco.toblast+fase-blastlung)->x*2)+1);
            printw("  ");
            }
        else
            {
            (*counter)=0;
            varia->gioco.toblast=NULL;
            }
        (*counter)++;
        }
}
void nuovoblast(vars *varia,punto *dove, int lung)
{
    if (varia->gioco.toblast!=NULL)
        {
        clear();
        varia->gioco.toblast=dove;
        varia->gioco.blastlung=lung;
        }
    else
        {
        varia->gioco.toblast=dove;
        varia->gioco.blastlung=lung;
        }
}
