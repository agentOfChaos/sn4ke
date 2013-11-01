#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.138                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -Wall
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG =  $(LDFLAGS) -lncursesw -lssl -lcrypto
OBJDIR_DEBUG = obj/Debug
DEP_DEBUG = 
OUT_DEBUG = sn4ke

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS) -s -lncursesw -lssl -lcrypto
OBJDIR_RELEASE = obj/Release
DEP_RELEASE = 
OUT_RELEASE = bin/Release/sn4ke

OBJ_DEBUG = $(OBJDIR_DEBUG)/ai.o $(OBJDIR_DEBUG)/blast_anim.o $(OBJDIR_DEBUG)/comandi.o $(OBJDIR_DEBUG)/game_loop.o $(OBJDIR_DEBUG)/graphics.o $(OBJDIR_DEBUG)/leaderboard.o $(OBJDIR_DEBUG)/main.o $(OBJDIR_DEBUG)/parse_cmd.o $(OBJDIR_DEBUG)/physics.o $(OBJDIR_DEBUG)/random_drops.o $(OBJDIR_DEBUG)/unicode_art.o

OBJ_RELEASE = $(OBJDIR_RELEASE)/ai.o $(OBJDIR_RELEASE)/blast_anim.o $(OBJDIR_RELEASE)/comandi.o $(OBJDIR_RELEASE)/game_loop.o $(OBJDIR_RELEASE)/graphics.o $(OBJDIR_RELEASE)/leaderboard.o $(OBJDIR_RELEASE)/main.o $(OBJDIR_RELEASE)/parse_cmd.o $(OBJDIR_RELEASE)/physics.o $(OBJDIR_RELEASE)/random_drops.o $(OBJDIR_RELEASE)/unicode_art.o

all: debug release

clean: clean_debug clean_release

before_debug: 
	test -d $(OBJDIR_DEBUG) || mkdir -p $(OBJDIR_DEBUG)

after_debug: 

debug: before_debug out_debug after_debug

out_debug: before_debug $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) $(LIBDIR_DEBUG) -o $(OUT_DEBUG) $(OBJ_DEBUG)  $(LDFLAGS_DEBUG) $(LIB_DEBUG)

$(OBJDIR_DEBUG)/ai.o: ai.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c ai.c -o $(OBJDIR_DEBUG)/ai.o

$(OBJDIR_DEBUG)/blast_anim.o: blast_anim.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c blast_anim.c -o $(OBJDIR_DEBUG)/blast_anim.o

$(OBJDIR_DEBUG)/comandi.o: comandi.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c comandi.c -o $(OBJDIR_DEBUG)/comandi.o

$(OBJDIR_DEBUG)/game_loop.o: game_loop.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c game_loop.c -o $(OBJDIR_DEBUG)/game_loop.o

$(OBJDIR_DEBUG)/graphics.o: graphics.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c graphics.c -o $(OBJDIR_DEBUG)/graphics.o

$(OBJDIR_DEBUG)/leaderboard.o: leaderboard.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c leaderboard.c -o $(OBJDIR_DEBUG)/leaderboard.o

$(OBJDIR_DEBUG)/main.o: main.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c main.c -o $(OBJDIR_DEBUG)/main.o

$(OBJDIR_DEBUG)/parse_cmd.o: parse_cmd.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c parse_cmd.c -o $(OBJDIR_DEBUG)/parse_cmd.o

$(OBJDIR_DEBUG)/physics.o: physics.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c physics.c -o $(OBJDIR_DEBUG)/physics.o

$(OBJDIR_DEBUG)/random_drops.o: random_drops.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c random_drops.c -o $(OBJDIR_DEBUG)/random_drops.o

$(OBJDIR_DEBUG)/unicode_art.o: unicode_art.c
	$(CC) $(CFLAGS_DEBUG) $(INC_DEBUG) -c unicode_art.c -o $(OBJDIR_DEBUG)/unicode_art.o

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf $(OBJDIR_DEBUG)

before_release: 
	test -d bin/Release || mkdir -p bin/Release
	test -d $(OBJDIR_RELEASE) || mkdir -p $(OBJDIR_RELEASE)

after_release: 

release: before_release out_release after_release

out_release: before_release $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) $(LIBDIR_RELEASE) -o $(OUT_RELEASE) $(OBJ_RELEASE)  $(LDFLAGS_RELEASE) $(LIB_RELEASE)

$(OBJDIR_RELEASE)/ai.o: ai.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c ai.c -o $(OBJDIR_RELEASE)/ai.o

$(OBJDIR_RELEASE)/blast_anim.o: blast_anim.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c blast_anim.c -o $(OBJDIR_RELEASE)/blast_anim.o

$(OBJDIR_RELEASE)/comandi.o: comandi.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c comandi.c -o $(OBJDIR_RELEASE)/comandi.o

$(OBJDIR_RELEASE)/game_loop.o: game_loop.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c game_loop.c -o $(OBJDIR_RELEASE)/game_loop.o

$(OBJDIR_RELEASE)/graphics.o: graphics.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c graphics.c -o $(OBJDIR_RELEASE)/graphics.o

$(OBJDIR_RELEASE)/leaderboard.o: leaderboard.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c leaderboard.c -o $(OBJDIR_RELEASE)/leaderboard.o

$(OBJDIR_RELEASE)/main.o: main.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c main.c -o $(OBJDIR_RELEASE)/main.o

$(OBJDIR_RELEASE)/parse_cmd.o: parse_cmd.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c parse_cmd.c -o $(OBJDIR_RELEASE)/parse_cmd.o

$(OBJDIR_RELEASE)/physics.o: physics.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c physics.c -o $(OBJDIR_RELEASE)/physics.o

$(OBJDIR_RELEASE)/random_drops.o: random_drops.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c random_drops.c -o $(OBJDIR_RELEASE)/random_drops.o

$(OBJDIR_RELEASE)/unicode_art.o: unicode_art.c
	$(CC) $(CFLAGS_RELEASE) $(INC_RELEASE) -c unicode_art.c -o $(OBJDIR_RELEASE)/unicode_art.o

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/Release
	rm -rf $(OBJDIR_RELEASE)

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release

