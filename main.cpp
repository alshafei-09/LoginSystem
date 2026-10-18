#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <cctype>
#include <vector>
using namespace std;

string NumberStage[4] = { 
    "st",
    "nd",
    "rd",
    "th" };
string Level[19] = {
    "1S",
    "/2S",",2P",
    "/3S",",3P",
    "/4S",",3D",",4P",
    "/5S",",4D",",5P",
    "/6S",",4F",",5D",",6P" };
string ElectronCapacity[19] = {
    "2",
    "2","6",
    "2","6",
    "2","10","6",
    "2","10","6",
    "2","14","10","6",
    "2","14","10","6" };
string Print[19];

enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mixed = 4 };
enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixedd = 5 };
enum enChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Computer = 0, Player = 1, Draw = 2 };
enum enCharType { SmallLetter = 1, CapitalLetter = 2, SpecialCharacter = 3, Digit = 4 };

struct stUserLoginData
{
    string UserName;
    string PassWord;
};
struct sQuestion
{
    int FirstNum = 0, SecondNum = 0, Result = 0, Answer = 0;
    string Operation = "";
};
struct sQuizInfo
{
    int NumOfQuestions = 0, CorrectAnswers = 0, WrongAnswers = 0;
    enQuestionLevel QuestionLevel = enQuestionLevel::Mixed;
    sQuestion Question;
    enOperationType OperationType = enOperationType::Mixedd;
};
struct stInfo
{
    int Remain = 0;
    int N = 0;
};

stUserLoginData UserData;
vector <stUserLoginData> vecUsers;
fstream fUserData;
short Limit = 7;

void vMainMenu();

void vValidation(int& Number)
{
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << "It must be a \"NUMBER\" : ";
		cin >> Number;
	}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void vNumberZone(int& Number, int From, int To)
{
	while (Number > To || Number < From)
	{
		cout << "The Number must be (" << From << "-" << To << ") : ";
		cin >> Number;
		vValidation(Number);
	}
}

void vWordZone(string& Word, int From, int To)
{
	while (Word.length() > To || Word.length() < From && !(Word == "x" || Word == "X"))
	{
		if (Word.length() < From)
			cout << "Too short, ";
		else
			cout << "Too long, ";

		cout << "Must be (" << From << "-" << To << ") : ";
		cin >> Word;
	}
}

int iReadPositiveNumber(string Text)
{
    int Num;
    do{
        cout << Text;
        cin >> Num;
        vValidation(Num);
    } while (Num < 1);

    return Num;
}

int iGetRandNum(int From, int To)
{
    int RandNum = rand() % (To - From + 1) + From;
    return RandNum;
}

void vResetScreen()
{
    cout << "\033[2J\033[H" << flush;
}

