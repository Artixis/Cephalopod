/*
 * Board.h
 *
 *  Created on: 25/02/2022
 *      Author: dongmo
 */

#ifndef BOARD_H_
#define BOARD_H_

class Board {
private:
	int row, col;
	int player;

public:

    int **grid;

	Board(int r, int c) :
			row(r), col(c) {
		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				grid[i][j] = 0;
			}
		}

		player = 1; // white has the first turn
	}

	~Board() {
		for (int i = 0; i < row; i++)
			delete[] grid[i];

		delete[] grid;
	}

	Board(const Board &cboard) {//Copy constructor
		row = cboard.row;
		col = cboard.col;

		grid = new int*[row];
		for (int i = 0; i < row; i++)
			grid[i] = new int[col];

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++) {
				grid[i][j] = cboard.grid[i][j];
			}

		player = cboard.getTurn();
	}

	bool isBoardFull() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if(grid[i][j] == 0)
					return false;
			}
		}
		return true;
	}

	int getTurn() const {
		return player;
	}

	int getRow();

	int getCol();

	bool validMove(int x, int y);

	bool addMove(int player, int x, int y);

	bool addHeurMove(int p, int x, int y);

    void getRandomMove(int &x, int &y);

	int capturingPlacement(int x, int y);

	priority_queue<Cell> getCombos(int x, int y);

	int heuristics(int player, int x, int y);

	int checkWinningStatus();

	void printBoard();

};



int Board::checkWinningStatus() {
	if (!isBoardFull())
		return -2; //error message

	int counter = 0;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grid[i][j] > 0)
				counter++;
		}
	}

	if (counter * 2 > row * col)
		return 1; //white player won
	else if (counter * 2 < row * col)
		return -1; //black player won
	else
		return 0;//draw
}

int Board::getRow() {
    return row;
}


int Board::getCol() {
    return col;
}

bool Board::validMove(int x, int y) {

	if (x < 0 || y < 0 || x > row - 1 || y > col - 1) {
		return false;
	}

	if (grid[x][y] != 0) {
		return false;
	}

	return true;
}

bool Board::addMove(int p, int x, int y) {
	if (p != player) {
		cout << "It is not the player's turn!" << endl;
		return false;
	}

	if (!validMove(x, y))
		return false;

	grid[x][y] = player * capturingPlacement(x, y);

	player = -1 * player;

	return true;
}

bool Board::addHeurMove(int p, int x, int y) {
    grid[x][y] = player * capturingPlacement(x, y);
}



void Board::getRandomMove(int &x, int &y) {
		row = getRow();
		col = getCol();

	do {
		x = (rand() % row) + 0;
        y = (rand() % col) + 0;
	} while (!validMove(x, y));
}

int Board::capturingPlacement(int x, int y) {
    priority_queue<Cell> possibleMoves;

    int totalCell = 0;
    int neighbourNum = 0;
    int left = (y-1);
    int right = (y+1);
    int up = (x-1);
    int down = (x+1);
    int leftValue, rightValue, upValue, downValue = 0;

    if(left >= 0) {
        leftValue = grid[x][left];
        struct Cell leftCell = {x, left, abs(leftValue)};

        possibleMoves.push(leftCell);

        if(leftValue != 0) {
            neighbourNum = neighbourNum + 1;
        }
    }


    if(right < col) {
        rightValue = grid[x][right];
        struct Cell rightCell = {x, right, abs(rightValue)};

        possibleMoves.push(rightCell);

        if(rightValue != 0) {
            neighbourNum = neighbourNum + 1;
        }
    }

    if(up >=0) {
        upValue = grid[up][y];
        struct Cell upCell = {up, y, abs(upValue)};

        possibleMoves.push(upCell);

        if(upValue != 0) {
            neighbourNum = neighbourNum + 1;
        }
    }

    if(down < row) {
        downValue = grid[down][y];
        struct Cell downCell = {down, y, abs(downValue)};

        possibleMoves.push(downCell);

        if(downValue != 0) {
            neighbourNum = neighbourNum + 1;
        }
    }

    totalCell = abs(leftValue) + abs(rightValue) + abs(upValue) + abs(downValue);


    // case 1
    if(neighbourNum < 2) {
            return 1;
    }


     //case 2
        if(neighbourNum == 2 ) {

            if(totalCell <= 6) {
                totalCell = 0;
                while(!possibleMoves.empty()) {
                    struct Cell currCell = possibleMoves.top();
                    x = currCell.x;
                    y = currCell.y;
                    grid[x][y] = 0;
                    totalCell = totalCell + currCell.value;
                    possibleMoves.pop();
                }

            return totalCell;

            } else {

                return 1;
            }

    }
    // case 3
    if(neighbourNum > 2){

            //option 1
            if(totalCell <=6) {
                 totalCell = 0;
                while(!possibleMoves.empty()) {
                    struct Cell currCell = possibleMoves.top();
                    x = currCell.x;
                    y = currCell.y;
                    grid[x][y] = 0;
                    totalCell = totalCell + currCell.value;
                    possibleMoves.pop();
                }
                return totalCell;
                //option 2
            } else if(totalCell > 6) {

                totalCell = 0;
                priority_queue<Cell> combo = getCombos(x, y);
                struct Cell topQue = combo.top();

                if(topQue.value == 0){
                    return 1;
                } else {
                    while(!combo.empty()) {
                        struct Cell comboMove = combo.top();
                        totalCell = totalCell + comboMove.value;
                        grid[comboMove.x][comboMove.y] = 0;
                        combo.pop();
                    }
                    return totalCell;
                }


            }

    }



}

