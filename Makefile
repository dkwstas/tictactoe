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

CC = gcc 
CFLAGS = -Wall -g -p
_OBJ = main.o game.o display.o utils.o msg.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
SDIR = src
BDIR = $(ODIR)/build
DDIR = $(ODIR)/debug
ODIR = out

#Generates final executable
.PHONY: all
all: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BDIR)/main

#Generates debug executable
debug: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(DDIR)/main_debug -fsanitize=address

#Generates object files for each module
$(ODIR)/%.o: $(SDIR)/%.c $(SDIR)/%.h dir
	$(CC) $(CFLAGS) -c  $< -o $@

#Creates output directory
.PHONY: dir
dir:
	mkdir -p $(BDIR) $(DDIR)

#Cleans previously generated files
clean:
	$(RM) -r out
