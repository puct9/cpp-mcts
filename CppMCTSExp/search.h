#pragma once
#include "board.h"

void search(Board * inBoard);
void search(Board * inBoard, unsigned long iterations);
void simulation(Board * board);
void simulation(Board * board, bool rebuild);
