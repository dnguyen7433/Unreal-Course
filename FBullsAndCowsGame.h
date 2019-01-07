#pragma once
#ifndef FBullsAndCowsGame_H
#define FBullsAndCowsGame_H
#include <string>
using int32 = int;
using FString = std:: string ;
struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};
enum class EWordStatus {
	OK,
	NO_Isogram,
	NOT_LowerCase,
	NOT_WordLength
};

class FBullsAndCowsGame {
public:
	FBullsAndCowsGame ();
	void InitializeTheHiddenWord (int32);
	void Reset (); //Reset the length of the hidden word

	int32 getMaxTries () const;
	int32 getCurrentTry () const;
	int32 getHiddenWordLength()const;

	bool isGameWon () const;
	EWordStatus isGuessValid (FString );
	// count bulls and cows, and increasing try #
	FBullCowCount SubmitValidGuess (FString) ;

private:

	int32 MyCurrentTry ;
	FString MyHiddenWord; // must be isogram
	bool bIsGameWon;
	bool Isogram (FString);
	bool IsLowerCase (FString);

};
#endif


