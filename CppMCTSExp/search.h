#pragma once
#include "board.h"

void search(Board inBoard, int team);
void search(Board inBoard, int team, unsigned long iterations);
int simulation(Board board);
int simulation(Board board, bool rebuild);