bool bContinueProject(string Text)
{
    char Continue = ' ';
    do{
        cout << Text;
        cin >> Continue;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (!(Continue == 'y' || Continue == 'Y' || Continue == 'n' || Continue == 'N'));

    if (Continue == 'y' || Continue == 'Y')
        return 1;
    else
        return 0;
}

void vResetInfo(stInfo Info)
{
    Info.N = 0;
    Info.Remain = 0;
}

stInfo stCalculation(int Number)
{
    int i = 86;
    stInfo Info;

    vResetInfo(Info);
    Info.Remain = Number - i;

    if (Info.Remain < 0) 
    {
        i = 54;
        for (int j = 18; j >= 2; j -= 8)
        {
            for (i; i > 18; i -= 18)
            {
                Info.Remain = Number - i;
                Info.N++;
                if (Info.Remain >= 0) {
                    break;
                }
            }

            if (Info.Remain >= 0) {

                break;
            }
            else {
                Info.Remain = Number - j;
            }

            Info.N++;
        }
    }

    Info.N = 6 - Info.N;
    return Info;
}

string sgInertGas(stInfo Info)
{
    vResetInfo(Info);

    if (Info.N == 3 || Info.N == 4 || Info.N == 5)
        Info.N = 3 * Info.N - 4;
    else if (Info.N == 2 || Info.N == 6)
        Info.N = 3 * Info.N - 3;
    else if (Info.N == 1 || Info.N == 7)
        Info.N = 3 * Info.N - 2;

    for (int X = 0; X < Info.N; X++)
        Print[X] = Level[X] + ElectronCapacity[X];

    for (int X = 1; X < Info.N; X++)
        Print[0] += Print[X];

    if (Info.Remain == -1)
        Print[0] = "1S1";

    return Print[0];
}

string sgRemain(stInfo Info)
{
    vResetInfo(Info);
    string Result = "";

    if (Info.Remain > 0) {

        if (Info.Remain >= 2) {
            Info.Remain -= 2;
            Result = to_string(Info.N + 1) + "S" + "2,";
        }
        else {
            Result = to_string(Info.N + 1) + "S" + to_string(Info.Remain);
            Info.Remain = 0;
        }

        if (Info.N + 1 >= 6) {

            if (Info.Remain < 15 && Info.Remain > 0)
            {
                Result += to_string(Info.N - 1) + "F" + to_string(Info.Remain - 1) + ",";
                Result += to_string(Info.N) + "D" + "1,";
                Info.Remain = 0;
            }
            else
            {
                if (Info.Remain >= 14) {
                    Info.Remain -= 14;
                    Result += to_string(Info.N - 1) + "F" + "14,";
                }
                else if (Info.Remain > 0) {
                    Result += to_string(Info.N - 1) + "F" + to_string(Info.Remain);
                    Info.Remain = 0;
                }

                if (Info.Remain >= 10) {
                    Info.Remain -= 10;
                    Result += to_string(Info.N) + "D" + "10,";
                }
                else if (Info.Remain > 0) {
                    Result += to_string(Info.N) + "D" + to_string(Info.Remain);
                    Info.Remain = 0;
                }
            }

            if (Result == "6S2,4F14,5D4")
                Result = "6S1,4F14,5D5";
            else if (Result == "6S2,4F14,5D9")
                Result = "6S1,4F14,5D10";
            else if (Result == "7S2,5F14,6D4")
                Result = "7S1,5F14,6D5";
            else if (Result == "7S2,5F14,69")
                Result = "7S1,5F14,6D10";

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }
        }
        else if (Info.N + 1 >= 4) {

            if (Info.Remain >= 10) {
                Info.Remain -= 10;
                Result += to_string(Info.N) + "D" + "10,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N) + "D" + to_string(Info.Remain);
                Info.Remain = 0;
            }

            if (Result == "4S2,3D4")
                Result = "4S1,3D5";
            else if (Result == "4S2,3D9")
                Result = "4S1,3D10";
            else if (Result == "5S2,4D4")
                Result = "5S1,4D5";
            else if (Result == "5S2,4D9")
                Result = "5S1,4D10";

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }

        }
        else if (Info.N + 1 >= 2) {

            if (Info.Remain >= 6) {
                Info.Remain -= 6;
                Result += to_string(Info.N + 1) + "P" + "6,";
            }
            else if (Info.Remain > 0) {
                Result += to_string(Info.N + 1) + "P" + to_string(Info.Remain);
                Info.Remain = 0;
            }
        }
    }

    if (Result != "") {
        Result = "/" + Result;
    }

    return Result;
}

void vStart(bool YesOrNo)
{
    if (YesOrNo == 1)
    {
        int Number = iReadPositiveNumber("Please enter the atomic number : ");
        vNumberZone(Number, 1, 118);

        string InvertGas = sgInertGas(stCalculation(Number));
        string Remain = sgRemain(stCalculation(Number));

        cout << endl << InvertGas + Remain << endl;
        cout << "\n--------------------------------------------\n";
    }
}

void vElectronConfiguration()
{
    vResetScreen();
     do{
         vStart(1);
     } while (bContinueProject("\nDo you want to Continue?... (y/n): "));
}

void vFillQuizInfo(sQuizInfo& Info)
{
    Info.NumOfQuestions = 0, Info.CorrectAnswers = 0, Info.WrongAnswers = 0;

    do{
        Info.NumOfQuestions = iReadPositiveNumber("How many questions do you want to answer 1 to 100 : ");
    } while (Info.NumOfQuestions > 100);

    do{
        Info.QuestionLevel = (enQuestionLevel)iReadPositiveNumber("Enter question level, [1] Easy, [2] Med, [3] Hard, [4] Mixed : ");
    } while (Info.QuestionLevel > 4);

    do{
        Info.OperationType = (enOperationType)iReadPositiveNumber("Enter operation type, [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mixed : ");
    } while (Info.OperationType > 5);
}

void vQuestionLevelDetection(sQuizInfo& Info, enQuestionLevel Level)
{
    Info.Question.FirstNum = iGetRandNum(1, 9), Info.Question.SecondNum = iGetRandNum(1, 9);

    if (Level != enQuestionLevel::Easy && Level != enQuestionLevel::Mixed)
    {
        Info.Question.FirstNum = iGetRandNum(10, 100);

        if (Level == enQuestionLevel::Hard)
            Info.Question.SecondNum = iGetRandNum(10, 100);
    }
    else if (Level == enQuestionLevel::Mixed)
        Info.Question.FirstNum = iGetRandNum(1, 100), Info.Question.SecondNum = iGetRandNum(1, 100);
}

