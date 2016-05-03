//Johnathan Kruse
//CSCI 2270 Final Project
//Instructor Hoenigman
//Terminal Battleship
//Driver File
#include <iostream>
#include <cstdlib>
#include "battleShipBoard.h"
using namespace std;
string retrieveName(string playerNumber);
void setupPlayerBoard(string _player1, string _player2, BattleShipBoard &playerBoard);
bool playTwoPlayerGame(string _nameOne, string _nameTwo, BattleShipBoard &_playerOneBoard, BattleShipBoard &_playerTwoBoard);


int main(){
	
	//Each player's board
	BattleShipBoard playerOneBoard;
	BattleShipBoard playerTwoBoard;

	//Lots of lines to make it appear as if the terminal screen was cleared.
	playerOneBoard.clearTerminalScreen();
	string playerOne,playerTwo;
	
	cout << "Welcome to Terminal Battleship! This game requires two players." << endl;

	//Player number is sent to function, and the name of the player is sent back.
	playerOne = retrieveName("1");
	playerTwo = retrieveName("2");
	
	//ask users if they want to setup their boards manually, or have the computer autommatically do it.
	setupPlayerBoard(playerOne,playerTwo,playerOneBoard);
	setupPlayerBoard(playerTwo,playerOne,playerTwoBoard);

	bool gameIsOver = false;
	bool playAgain = true; //declaration of play again 
	//Operate game, cycling between users until game is over.
	while (!gameIsOver){
		gameIsOver = playTwoPlayerGame(playerOne, playerTwo, playerOneBoard, playerTwoBoard);
		
		//Don't have the next player play if the other player has already won.
		if (!gameIsOver){
			gameIsOver = playTwoPlayerGame(playerTwo, playerOne, playerTwoBoard, playerOneBoard);
		}
	}

	playerOneBoard.clearTerminalScreen();
	//If all ships are sunk of player 2, then congratulate player 1, else player 2
	if (playerTwoBoard.allShipsSunk()){
		playerTwoBoard.congratsOnWinning(playerOne, playerTwo);
	}
	else{
		playerTwoBoard.congratsOnWinning(playerTwo, playerOne);
	}
	while(playAgain){
		setupPlayerBoard(string _name1, string _name2, BattleShipBoard &_playerBoard)
		char again; // for user to play again
		cout<<"Play again? Enter yes or no."<<endl;
		cin >> again;
		if(again != 'y'){
			playAgain = false;
		}
	}

    cout << "CU later!" << endl;    
}

//Setsup locations of battleship for each player.
void setupPlayerBoard(string _name1, string _name2, BattleShipBoard &_playerBoard){
	_playerBoard.clearTerminalScreen();
	cout << endl <<  _name1 << " will setup his/her board now. " << endl << _name2 << " please look away from the screen until " << _name1 <<" has finished setup." << endl;
	_playerBoard.pauseDialog();
	_playerBoard.assembleBoard();
	
	string userInput = " ";

	//Ask user if they want to manually control where their ships are placed, or if they want the computer to do this for them.
	while (userInput!="m" && userInput!="M" && userInput!="r" && userInput!="R"){
		cout << endl << "Type (m) to manually place your ships or type (r) to have the computer randomly place your ships then hit Enter: ";
		cin >> userInput;
	}

	//If the user selected manual, then call class method to give the user options on where to place ships.
	if (toupper(userInput[0]) == 'M'){
		_playerBoard.createShips();
	}
	else{ 
		//Else call class method to have computer determine
		_playerBoard.randomizeBoatPositions();
	}

	//Print out current user board
	cout << "Here is your board: " << endl;
	_playerBoard.printMyCurrentBoard();

	//Pause screen until user selects to continue
	_playerBoard.pauseDialog();
}

//Handles game, displaying boards and asking user to fire at a coordinate
bool playTwoPlayerGame(string _nameOne, string _nameTwo, BattleShipBoard &_nameOneBoard, BattleShipBoard &_nameTwoBoard){
	_nameOneBoard.clearTerminalScreen();
	cout << endl << "It is now " << _nameOne << "'s turn." << endl;
	
	//Pause screen until user selects to continue
	_nameOneBoard.pauseDialog();

	bool hitBattleship = true;
	int column, row;

	//While the user keeps hitting battleships, let them keep playing, uless they miss, or sink all battleships.
	while (hitBattleship && !_nameTwoBoard.allShipsSunk()){
		//Print current user board.
		cout << endl << "Your Board (note this is where your opponent has fired missiles):" << endl;
		_nameOneBoard.printMyCurrentBoard();

		//Print where user has striked opponents board.
		cout << endl << "Where you have struck: " << endl;
		_nameTwoBoard.printBoard();

		cout << " O = Missed ship" << endl;
		cout << " X = Hit ship" << endl;

		//Ask user where they would like to fire and retrieve this coordinate.
		cout << endl << "Where would you like to strike? " << endl;
		hitBattleship = _nameTwoBoard.strike();

		//If the user hits a battleship, let them know.
		if (hitBattleship == true){
			cout << endl << "SUCCESSFUL HIT! " << _nameOne << " plays again." << endl;
			//Pause screen until user selects to continue
			_nameTwoBoard.pauseDialog();
		}
	}

	//If the player has sunken all the oppenent's ships, then return true (that game is over)
	if (_nameTwoBoard.allShipsSunk()){
		return true;
	}
	else{
		return false;
	}
}

//Get the names of the players.
string retrieveName(string playerNumber){
	string name;
	bool correctResponse = false;
	
	//Don't continue program until the user has entered a name.
	while (!correctResponse){
		cout << "Please Enter the name of Player " << playerNumber << ": ";
		//cin.get(); //Gets extra character return that is sometimes picked up in getline.
		getline(cin,name);

		//Make sure name is not 0 characters long, and make sure that it is not longer than 10 characters.
		if (name.length()<=10 && name.length()>0){
			correctResponse = true;
		}
		else{
			cout << "Error. Please enter a name that is no longer than 10 characters, but has at least 1 character." << endl;
		}
	}
	return name;
}
