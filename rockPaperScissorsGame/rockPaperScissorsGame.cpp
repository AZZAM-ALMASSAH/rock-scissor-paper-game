// rockPaperScissorsGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib> 
#include <ctime> 

using namespace std;






enum enGameChoice { Rock=1,Paper=2,Scissors=3};

enum enWinner{Player1=1,Computer=2,Draw=3};

struct stRoundInfo { 

   
  
   
enWinner Winner;             
enGameChoice Player1Choice; 
enGameChoice ComputerChoice; 
string winnerName; 
short RoundCount=0;

};

struct stGameResults
{
    short GameRounds = 0;        
    short Player1WinTimes = 0;   
    short ComputerWinTimes = 0; 
    short DrawTimes = 0;         
    enWinner GameWinner;         
    string WinnerName = "";      
};
int randomNumber(int from ,int to) {
    return rand() % (to - from + 1) + from;
}

enGameChoice getComputerChoice() {
    return (enGameChoice)randomNumber(1, 3);
}

enWinner whoWonTheRound(stRoundInfo roundInfo) {
    if (roundInfo.ComputerChoice == roundInfo.Player1Choice) {
        return enWinner::Draw;
    }
    switch (roundInfo.Player1Choice) {
    case enGameChoice::Rock :{
        return (roundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
        }
    case enGameChoice::Paper: {
        return (roundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    }
    case enGameChoice::Scissors: {
        return (roundInfo.ComputerChoice == enGameChoice::Rock) ? enWinner::Computer : enWinner::Player1;
    }
    }
}

enWinner whoWonTheGame(short player1WinCount,short computerWinCount) {
    if (player1WinCount > computerWinCount) {
        return enWinner::Player1;
    }
    else if (computerWinCount > player1WinCount) {
        return enWinner::Computer;
    }
    else {
        return enWinner::Draw;
    }
}

string choiceName(enGameChoice choice) {
    string gameChoice[3] = { "Rock","Paper","Scissors" };
    return gameChoice[choice - 1];
}

string winnerName(enWinner winner) {
    string winnerName[3] = { "Player1","Computer","Draw" };
    return winnerName[winner - 1];
}

void setScreenColor(enWinner winner) {
    switch (winner) {
    case enWinner::Computer: {
        system("color 4F");
        cout << "\a";
        break;
    }
    case enWinner::Player1: {
        system("color 2F");
        break;
    }
    default:
        system("color 6F");
        break;
    }
}


enGameChoice readPlayerChoice() {
    
    short choice = 0;

    do {
        cout << "Your Choice : [1]:Rock, [2]:Paper, [3]:Scissors " << endl;
        cin >> choice;
    } while (choice < 1 || choice > 3);

    return (enGameChoice)choice;

}
int readHowManyTimes(string message) {
    int number = 0;
    do {
        cout << message << endl;
        cin >> number;
    } while (number <= 0 || number > 10);
    return number;
}
void showGameOver() {

    cout << "\t\t\t----------------------------------------------------------------" << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t+++GAME OVER+++" << endl;
    cout << endl;
    cout << "\t\t\t----------------------------------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "\t\t\t__________________________[GAME RESULTS]_________________________" << endl;
    
    
}
void showFinalGameResults(stGameResults info) {
    cout << "\t\t\tGame Rounds                 :" << info.GameRounds << endl;
    cout << "\t\t\tPlayer1 Won times           :" << info.Player1WinTimes << endl;
    cout << "\t\t\tcomputer won times          :" << info.ComputerWinTimes << endl;
    cout << "\t\t\tDraw times                  :" << info.DrawTimes << endl;
    cout << "\t\t\tGame Winner                 :" << info.WinnerName << endl;

}

char readPlayAgain(string message) {
    char answer= ' ';

    do {
        cout << message << endl;
        cin >> answer;
    } while (answer != 'y' && answer != 'n' && answer != 'Y' && answer != 'N');
    return answer;

}
void printRoundResult(stRoundInfo info) {
    cout << "\n____________ Round [" << info.RoundCount+1 << "] ____________\n\n";
    cout << "Player1 Choice: " << choiceName(info.Player1Choice) << endl;
    cout << "Computer Choice: " << choiceName(info.ComputerChoice) << endl;
    cout << "Round Winner: " << info.winnerName << endl;
    cout << "_________________________________________\n" << endl;
}
void resetScreen() {
    system("color 0F");
    system("cls");
}

stGameResults playGame(short roundsToPlay) {
    stRoundInfo info;
    short player1WinCount = 0; short computerWinCount = 0; short drawCount = 0;
    for (int i = 0; i < roundsToPlay; i++) {
        cout << "\nRound [" << i+1 << "] begins:\n";
        info.RoundCount = i;
        info.ComputerChoice = getComputerChoice();
        info.Player1Choice = readPlayerChoice();
        info.Winner = whoWonTheRound(info);
        info.winnerName = winnerName(info.Winner);

        setScreenColor(info.Winner);
            if (info.Winner == enWinner::Computer) {
                computerWinCount++;


            }
            else if (info.Winner == enWinner::Player1) {
                player1WinCount++;
            }
            else {
                drawCount++;
            }
        printRoundResult(info);
    };
    return { roundsToPlay ,player1WinCount,computerWinCount ,drawCount,  whoWonTheGame(player1WinCount, computerWinCount), winnerName(whoWonTheGame(player1WinCount, computerWinCount) )};
}
void startGame()
{
    char PlayAgain = ' ';
    
    do
    {
        resetScreen();
        stGameResults GameResults = playGame(readHowManyTimes("How many rounds you want to play :"));
        cout << "\nGame Over! Winner: " << GameResults.WinnerName << endl;
        showGameOver();
        showFinalGameResults(GameResults);
        PlayAgain= readPlayAgain("\nDo you want to play again? (Y/N): ");
        
       
      
    } while (PlayAgain != 'N' && PlayAgain != 'n');
}


int main()
{
    srand((unsigned)time(NULL));  
    startGame();
}

