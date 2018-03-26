#include "stdafx.h"
#include "search.h"
#include "node.h"
#include <iostream>
#include <vector>


void search(Board inBoard, int team)
{
	search(inBoard, team, 10000);
}

void search(Board inBoard, int team, unsigned long iterations)
{
	std::cout << "test" << std::endl;
	if (!inBoard.getMoves())
	{
		std::cout << inBoard.getSize() / 2 << "," << inBoard.getSize() / 2 << std::endl;
	}

	Node topNode;
	topNode.team_multiplier = -team;

	/////////////////////////////// M C T S //////////////////////////////////
	for (unsigned long iteration = 0; iteration < iterations; ++iteration)
	{
		//if (iteration % 100) std::cout << iteration << std::endl;
		Board tmp_board{ inBoard };
		Node* bestLeaf = topNode.SelectBest(&tmp_board);
		if (bestLeaf->terminal)
		{
			bestLeaf->BackPropagateScore(bestLeaf->termscore);
			continue;
		}
		if (!bestLeaf->visits)
		{
			int score = simulation(tmp_board, false);
			bestLeaf->BackPropagateScore(score);
			continue;
		}
		for (const std::array<int, 2>&move : tmp_board.getObvMoves())
		{
			tmp_board.playMove(move[0], move[1]);
			int termscore = tmp_board.checkWin();
			if (termscore) bestLeaf->CreateChild(topNode.visits, move[0], move[1], termscore);
			bestLeaf->CreateChild(topNode.visits, move[0], move[1]);
			// Undo the move
			tmp_board.undoMove();
		}
	}

	// Suggest move
	int bestmove[2];
	unsigned long maxvisits = 0;
	for (const std::unique_ptr<Node>& move : topNode.children)
	{
		if (move->visits > maxvisits)
		{
			maxvisits = move->visits;
			bestmove[0] = move->move_to[0];
			bestmove[1] = move->move_to[1];
		}
	}
	std::cout << "Suggest: " << bestmove[0] << "," << bestmove[1] << std::endl;
}


int simulation(Board board)
{
	return simulation(board, true);
}

int simulation(Board board, bool rebuild)
{
	if (rebuild)
	{
		/* Rebuild the board states to make sure it works properly
		   Will not guarantee proper working order initially, but
		       for the purpose of this function, it will suffice
		*/
		std::vector<std::array<int, 2>> tmp;
		for (int r = 0; r < board.getSize(); ++r)
		{
			for (int c = 0; c < board.getSize(); ++c)
			{
				if (board.getBoardPos(r, c)) tmp.push_back(std::array<int, 2>{ r, c });
			}
		}
		board.manOverridePlayedPieces(tmp);
	}

	while (board.getMoves() < pow(board.getSize(), 2))
	{
		// Make a random move
		std::vector<std::array<int, 2>> choices = board.getObvMoves();
		std::array<int, 2> randMove = choices[rand() % choices.size()];
		board.playMove(randMove[0], randMove[1]);
		if (board.checkWin()) return board.checkWin();
	}
	return 0;
}
