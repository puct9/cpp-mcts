#include "stdafx.h"
#include "search.h"
#include "node.h"
#include <iostream>
#include <vector>


void search(Board * inBoard)
{
	search(inBoard, 2000);
}

void search(Board * inBoard, unsigned long iterations)
{
	Board * board = new Board(*inBoard);
	if (!board->getMoves())
	{
		std::cout << board->getSize() / 2 << "," << board->getSize() / 2 << std::endl;
	}
	Node topNode;
	// Get things kicked off; run a sim.

	for (int iteration = 0; iteration < iterations; ++iteration)
	{
		std::unique_ptr<Node>* bestLeaf = topNode.SelectBest();
	}
}

void simulation(Board * board)
{
	simulation(board, false);
}

void simulation(Board * board, bool rebuild)
{
	if (rebuild)
	{
		/* Rebuild the board states to make sure it works properly
		   Will not guarantee proper working order initially, but
		       for the purpose of this function, it will suffice
		*/
		std::vector<std::array<int, 2>> tmp;
		for (int r = 0; r < board->getSize(); ++r)
		{
			for (int c = 0; c < board->getSize(); ++c)
			{
				if (board->getBoardPos(r, c)) tmp.push_back(std::array<int, 2>{ r, c });
			}
		}
		board->manOverridePlayedPieces(tmp);
	}

	while (board->getMoves() < pow(board->getSize(), 2))
	{
		// Make a random move
		std::vector<std::array<int, 2>> choices = board->getObvMoves();
	}
}
