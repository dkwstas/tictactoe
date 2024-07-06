#
# Makefile for tictactoe game.
# 
# Copyright (C) 2024  Kostas Drakontidis
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

CC = gcc										#Compiler 
CFLAGS = -Wall -g								#Compiler flags
OBJ = main.o game.o display.o utils.o msg.o		#Object files as targets

#Generates final executable
all: $(OBJ)
	$(CC) $(CFLAGS) *.o -o main

debug: $(OBJ)
	$(CC) $(CFLAGS) *.o -o main -fsanitize=address
#Generates object files for each module
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $*.c

#Cleans previously generated files
clean:
	$(RM) main
	$(RM) *.o
