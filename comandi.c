#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <wchar.h>
#include "structures.h"
#include "prototypes.h"
#include "unicode_art.h"

void comandi(vars *varia)
{
    wchar_t ch;
    int esit;
    esit=get_wch((wint_t*)&ch);
    if (esit==ERR)
        {
        }
    else
        {
        switch (ch)
            {
            case KEY_LEFT: snake_direz(&(varia->gioco.serpente),3); break;
            case KEY_RIGHT: snake_direz(&(varia->gioco.serpente),1); break;
            case KEY_UP: snake_direz(&(varia->gioco.serpente),0); break;
            case KEY_DOWN: snake_direz(&(varia->gioco.serpente),2); break;
            case 'a': snake_direz(&(varia->gioco.serpente),3); break;
            case 'd': snake_direz(&(varia->gioco.serpente),1); break;
            case 'w': snake_direz(&(varia->gioco.serpente),0); break;
            case 's': snake_direz(&(varia->gioco.serpente),2); break;
            case 'q': varia->quit=1; break;
            case 'p': if (varia->paused)varia->paused=0; else varia->paused=1; break;
            default:
            break;
            }
        }
}
void snake_direz(snake *chi, int facing)
{
    if (chi->direz==1 && facing==3) return;
    if (chi->direz==0 && facing==2) return;
    if (chi->direz==3 && facing==1) return;
    if (chi->direz==2 && facing==0) return;
    chi->scheduledir=facing;
}
void comandi_pausa(vars *varia)
{
    wchar_t ch;
    int esit;
    esit=get_wch((wint_t*)&ch);
    if (esit==ERR)
        {
        }
    else
        {
        switch (ch)
            {
            case KEY_UP:
                if (varia->board.curr>0) varia->board.curr--;
            break;
            case KEY_DOWN:
                if (varia->board.curr+leaderboard_size<(varia->board.numentry)) varia->board.curr++;
            break;
            case 'q': varia->quit=1; break;
            case 'p':
                if (varia->gameover>=0)
                    {
                    if (varia->paused)varia->paused=0;
                    else varia->paused=1;
                    }
            break;
            case 'r':
                if (varia->gameover<0)
                    {
                    riprova(varia);
                    }
            break;
            default:
            break;
            }
        }
}
void comandi_titolo(vars *varia)
{
    wchar_t ch;
    int esit;
    esit=get_wch((wint_t*)&ch);
    if (esit==ERR)
        {
        }
    else
        {
        switch (ch)
            {
            case 'q': varia->quit=1; break;
            case 's':
                varia->gamemode+=vanilla;
                varia->paused=0;
            break;
            case 'd':
                varia->gamemode+=doubled;
                varia->paused=0;
            break;
            case 'e':
                varia->gamemode+=exponential;
                varia->paused=0;
            break;
            case 'r':
                varia->gamemode+=russian;
                varia->paused=0;
            break;
            case 'p':
                if ((varia->gamemode&portals)!=0)varia->gamemode-=portals;
                else varia->gamemode+=portals;
            break;
            case 'l':
                if ((varia->gioco.serpente.ai==noAI))varia->gioco.serpente.ai=assistedAI;
                else if ((varia->gioco.serpente.ai==assistedAI))varia->gioco.serpente.ai=noAI;
            break;
            case 'c':
                varia->speed++;
                if (varia->speed>=num_speedset)varia->speed=0;
            break;
            default:
            break;
            }
        }
}