string sgQuestionLVLNumToString(enQuestionLevel Level)
{
    string QuestionLevel[4] = { "Easy", "Med", "Hard", "Mixed" };
    return QuestionLevel[Level - 1];
}

void vOperationTypeDetection(sQuizInfo& Info, enOperationType Type)
{
    if (Type == enOperationType::Add)
    {
        Info.Question.Result = Info.Question.FirstNum + Info.Question.SecondNum;
        Info.Question.Operation = "+";
    }
    else if (Type == enOperationType::Sub)
    {
        Info.Question.Result = Info.Question.FirstNum - Info.Question.SecondNum;
        Info.Question.Operation = "-";
    }
    else if (Type == enOperationType::Mul)
    {
        Info.Question.Result = Info.Question.FirstNum * Info.Question.SecondNum;
        Info.Question.Operation = "*";
    }
    else if (Type == enOperationType::Div)
    {
        Info.Question.Result = round((double)Info.Question.FirstNum / (double)Info.Question.SecondNum);
        Info.Question.Operation = "/";
    }
}

void vOperationDetection(sQuizInfo& Info, enOperationType Type)
{
    if (Type != enOperationType::Mixedd)
    {
        vOperationTypeDetection(Info, Type);
    }
    else if (Type == enOperationType::Mixedd)
    {
        Type = (enOperationType)iGetRandNum(1, 4);
        vOperationTypeDetection(Info, Type);
    }
}

string sgOperationNumToString(enOperationType Type)
{
    string OperationType[5] = { "+", "-", "*", "/", "Mixed" };
    return OperationType[Type - 1];
}

void vPrintQuestion(sQuizInfo& Info)
{
    cout << to_string(Info.Question.FirstNum) << endl;
    cout << to_string(Info.Question.SecondNum) << " ";
    cout << Info.Question.Operation << endl;
    cout << "__________\n";
    cin >> Info.Question.Answer;

    vValidation(Info.Question.Answer);
}

bool IsAnswwerCorrect(sQuizInfo Info, int Answer)
{
    if (Answer == Info.Question.Result)
        return true;
    else
        return false;
}

void vQuiz(sQuizInfo& Info)
{
    for (int Question = 1; Question <= Info.NumOfQuestions; Question++)
    {
        cout << "\nQuestion [" << Question << "/" << Info.NumOfQuestions << "]\n\n";

        vQuestionLevelDetection(Info, Info.QuestionLevel);

        vOperationDetection(Info, Info.OperationType);

        vPrintQuestion(Info);

        if (IsAnswwerCorrect(Info, Info.Question.Answer))
        {
            cout << "\nCorrect Answer :-)";
            Info.CorrectAnswers++;
        }
        else
        {
            cout << "\nWrong Answer :-(\n\a" << "The Correct answer is : " << Info.Question.Result;
            Info.WrongAnswers++;
        }

        cout << endl;
    }

}

void vFinalResult(sQuizInfo Info)
{
    if (Info.CorrectAnswers >= Info.WrongAnswers)
    {
        cout << "\n\n================================\n";
        cout << " Fianl Result is Pass :-)";
        cout << "\n================================\n";
    }
    else
    {
        cout << "\n\n================================\n";
        cout << " Fianl Result is Fail :-(\a";
        cout << "\n================================\n";
    }
}

void vQuizResult(sQuizInfo Info)
{
    vFinalResult(Info);
    cout << "\nNumber of questions : " << Info.NumOfQuestions;
    cout << "\nQuestion Level      : " << sgQuestionLVLNumToString(Info.QuestionLevel);
    cout << "\nOperation Type      : " << sgOperationNumToString(Info.OperationType);
    cout << "\nYour Percentage     : " << ((double)Info.CorrectAnswers / (double)Info.NumOfQuestions) * 100 << "%";
    cout << "\nCorrect Answers     : " << Info.CorrectAnswers;
    cout << "\nWrong Answers       : " << Info.WrongAnswers;
    cout << "\n================================\n";
}

void vStartQuiz()
{
    sQuizInfo Info;
    do{
        vResetScreen();
        vFillQuizInfo(Info);
        vQuiz(Info);
        vQuizResult(Info);
    } while (bContinueProject("\nDo you want to Continue?... (y/n): "));
}

void vMathQuiz()
{
    srand((unsigned)time(NULL));
    vStartQuiz();
}


