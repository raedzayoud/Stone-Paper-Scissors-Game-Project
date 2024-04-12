#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum GameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum Winner { Player1 = 1, Computer = 2, Draw = 3 };

struct RoundInfo {
    short RoundNumber = 0;
    GameChoice Player1Choice;
    GameChoice ComputerChoice;
    Winner RoundWinner;
    string WinnerName;
};
struct GameResults {
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    Winner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To) {
    // Fonction pour générer un nombre aléatoire
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}


string WinnerName(Winner winner) {
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner" };
    return arrWinnerName[winner - 1];
}
Winner WhoWonTheRound(RoundInfo RoundInfo) {
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice) {
        return Draw;
    }
    switch (RoundInfo.Player1Choice) {
    case Stone:
        if (RoundInfo.ComputerChoice == Paper) {
            return Computer;

        }
        break;
    case Paper:
        if (RoundInfo.ComputerChoice == Scissors) {
            return Computer;

        }
        break;

    case Scissors:
        if (RoundInfo.ComputerChoice == Stone) {
            return Computer;
        }
        break;
    }
    return Player1;

}

string ChoiceName(GameChoice Choice) {
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

void SetWinnerScreenColor(Winner Winner) {
    switch (Winner) {
    case Player1:
        system("color 2F"); // Écran en vert
        break;
    case Computer:
        system("color 4F"); // Écran en rouge
        cout << "\a"; // Faire un bip sonore
        break;
    default:
        system("color 6F"); // Écran en jaune
        break;
    }
}
void PrintRoundResults(RoundInfo RoundInfo) {
    cout << "\n____________Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1  Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "] \n";
    cout << "__________________________________\n" << endl;
    SetWinnerScreenColor(RoundInfo.RoundWinner);
}

Winner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes) {
    if (Player1WinTimes > ComputerWinTimes)
        return Player1;
    else if (ComputerWinTimes > Player1WinTimes)
        return Computer;
    else
        return Draw;
}
GameResults FillGameResults(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes) {
    GameResults Results;
    Results.GameRounds = GameRounds;
    Results.Player1WinTimes = Player1WinTimes;
    Results.ComputerWinTimes = ComputerWinTimes;
    Results.DrawTimes = DrawTimes;
    Results.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
    Results.WinnerName = WinnerName(Results.GameWinner);
    return Results;
}

GameChoice ReadPlayer1Choice() {
    short Choice = 1;
    do {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return static_cast<GameChoice>(Choice);
}

GameChoice GetComputerChoice() {
    return static_cast<GameChoice>(RandomNumber(1, 3));
}

GameResults PlayGame(short HowManyRounds) {
    RoundInfo Round;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++) {
        cout << "\nRound [" << GameRound << "] begins:\n";
        Round.RoundNumber = GameRound;
        Round.Player1Choice = ReadPlayer1Choice();
        Round.ComputerChoice = GetComputerChoice();
        Round.RoundWinner = WhoWonTheRound(Round);
        Round.WinnerName = WinnerName(Round.RoundWinner);

        // Incrémentation des compteurs de victoires/nuls
        if (Round.RoundWinner == Player1)
            Player1WinTimes++;
        else if (Round.RoundWinner == Computer)
            ComputerWinTimes++;
        else
            DrawTimes++;

        PrintRoundResults(Round);
    }

    return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs) {
    string t = "";
    for (int i = 1; i < NumberOfTabs; i++) {
        t = t + "\t";
        cout << t;
    }
    return t;
}

void ShowGameOverScreen() {
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";
}

void ShowFinalGameResults(GameResults Results) {
    cout << Tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << Tabs(2) << "Game Rounds        : " << Results.GameRounds << endl;
    cout << Tabs(2) << "Player1 won times  : " << Results.Player1WinTimes << endl;
    cout << Tabs(2) << "Computer won times : " << Results.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times         : " << Results.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner       : " << Results.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(Results.GameWinner);
}

short ReadHowManyRounds() {
    short GameRounds = 1;
    do {
        cout << "How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds;
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'Y';
    do {
        ResetScreen();
        GameResults Results = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(Results);

        cout << endl << Tabs(3) << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand(static_cast<unsigned>(time(NULL))); // Initialise le générateur de nombres aléatoires

    StartGame();

    return 0;
}
