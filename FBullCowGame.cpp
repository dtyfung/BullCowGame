#pragma once
#include "FBullCowGame.h"
#include <map>

#define TMap std::map    // TMap is in Unreal Convention 
using int32 = int;		 // Unreal convention

// Default Constructor
FBullCowGame::FBullCowGame() { Reset(); }

/* Getter methods */
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

/* Setter methods */
// Changes hidden word in game based on the user's length input (must be isogram)
void FBullCowGame::SetHiddenWord(FString WordLength) { 
	TMap<FString, FString> WordMap = { { "1", "a"},
							           { "2", "to" },
								       { "3", "car" },
								       { "4", "like" },
								       { "5", "house" },
								       { "6", "planet" },
								       { "7", "victory" } };
	MyHiddenWord = WordMap[WordLength];
	return;
}


int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries = { {1, 1}, { 2, 3 }, { 3 ,5 }, {4, 7}, {5, 10}, {6, 15} };
	if (GetHiddenWordLength() > 6)
	{
		return WordLengthToMaxTries[6];
	} 
	else
	{
		return WordLengthToMaxTries[GetHiddenWordLength()];
	}
}


void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())	
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK; 
	}
}

// Receives a VALID guess, increments turn, and returns bull and cow counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength();  // assuming same length as guess
	
	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) 
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			// if they match then
			if (Guess[MHWChar] == MyHiddenWord[GChar]) 
			{
				// increment bulls if they're in the same place
				if (MHWChar == GChar)	
				{
					BullCowCount.Bulls++;
				}
				else 
				{ 
					BullCowCount.Cows++;
				}
			}
		}
	}
	bGameWon = (BullCowCount.Bulls == GetHiddenWordLength());
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)       // let compiler determine type
	{
		Letter = tolower(Letter);  // handle mixed case
		if (LetterSeen[Letter])
		{
			return false; 
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;  // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
