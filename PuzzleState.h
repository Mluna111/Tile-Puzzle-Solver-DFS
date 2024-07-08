/*
	* This class describes what a PuzzleState is.
	* The blank_position is for decreasing the time
	* to check what tile operator is applicable
*/
#ifndef _PUZZLESTATE_
#define _PUZZLESTATE_
#include <iostream>
#include <vector>

using namespace std;

class PuzzleState
{
public:
	// default constructor
	PuzzleState() {}

	//constructor
	PuzzleState(int n, int m){
		tiles.resize(long(n) * m);
		rows = n;
		cols = m;
	}
	// destructor
	~PuzzleState() { }

	// copy constructor
	PuzzleState(const PuzzleState& rhs)
		: rows(rhs.rows), cols(rhs.cols), tiles(rhs.tiles),
		blank_position_row(rhs.blank_position_row),
		blank_position_col(rhs.blank_position_col)
	{
		/*rows = rhs.rows;
		cols = rhs.cols;
		tiles = rhs.tiles;
		blank_position_row = rhs.blank_position_row;
		blank_position_col = rhs.blank_position_col;*/


	}

	bool operator==(const PuzzleState& rhs) const {
		if (rows == rhs.rows 
			|| cols == rhs.cols				//checking if rows, cols, and blank position match before looping.
			|| blank_position_col == rhs.blank_position_col
			|| blank_position_row == rhs.blank_position_row) 
		{
			for (int i = 0; i < tiles.size(); i++) {
				if (tiles[i] != rhs.tiles[i]) {					//looping to check all tiles are equal
					return 0;
				}
			}
			return 1;
		}
		else {
			return 0;

		}
	};
	bool operator!=(const PuzzleState& rhs) const {
		return !(*this == rhs);
	};
	const PuzzleState& operator=(const PuzzleState& rhs) {
		if (this == &rhs) {
			return *this;
		}
		rows = rhs.rows;
		cols = rhs.cols;
		tiles = rhs.tiles;
		blank_position_row = rhs.blank_position_row;
		blank_position_col = rhs.blank_position_col;

		return *this;

	}; //assignment op

	bool isNullState() { return rows == 0; } // can be excluded

	bool canMoveUp() {
		if (blank_position_row == 0) {
			return false;
		}
		return true;
	};

	bool canMoveDown() {
		if (blank_position_row == rows - 1) {
			return false;
		}
		return true;
	};

	bool canMoveLeft() { 
		if (blank_position_col == 0) {
			return false;
		}
		return true;
	};

	bool canMoveRight() {
		if (blank_position_col == cols - 1) {
			return false;
		}
		return true;
	};

	PuzzleState moveBlankUp() {
		int temp;
		if (canMoveUp()) {
			temp = tiles[(blank_position_row-1) * cols + blank_position_col]; //getting elemnt where blank is moving
			tiles[(blank_position_row-1) * cols + blank_position_col ] = 0; // moving blank up
			tiles[blank_position_row * cols + blank_position_col] = temp; // placing temp in previous blank 
			blank_position_row--; // adjusting blanks column postion
		}
		return *this;

	};

	PuzzleState moveBlankDown() {
		int temp;
		if (canMoveDown()) {
			temp = tiles[(blank_position_row + 1) * cols + blank_position_col]; //getting elemnt where blank is moving
			tiles[(blank_position_row + 1) * cols + blank_position_col] = 0; // moving blank up
			tiles[blank_position_row * cols + blank_position_col] = temp; // placing temp in previous blank 
			blank_position_row++; // adjusting blanks column postion
		}
		return *this;
	};

	PuzzleState moveBlankLeft() {
		int temp;
		if (canMoveLeft()) {
			temp = tiles[blank_position_row * cols + (blank_position_col-1)]; //getting elemnt where blank is moving
			tiles[blank_position_row * cols + (blank_position_col-1)] = 0; // moving blank up
			tiles[blank_position_row * cols + blank_position_col] = temp; // placing temp in previous blank 
			blank_position_col--; // adjusting blanks column postion
		}
		return *this;
	};

	PuzzleState moveBlankRight() {
		int temp;
		if (canMoveRight()) {
			temp = tiles[blank_position_row * cols + (blank_position_col+1)]; //getting elemnt where blank is moving
			tiles[blank_position_row * cols + (blank_position_col + 1)] = 0; // moving blank up
			tiles[blank_position_row * cols + blank_position_col] = temp; // placing temp in previous blank 
			blank_position_col++; // adjusting blanks column postion
		}
		return *this;
	};

	void read(istream& in) {

		vector<bool> used;
		used.resize(rows * cols);

		for (int i = 0; i < used.size(); i++) {
			used[i] = 0;
		}


		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) {
				in >> tiles[i * cols + j];
				if (tiles[i * cols + j] == 0) {
					blank_position_row = i;
					blank_position_col = j;
				}
				if (tiles[i * cols + j] >= (rows*cols)) {
					cout << "Invalid Puzzle Input: no #'s greater than (rows^2)-1 allowed";
					exit(1);
				}
				if (used[tiles[i * cols + j]] == 1) {
					cout << "Invalid Puzzle Input: no repeat #'s allowed";
					exit(1);
				}
				used[tiles[i * cols + j]] = true;
			}
		}

	};

	void print(ostream& out) {

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				out << tiles[i * cols + j] << " ";
			}
			out << endl;
		}
	};

	static PuzzleState  NullState;

private:
	int rows;
	int cols;
	vector<int> tiles;
	int blank_position_row;
	int blank_position_col;
};

istream& operator>>(istream& in, PuzzleState& rhs) {
	rhs.read(in);
	return in;

};
ostream& operator<<(ostream& out, PuzzleState& rhs) {
	rhs.print(out);
	return out;

};
#endif
