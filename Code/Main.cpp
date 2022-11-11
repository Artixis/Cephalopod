/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from any
other student’s work or from any other source. No part of the code has
been written/produced for me by another person.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

#include<iostream>
#include<time.h>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

#include "Cell.h"
#include "UtilityCell.h"
#include "Board.h"
#include "Player.h"
#include "CephalopodGame.h"
#include "HumanPlayer.h"
#include "RandomPlayer.h"
#include "Heuristic.h"
#include "MiniMaxPlayer.h"
#include "MonteCarloPlayer.h"



int main() {
	srand(time(0));

	Player *players[2];

    cout << "***** Cephalopod Game ***** \n\n" << endl;

	cout << "Select one of the following:" << endl;
	cout << "1. Human player vs Human player" << endl;
	cout << "2. Human player vs Random player" << endl;
	cout << "3. Human player vs Heuristic player" << endl;
	cout << "4. Random player vs Heuristic(greedy) player" << endl;
	cout << "5. Heuristic(greedy) player vs Monte Carlo player" << endl;
	cout << "6. MiniMax player vs Monte Carlo player" << endl;
	cout << "7. MiniMax player vs Heuristic Player" << endl;

	int choice;
	cin >> choice;

	if(choice == 1){
        players[0] = new HumanPlayer(1);
        players[1] = new HumanPlayer(-1);
	}

	if(choice == 2){
        players[0] = new HumanPlayer(1);
        players[1] = new RandomPlayer(-1);
	}

	if(choice == 3){
        players[0] = new HumanPlayer(1);
        players[1] = new HeuristicPlayer(-1);
	}

	if(choice == 4){
        players[0] = new RandomPlayer(1);
        players[1] = new HeuristicPlayer(-1);
	}

	if(choice == 5){
        players[0] = new HeuristicPlayer(1);
        players[1] = new MonteCarloPlayer(-1);
	}

	if(choice == 6){
        players[0] = new MiniMaxPlayer(1);
        players[1] = new MonteCarloPlayer(-1);
	}

	if(choice == 7){
        players[0] = new MiniMaxPlayer(1);
        players[1] = new HeuristicPlayer(-1);
	}

	cout << "Input size of the board (say (2,2), (2,3), (3,3), (3,5), (5,5) ... " << endl;

	int row, col;
	cin >> row >> col;

    cout << "Input number of games you'd like to play or see played." << endl;

	int games;
	cin >> games;

	int player1Wins = 0;
    int player2Wins = 0;

	for(int i = 0; i < games; i++){
        cout << "\n*** Game number: " << (i+1) << " ***" << endl;
        Board board(row, col);
        CephalopodGame game(board, players);
        int winnerInt = game.play();
        if(winnerInt == 1) {
            player1Wins++;
        }

        if(winnerInt == -1) {
            player2Wins++;
        }
	}

    cout << "Player 1 won: " << player1Wins << " games." << endl;
    cout << "Player 2 won: " << player2Wins << " games." << endl;

	delete players[0];
	delete players[1];

	return 0;
}
