#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <algorithm>
#include <iterator>

using namespace std; 

void flipBoard(char* board);
int MinMax(char board[], int currDepth, int maxDepth);
int MaxMin(char board[], int currDepth, int maxDepth);
int StaticEstimationMidgameEndgame(char board[]);
list<string> GenerateRemove(char board[]);
list<string> GenerateAdd(char board[]);
list<string> GenerateMovesMidgameEndgame(char board[]);
list<string> GenerateMove(char board[]);
list<string> GenerateHopping(char board[]);


const int boardSize = 21;
int MinMaxEvalCount;

string bestMove;


string convertToString(char a[], int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++)
    {
        s.append(string{a[i]});
    }
    return s;
}


list<int> Neighbors(int location)
{
    switch (location)
    {
    case 0:
        return list<int>({1, 2, 6});
        break;
    case 1:
        return list<int>({0, 3, 11});
        break;
    case 2:
        return list<int>({0, 3, 4, 7});
        break;
    case 3:
        return list<int>({1, 2, 5, 10});
        break;
    case 4:
        return list<int>({2, 5, 8});
        break;
    case 5:
        return list<int>({3, 4, 9});
        break;
    case 6:
        return list<int>({0, 7, 18});
        break;
    case 7:
        return list<int>({2, 6, 8, 15});
        break;
    case 8:
        return list<int>({4, 7, 12});
        break;
    case 9:
        return list<int>({5, 10, 14});
        break;
    case 10:
        return list<int>({3, 9, 11, 17});
        break;
    case 11:
        return list<int>({1, 10, 20});
        break;
    case 12:
        return list<int>({8, 13, 15});
        break;
    case 13:
        return list<int>({12, 14, 16});
        break;
    case 14:
        return list<int>({9, 13, 17});
        break;
    case 15:
        return list<int>({7, 12, 18});
        break;
    case 16:
        return list<int>({13, 15, 17, 19});
        break;
    case 17:
        return list<int>({10, 14, 20});
        break;
    case 18:
        return list<int>({6, 15, 19});
        break;
    case 19:
        return list<int>({16, 18, 20});
        break;
    case 20:
        return list<int>({11, 17, 19});
        break;
    }
}


bool CloseMill(int location, char board[])
{
    char color = board[location];

    switch (location)
    {
    case 0:
        if (board[2] == color && board[4] == color)
            return true;
        else if (board[6] == color && board[18] == color)
            return true;
        else
            return false;
    case 1:
        if (board[3] == color && board[5] == color)
            return true;
        else if (board[11] == color && board[20] == color)
            return true;
        else
            return false;
    case 2:
        if (board[0] == color && board[4] == color)
            return true;
        else if (board[7] == color && board[15] == color)
            return true;
        else
            return false;
    case 3:
        if (board[10] == color && board[17] == color)
            return true;
        else if (board[5] == color && board[1] == color)
            return true;
        else
            return false;
    case 4:
        if (board[8] == color && board[12] == color)
            return true;
        else if (board[2] == color && board[0] == color)
            return true;
        else
            return false;
    case 5:
        if (board[9] == color && board[14] == color)
            return true;
        else if (board[3] == color && board[1] == color)
            return true;
        else
            return false;
    case 6:
        if (board[0] == color && board[18] == color)
            return true;
        else if (board[7] == color && board[8] == color)
            return true;
        else
            return false;
    case 7:
        if (board[6] == color && board[8] == color)
            return true;
        else if (board[2] == color && board[15] == color)
            return true;
        else
            return false;
    case 8:
        if (board[4] == color && board[12] == color)
            return true;
        else if (board[6] == color && board[7] == color)
            return true;
        else
            return false;
    case 9:
        if (board[5] == color && board[14] == color)
            return true;
        else if (board[10] == color && board[11] == color)
            return true;
        else
            return false;
    case 10:
        if (board[9] == color && board[11] == color)
            return true;
        else if (board[3] == color && board[17] == color)
            return true;
        else
            return false;
    case 11:
        if (board[1] == color && board[20] == color)
            return true;
        else if (board[9] == color && board[10] == color)
            return true;
        else
            return false;
    case 12:
        if (board[18] == color && board[15] == color)
            return true;
        else if (board[14] == color && board[13] == color)
            return true;
        else if (board[8] == color && board[4] == color)
            return true;
        else
            return false;
    case 13:
        if (board[12] == color && board[14] == color)
            return true;
        else if (board[16] == color && board[19] == color)
            return true;
        else
            return false;
    case 14:
        if (board[12] == color && board[13] == color)
            return true;
        else if (board[9] == color && board[5] == color)
            return true;
        else if (board[17] == color && board[20] == color)
            return true;
        else
            return false;
    case 15:
        if (board[7] == color && board[2] == color)
            return true;
        else if (board[12] == color && board[18] == color)
            return true;
        else if (board[17] == color && board[16] == color)
            return true;
        else
            return false;
    case 16:
        if (board[13] == color && board[19] == color)
            return true;
        else if (board[15] == color && board[17] == color)
            return true;
        else
            return false;
    case 17:
        if (board[15] == color && board[16] == color)
            return true;
        else if (board[14] == color && board[20] == color)
            return true;
        else if (board[10] == color && board[3] == color)
            return true;
        else
            return false;
    case 18:
        if (board[6] == color && board[0] == color)
            return true;
        else if (board[15] == color && board[12] == color)
            return true;
        else if (board[19] == color && board[20] == color)
            return true;
        else
            return false;
    case 19:
        if (board[16] == color && board[13] == color)
            return true;
        else if (board[18] == color && board[20] == color)
            return true;
        else
            return false;
    case 20:
        if (board[18] == color && board[19] == color)
            return true;
        else if (board[14] == color && board[17] == color)
            return true;
        else if (board[1] == color && board[11] == color)
            return true;
        else
            return false;
    }
}


