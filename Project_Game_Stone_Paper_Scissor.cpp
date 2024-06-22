
#include <iostream>
#include<cstdlib>

using namespace std;
void StartGame();
enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice PlayerChoice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName = "";

};
struct stGameResults
{

    short GameRounds = 0;
    short   Player1WonTimes;
    short   ComputerWonTimes;
    short  Drawtimes;
    enWinner GameWinner;
    string WinnerName = "";

};

int RandomNumber(int From, int To) {

    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

string Tabs(int NumberOfTabs) {


    for (int i = 0; i < NumberOfTabs; i++)
    {
        cout << "\t";

    }

    return "";

}

short ReadHowManyRounds() {

    short GameRounds = 0;
    do
    {
        cout << "How many Rounds 1 to 10 ?\n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

enGameChoice ReadPlayerChoice(){

    short Choice = 0;
    do
    {
        cout << "\n Your Choice: [1]:Ston, [2]:Paper ,[3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;


}

enGameChoice GetComputerChoice() {

    return (enGameChoice)RandomNumber(1,3);

}

enWinner WhoWonTheRound(stRoundInfo RoundInfo) {


    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw;
    }

    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone:
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Paper:
        if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
        {
            return enWinner::Computer;
        }
        break;
    case enGameChoice::Scissors:
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer;
        }
        break;
    }

    return enWinner::Player1;

}

string WinnerName(enWinner Winner) {

    string WinnerName[3]{ "Player1","Computer","No Winner" };
    return WinnerName[Winner - 1];
}

string ChoiceName(enGameChoice Choise) {

    string arrGameChoice[3]{ "Ston","Paper","Scissors" };
    return arrGameChoice[Choise - 1];

}

void SetWinnerScreenColor(enWinner Winner) {

    switch (Winner)
    {
    case enWinner::Player1:
        system("color 2F");
        break;
    case enWinner::Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
        break;
    }

}

void PrintRoundresult(stRoundInfo RoundInfo) {

    cout << "_________Round [" << RoundInfo.RoundNumber << "]_________\n";
    cout << "Player1  Choise: " << ChoiceName(RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choise: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner: [" << RoundInfo.WinnerName<<"]" << endl;
    cout << "___________________________\n" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}

enWinner WhoWonTheGame(short Player1WonTimes, short ComputerWonTimes) {

    if (Player1WonTimes > ComputerWonTimes)
        return enWinner::Player1;
    else if (Player1WonTimes < ComputerWonTimes)
        return enWinner::Computer;
    else
        return enWinner::Draw;
}

stGameResults FillGameResults(short GameRounds, short Player1WonTimes, short ComputerWonTimes, short Drawtimes) {

    stGameResults GameResults;

    GameResults.GameRounds = GameRounds;
    GameResults.Player1WonTimes = Player1WonTimes;
    GameResults.ComputerWonTimes = ComputerWonTimes;
    GameResults.Drawtimes = Drawtimes;
    GameResults.GameWinner =WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
    GameResults.WinnerName =WinnerName(GameResults.GameWinner);
   
    return GameResults;
}

stGameResults PlayGame(short HowManyRounds) {

    stRoundInfo RoundInfo;

    short Player1WonTimes = 0, ComputerWonTimes = 0, Drawtimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";

        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
            Player1WonTimes++;
        else if (RoundInfo.Winner == enWinner::Computer)
            ComputerWonTimes++;
        else
            Drawtimes++;

        PrintRoundresult(RoundInfo);

    }

    return FillGameResults(HowManyRounds, Player1WonTimes, ComputerWonTimes, Drawtimes);
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "_____________________________________________________\n\n";
    cout << Tabs(2) << "              +++ G A M E  O V E R+++\n\n";
    cout << Tabs(2) << "_____________________________________________________\n\n";
}

void RestScreen() {

    system("cls");
    system("color 0F");

}

void ShowFinalGameResults(stGameResults GameResults) {

    cout << Tabs(2) << "_____________________[ Game Results ]________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player1 win times  : " << GameResults.Player1WonTimes << endl;
    cout << Tabs(2) << "Computer win times : " << GameResults.ComputerWonTimes << endl;
    cout << Tabs(2) << "Draw times         : " << GameResults.Drawtimes << endl;
    cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "_____________________________________________________\n\n";
    
    SetWinnerScreenColor(GameResults.GameWinner);

}

void StartGame() {

    char PlayAgain = 'Y';

    do
    {
        RestScreen();
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{

    srand((unsigned)time(NULL));

    StartGame();


}