string sgChoiceNumToString(int ChoiceNum)
{
    if (ChoiceNum == enChoice::Stone)
        return "Stone";
    else if (ChoiceNum == enChoice::Paper)
        return "Paper";
    else
        return "Scissors";
}

enWinner eGameRules(int PlayerChoice, int ComputerChoice)
{
    if (PlayerChoice == ComputerChoice)
        return enWinner::Draw;

    if (PlayerChoice == enChoice::Stone)
    {
        if (ComputerChoice == enChoice::Paper)
            return enWinner::Computer;
    }
    else if (PlayerChoice == enChoice::Paper)
    {
        if (ComputerChoice == enChoice::Scissors)
            return enWinner::Computer;
    }
    else if (PlayerChoice == enChoice::Scissors)
    {
        if (ComputerChoice == enChoice::Stone)
            return enWinner::Computer;
    }

    return enWinner::Player;
}

void vRoundWinnerDetectoin(enWinner Winner, int& CopmuterWins, int& PlayerWins, int& Draws)
{
    if (Winner == enWinner::Computer)
    {
        cout << "Computer\a";
        CopmuterWins++;
    }
    else if (Winner == enWinner::Player)
    {
        cout << "Player";
        PlayerWins++;
    }
    else if (Winner == enWinner::Draw)
    {
        cout << "Draw";
        Draws++;
    }
}

void vRound(int Num, int& PlayerChoice, int ComputerChoice)
{
    cout << "\nRound [" << Num << "] begins : \n";

    do{
        string Text = "[1]Stone,[2]Paper,[3]Scissors, Your Choice : ";
        PlayerChoice = iReadPositiveNumber(Text);
    } while (PlayerChoice > 3);
}

void vRoundResult(int Num, int PlayerChoice, int ComputerChoice, int& CopmuterWins, int& PlayerWins, int& Draws)
{
    cout << "\n================== Round [" << Num << "] ==================\n";
    cout << "Player Choice : " << sgChoiceNumToString(PlayerChoice);
    cout << "\nComputer Choice : " << sgChoiceNumToString(ComputerChoice);
    cout << "\nRound Winner : [";
    vRoundWinnerDetectoin(eGameRules(PlayerChoice, ComputerChoice), CopmuterWins, PlayerWins, Draws);
    cout << "]";
    cout << "\n===============================================\n";
}

void vGame(int NumOfRounds, int& CopmuterWins, int& PlayerWins, int& Draws)
{
    for (int i = 1; i <= NumOfRounds; i++)
    {
        int PlayerChoice = 0, ComputerChoice = iGetRandNum(1, 3);

        vRound(i, PlayerChoice, ComputerChoice);
        vRoundResult(i, PlayerChoice, ComputerChoice, CopmuterWins, PlayerWins, Draws);
    }
}

void vGameWinnerDetectoin(int CopmuterWins, int PlayerWins)
{
    if (CopmuterWins == PlayerWins)
        cout << "No Winner";
    else if (CopmuterWins > PlayerWins)
        cout << "Computer\a";
    else
        cout << "Player";
}

void vGameEndedScreenWord(int CopmuterWins, int PlayerWins)
{
    if (CopmuterWins == PlayerWins)
        cout << "\t\t\t\t\t\tD r a w \n\n";
    else if (CopmuterWins > PlayerWins)
        cout << "\t\t\t\t\t  G A M E  O V E R\n\n";
    else
        cout << "\t\t\t W i n n e r  W i n n e r  C h i c k e n  D i n n e r \n\n";
}

void vGameResult(int NumOfRounds, int CopmuterWins, int PlayerWins, int Draws)
{
    cout << endl << endl;
    cout << "\t\t\t========================================================\n\n";
    vGameEndedScreenWord(CopmuterWins, PlayerWins);
    cout << "\t\t\t========================================================\n\n";
    cout << "\t\t\t______________________[Game Result]_____________________\n";
    cout << "\n\t\t\tGame rounds        : " << NumOfRounds;
    cout << "\n\t\t\tPlayer won times   : " << PlayerWins;
    cout << "\n\t\t\tComputer won times : " << CopmuterWins;
    cout << "\n\t\t\tDraw times         : " << Draws;
    cout << "\n\t\t\tFinal Winner       : ";  vGameWinnerDetectoin(CopmuterWins, PlayerWins);
    cout << "\n\t\t\t========================================================\n\n";
    cout << endl;
}

