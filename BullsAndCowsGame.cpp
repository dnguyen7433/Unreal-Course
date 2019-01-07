/* This is the console executable, that makes use of the FBullsAndCowsGame class.
 * This acts as the view in a MVC pattern, and is responsible for all.
 * user interaction. For game logics, see the FBullsAndCowsGame class.
 */
/*Future Improvements could be:
 * -Set the timer for the game
 * -Wider variety of hidden words
 * -Set up game tournament for multiple player; that is, the players are allowed to play for
 * specific number of turns, and those who won more turns would be the winner.
 */
#pragma once
#include <iostream>
#include <string>
#include "FBullsAndCowsGame.h"
// to make syntax Unreal friendly
using int32 = int;
using FText = std:: string;
FBullsAndCowsGame BCGame;
void PrintIntro(){
	// Introduction to the game of Bulls and Cows
	std:: cout << std:: endl;
	std:: cout << "    		Welcome to the Bulls and Cows game, a fun word game. \n";
	std:: cout << std:: endl;
	std:: cout << "\\_ |__  __ __|  | |  |   ______   ____  ______  _  ________"<< std:: endl;
	std:: cout << " | __ \\|  |  \\  | |  |  /  ___/ _/ ___\\/  _ \\ \\/ \\/ /  ___/"<< std:: endl;
	std:: cout << " | \\_\\ \\  |  /  |_|  |__\\___\\  \\  \\__(  <_> )     /\\___ \\ "<< std:: endl;
	std:: cout << " |___  /____/|____/____/____  >  \\___  >____/ \\/\\_//____  >"<< std:: endl;
	std:: cout << "     \\/                     \\/       \\/                 \\/ "<< std:: endl;
	std:: cout << "    		Do you know the hidden word I'm thinking of ? \n\n";
	std:: cout << std:: endl;
	return;
}

FText GetValidGuess (){

	int32 CurrentTry = BCGame.getCurrentTry();
	FText Guess = " ";
	EWordStatus Status;
	// looping until getting the valid guess from the user
	do{
		std:: cout << "Try " << CurrentTry << " of " << BCGame.getMaxTries() <<" . ";
		std:: cout << "Enter your guess here: ";
		getline (std:: cin, Guess);
		Status = BCGame.isGuessValid (Guess);
		switch (Status){
			case EWordStatus:: NOT_WordLength:
				std:: cout << "Please enter " << BCGame.getHiddenWordLength() <<" letter word." << std:: endl;
				break;
			case EWordStatus:: NOT_LowerCase:
				std:: cout << "Please enter your guess in lower case" << std:: endl;
				break;
			case EWordStatus:: NO_Isogram:
				std:: cout << "Please to enter a word without repeating letters ." << std:: endl;
				break;
			default:
				break;
		}
		}
		while (Status != EWordStatus::OK);
	return Guess;
}


void PlayGame() {
	BCGame.Reset();
	// Initialize the hidden word
	int32 Length = 0;
	std:: cout << "***You can choose the level of difficulty by choosing the hidden word length. \n";
	std:: cout << "   (the word length should be from 1 to 8, otherwise the default length would be 5) \n";
	std:: cout << "Please enter the hidden word length: ";
	std:: cin >> Length;
	std:: cout << std:: endl;
	BCGame.InitializeTheHiddenWord (Length);
	FText Guess = " ";
	int32 MaxTries = BCGame.getMaxTries();
	FBullCowCount BullCountCow;

	// loop to ask for guesses only if
		// the game is not won and there are still tries remaining
	while ((!BCGame.isGameWon()) && (BCGame.getCurrentTry () <= MaxTries)) {
		//get the valid guess, keep looping until I guess the valid guess
		Guess = GetValidGuess();
		// submit the guess to the game
		BullCountCow = BCGame.SubmitValidGuess (Guess);

		std:: cout << "Bulls: " << BullCountCow.Bulls << " ";
		std:: cout << "Cows: " << BullCountCow.Cows << "\n";
		std:: cout <<  std:: endl;
	}

}
void PrintGameSummary (){
	// print out the message "You won / You lose"
	if (BCGame.isGameWon ())// if the user won the game, print out "you won"
	{
		std:: cout << "GOOD JOB - YOU WON" << std:: endl;
	}
	else // if the user lost the game, print out "you lose"
	{
		std:: cout << "Good Luck Next Time!" << std:: endl;
	}
}
bool AskToPlayAgain(){
	// Asking the player to continue the game or not by entering yes or no
	FText response = " ";
	std:: cout << "Do you want to play again (y/n)?";
	std:: getline (std:: cin, response);
	return (response [0] == 'y') || (response [0] == 'Y');
}

// Entry Point
int main() {

	do{
		PrintIntro ();
		PlayGame();
		PrintGameSummary ();
	}
	while (AskToPlayAgain ());
	return 0;
}
