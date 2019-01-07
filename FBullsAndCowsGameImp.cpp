/*
 * The game logic (No view or No user interaction)
 */
#include "FBullsAndCowsGame.h"
#include <map>
#include <cctype>

// to make Unreal syntax friendly
#define TMap std:: map
using int32 = int;
using FString = std:: string ;

FBullsAndCowsGame:: FBullsAndCowsGame (){
	Reset ();
}
void FBullsAndCowsGame:: InitializeTheHiddenWord (int32 WordLength){
	switch(WordLength){
	case 1:
			MyHiddenWord = "z";
			break;
	case 2:
			MyHiddenWord = "as";
			break;
	case 3:
			MyHiddenWord = "ant";
			break;
	case 4:
			MyHiddenWord = "neck";
			break;
	case 5:
			MyHiddenWord = "lucky";
			break;
	case 6:
			MyHiddenWord = "planet";
			break;
	case 7:
			MyHiddenWord = "naughty";
			break;
	case 8:
			MyHiddenWord = "computer";
			break;
	default:
			MyHiddenWord = "begin";
			break;
	}
}
void FBullsAndCowsGame:: Reset (){
	const FString HIDDEN_WORD = "begin";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;

	bIsGameWon = false;

	return;
}
bool FBullsAndCowsGame:: Isogram (FString Guess) {
	if (Guess.length() <= 1)// if the guess is longer than 1 letter,
	{
		return true;
	}
	TMap <char, bool> LetterSeen; // set up the map
	std:: string alphabetTable = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < static_cast<int>(alphabetTable.length()); i++){ // initialize the map to make sure that it doesn't contain
																			// special character
		LetterSeen  [tolower (alphabetTable[i])] = false;
	}
	for (auto Letter: Guess)
	{
		Letter = tolower (Letter);// translate all letter to lower case
			if (LetterSeen[Letter]){// if the letters are in the map
				return false;				// then it is not a isogram
			}
			else {							// otherwise
				LetterSeen[Letter] = true;	// then add the letter to the map
			}
	}
	return true; // for example in cases where /0 is entered
}
bool FBullsAndCowsGame:: IsLowerCase (FString Guess){
	for (auto Letter: Guess){
		if (islower(Letter) == 0){
			return false; // if the letter are not in lower case, return false
		}
	}
	return true; // otherwise, return true
}
int32 FBullsAndCowsGame:: getMaxTries  ()const{
	TMap <int32, int32> WordLengthToMaxTries {{1,3},{2,3},{3,5},{4,5},{5,8},{6,10},{7,12},{8,15}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}
int32 FBullsAndCowsGame:: getCurrentTry  ()const{
	return MyCurrentTry;
}
int32 FBullsAndCowsGame:: getHiddenWordLength()const {
	return MyHiddenWord.length();
}
bool FBullsAndCowsGame:: isGameWon ()const{
	return bIsGameWon;
}
EWordStatus FBullsAndCowsGame:: isGuessValid (FString Guess ){
	if (!Isogram (Guess)){
		return EWordStatus:: NO_Isogram;//return error
	}
	else if (!IsLowerCase (Guess)){
		return EWordStatus:: NOT_LowerCase;//return error
	}
	else if (Guess.length() != getHiddenWordLength()){// if the guess length is wrong
		return EWordStatus:: NOT_WordLength;//return error
	}
	else {// otherwise
		return EWordStatus:: OK;// return OK
	}

}
// receive the valid guess
FBullCowCount FBullsAndCowsGame:: SubmitValidGuess (FString Guess) {
	MyCurrentTry ++;
	// set up a return variable
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();
	// loop through all letters in the guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
		// compare the letters against the hidden word
		for (int32 GuessChar = 0; GuessChar < WordLength; GuessChar++){
		if (Guess [GuessChar] == MyHiddenWord [MHWChar]){
			if (MHWChar == GuessChar){
				BullCowCount.Bulls ++;
			}
			else {
				BullCowCount.Cows ++;
			}
		}
		}
	}
	// decide if the user won the game or not

	if (BullCowCount.Bulls == getHiddenWordLength()){ // if the number of bulls equals the length of the hidden word, then won
		bIsGameWon = true;
	}
	return BullCowCount;
}

