#include "stdafx.h"
#include "node.h"
#include <string>
#include <iostream>
#include <limits>


// Node implementations

Node::Node()
{
	// Default constuctor
	// Node * parentNode will be left undefined
	// It is the duty of the programmer to not do anything foolish
	parentNode = nullptr;
	visits = 0, score = 0, visit_offset = 0;
}

Node::Node(Node *parent, unsigned long offset)
{
	// Constructor used when the node is not the top node.
	parentNode = parent;
	visits = 0, score = 0, visit_offset = offset;
}

void Node::Backtrack()
{
	std::cout << "yeet" << std::endl;
	if (parentNode == nullptr) return;
	parentNode->Backtrack();
}

void Node::CreateChild(unsigned long offset)
{
	// Creates a child and appends it to Node<std::unique_ptr<Node>> children
	// Nodes created here use the second constructor,
	// and `this` is the parent of its children, hence the `this` argument
	children.push_back(std::make_unique<Node>(this, offset));
}

bool Node::IsLeaf()
{
	return !children.size();
}

double Node::ucb1()
{
	return ucb1(sqrt(2));
}

double Node::ucb1(double exploration)
{
	if (!visits) return std::numeric_limits<double>::infinity();
	double average = (double)score / visits;
	return average + exploration * sqrt(log(parentNode->visits) / visits);
}

std::unique_ptr<Node>* Node::SelectBest()
{
	double max_value = -1.0;
	int max_index = 0;
	for (unsigned int i = 0; i < children.size(); i++)
	{
		double tmp = children[i]->ucb1();
		if (tmp > max_value)
		{
			max_value = tmp;
			max_index = i;
		}
	}
	if (children[max_value]->IsLeaf()) return &children[max_value];
	return children[max_value]->SelectBest();
}
