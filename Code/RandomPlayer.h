
#ifndef RANDOMPLAYER_H_
#define RANDOMPLAYER_H_

class RandomPlayer: public Player {
public:

	RandomPlayer(int t):Player("Random", t){}
	void getMove(Board board, int&, int&);

};


void RandomPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

		vector<Cell> possibleMoves;


		int row, col;
		row = board.getRow();
		col = board.getCol();

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(board.grid[i][j] == 0) {
                    struct Cell emptyCell = {i, j, 0};
                    possibleMoves.push_back(emptyCell);
                }
            }
        }

        int numOfMoves = possibleMoves.size();
        int randomChoice = (rand() % numOfMoves) + 0;
        struct Cell choice = possibleMoves.at(randomChoice);
        x = choice.x;
        y = choice.y;

}

#endif /* RANDOMPLAYER_H_ */
