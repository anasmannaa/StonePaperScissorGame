
#include <iostream>
using namespace std;

enum enWinner {Player = 1, Computer = 2, Dawin = 3};

enum enSelection {Stone = 1, Paper = 2, Scissor = 3};

struct stRoundResults
{
    short RoundNumber = 0;
    enSelection PlayerSelect;
    enSelection ComputerSelect;
    enWinner RoundWinner;
    string RoundWinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short PlayerWins = 0;
    short ComputerWins = 0;
    short DawnWins = 0;
    enWinner Winner;
    string WinnerName;
};

short RandomNumber(short From, short To)
{
    short randNum = rand() % (To - From + 1) + From;
    return randNum;
}

short ReadPostiveNumber(string Message, short MaxRoundNumbers)
{
    short Number;
    do
    {
        cout << "\n" << Message << endl;
        cin >> Number;
    } while ((Number < 0) && (Number >= MaxRoundNumbers));
    return Number;
}

enSelection ReadUserSelection(string Message)
{
    short Selection;
    cout << "\n" << Message;
    cin >> Selection;
    
    return (enSelection)Selection;
}

enSelection GetComputerSelection()
{
    return (enSelection)RandomNumber(1, 3);
}

enWinner GetRoundWinner(stRoundResults RoundResults)
{
    if (RoundResults.PlayerSelect == RoundResults.ComputerSelect)
    {
        return enWinner::Dawin;
    }
    switch (RoundResults.PlayerSelect)
    {
    case enSelection::Stone:
        if (RoundResults.ComputerSelect == enSelection::Paper)
            return enWinner::Computer;

    case enSelection::Scissor:
        if (RoundResults.ComputerSelect == enSelection::Stone)
            return enWinner::Computer;

    case enSelection::Paper:
        if (RoundResults.ComputerSelect == enSelection::Scissor)
            return enWinner::Computer;
    }

    return enWinner::Player;
}

enWinner WhoWonGame(short PlayerScore, short ComputerScore)
{
    if (PlayerScore > ComputerScore)
        return enWinner::Player;
    else if (PlayerScore < ComputerScore)
        return enWinner::Computer;
    else
        return enWinner::Dawin;
}

string GetNameOfEnum(enWinner Winner)
{
    string Name[3] = { "Player", "Computer", "Dawin" };
    return Name[Winner - 1];
}

stRoundResults PlayRound(short RoundNum)
{
    stRoundResults RoundResults;
    RoundResults.RoundNumber = RoundNum;
    RoundResults.PlayerSelect = ReadUserSelection("Your Choice: [1]Stone [2]Paper [3]Scissor? ");
    RoundResults.ComputerSelect = GetComputerSelection();
    RoundResults.RoundWinner = GetRoundWinner(RoundResults);
    RoundResults.RoundWinnerName = GetNameOfEnum(RoundResults.RoundWinner);
    return RoundResults;
}

string NameOfSelection(enSelection Selection)
{
    string Name[3] = { "Stone", "Paper", "Scissor" };
    return Name[Selection - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
    switch (Winner)
    {
    case Player:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << "\a";
        break;
    case Dawin:
        system("color 6F");
        break;
    default:
        break;
    }
}

void PrintRoundResult(stRoundResults RoundResults)
{
    cout << "\n\n-------------------" << "Round[" << RoundResults.RoundNumber << "]" << "-------------------\n";
    cout << "\nPlayer Choose: [" << NameOfSelection(RoundResults.PlayerSelect) << "]";
    cout << "\nPlayer Choose: [" << NameOfSelection(RoundResults.ComputerSelect) << "]";
    cout << "\nRound Winner: [" << RoundResults.RoundWinnerName << "]";
    cout << "\n------------------------------------------" << endl;

    SetWinnerScreenColor(RoundResults.RoundWinner);
}

void PrintResult(stGameResults GameResults)
{
    cout << "\nPlayer Wins  : [" << GameResults.PlayerWins << "]";
    cout << "\nComputer Wins: [" << GameResults.ComputerWins << "]";
    cout << "\nDawin Wins   : [" << GameResults.DawnWins << "]";
    cout << "\nDawin Wins   : [" << GameResults.WinnerName << "]";
    cout << "\n------------------------------------------" << endl;

    SetWinnerScreenColor(GameResults.Winner);
}

void PrintGameOver()
{
    cout << "\n--------------------------------------\n";
    cout << "\t\t ++ GAMEOVER ++ \t\t";
    cout << "\n--------------------------------------\n";
}

void PrintGameSummary(stGameResults GameResult)
{
    cout << "\nGame Rounds        =" << GameResult.GameRounds << ".";
    cout << "\nPlayer Won Times   =" << GameResult.PlayerWins << ".";
    cout << "\nComputer Won Times =" << GameResult.ComputerWins << ".";
    cout << "\nDawin Times        =" << GameResult.DawnWins << ".";
    cout << "\nFinal Winner       =" << GameResult.WinnerName << ".";
    SetWinnerScreenColor(GameResult.Winner);
}

stGameResults PlayGame(short Rounds)
{
    short PlayerWins = 0, ComputerWins = 0, DawinWins = 0;

    for (int i = 0; i < Rounds; i++)
    {
        cout << "\nRound [" << i + 1 << "] Begins\n";

        stRoundResults RoundResult = PlayRound(i + 1);

        if (RoundResult.RoundWinner == enWinner::Player)
            PlayerWins++;
        else if (RoundResult.RoundWinner == enWinner::Computer)
            ComputerWins++;
        else
            DawinWins++;

        PrintRoundResult(RoundResult);
    }

    stGameResults GameResult;
    GameResult.GameRounds = Rounds;
    GameResult.PlayerWins = PlayerWins;
    GameResult.ComputerWins = ComputerWins;
    GameResult.DawnWins = DawinWins;
    GameResult.Winner = WhoWonGame(GameResult.PlayerWins, GameResult.ComputerWins);
    GameResult.WinnerName = GetNameOfEnum(GameResult.Winner);

    return GameResult;

}

void ResetGame()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    string PlayAgain = "Y";
    do
    {
        ResetGame();
        stGameResults FinalResult = PlayGame(ReadPostiveNumber("How Many Rounds 1 / 10? ", 10));
        PrintGameOver();
        PrintResult(FinalResult);
        cout << "\nDo you want to play again Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == "Y" || PlayAgain == "y");
    
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}