void vMiniGame()
{
    srand((unsigned)time(NULL));
    do {
        vResetScreen();
        int NumOfRounds = 0;
        do{
            NumOfRounds = iReadPositiveNumber("How many rounds 1 to 10 : ");
        } while (NumOfRounds > 10);

        int CopmuterWins = 0, PlayerWins = 0, Draws = 0;

        vGame(NumOfRounds, CopmuterWins, PlayerWins, Draws);
        vGameResult(NumOfRounds, CopmuterWins, PlayerWins, Draws);

    } while (bContinueProject("\nDo you want to Continue?... (y/n): "));
}


char cGetRandomChar(enCharType CharType)
{
    if (CharType == enCharType::CapitalLetter)
        return char(iGetRandNum(97, 122));
    else if (CharType == enCharType::SmallLetter)
        return char(iGetRandNum(65, 90));
    else if (CharType == enCharType::SpecialCharacter)
        return char(iGetRandNum(33, 47));
    else if (CharType == enCharType::Digit)
        return char(iGetRandNum(48, 57));
    else
        return cGetRandomChar((enCharType)iGetRandNum(1, 4));
}

enCharType iReadCharType()
{
    int CharType;

    cout << "[1] Capital Letter\n";
    cout << "[2] Small Letter\n";
    cout << "[3] Special Character\n";
    cout << "[4] Digit\n";
    cout << "[5] Mixed\n";
    cout << "Enter character type: ";
    cin >> CharType;
    vValidation(CharType);
    vNumberZone(CharType, 1, 5);

    return (enCharType)CharType;
}

string sgGetRandWord(int Length, enCharType CharType)
{
    string Word = "";

    for (int i = 1; i <= Length; i++)
    {
        Word += cGetRandomChar(CharType);
    }

    return Word;
}

string sgGetRandKey(int NumOfWords, int WordLength, enCharType CharType)
{
    string Key = "";

    for (int i = 1; i <= NumOfWords; i++)
    {
        Key += sgGetRandWord(WordLength, CharType);

        if (i < NumOfWords)
        {
            Key += "-";
        }

    }

    return Key;
}

void vGetArray(string Arr[100], int NumOfElements, int NumOfWords, int WordLength, enCharType CharType)
{
    for (int i = 0; i < NumOfElements; i++)
    {
        Arr[i] = sgGetRandKey(NumOfWords, WordLength, CharType);
    }
}

void vPrintArray(string Arr[100], int NumOfElements)
{
    string Space;
    for (int i = 0; i < NumOfElements; i++)
    {
        if (i + 1 < 10)  Space = "]  : ";
        else if (i < 100) Space = "] : ";
             else         Space = "] : ";
        cout << "Array [" << i + 1 << Space << Arr[i] << endl;
    }
}

void vGenerateRandomKeys()
{
    string Array[100];
    int NumOfElements = iReadPositiveNumber("Please, Enter the number of elements : "); \
        vNumberZone(NumOfElements, 1, 100);
    int NumOfWords = iReadPositiveNumber("Please, Enter the number of words : ");
        vNumberZone(NumOfWords, 1, 100);
    int WordLength = iReadPositiveNumber("Please, Enter the Length of word : ");
        vNumberZone(WordLength, 1, 100);
    enCharType CharType = iReadCharType();


    vGetArray(Array, NumOfElements, NumOfWords, WordLength, CharType);

    cout << "\nArray elements: \n";
    vPrintArray(Array, NumOfElements);
    cout << "\n------------------------------------------\n";
}

void vGenerateRandomKeysScreen()
{
    vResetScreen();
    do {
        vGenerateRandomKeys();
    } while (bContinueProject("\nDo you want to Continue?... (y/n): "));
}


bool bReturnToMainMenuScreen(string esc = "")
{
    if (esc == "")
    {
        cout << endl;
        while (!(esc == "x" || esc == "X"))
        {
            cout << "Enter [x] to return to the MAIN MENU: ";
            cin >> esc;
        }
    }

    if (esc == "x" || esc == "X")
    {
        vMainMenu();
        return 1;
    }
    return 0;
}

void vFillVectorFromFile(string FileName)
{
    if (vecUsers.size() == 0)
    {
        fUserData.open(FileName, ios::in);

        if (fUserData.is_open())
        {
            if (UserData.UserName == "")
            {
                while (getline(fUserData, UserData.UserName) &&
                    getline(fUserData, UserData.PassWord)) {
                    vecUsers.push_back(UserData);
                }
            }

            fUserData.close();
        }
    }
}

