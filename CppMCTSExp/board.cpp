#include "stdafx.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>


// Board class implementation goes here (the literal functions)

Board::Board()
{
	size = 19;
	reset();
}

Board::Board(const int s)
{
	std::cout << "Maximum board size is 19" << std::endl;
	size = (s < 19) ? s : 19;
	reset();
}

void Board::print()
{
	for (int r = 0; r < size; ++r)
	{
		for (int c = 0; c < size; ++c)
		{
			std::cout << board[r][c] << "\t";
		}
		std::cout << std::endl;
	}
}

void Board::reset()
{
	// Reset values
	moves = 0;

	// Reset board
	for (int r = 0; r < 23; ++r)
	{
		for (int c = 0; c < 23; ++c)
		{
			board[r][c] = 0;
		}
	}

	playedPieces.clear();
}

void Board::playMove(int l)
{
	playMove(l / size, l % size);
}

void Board::playMove(int r, int c)
{
	if (!board[r][c])
	{
		board[r][c] = (moves % 2) * 2 - 1;
	}
	++moves;

	lastPlaced[0] = r;
	lastPlaced[1] = c;
	std::array<int, 2> lp{ {r,c} };
	playedPieces.push_back(lp);
}

void Board::replayMoves()
{
	std::cout << "Replaying moves:" << std::endl;
	for (unsigned int i = 0; i < playedPieces.size(); ++i)
	{
		std::cout << i << ": " << playedPieces[i][0] << ", " << playedPieces[i][1] << std::endl;
	}
}

void Board::manOverridePlayedPieces(std::vector<std::array<int, 2>> ov)
{
	playedPieces = ov;
	moves = playedPieces.size();
}


int Board::checkWin()
{
	// Fast version: Check only the surroundings of the last placed piece
	int locR{ lastPlaced[0] };
	int locC{ lastPlaced[1] };

	// Check horizontal of the area. Verified to work.
	int startC{ (locC - 4 < 0) ? 0 : locC - 4 };
	int endC{ (size - locC >= 4) ? locC : size - 4 }; // Maths checks out
	for (int sC = startC; sC <= endC; ++sC)
	{
		int sum{ 0 };
		for (int a = 0; a < 5; ++a)
		{
			sum += board[locR][sC + a];
		}
		if (sum == -5)
		{
			return -1;
		}
		if (sum == 5)
		{
			return 1;
		}
	}

	// Check vertical of the area. Seems to work as well...
	int startR{ (locR - 4 < 0) ? 0 : locR - 4 };
	int endR{ (size - locR >= 4) ? locR : size - 4 };
	for (int sR = startR; sR <= endR; ++sR)
	{
		int sum{ 0 };
		for (int a = 0; a < 5; ++a)
		{
			sum += board[sR + a][locC];
		}
		if (sum == -5)
		{
			return -1;
		}
		if (sum == 5)
		{
			return 1;
		}
	}
	
	// Check the \ diagonal (top left to bottom right)
	// startR and startC will be used from above code for streamlining
	// delta-Row / delta-Col to be used in future
	int dRow = locR - startR;
	int dCol = locC - startC;
	int offset{ (dRow < dCol) ? dRow : dCol };
	// Too lazy for now to program more to truncate the search if it goes out of the zone
	// trust me I'm a programmer and it won't go out of index
	for (int sD = -offset; sD <= 0; ++sD)
	{
		int sum{ 0 };
		for (int a = 0; a < 5; ++a)
		{
			sum += board[locR + sD + a][locC + sD + a];
			//std::cout << "Access: " << locR + sD + a << " " << locC + sD + a << std::endl;
		}
		if (sum == -5)
		{
			return -1;
		}
		if (sum == 5)
		{
			return 1;
		}
	}

	// Check the / diagonal (bottom left to top right) - holy shit I hope this works
	// Calculate the offset to the left of which we start looking
	// Reuse `dRow` from last time
	offset = dCol; // I put a buffer so it won't go out of range
	// Scenario: Top left of board. Program will go too far up. Going too far up is the only concern.
	int truncate{ (dRow < 4) ? dRow - 4 : 0 };
	for (int sD = -offset; sD <= truncate; ++sD)
	{
		int sum{ 0 };
		for (int a = 0; a < 5; ++a)
		{
			sum += board[locR - sD - a][locC + sD + a];
			//std::cout << "Access: " << (locR + sD + a) << " " << (locC + sD + 4 - a) << std::endl;
			//std::cout << board[locR + sD + a][locC + sD + 4 - a] << " log" << std::endl;
		}
		if (sum == -5)
		{
			return -1;
		}
		if (sum == 5)
		{
			return 1;
		}
	}

	// Draw
	return 0;
}

int Board::getMoves()
{
	return moves;
}

int Board::getSize()
{
	return size;
}

int Board::getBoardPos(int r, int c)
{
	return board[r][c];
}

std::vector<std::array<int, 2>> Board::getObvMoves() //TODO
{
	std::vector<std::array<int, 2>> adjCells;

	for (const std::array<int, 2>& piece : playedPieces)
	{
		int cpR = piece[0];
		int cpC = piece[1];

		int direc[8][2] = { { cpR - 1, cpC - 1 }, { cpR - 1, cpC }, { cpR - 1, cpC + 1 },
							{ cpR, cpC - 1 }, { cpR, cpC + 1 },
							{ cpR + 1, cpC - 1 }, { cpR + 1, cpC }, { cpR + 1, cpC + 1 } };
		for (int i = 0; i < 8; ++i)
		{

		}
	}

	return std::vector<std::array<int, 2>>();
}