int StaticEstimationMidgameEndgame(char board[])
{
    int n = 21;
    int countW = 0;
    int countB = 0;

    int blackMoves = 0;


    char blackBoard[22];
    blackBoard[21] = '\0';
    for(int i = 0; i < 21; i++){
        if(board[i] == 'W'){
            blackBoard[i] = 'B';
        }
        else if(board[i] == 'B'){
            blackBoard[i] = 'W';
        }
        else{
            blackBoard[i] = 'x';
        }
    }
    list<string> temp = GenerateMovesMidgameEndgame(blackBoard);

    for(const string & position : temp){
        blackMoves++;
    }

    for (int i = 0; i < n; i++)
    {
        if (board[i] == 'W')
            countW++;
        else if (board[i] == 'B')
            countB++;
    }


    if(countB <= 2){
        return 10000;
    }
    else if(countW <= 2){
        return -10000;
    }
    else if(blackMoves == 0){
        return 10000;
    }
    else{
        return ((1000 * (countW - countB)) - blackMoves);
    }
}


list<string> GenerateRemove(char board[])
{
    list<string> L;

    int n = 21;
    char boardCopy[n + 1];
    boardCopy[21] = '\0';
    bool positionAdded = false;

    for (int i = 0; i < n; i++)
    {
        if (board[i] == 'B')
        {
            if (!CloseMill(i, board))
            {
                positionAdded = true;
                for (int l = 0; l < n; l++)
                    boardCopy[l] = board[l];

                boardCopy[i] = 'x';
                L.push_back(convertToString(boardCopy, n));
            }
        }
    }
    if (!positionAdded){
        L.push_back(convertToString(board, n));
    }
    return L;
}

list<string> GenerateAdd(char board[])
{
    list<string> L;
    char boardCopy[22];
    boardCopy[21] = '\0';

    for (int i = 0; i < 21; i++)
    {

        if (board[i] == 'x')
        {
            strcpy(boardCopy, board);
            boardCopy[i] = 'W';

            if (CloseMill(i, boardCopy)){
                L.splice(L.end(), GenerateRemove(boardCopy));
            }
            else
                L.push_back(string(boardCopy));
        }
    }
    return L;
}

list<string> GenerateHopping(char board[])
{
    list<string> L;
    int n = 21;
    char boardCopy[n + 1];
    boardCopy[21] = '\0';

    for (int i = 0; i < n; i++){
        if (board[i] == 'W')
        {
            for (int j = 0; j < n; j++)
            {
                if (board[j] == 'x')
                {
                    for (int l = 0; l < n; l++)
                    boardCopy[l] = board[l];
                    
                    boardCopy[i] = 'x';
                    boardCopy[j] = 'W';

                    if (CloseMill(j, boardCopy)){
                        L.splice(L.end(), GenerateRemove(boardCopy));
                    }
                    else{
                        L.push_back(convertToString(boardCopy, 21));
                    }
                }
            }
        }
    }
    return L;
}

