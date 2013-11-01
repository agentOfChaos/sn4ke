#include "constants.h"
/*
    " data structures are important.
    the program flow is itself a mere
    reflection of what and how the data
    structures are"
                    -- myself
    in layman's terms, think twice and code half
*/
typedef struct{
    int x;
    int y;
} punto; // simple 2d point coordinates
typedef struct{
    punto *sezioni; // array of snake modules "caterpillar-like". 0 is always the head
    int numsezioni; // numver of said modules
    int direz; // 0 up 1 right 2 down 3 left
    int scheduledir; // direz to be taken next
    int ciclo_anim; // counter for the blinking head
    int ate; // number of cells to grow
    int keepexp; // base for the exponential grow mode
    int portalcross; // number of modules wich have currently crossed a portal. 0 means no portal is being crossed
    int ai; // ai autopilot mode
    char **cache; // 2d matrix caching snake positions for optimized collision detection
}snake; // snake data structure
typedef struct {
    snake serpente; // the snake
    punto portale[2]; // the 2 portals
    int numportals; // number of portals currently opened
    int nextportime; // timeout for portal position switching
    punto *powerup; // array of points representing the currently avaible 'food'
    int numpowerups; // number of food units avaible
    int larg; // width of the field
    int alt; // height of the field
    punto *toblast; // pointer to an array of points where an 'explosion' animation must be displayed
    int blastlung; // end boundary of said explosion points
}campo; // physical game field structure
typedef struct {
    int score; // no explanation needed
    char nome[maxnome]; // player name
    char flags[scoreflags]; // flags representing the game status
}punteggio; // entry in  the scoreboard
typedef struct {
    punteggio *entry; // array of entries
    int numentry; // number of entries
    int curr; // current top entry (for graphical scrolling purposes)
} leaderboard; // the scoreboard data structure
typedef struct {
    campo gioco; // the game field
    leaderboard board; // the leaderboard
    int score; // current score
    int speed; // speed mode (see speed table in constants.h)
    int quit; // exit condition of the main game loop
    int paused; // same for the pause loop, but inverted
    int gameover; // game over status: -2 hit wall  -1 hit tail  0 currently in game  1 title screen  2 HUGE success it's hard to overstate mt satisfaction
    int gamemode; // current game mode (first 4 bits); portal mode (the 5th bit)
    int colori; // 1 if colors are avaible in terminal, 0 otherwise
    int safe_graph; // 1 if safe unicode symbols are engaged, 0 for normal fancy mode
    int game_insane; // nonzero if the score save file was found altered
    char playername[maxnome]; // current player's name
} vars; // structure containing ALL the global variables, for easy handling (my idea :)
