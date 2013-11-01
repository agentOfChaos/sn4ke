#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "prototypes.h"
//  0
//3 + 1
//  2
#define indice(x,y,l) (((y)*(l))+(x))
void ailog(char *stringa)
{
    FILE *apri;
    apri=fopen("ailog.txt","a");
    fprintf(apri,"%s",stringa);
    fclose(apri);
}
void turnleft(int *direz)
{
    switch (*direz)
        {
        case 0: (*direz)=3; break;
        case 1: (*direz)=0; break;
        case 2: (*direz)=1; break;
        case 3: (*direz)=2; break;
        }
}
void turnright(int *direz)
{
    switch (*direz)
        {
        case 0: (*direz)=1; break;
        case 1: (*direz)=2; break;
        case 2: (*direz)=3; break;
        case 3: (*direz)=0; break;
        }
}
void clearmatrix(char *matrix, int size)
{
    int cont;
    for (cont=0; cont<size; cont++)matrix[cont]=0;
}
void colora_dbg(int x,int y,char car)
{
    move(y+1,(x*2)+1);
    printw("%c%c",car,car);
    refresh();
    usleep(1000*10);
}
inline int eligible(int x, int y, vars *varia, char *campo,int larg,int alt)
{
    if (x>0) // sinistra
        {
        if (campo[indice(x-1,y,larg)]==1) return 1;
        }
    if (y>0) //sopra
        {
        if (campo[indice(x,y-1,larg)]==1) return 1;
        }
    if (x<(larg-1)) // destra
        {
        if (campo[indice(x+1,y,larg)]==1) return 1;
        }
    if (y<(alt-1)) // sotto
        {
        if (campo[indice(x,y+1,larg)]==1) return 1;
        }

    return 0;
}
inline int addcella(vars *varia,char *campo,int larg,int alt)
{
    int x,y;
    for (x=0; x<larg; x++)
        {
        for (y=0; y<alt; y++) // attraversa la matrice
            {
            if ((campo[indice(x,y,larg)]==0) && !(morsocoda(varia,x,y) || presomuro(varia,x,y))) // se è libera la cella d'esame
                { // controlla che sia adiacente ad almeno una presa
                if (eligible(x,y,varia,campo,larg,alt)==1)
                    {
                    campo[indice(x,y,larg)]=1;
                    //colora_dbg(x,y,'8');
                    return 1;
                    }
                }
            }
        }
    return 0;
}
void ailog_matrix(char *campo, int alt, int larg)
{
    int x,y;
    for (y=0; y<alt; y++)
        {
        for (x=0; x<larg; x++) // attraversa la matrice
            {
            if (campo[indice(x,y,larg)])ailog("X");
            else ailog("_");
            }
        ailog("\n");
        }
    ailog("\n");
}
int contalibere(int sx, int sy, char *campo, int larg, int alt,vars *varia)
{
    int numlibere=0;
    int fatta=1;
    int ret;
    campo[indice(sx,sy,larg)]=1;
    numlibere++;
    while (fatta)
        {
        //ailog_matrix(campo,alt,larg);
        ret=addcella(varia,campo,larg,alt);
        if (ret) numlibere++;
        else fatta=0;
        }
    return numlibere;
}
int findway(int ex, int ey, int dir1, int dir2, vars *varia) // 0 sinistra 1 destra
{
    int sin=0,des=0;
    char *matrix; // matrice delle celle occupate
    int sx=ex,sy=ey,dx=ex,dy=ey;
    calc_direz(dir1,&sx,&sy);
    calc_direz(dir2,&dx,&dy); // calcola i punti d'inizio destro e sinistro
    matrix=(char*)malloc(sizeof(char)*varia->gioco.larg*varia->gioco.alt);
    if (matrix==NULL)return -1;
    clearmatrix(matrix,varia->gioco.larg*varia->gioco.alt);
    //ailog("libere sinistra:\n");
    sin=contalibere(sx,sy,matrix,varia->gioco.larg,varia->gioco.alt,varia);
    clearmatrix(matrix,varia->gioco.larg*varia->gioco.alt);
    //ailog("libere destra:\n");
    des=contalibere(dx,dy,matrix,varia->gioco.larg,varia->gioco.alt,varia);
    free(matrix);
    return (des>sin);
}
int rotelle(vars *varia, int *px, int *py, int direz)
{
    int newposx=(*px);
    int newposy=(*py);
    snake *serp=&(varia->gioco.serpente);
    int turndir,turndir2,turnposx,turnposy,way;
    calc_direz(direz,&newposx,&newposy);
    if (morsocoda(varia,newposx,newposy) || presomuro(varia,newposx,newposy)) // posizione guardando un muro
        {
        //ailog("obstacle detected ahead! ");
        /*if (morsocoda(varia,newposx,newposy))ailog("class: tail\n");
        if (presomuro(varia,newposx,newposy))ailog("class: wall\n");*/
        turnposx=*px;
        turnposy=*py;
        turndir=direz;
        turnright(&turndir);
        calc_direz(turndir,&turnposx,&turnposy);
        if (morsocoda(varia,turnposx,turnposy) || presomuro(varia,turnposx,turnposy)) // muro a destra
            {
            //ailog("wall detected right!\n");
            turnposx=*px;
            turnposy=*py;
            turndir=direz;
            turnleft(&turndir);
            calc_direz(turndir,&turnposx,&turnposy);
            if (morsocoda(varia,turnposx,turnposy) || presomuro(varia,turnposx,turnposy)) // muro a sinistra -gasp!-
                {
                //ailog("addio mondo crudele!\n");
                }
            else // libero a sinistra
                {
                calc_direz(turndir,px,py);
                serp->direz=turndir;
                //ailog("vado a sinistra\n");
                }
            }
        else // libero a destra
            {
            turnposx=*px;
            turnposy=*py;
            turndir=direz;
            turnleft(&turndir);
            calc_direz(turndir,&turnposx,&turnposy);
            if (morsocoda(varia,turnposx,turnposy) || presomuro(varia,turnposx,turnposy)) // muro a sinsitra
                {
                //ailog("wall detected left\n");
                turndir2=direz;
                turnright(&turndir2);
                calc_direz(turndir2,px,py);
                serp->direz=turndir2;
                //ailog("vado a destra\n");
                }
            else // entrambe libere
                {
                turndir2=direz;
                turnright(&turndir2);
                //ailog("computing my best...\n");
                way=findway(*px,*py,turndir,turndir2,varia);
                if (way)
                    {
                    calc_direz(turndir2,px,py);
                    serp->direz=turndir2;
                    //ailog("vado a destra\n");
                    }
                else
                    {
                    calc_direz(turndir,px,py);
                    serp->direz=turndir;
                    //ailog("vado a sinistra\n");
                    }
                }
            }
        return 1;
        }
    return 0;
}
