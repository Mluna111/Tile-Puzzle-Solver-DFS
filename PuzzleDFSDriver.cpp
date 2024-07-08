#include "PuzzleMove.h"
#include "PuzzleState.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;



bool inClosedList(PuzzleState& const currentState, vector<PuzzleMove>& const closed) {
	
	bool val = 0;
	for (int i = 0; i < closed.size(); i++) {
		if (currentState == closed[i].getState()) {
			val = 1;
		}
	}
	return val;
}

void expand(PuzzleMove& const currentMove,  stack<PuzzleMove>& fringe, vector<PuzzleMove>& const closed) {
	PuzzleState currentState = currentMove.getState();
	PuzzleState tempState;
	
	if (currentState.canMoveRight()) {
		tempState = currentState;
		tempState.moveBlankRight();
		if (!(currentMove.getParent() == tempState /* && !(inClosedList(currentState, closed))*/)) {
			fringe.push(PuzzleMove(tempState, currentState, ::right));
		}
	}
	if (currentState.canMoveUp()) {
		tempState = currentState;
		tempState.moveBlankUp();
		if (!(currentMove.getParent() == tempState /* && !(inClosedList(currentState, closed))*/)) {
			fringe.push(PuzzleMove(tempState, currentState, up));
		}
	}
	if (currentState.canMoveLeft()) {
		tempState = currentState;
		tempState.moveBlankLeft();
		if (!(currentMove.getParent() == tempState /* && !(inClosedList(currentState, closed))*/)) {
			fringe.push(PuzzleMove(tempState, currentState, ::left));
		}
	}
	if (currentState.canMoveDown()) {
		tempState = currentState;
		tempState.moveBlankDown();
		if (!(currentMove.getParent() == tempState /* && !(inClosedList(currentState, closed))*/)) {
			fringe.push(PuzzleMove(tempState, currentState, down));
		}
	}
	
	
	
}

void PrintPath(PuzzleMove currentMove,  vector<PuzzleMove>& const closed) {

	PuzzleState pathState;
	stack<PuzzleMove> sol;

	do {
		pathState = currentMove.getParent();
		sol.push(currentMove);
		for (int i = 0; i < closed.size(); i++) {
			if (pathState == closed[i].getState()) {
				currentMove = closed[i];
			}
		}
	
	} while (currentMove.getState() != currentMove.getParent());

	cout << "\n*** Solution Found *** \n";
	cout << "\nNumber of nodes expanded: " << closed.size();
	cout << "\nPath length to Goal: " << sol.size();
	
	cout << endl << endl << currentMove.getState();

	while(!sol.empty()) {
		currentMove = sol.top();
		sol.pop();
		cout  << endl << moves[currentMove.getMoveName()]<< endl << endl << currentMove.getState() ;
	}
}


void solve(PuzzleState& start,  PuzzleState& goal, vector<PuzzleMove>& closed){
	stack<PuzzleMove> fringe;
	PuzzleMove root(start, start, nullMove);
	PuzzleMove currentMove;
	PuzzleState currentState;

	fringe.push(root);
	bool solution = 0;
	while (fringe.empty() != 1 && solution == 0) {
		currentMove = fringe.top();
		fringe.pop();
		currentState = currentMove.getState();
		if (currentState == goal) {
			PrintPath(currentMove, closed);
			solution = 1;
		}
		else {
			if (!(inClosedList(currentState, closed))) {
				//cout << endl << "curr:\n" << currentState << endl;
				closed.push_back(currentMove);
				expand(currentMove, fringe, closed);
			}
		}
	}
	if (solution == 0) {
		cout << "\nNo Solution Found";
	}
}


int main() {

	int rows = 0;
	int cols = 0;
	cout << "Enter number of rows and columns: ";
	cin >> rows;// >> cols;
	cols = rows;

	//if (rows != cols || cols == 0 || rows == 0) {								//checking for square vector n*n where n > 0
	//	cout << "\n*** No solution found, incorrect number of rows and/or columns ***";
	//}
	cout << "\nEnter Start State row by row:\n";
	PuzzleState start(rows, cols);
	cin >> start;

	cout << "\nEnter End State row by row:\n";
	PuzzleState goal(rows, cols);

	cin >> goal;

	if (start == goal) {
		cout << "\n*** Solution found immediately: start state is the goal state. ***";
	}

	vector<PuzzleMove> closed;


	solve(start, goal, closed);

	
}

// 2 2 1 2 0 3 1 2 3 0
// 2 2 1 0 2 3 1 2 3 0
// 3 1 3 5 4 2 0 7 8 6 1 2 3 4 5 6 7 8 0