void vFillFileFromVector(string FileName)
{
    if (fUserData.is_open())
        fUserData.close();
    
    fUserData.open(FileName, ios::out | ios::app);

    if (fUserData.is_open())
    {
        for (stUserLoginData& Counter : vecUsers)
        {
           if(!(Counter.UserName == "" && Counter.PassWord == ""))
            {
                fUserData << Counter.UserName << endl;
                fUserData << Counter.PassWord << endl;
            }
        }

        fUserData.close();
    }
}

bool bAccountIsFound(string FileName, string UserName, string PassWord)
{
    vFillVectorFromFile(FileName);
    for (stUserLoginData& Counter : vecUsers)
    {
        if (UserName == Counter.UserName && PassWord == Counter.PassWord)
            return 1;
    }

    return 0;
}

int iCheckFreeDataBase(string FileName)
{
    vFillVectorFromFile(FileName);

    return vecUsers.size();
}

bool bIsUserNameExist(string FileName, string &UserName)
{
    vFillVectorFromFile(FileName);
    for (stUserLoginData& Counter : vecUsers)
    {
        if (UserName == Counter.UserName)
            return 1;
    }
    return 0;
}

void vReadUserName(string FileName, string& UserName)
{
    cin >> UserName;
    vWordZone(UserName, 3, 14);

    while ((bIsUserNameExist(FileName, UserName) || UserName == "admin") &&
          !(UserName == "x" || UserName == "X")) {

        cout << "Sorry, This Username is NOT available !!, Try again...\n";
        cout << "Username: ";
        cin >> UserName;
        vWordZone(UserName, 3, 14);
    }
}

void vCreateNewAccount(string FileName)
{
    vResetScreen();

    vFillVectorFromFile(FileName);

    if (vecUsers.size() == Limit)
    {
        cout << "Sorry, Your Account limit is OVER\n";
        bReturnToMainMenuScreen();
    }
    else
    {
        cout << "Enter [x] to back to MAIN MENU\n";
        cout << "Username: ";
        vReadUserName(FileName, UserData.UserName);
        
        if (!bReturnToMainMenuScreen(UserData.UserName))
        {
            cout << "Password: ";
            cin >> UserData.PassWord;
            vWordZone(UserData.PassWord, 5, 14);
            if (!bReturnToMainMenuScreen(UserData.PassWord))
            {
                cout << "\nDONE...";
                vecUsers.push_back(UserData);

                fUserData.open(FileName, ios::out | ios::app);
                if (fUserData.is_open())
                {
                    fUserData << UserData.UserName << endl;
                    fUserData << UserData.PassWord << endl;
                    fUserData.close();
                }
                bReturnToMainMenuScreen();
            }
        }
    }
}

int iAccountNumToDelete()
{
    string Deletion;
    int AccountNum = 0;

    while (!(Deletion == "y" || Deletion == "Y" || Deletion == "n" || Deletion == "N"))
    {
        cout << "Do you want to DELETE an account (y/n)?...";
        cin >> Deletion;
    }

    if (Deletion == "y" || Deletion == "Y")
    {
        cout << "Enter the number of the account: ";
        cin >> AccountNum;

        vNumberZone(AccountNum, 1, vecUsers.size());
        vValidation(AccountNum);
    }

    return AccountNum;
}

void vDeleteAccount(string FileName, int AccountNum)
{
    for(int i = AccountNum - 1; i < vecUsers.size() - 1; i++)
    {
        vecUsers[i].UserName = vecUsers[i + 1].UserName;
        vecUsers[i].PassWord = vecUsers[i + 1].PassWord;
    }

    if(AccountNum > 0)
    {
        vecUsers.pop_back();

        fUserData.open(FileName, ios::out | ios::trunc);
        fUserData.close();
        vFillFileFromVector(FileName);
    }
}

void vResetAll(string FileName)
{
    string Reset;
    vResetScreen();

    while (!(Reset == "y" || Reset == "Y" || Reset == "n" || Reset == "N"))
    {
        cout << "Are you sure (y/n)?...";
        cin >> Reset;
    }

    if (Reset == "y" || Reset == "Y")
    {
        fUserData.open(FileName, ios::out | ios::trunc);
        fUserData.close();
        vecUsers.clear();

        cout << "\nDONE...";
    }

    bReturnToMainMenuScreen();
}

void vNoDataFoundScreen()
{
    vResetScreen();

    cout << "NO DATA FOUND!!\n";

    bReturnToMainMenuScreen();
}

