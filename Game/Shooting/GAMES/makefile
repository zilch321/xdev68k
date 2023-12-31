#
#
#
CC = gcc
OBJS =  game.o clash.o enemy.o mychr.o sprite.o utiles.o map.o back.o
CFLAGS = -O -Wall -g

all:game.x

game.x: $(OBJS)
	$(CC) -o game.x $(OBJS) -liocs -ldos -lsignal

game.o : game.c game.h
clash.o : clash.c game.h
sprite.o : sprite.c game.h
mychr.o : mychr.c game.h
enemy.o : enemy.c game.h
utiles.o : utiles.c game.h
map.o: map.c game.h mapdata.h
back.o:back.c game.h
