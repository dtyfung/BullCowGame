/* The game logic (no view code or direct use interaction) 
The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

using FString = std::string;  // FString is mutable in the Unreal Convention
using int32 = int;			  // int32 for Unreal convention

// Structs have all public fields by default
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// Enum *class* allows class scope, while enum only has global scope
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Not_Lowercase,
	Wrong_Length,
};

// Class interface
class FBullCowGame 
{
public:
	FBullCowGame(); // constructor 

	// These methods aren't allowed to change other variable values of the object 
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void FBullCowGame::SetHiddenWord(FString);
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