void vUserAccounts(string FileName)
{
    vFillVectorFromFile(FileName);

    if (vecUsers.size() == 0)
        vNoDataFoundScreen();
    else
    {
        vResetScreen();
        
        int i = 1;
        for (stUserLoginData& Counter : vecUsers)
        {
            cout << "[" << i++ << "]\n";
            cout << "Username: " << Counter.UserName;
            cout << "\nPassword: " << Counter.PassWord;
            cout << endl << endl;
        }

        vDeleteAccount(FileName, iAccountNumToDelete());
        bReturnToMainMenuScreen();
    }
}

void vAdminAccount(string);

void vReadScreenNumber(int ScreenNumber, string AdminFIleName, bool AdminOrNot)
{
    int MaxNumber = 4;
    if (AdminOrNot == 1)
        MaxNumber = 5;
    vValidation(ScreenNumber);
    vNumberZone(ScreenNumber, 0, MaxNumber);

    if (ScreenNumber == 1)
        vMathQuiz();
    else if (ScreenNumber == 2)
        vMiniGame();
    else if (ScreenNumber == 3)
        vElectronConfiguration();
    else if (ScreenNumber == 4)
        vGenerateRandomKeysScreen();
    else if (ScreenNumber == 5)
        vAdminAccount(AdminFIleName);
    else if (ScreenNumber == 0)
        vMainMenu();
}

void vProjectMenu(int& ScreenNumber, string AdminFIleName, bool AdminOrNot)
{
    cout << "===========================\n";
    cout << "       W E L C O M E       \n";
    cout << "===========================\n";
    cout << "[1] Math Quiz\n";
    cout << "[2] Rock, Paper, Scissor\n";
    cout << "[3] Electron Configuration\n";
    cout << "[4] Generate Random Keys\n"; 
    if(AdminOrNot == 1)
    cout << "[5] Back to Admin Menu\n"; 
    cout << "[0] Logout\n";
    cout << "===========================\n";
    cin >> ScreenNumber;
    vReadScreenNumber(ScreenNumber, AdminFIleName, AdminOrNot);
}

void vUserAccountDetector(string AdminFIleName, bool AdminOrNot)
{
    string Stage;
    int ScreenNum = 0;
    do {
        vResetScreen();
        vProjectMenu(ScreenNum, AdminFIleName, AdminOrNot);
    } while (ScreenNum != 0);
}

void vSetSecretCode(string AdminFIleName, string &SecretCode)
{
    string Temp = "";
    fstream AdminFile;
    AdminFile.open(AdminFIleName, ios::out | ios::in);
    if (AdminFile.is_open())
    {
        getline(AdminFile, Temp);

        if (Temp != "")
            SecretCode = Temp;

        AdminFile.close();
    }
}

void vEditSecretCode(string AdminFIleName)
{
    int newSecretCode = 0, SecretCodeConfirmation = 0;
    fstream AdminFile;
    AdminFile.open(AdminFIleName, ios::out);

    if (AdminFile.is_open())
    {
        vResetScreen();

        do{ 
            if (SecretCodeConfirmation != newSecretCode)
            {
                vResetScreen();
                cout << "Non-indetical, Try again...\n";

            }
            cout << "Enter the new Secret Code: ";
            cin >> newSecretCode;
            vValidation(newSecretCode);
            cout << "Enter it again: ";
            cin >> SecretCodeConfirmation;
            vValidation(SecretCodeConfirmation);
        }while (SecretCodeConfirmation != newSecretCode);

        AdminFile << newSecretCode;
        AdminFile.close();

        vAdminAccount(AdminFIleName);
    }
}

void vReadScreenNumber(int ScreenNumber, string AdminFIleName)
{
    vValidation(ScreenNumber);
    vNumberZone(ScreenNumber, 0, 2);

    if (ScreenNumber == 1)
        vUserAccountDetector(AdminFIleName, 1);
    else if (ScreenNumber == 2)
        vEditSecretCode(AdminFIleName);
    else if (ScreenNumber == 0)
        vMainMenu();
}

void vAdminAccount(string AdminFIleName)
{
    vResetScreen();
    int ScreenNumber;
    cout << "==========================\n";
    cout << "    A D M I N  M E N U    \n";
    cout << "==========================\n";
    cout << "[1] Project Menu\n";
    cout << "[2] Edit Secret Code\n"; 
    cout << "[0] Logout\n";
    cout << "==========================\n";
    cin >> ScreenNumber;
    vReadScreenNumber(ScreenNumber, AdminFIleName);
}

