
#ifndef HEURISTICPPLAYER_H_
#define HEURISTICPPLAYER_H_

class HeuristicPlayer: public Player {
public:

	HeuristicPlayer(int t):Player("Heuristic", t){}
	void getMove(Board board, int&, int&);

};


void HeuristicPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

		priority_queue<Cell> moves;

        vector<Cell> sameValueMoves;

		int row, col;
		row = board.getRow();
		col = board.getCol();
		int player = board.getTurn();

        struct Cell baseCell = {0,0,0};

        for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				Board tempBoard(board);
				if (tempBoard.validMove(i, j)) {
					tempBoard.addHeurMove(player, i, j);
					int moveValue = tempBoard.grid[i][j];
					struct Cell c = {i, j, moveValue};
					moves.push(c);
					sameValueMoves.push_back(c);

                    int sizeOfQue = moves.size();

					if(sizeOfQue == 1) {
                        baseCell = c;
					}
				}
			}
		}


		struct Cell topQue = moves.top();
        if(topQue.value == baseCell.value) {
            int numOfMoves = sameValueMoves.size();
            int randomChoice = (rand() % numOfMoves) + 0;
            struct Cell choice = sameValueMoves.at(randomChoice);
            x = choice.x;
            y = choice.y;

        } else{
            if (moves.size() > 0) {
                x = moves.top().x;
                y = moves.top().y;
            }

        }





}

#endif /* HEURISTICPPLAYER_H_ */

