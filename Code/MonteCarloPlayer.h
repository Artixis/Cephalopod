
#ifndef MONTECARLOPPLAYER_H_
#define MONTECARLOPPLAYER_H_

class MonteCarloPlayer: public Player {
public:

	MonteCarloPlayer(int t):Player("MonteCarlo", t){}
	void getMove(Board board, int&, int&);

	double expansion(int player, Board board);
	double simulation(Board board);

};

void MonteCarloPlayer::getMove(Board board, int& x, int& y)
{
	if(board.isBoardFull())
		return;

		priority_queue<UtilityCell> moves;




		int row, col;
		row = board.getRow();
		col = board.getCol();
		int player = board.getTurn();


		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (board.grid[i][j] != 0) {

					continue;
				}
				Board tempBoard(board);

				tempBoard.addMove(player, i, j);
				if (tempBoard.checkWinningStatus() == player) {
					x = i;
					y = j;
					return;
				}

				double utility = simulation(tempBoard);
                struct UtilityCell c = {i, j, utility};
				moves.push(c);
			}
			cout << endl;
		}


		if (!moves.empty()) {
			x = moves.top().x;
			y = moves.top().y;
		}

		return;

}

//Functions of Monte Carlo
    double MonteCarloPlayer::simulation(Board board) {
		int times = 10000;
		double winning = 0.0;
		int player = board.getTurn();

		for (int i = 0; i < times; i++) {
			Board tempBoard(board);
			int playerTing = (player == -1) ? 1 : -1;
			winning += expansion(player, tempBoard);
		}
		return (winning / (double) times);
	}



	double MonteCarloPlayer::expansion(int player, Board board) {


		if (board.checkWinningStatus() == player) {
			return 1.0;
		} else if (board.checkWinningStatus() == 0) { //draw game
			return 0.5;
		} else if (board.checkWinningStatus() == -2) { //No player is winning; continue.
			return 0.0;
		}
		int x, y;
		board.getRandomMove(x, y);
		board.addMove(player, x, y);
		player = (player == -1) ? 1 : -1;



		return expansion(player, board);
	}





#endif /* MONTECARLOPPLAYER_H_ */
