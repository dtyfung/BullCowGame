/* 
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame Class.
*/

/* 
Future Improvements
	- Add timer to game
	- Include a dictionary of words for each word length
	- Denote letters which are bulls and cows
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// This reduces repetition of using :: but can conflict with same function of other libraries or multiple namespaces within a library
/*using namespace std;*/  

using FText = std::string; // FText is immutable in Unreal Convention (usually used for user interaction)
using int32 = int;		   // alias as 32 bit for crossplaform when going to Unreal

// Function prototypes as outside a class
void PrintIntro();
void SetHiddenWord();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we re-use across play

// This is the entry point of the application
int main()
{

	bool bPlayAgain = false;
	do {
		PrintIntro();
		SetHiddenWord();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		std::cout << std::endl;
	} 
	while (bPlayAgain);
	return 0; // exit application
}

void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << "    /       \\                _         _" << std::endl;
	std::cout << "    \\---v---/       _         \\---v---/ " << std::endl;
	std::cout << "    | \\   / |    __| |__      | ^   ^ | " << std::endl;
	std::cout << "    | o   o |   |__   __|     | _   _ | " << std::endl;
	std::cout << "    \\  oo   /      |_|        \\  oo   / " << std::endl;
	std::cout << "     \\__U__/                   \\__w__/ " << std::endl;	  
	std::cout << "     THE BULL                  THE COW \n" << std::endl;

	return;
}

void SetHiddenWord()
{
	FText WordLength;
	std::cout << "Please choose the word length (1-7): ";   // TODO make changes for length validation (edge cases)
	std::getline(std::cin, WordLength);
	BCGame.SetHiddenWord(WordLength);
	return;
}

// Plays a single game to completion 
void PlayGame()
{
	BCGame.Reset();

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	int32 MaxTries = BCGame.GetMaxTries();

	// Loop for the number of guesses while the game is NOT won 
	// and there are tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); 

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ". \n\n";
	}

	PrintGameSummary();
	return;
}

// Loop continually until a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status; // default error

	do {
		// Get a guess from a player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		// Check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word with all lowercase letters.\n\n";
			break;
		default:
			// assumes guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);   // loop looping until error-free
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";
	FText Response = "";
	std::getline(std::cin, Response);
    return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Good job, you win!\n";
	}
	else {
		std::cout << "Better luck next time!\n";
	}
	std::cout << std::endl;

	return;
}



	