priority_queue<Cell> Board::getCombos(int x, int y) {



    priority_queue<Cell> chosenCombo;
    struct Cell baseCell = {1,1,0};
    chosenCombo.push(baseCell);

    int left = (y-1);
    int right = (y+1);
    int up = (x-1);
    int down = (x+1);


    struct Cell upperCell = {-1,-1,1};;
    struct Cell rightCell = {-1,-1,1};;
    struct Cell leftCell = {-1,-1,1};;
    struct Cell lowerCell = {-1,-1,1};;


    if( up >=0 ) {
        upperCell = {up, y, abs(grid[up][y])};
    } else {
        upperCell = {up,y,0};
    }

    if( right < col ) {
        rightCell = {x, right, abs(grid[x][right])};
    } else {
        rightCell = {x,right,0};
    }

    if( left >=0 ) {
        leftCell = {x, left, abs(grid[x][left])};
    } else {
        leftCell = {x,left,0};
    }

    if( down < row ) {
        lowerCell = {down, y, abs(grid[down][y])};
    } else {
        lowerCell = {down,y,0};
    }



    if(left >= 0  && right < col){
        if(leftCell.value !=0  && rightCell.value!= 0){
        int comboVal = leftCell.value + rightCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(leftCell);
                chosenCombo.push(rightCell);
                }
            }
        }
    }



    if(left >= 0  && up >=0){
        if(leftCell.value !=0  && upperCell.value!= 0){
        int comboVal = leftCell.value + upperCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(leftCell);
                chosenCombo.push(upperCell);
                }
            }
        }
    }


    if(left >= 0  && down < row){
        if(leftCell.value !=0  && lowerCell.value!= 0){
        int comboVal = leftCell.value + lowerCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(leftCell);
                chosenCombo.push(lowerCell);
                }
            }
        }
    }


    if(right < col && up >=0){
        if(leftCell.value !=0  && upperCell.value!= 0){
        int comboVal = rightCell.value + upperCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(rightCell);
                chosenCombo.push(upperCell);
                }
            }
        }
    }



    if(right < col && down < row ){
        if(rightCell.value !=0  && lowerCell.value!= 0){
        int comboVal = rightCell.value + lowerCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(rightCell);
                chosenCombo.push(lowerCell);
                }
            }
        }
    }



    if(up >=0 && down < row ){
        if(upperCell.value !=0  && lowerCell.value!= 0){
        int comboVal = upperCell.value + lowerCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(upperCell);
                chosenCombo.push(lowerCell);
                }
            }
        }
    }


    if(left >=0 && right < col && down < row){
        if(leftCell.value !=0  && rightCell.value!= 0 && lowerCell.value != 0){
        int comboVal = leftCell.value + rightCell.value + lowerCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(leftCell);
                chosenCombo.push(rightCell);
                chosenCombo.push(lowerCell);
                }
            }
        }
    }


    if(left >=0 && right < col && up >=0){
        if(leftCell.value !=0  && rightCell.value!= 0 && upperCell.value != 0){
        int comboVal = leftCell.value + rightCell.value + upperCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(leftCell);
                chosenCombo.push(rightCell);
                chosenCombo.push(upperCell);
                }
            }
        }
    }


    if(right < col && up >=0  && down < row){
        if(rightCell.value !=0  && upperCell.value!= 0 && lowerCell.value != 0){
        int comboVal = rightCell.value + upperCell.value + lowerCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){
                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }
                chosenCombo.push(rightCell);
                chosenCombo.push(upperCell);
                chosenCombo.push(lowerCell);
                }
            }
        }
    }


    if(up >=0 && down < row  && left >=0){
        if(upperCell.value !=0  && lowerCell.value!= 0 && leftCell.value != 0){
        int comboVal = upperCell.value + lowerCell.value + leftCell.value;
        if(comboVal <= 6) {
            struct Cell topCell = chosenCombo.top();
            if(comboVal > topCell.value){

                while(!chosenCombo.empty()){
                    chosenCombo.pop();
                }

                chosenCombo.push(upperCell);
                chosenCombo.push(lowerCell);
                chosenCombo.push(leftCell);
                }
            }
        }

    }


    return chosenCombo;

}

int Board::heuristics(int player, int x, int y) {
    int value =0;

    value = player * capturingPlacement(x, y);
    cout << "Board moves being entered: (" << x << "," << y << ")" << endl;
    cout << "Placement value = " << capturingPlacement(x, y) << "Player = " << player  << endl;

    return value;
}

void Board::printBoard() {
	cout << "    ";
	for (int j = 0; j < col; j++) {
		cout << j + 1 << "   ";
	}
	cout << endl;

	for (int i = 0; i < row; i++) {
		cout << "  ";
		for (int j = 0; j < col; j++) {
			cout << " ---";
		}
		cout << endl;

		cout << (i + 1) << " |";

		for (int j = 0; j < col; j++) {
			if (grid[i][j] == 0) {
				cout << "   |";
			} else if (grid[i][j] > 0) {
				cout << " " << grid[i][j] << " |";
			} else if (grid[i][j] < 0) {
				cout << "" << grid[i][j] << " |";
			}
		}
		cout << endl;
	}
	cout << "  ";

	for (int j = 0; j < col; j++) {
		cout << " ---";
	}
	cout << endl << endl;
}

#endif /* BOARD_H_ */
