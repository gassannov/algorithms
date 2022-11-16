//
// Created by Марат Гасанов on 25.05.2022.
//

#include <set>
#include "queue"
#include "map"
#include "string"
#include "iostream"
#include "unordered_set"
#include "time.h"
using namespace std;

int manhattan(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int size){
    int result = 0;
    for (int i = 0; i < matrix1.size()*matrix1.size(); ++i){
        int j = i/4;
        int k = i%4;
        result += abs(matrix1[j][k] - (i+1));
    }
    return result;
}

int dismissCount(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int size){
    int error = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix1[i][j] == 0){
                continue;
            }
            error = matrix1[i][j] == matrix2[i][j] ? error : error+1;
        }
    }
    return error;
}

int errorRate(vector<vector<int>> matrix1, vector<vector<int>> matrix2, int size){
    return manhattan(matrix1, matrix2, size);
}

bool isGamePossible(vector<vector<int>> currentState, vector<vector<int>> goalState){
    int N = 0;
    int K = 0;
    for(int i = 0; i < 16; ++i){
        uint8_t cur = currentState[i/4][i%4];
        if(cur){
            for(int j = 0; j < i; j++){
                if(currentState[j/4][j%4] > cur){
                    N+=1;
                }
            }
        } else {
            K = i/4 + 1;
        }
    }
    if(!((N+K)%2)) {
        return true;
    } else {
        return false;
    }
}

class GameState{
    friend struct Hash;
    friend struct Comparator;
    std::vector<std::vector<int>> gameMatrix;
    vector<vector<int>> goalMatrix;
    int zeroIndex1;
    int zeroIndex2;
    int size;

    int (*errorRate)(vector<vector<int>>, vector<vector<int>>, int);
public:
    int depth;
    GameState(vector<vector<int>> gameMatrix, vector<vector<int>> goalMatrix, int size, int (*errorFunc)(vector<vector<int>>, vector<vector<int>>, int),  int depth, string sequence);
    int getError() const;
    GameState* getStateUp();
    GameState* getStateDown();
    GameState* getStateRight();
    GameState* getStateLeft();
    bool operator < (const GameState& state) const;
    bool operator == (const GameState& state) const;
    bool operator > (const GameState& state) const;
    bool operator == (const vector<vector<int>>& matrix);
    bool operator != (const vector<vector<int>>& matrix);
    string commandSequence;
    bool isStatePossible();
};

bool GameState::operator==(const vector<vector<int>>& matrix) {
    return this->gameMatrix == matrix;
}

bool GameState::operator!=(const vector<vector<int>> &matrix) {
    return this->gameMatrix != matrix;
}

GameState::GameState(vector<vector<int>>gameMatrix, vector<vector<int>> goalMatrix, int size, int (*errorFunc)(vector<vector<int>>, vector<vector<int>>, int), int depth, string sequence):size(size), errorRate(errorFunc), depth(depth), commandSequence(sequence) {
    this->gameMatrix = gameMatrix;
    this->goalMatrix = goalMatrix;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (gameMatrix[i][j] == 0){
                zeroIndex1 = i;
                zeroIndex2 = j;
            }
        }
    }
}

int GameState::getError() const{
    return errorRate(gameMatrix, goalMatrix, size) + depth;
}

bool GameState::operator < (const GameState& state) const {
    return this->getError() > state.getError();
}

bool GameState::operator > (const GameState& state) const {
    return this->getError() < state.getError();
}

bool GameState::operator==(const GameState &state) const {
    return this->gameMatrix == state.gameMatrix;
}

GameState *GameState::getStateUp() {
    if (zeroIndex1 == 0){
        return nullptr;
    }
    vector<vector<int>> curr = gameMatrix;
    curr[zeroIndex1][zeroIndex2] = curr[zeroIndex1-1][zeroIndex2];
    curr[zeroIndex1-1][zeroIndex2] = 0;
    string currSeq = commandSequence;
    currSeq.push_back('D');
    currSeq.push_back(' ');
    return new GameState(curr, goalMatrix, size, errorRate, depth+1, currSeq);
}

GameState *GameState::getStateDown() {
    if (zeroIndex1 == size-1){
        return nullptr;
    }
    vector<vector<int>> curr = gameMatrix;
    curr[zeroIndex1][zeroIndex2] = curr[zeroIndex1+1][zeroIndex2];
    curr[zeroIndex1+1][zeroIndex2] = 0;
    string currSeq = commandSequence;
    currSeq.push_back('U');
    currSeq.push_back(' ');
    return new GameState(curr, goalMatrix, size, errorRate, depth+1, currSeq);
}

