#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "unicode_art.h"
#include "prototypes.h"
#include "constants.h"

// todo: add prototypes. all of them.

int opt_normalmode(char *opt)
{
    if (strcmp(opt,"-s")==0) return 1;
    if (strcmp(opt,"--start")==0) return 1;
    return 0;
}
int opt_doublemode(char *opt)
{
    if (strcmp(opt,"-d")==0) return 1;
    if (strcmp(opt,"--double")==0) return 1;
    return 0;
}
int opt_russianmode(char *opt)
{
    if (strcmp(opt,"-r")==0) return 1;
    if (strcmp(opt,"--russian")==0) return 1;
    return 0;
}
int opt_expmode(char *opt)
{
    if (strcmp(opt,"-e")==0) return 1;
    if (strcmp(opt,"--exponential")==0) return 1;
    return 0;
}
int opt_speed(char *opt)
{
    if (strcmp(opt,"-v")==0) return 1;
    if (strcmp(opt,"--velocity")==0) return 1;
    return 0;
}
int opt_version(char *opt)
{
    if (strcmp(opt,"-V")==0) return 1;
    if (strcmp(opt,"--version")==0) return 1;
    return 0;
}
int opt_portals(char *opt)
{
    if (strcmp(opt,"-a")==0) return 1;
    if (strcmp(opt,"--aperture")==0) return 1;
    return 0;
}
int opt_paused(char *opt)
{
    if (strcmp(opt,"-p")==0) return 1;
    if (strcmp(opt,"--paused")==0) return 1;
    return 0;
}
int opt_leaderboard(char *opt)
{
    if (strcmp(opt,"-l")==0) return 1;
    if (strcmp(opt,"--leaderboard")==0) return 1;
    return 0;
}
int opt_help(char *opt)
{
    if (strcmp(opt,"-h")==0) return 1;
    if (strcmp(opt,"--help")==0) return 1;
    if (strcmp(opt,"-?")==0) return 1;
    return 0;
}
int opt_playername(char *opt)
{
    if (strcmp(opt,"-n")==0) return 1;
    if (strcmp(opt,"--name")==0) return 1;
    return 0;
}
int opt_resize(char *opt)
{
    if (strcmp(opt,"-m")==0) return 1;
    if (strcmp(opt,"--map")==0) return 1;
    return 0;
}
int opt_safegraph(char *opt)
{
    if (strcmp(opt,"-S")==0) return 1;
    if (strcmp(opt,"--simple-graphic")==0) return 1;
    return 0;
}
int opt_ai(char *opt)
{
    if (strcmp(opt,"-c")==0) return 1;
    if (strcmp(opt,"--computer")==0) return 1;
    return 0;
}
int opt_singola(char *opt)
{
    if (opt_speed(opt)) return 1;
    return 0;
}
void printHelpExit(vars *varia,char *nome)
{
    char lang[3];
    snprintf(lang,3,"%s",getenv("LANG"));
    end_gioco(varia);
    endNcurses();
    printf("%s -- Language: %s\n",versionstring,lang);
    if (strcmp(lang,"it")==0)
        {
        printf("sn4ke! Gioco per console simile a snake.\n");
        printf("Comandi:\twasd / tasti freccia per muovere il serpente\n");
        printf("\t\ttastiera per operare nei menu; freccie su/giu per scorrere i punteggi\n");
        printf("\tUtilizzo: %s [opzioni]\n",nome);
        printf("Opzioni riga di comando:\n");
        printf("\t-s --start\t\t\tInzia subito il gioco (modalità normale)\n");
        printf("\t-d --double\t\t\tInzia subito il gioco (modalità crescita doppia)\n");
        printf("\t-r --russian\t\t\tInzia subito il gioco (modalità roulette russa)\n");
        printf("\t-e --exponential\t\tInzia subito il gioco (modalità crescita esponenziale)\n");
        printf("\t-v [num] --velocity [num]\tImposta la velocità di gioco (0-4)\n");
        printf("\t-p --paused\t\t\tInizia il gioco in pausa (solo con -s -d -e -r)\n");
        printf("\t-a --aperture\t\t\tAttiva i portali\n");
        printf("\t-s --simple-graphic\t\tUsa un set di simboli grafici più semplice e portabile\n");
        printf("\t-m [h] [w] --map [h] [w]\tImposta manualmente la dimensione dello schermo (WxH)\n");
        printf("\t-n [nome] --name [nome]\t\tImposta il nome del giocatore a [nome]. Default è env(USER)\n");
        printf("\t-c [mode] --computer [mode]\tAttiva il sottosistema AI. Mode può essere \"no\" oppure \"lazy\". Default è \"no\"\n");
        printf("\t-l [num] --leaderboard [num]\tScrive i primi [num] punteggi migliori, poi termina. Il file dei punteggi non viene alterato\n");
        printf("\t-h --help -?\t\t\tScrivi questo menu di aiuto e termina\n");
        printf("Sottosistema AI (Artificial Intelligence)\n");
        printf("\tlazy mode: il programma prende automaticamante il controllo in caso di urto imminente; ");
        printf("L' ia si limita a deviare il serpente nella direzione più conveniente.\n");
        printf("\nIndicatori partita (ultima colonna della tavola punteggi)\n");
        printf("\tStringa d'esempio:\tdpl2\n");
        printf("\ts / d / r / e\t\tIndica la modalità di gioco\n");
        printf("\tp\t\t\tIndica che i portali sono attivi\n");
        printf("\tl\t\t\tIndica che la AI è attiva in lazy mode\n");
        printf("\t0 / 1 / 2 / 3 / 4\t\tIndica la velocità di gioco\n");
        printf("\tk\t\t\tIndica che la partita è stata vinta (il serpente ha riempito il campo)\n");
        }
    else
        {
        printf("sn4ke! Snake-like game for the console.\n");
        printf("Controls:\twasd / arrow keys move snake around\n");
        printf("\t\tkeyboard operates menus; arrow keys up/down to scroll the scoreboard\n");
        printf("\tUsage: %s [options]\n",nome);
        printf("Command line options:\n");
        printf("\t-s --start\t\t\tStart the game immediately (normal mode)\n");
        printf("\t-d --double\t\t\tStart the game immediately (double growth mode)\n");
        printf("\t-r --russian\t\t\tStart the game immediately (russian roulette mode)\n");
        printf("\t-e --exponential\t\tStart the game immediately (exponential growth mode)\n");
        printf("\t-v [num] --velocity [num]\tSet snake's speed (0-4)\n");
        printf("\t-p --paused\t\t\tStart the game paused (only with -s -d -e -r)\n");
        printf("\t-a --aperture\t\t\tEnable portals\n");
        printf("\t-s --simple-graphic\t\tUses a more simple and portable set of graphic symbols\n");
        printf("\t-m [h] [w] --map [h] [w]\tManually override screen size (WxH)\n");
        printf("\t-n [name] --name [name]\t\tSet player's name as [name]. Default is env(USER)\n");
        printf("\t-c [mode] --computer [mode]\tEnable AI subsystem. Mode can be \"no\" or \"lazy\". Default is \"no\"\n");
        printf("\t-l [num] --leaderboard [num]\tPrints the first [num] top scores, then quits. The leaderboard file won't be modified\n");
        printf("\t-h --help -?\t\t\tPrint this help menu and quit\n");
        printf("AI subsystem (Artificial Intelligence)\n");
        printf("\tlazy mode: the program will automatically assume control in case of imminent crash; ");
        printf("AI action is limited to redirecting the snake in the most convenien direction.\n");
        printf("\nGame indicators (last column in the leaderboard)\n");
        printf("\tExample string:\tdpl2\n");
        printf("\ts / d / r / e\t\tIndicates game mode\n");
        printf("\tp\t\t\tIndicates portals are enabled \n");
        printf("\tl\t\t\tIndicates lazy mode AI is enabled\n");
        printf("\t0 / 1 / 2 / 3 / 4\t\tIndicates game speed\n");
        printf("\tk\t\t\tMarks a won game (snake filling the whole screen)\n");
        }
    exit(0);
}
void printVersExit(vars *varia)
{
    end_gioco(varia);
    endNcurses();
    printf("%s\n",versionstring);
    exit(0);
}
int parse_cmdline(int argc, char *argv[],vars *varia)
{
    int skiptitle=0;
    int cont;
    int gameset=0;
    int speedset=0;
    int portalset=0;
    int nomeset=0;
    for (cont=1; cont<argc; cont++)
        {
        if (opt_help(argv[cont]))
            {
            printHelpExit(varia,argv[0]);
            }
        if (opt_safegraph(argv[cont]))
            {
            varia->safe_graph=1;
            }
        if (!gameset)
            {
            if (opt_normalmode(argv[cont]))
                {
                varia->gamemode+=vanilla;
                gameset=1;
                continue;
                }
            else if (opt_doublemode(argv[cont]))
                {
                varia->gamemode+=doubled;
                gameset=1;
                continue;
                }
            else if (opt_russianmode(argv[cont]))
                {
                varia->gamemode+=russian;
                gameset=1;
                continue;
                }
            else if (opt_expmode(argv[cont]))
                {
                varia->gamemode+=exponential;
                gameset=1;
                continue;
                }
            }
        if (!speedset)
            {
            if (opt_speed(argv[cont]) && argv[cont+1]!=NULL)
                {
                varia->speed=atoi(argv[cont+1])%num_speedset;
                cont++;
                speedset=1;
                continue;
                }
            }
        if (!portalset)
            {
            if (opt_portals(argv[cont]))
                {
                varia->gamemode+=portals;
                portalset=1;
                continue;
                }
            }
        if (!nomeset)
            {
            if (opt_playername(argv[cont]) && (strlen(argv[cont+1])<maxnome))
                {
                snprintf(varia->playername,maxnome,"%s",argv[cont+1]);
                cont++;
                nomeset=1;
                continue;
                }
            }
        if (opt_paused(argv[cont]))
            {
            varia->paused=1;
            continue;
            }
        if (opt_leaderboard(argv[cont]))
            {
            if (argv[cont+1]==NULL) printNexit(varia,50);
            else printNexit(varia,atoi(argv[cont+1]));
            }
        if (opt_resize(argv[cont]) && argv[cont+1]!=NULL && argv[cont+2]!=NULL)
            {
            varia->gioco.alt=abs(atoi(argv[cont+1]));
            varia->gioco.larg=abs(atoi(argv[cont+2]));
            cont+=2;
            continue;
            }
        if (opt_ai(argv[cont]) && argv[cont+1]!=NULL)
            {
            if (strcmp(argv[cont+1],"no")==0) varia->gioco.serpente.ai=noAI;
            else if (strcmp(argv[cont+1],"lazy")==0) varia->gioco.serpente.ai=assistedAI;
            cont++;
            continue;
            }
        if (opt_version(argv[cont]))
            {
            printVersExit(varia);
            }
        }
    return gameset;
}
