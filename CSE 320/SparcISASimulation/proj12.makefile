#Charles Bean
#CSE 320
#SS14 - Project 12 makefile

#add /user/cse320/lib/reglib.o below (before -o)

CC = gcc
OBJS = proj12.driver.o proj12.support.o

proj12: $(OBJS)
	$(CC) $(OBJS) /user/cse320/lib/reglib.o -o proj12

proj12.driver.o: proj12.driver.c
	$(CC) -c proj12.driver.c

proj12.support.o: proj12.support.c
	$(CC) -c proj12.support.c




