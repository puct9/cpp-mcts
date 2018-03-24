#pragma once
#include <vector>
#include <string>
#include <memory>

// Node class

class Node
{
public:
	Node *parentNode;
	std::vector<std::unique_ptr<Node>> children;
	unsigned long visits;
	unsigned long score;
	unsigned long visit_offset;

	// Constructors
	// Default. Will assume top node
	Node();
	// Norm
	Node(Node *parent, unsigned long offset);
	
	//Methods
	void Backtrack();
	void CreateChild(unsigned long offset);
	bool IsLeaf();
	double ucb1();
	double ucb1(double exploration);
	std::unique_ptr<Node>* SelectBest();
};