list<string> GenerateMovesMidgameEndgame(char board[])
{
    int whiteCount = 0;

    for(int i = 0; i < 21; i++){
        if(board[i] == 'W'){
            whiteCount++;
        }
    }

    if(whiteCount == 3){
        return GenerateHopping(board);
    }
    else{
        return GenerateMove(board);
    }

}

list<string> GenerateMove(char board[])
{
    list<string> L;
    int n = 21;
    char boardCopy[n + 1];
    boardCopy[21] = '\0';

    for (int i = 0; i < n; i++)
    {
        if (board[i] == 'W')
        {
            list<int> neighbor = Neighbors(i);
            for (int j = 0; j < neighbor.size(); j++)
            {
                list<int>::iterator it = neighbor.begin();
                advance(it, j);

                if (board[*it] == 'x')
                {
                    for (int l = 0; l < n; l++)
                        boardCopy[l] = board[l];
                    boardCopy[i] = 'x';
                    boardCopy[*it] = 'W';

                    if (CloseMill(*it, boardCopy)){
                         L.splice(L.end(), GenerateRemove(boardCopy));
                    }
                    else
                        L.push_back(convertToString(boardCopy, n));
                }

            }
        }
    }
    return L;
}

int MaxMin(char board[], int currDepth, int maxDepth){
    string nextMove;
    if(currDepth == maxDepth){
        flipBoard(board);
        MinMaxEvalCount++;
        return StaticEstimationMidgameEndgame(board);
    }
    else if (currDepth == 0) {
        char temp[22];
        int v = -10000;

        list<string> L = GenerateMovesMidgameEndgame(board);

        for(const string & position : L){
            strcpy(temp, position.c_str());
            int maxV = MinMax(temp, currDepth + 1, maxDepth);
            if(maxV > v){
                v = maxV;
                nextMove = position.c_str();
            }

        }

        bestMove = nextMove;
        return v;
    }
    else {
        char temp[boardSize];
        int v = -10000;
        
        flipBoard(board);
        list<string> L = GenerateMovesMidgameEndgame(board);

        for(const string & position : L){
            strcpy(temp, position.c_str());
            int maxResult = MinMax(temp, currDepth + 1, maxDepth);
            if(maxResult > v){
                v = maxResult;
            }     
        }
        return v;
    }
}


int MinMax(char board[], int currDepth, int maxDepth){

    if(currDepth == maxDepth){
        MinMaxEvalCount++;
        int evaluation = StaticEstimationMidgameEndgame(board);
        return evaluation;
    }

    else{
        int v = 10000;
        char temp[boardSize];
        flipBoard(board);
        list<string> L = GenerateMovesMidgameEndgame(board);

        for(const string & position : L){
            strcpy(temp, position.c_str());
            int maxMinResult = MaxMin(temp, currDepth + 1, maxDepth);
            if(maxMinResult < v){
                v = maxMinResult;
            }        
        }
        
        return v;
    }

}

void flipBoard(char* board){
    for(int i = 0; i < 21; i++){
        if(board[i] == 'B')
            board[i] = 'W';
        else if(board[i] == 'W')
            board[i] = 'B';
    }
}

int main()
{
    string boardtxt;

    ifstream in;
    ofstream out;

    string inputBoard;
    string outputBoard;

    int depth;

    cout << "Enter input board: " << endl;
    cin >> inputBoard;

    cout << "Enter output board: " << endl;
    cin >> outputBoard;

    cout << "Enter depth: " << endl;
    cin >> depth;
    
    in.open(inputBoard);

    getline(in, boardtxt);

    in.close();

    int n = boardtxt.length();
    char board[n];
    strcpy(board, boardtxt.c_str());


    int minimaxEst = MaxMin(board, 0, depth);

    cout << "Board Position: " << bestMove << endl;
    cout << "MINIMAX estimate: " << minimaxEst << endl;
    cout << "Positions Evaluated by static estimation: " << MinMaxEvalCount << endl;


    out.open(outputBoard);
    out << bestMove;
    out.close();

    return 0;
}