bool bAdminAccountLogin(string AdminFIleName, string UserName, string PassWord)
{
    string Answer = "", SecretCode = "41412";
    vSetSecretCode(AdminFIleName, SecretCode);
    int Try = 2;

    if (UserName == "admin" && PassWord == "admin")
    {
        while (Try > 0)
        {
            cout << "Secret Code: ";
            cin >> Answer;

            if (Answer == SecretCode)
            {
                vAdminAccount(AdminFIleName);
                return 1;
            }
            else if (Answer == "exit")
            {
                vMainMenu();
                return 1;
            }
            else if (Try == 2)
            {
                cout << "Invalid!!, Try again...\n";
                Try--;
            }
            else
                break;
        }
    }
    
    return 0;
}

void vLoginFaild(string FileName, string AdminFIleName,string& UserName, string& PassWord, short Try)
{
    while (!bAccountIsFound(FileName, UserName, PassWord) && Try != 0)
    {
        vResetScreen();

        cout << "\"Sorry, The USERNAME or the PASSWORD is wrong, Try again\"\n\n";
        cout << "Enter [x] to back to MAIN MENU\n";
        cout << "Username: ";
        cin >> UserName;
        vWordZone(UserName, 3, 14);
        if (!bReturnToMainMenuScreen(UserName))
        {
            cout << "Password: ";
            cin >> PassWord;
            vWordZone(PassWord, 5, 14);
            if (bAdminAccountLogin(AdminFIleName, UserName, PassWord))
                break;
            else if (bReturnToMainMenuScreen(PassWord))
                break;
            else
                Try--;
        }
        else
            break;

        if (Try == 0)
        {
            vResetScreen();

            cout << "\"Try again later\"\n";

            bReturnToMainMenuScreen();
        }
    }
}

void vLoginScreen(string FileName, string AdminFIleName)
{
    vResetScreen();
    string UserName, PassWord;
    short Try = 5;

    cout << "Enter [x] to back to MAIN MENU\n";
    cout << "Username: ";
    cin >> UserName;
    vWordZone(UserName, 3, 14);
    if (!bReturnToMainMenuScreen(UserName))
    {
        cout << "Password: ";
        cin >> PassWord;
        vWordZone(PassWord, 5, 14);
        if (!bReturnToMainMenuScreen(PassWord))
        {
            if (!(bAdminAccountLogin(AdminFIleName, UserName, PassWord)))
                vLoginFaild(FileName, AdminFIleName, UserName, PassWord, Try);

            if (bAccountIsFound(FileName, UserName, PassWord))
                vUserAccountDetector(AdminFIleName, 0);
        }
    }
}

void vScreen(string FileName, string AdminFIleName, int ScreenNumber)
{
    if (ScreenNumber == 4)
        vResetAll(FileName);
    else if (ScreenNumber == 3)
        vUserAccounts(FileName);
    else if (ScreenNumber == 2)
        vCreateNewAccount(FileName);
    else if (ScreenNumber == 1)
        vLoginScreen(FileName, AdminFIleName);
}

void vBossScreen()
{
    vResetScreen();
    cout << "(Welcome boss)\n\n";
    cout << "  ----      ----  \n";
    cout << "|      \\  /      |\n";
    cout << "|       --       |\n";
    cout << " \\      I       / \n";
    cout << "  \\    LOVE    /  \n";
    cout << "    \\    U   /    \n";
    cout << "      \\    /      \n";
    cout << "        \\/        \n\n";
    cout << "What an amazing person, I love you so much <3\n";
    cout << "Press \"ENTER\" to return to the MAIN MENU...\n";
    cin.get();
    cin.get();
    vMainMenu();
}

void vReadScreenNumber(string FileName, string AdminFIleName, int ScreenNumber)
{
    cout << endl;
    vValidation(ScreenNumber);

    if (ScreenNumber == 1234567890)
        vBossScreen();
    else
        vNumberZone(ScreenNumber, 0, 4);

    if (ScreenNumber != 0)
        vScreen(FileName, AdminFIleName, ScreenNumber);
    else if (ScreenNumber == 0)
    {
        cout << "\nThanks for using our program :)\n\n";
        exit(0);
    }
}

void vMainMenu()
{
    vResetScreen();
    int ScreenNumber = 0;

    cout << "======================\n";
    cout << "   M A I N  M E N U   \n";
    cout << "======================\n";
    cout << "[1] Login\n";
    cout << "[2] New Account\n";
    cout << "[3] My Accounts\n";
    cout << "[4] Reset\n";
    cout << "[0] EXIT\n";
    cout << "======================\n";
    cin >> ScreenNumber;
    vReadScreenNumber("UserDataFile.txt", "AdminSecretCodeFile.txt", ScreenNumber);
}

void vStartProgram(bool Start)
{
    if (Start)
        vMainMenu();
}

int main()
{
    vStartProgram(1);
}