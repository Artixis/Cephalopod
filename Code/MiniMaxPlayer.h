#ifndef MINIMAXPLAYER_H_
#define MINIMAXPLAYER_H_

class MiniMaxPlayer: public Player  {
public:
	MiniMaxPlayer(int t):Player("MiniMax", t){}
	void getMove(Board board, int &x, int &y);

	double maxMove(Board board);
	double minMove(Board board);
	int steps;

};


void MiniMaxPlayer::getMove(Board board, int &x, int &y) {

    int row, col;
    row = board.getRow();
    col = board.getCol();

    cout << "Row: " << row << ", Col: " << col << endl;

	priority_queue<UtilityCell> moves;

    int playerSymbol = board.getTurn();

    //if theres only 1 valid move make it, else run the rest
    vector<Cell> validMoves;

    for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(board.grid[i][j] == 0) {
                    struct Cell emptyCell = {i, j, 0};
                    validMoves.push_back(emptyCell);
                }
            }
        }

    int numOfMoves = validMoves.size();

    if(numOfMoves == 1){
        struct Cell onlyMove = validMoves.at(0);
        x = onlyMove.x;
        y = onlyMove.y;
        return;
    }


    else{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			steps = 1000;
			Board tempBoard(board);
			if(!tempBoard.validMove(i,j) ) {
				continue;
			}

			tempBoard.addMove(playerSymbol, i, j);
			if (tempBoard.isBoardFull()) {
				if (tempBoard.checkWinningStatus() == playerSymbol) {
					x = i;
					y = j;
					return;
				} else {
					continue;
				}
			}
			double minUtility = minMove(tempBoard);
			struct UtilityCell c = {i, j, minUtility};
			moves.push(c);
		}
	}
	if (moves.size() > 0) {
		x = moves.top().x;
		y = moves.top().y ;
	}

	return;
    }
}

double MiniMaxPlayer::maxMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
			return 0.01;
    int playerSymbol = board.getTurn();

    int row, col;
    row = board.getRow();
    col = board.getCol();



	double maxUtility = -2;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Board tempBoard(board);
			if(!tempBoard.validMove(i,j)) {
                continue;
			}

			tempBoard.addMove(playerSymbol, i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == playerSymbol)
					return 1; //score 1 if wins
				else if (gameStatus == 0)
					return 0; //score 0 if tie
				else
					return -1; //score -1 if lose
			}

			double utility;
			utility = minMove(tempBoard);

			if (utility > maxUtility) {
				maxUtility = utility;
			}
		}
	}
	steps--;
	return maxUtility;
}

double MiniMaxPlayer::minMove(Board board) {
	if (board.isBoardFull() || steps <= 0)
			return 0.01;

    int playerSymbol = board.getTurn();

    int row, col;
    row = board.getRow();
    col = board.getCol();


	double minUtility = 2;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			Board tempBoard(board);
			if(!tempBoard.validMove(i,j)){
                continue;
			}

			tempBoard.addMove(playerSymbol, i, j);
			int gameStatus = tempBoard.checkWinningStatus();
			if (gameStatus != -2) {
				if (gameStatus == playerSymbol)
					return 1; //score 1 if wins
				else if (gameStatus == 0)
					return 0; //score 0 if tie
				else
					return -1; //score -1 if lose
			}

			double utility = maxMove(board);

			if (utility < minUtility) {
				minUtility = utility;
			}
		}
	}
	steps--;
	return minUtility;
}

#endif /* MINIMAXPLAYER_H_ */