GameState *GameState::getStateRight() {
    if (zeroIndex2 == size-1){
        return nullptr;
    }
    vector<vector<int>> curr = gameMatrix;
    curr[zeroIndex1][zeroIndex2] = curr[zeroIndex1][zeroIndex2+1];
    curr[zeroIndex1][zeroIndex2+1] = 0;
    string currSeq = commandSequence;
    currSeq.push_back('L');
    currSeq.push_back(' ');
    return new GameState(curr, goalMatrix, size, errorRate, depth+1, currSeq);
}

GameState *GameState::getStateLeft() {
    if (zeroIndex2 == 0){
        return nullptr;
    }
    vector<vector<int>> curr = gameMatrix;
    curr[zeroIndex1][zeroIndex2] = curr[zeroIndex1][zeroIndex2-1];
    curr[zeroIndex1][zeroIndex2-1] = 0;
    string currSeq = commandSequence;
    currSeq.push_back('R');
    currSeq.push_back(' ');
    return new GameState(curr, goalMatrix, size, errorRate, depth+1, currSeq);
}

struct Hash{
    int operator () (const GameState& gameState) const{
        int hash = 0;
        for (int i = 0; i < gameState.size; ++i) {
            for (int j = 0; j < gameState.size; ++j) {
                hash = 17*hash + gameState.gameMatrix[i][j];
            }
        }
        return hash;
    };
};

struct Comparator{
    bool operator()(GameState& state1, GameState& state2){
        return errorRate(state1.gameMatrix, state1.goalMatrix, state1.size) < errorRate(state1.gameMatrix, state1.goalMatrix, state1.size);
    };
};

bool GameState::isStatePossible() {
    GameState* currState = new GameState(this->gameMatrix, this->goalMatrix, this->size, this->errorRate, this->depth, this->commandSequence);
    while (currState->getStateRight()){
        currState = currState->getStateRight();
    }
    while (currState->getStateDown()){
        currState = currState->getStateDown();
    }
    return isGamePossible(currState->gameMatrix, currState->goalMatrix);
}

class WinningAlgorithm{
    std::priority_queue<GameState> statesInQueue;
    std::unordered_set<GameState, Hash> watchedState;
    vector<vector<int>> goalState;
    size_t watchedStateCnt = 0;
    GameState getBestState(GameState state);
public:
    WinningAlgorithm(vector<vector<int>> currentState, vector<vector<int>> goalState, int size);
    GameState runAlgorithm();
};

WinningAlgorithm::WinningAlgorithm(vector<vector<int>>currentState, vector<vector<int>>goalState, int size) {
    GameState startState = GameState(currentState, goalState, size, errorRate, 0, "");
    statesInQueue.push(startState);
    watchedState.insert(startState);
    this->goalState = goalState;
}

GameState WinningAlgorithm::runAlgorithm() {
    GameState currentState = statesInQueue.top();
    if (!currentState.isStatePossible()){
        currentState.depth = -1;
        return currentState;
    }
    while (!statesInQueue.empty()){
        currentState = statesInQueue.top();
        statesInQueue.pop();
        if (currentState == goalState){
            return currentState;
        }
        getBestState(currentState);
//        cout << currentState.getError() << endl;
    }
    return currentState;
}

GameState WinningAlgorithm::getBestState(GameState state) {
    GameState* stateUp = state.getStateUp();
    GameState* stateDown = state.getStateDown();
    GameState* stateRight = state.getStateRight();
    GameState* stateLeft = state.getStateLeft();
    std::vector<GameState*> nextStates = {stateUp, stateDown, stateLeft, stateRight};
    GameState bestState = state;
    int k = 0;

    for (int i = 0; i < 4; ++i) {
        if (nextStates[i]){
            GameState cur = *nextStates[i];
            if ((watchedState.find(cur) == watchedState.end())){
                statesInQueue.push(cur);
                watchedState.insert(cur);
            }
            else{
                delete nextStates[i];
            }
        }
    }
    return bestState;
}

int main(){
    vector<vector<int>> currentState(4, vector<int> (4));
    vector<vector<int>> goalState = {{1, 2, 3, 4},
                                     {5, 6, 7, 8},
                                     {9, 10, 11, 12},
                                     {13, 14, 15, 0}};
    int num;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> num;
            currentState[i][j] = num;
        }
    }

    WinningAlgorithm alg = WinningAlgorithm(currentState, goalState, 4);
    GameState finalState = alg.runAlgorithm();
    cout << finalState.depth << endl;
    cout << finalState.commandSequence << endl;
};


