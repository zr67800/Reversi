//
//  main.cpp
//  Reversi
//
//  Created by 张 睿 on 10/31/2015.
//  Copyright © 2015年 张 睿. All rights reserved.
//

#include <iostream>
//#include <curses.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SPACE = 32;
const int BLACK = 35;
const int WHITE = 79;

void blackAi(char color[10][10], bool &gameOver, int gameMode, int aiLevel);
void whiteAi(char color[10][10], bool &gameOver, int gameMode, int aiLevel);
void AI(int &row, int &col,const char color[10][10], char aiColor, int aiLevel );
void aiLevel3Recursion(int depth,const char colorCopy[10][10],int &ii,int &jj, char aiColor );
int aiLevel3RecursionRow(int depth,const char color[10][10], char aiColor );
int aiLevel3RecursionCol(int depth,const char color[10][10], char aiColor );



void start(string &blackPlayer, string &whitePlayer, int &gameMode, int &aiLevelBlack, int &aiLevelWhite, int &testCircle){
    //game mode: 0 white-1player, 1 black-1player, 2 2players, 3 AI to AI, 23333 War story, 9999 fast test
    
    cout << "Welcome to Reversi game!" << endl;
    sleep(1);
    
    cout << "Please input game mode (1 for 1 player, 2 for 2 players, 3 for watching):\n";
    cin >> gameMode;
    while (gameMode!=1&&gameMode!=2&&gameMode!=3&&gameMode!=23333&&gameMode!=9999) {
        cout << "We are not as smart as you may think 23333...\nBut if you are trying to find a Ester egg... Good luck~ \n";
        cout << "Please input game mode (1 for 1 player, 2 for 2 players, 3 for watching):\n";
        cin >> gameMode;
    }
    
    if (gameMode==2) {
        cout << "Please input your name, for black:\n";
        cin >> blackPlayer;
        cout << "Please input your name, for white:\n";
        cin >> whitePlayer;
    }
    else if(gameMode<2){
        cout << "Do you want to take black, or white? (Black move first)\n";
        cout << "Input 0 for black, any other INT NUMBER for white \n";
        int isWhiteInt=0;
        bool isWhite=false;
        cin >> isWhiteInt;
        if (isWhiteInt!=0)
            isWhite=true;
        gameMode-=isWhite;
        
        cout << "Please input your name:\n";
        if (gameMode)
            cin >> blackPlayer;
        else
            cin >> whitePlayer;
        
        cout << "How smart do you want the AI to be? Choose from {0,1}... \n(Actually we don't know which is more clever...)\n";
        if (gameMode){
            cin >> aiLevelWhite;
            while (aiLevelWhite!=0&&aiLevelWhite!=1&&aiLevelWhite!=3&&aiLevelWhite!=4) {
                cout << "That AI have not been born yet...\n";
                cout << "How smart do you want the AI to be? Choose from {0,1}... \n(Actually we don't know which is more clever...)\n";
                cin >> aiLevelWhite;
            }
        }
        else{
            cin >> aiLevelBlack;
            while (aiLevelBlack!=0&&aiLevelBlack!=1&&aiLevelWhite!=3&&aiLevelWhite!=4) {
                cout << "That AI have not been born yet...\n";
                cout << "How smart do you want the AI to be? Choose from {0,1}... \n(Actually we don't know which is more clever...)\n";
                cin >> aiLevelBlack;
            }
            
        }
    }
    else if (gameMode==3||gameMode==23333||gameMode==9999){
        
        if (gameMode==23333) {
            sleep(1);
            cout << "You got it... (smile)\n";
            sleep(2);
            cout << "Now you are the master...\n";
            sleep(2);
            cout << "I, the programmer, give you the right...\n";
            sleep(2);
            cout << "The right, \"We hold these truths to be self-evident, that...\"\n";
            sleep(2);
            cout << "\"The player who find this game mode, can let AI has a ...\n";
            sleep(2);
            cout << "...great...\n";
            sleep(2);
            cout << "...prolonged...\n";
            sleep(2);
            cout << "...war.\"\n";
            sleep(2);
            cout << "----the programmer, the creator, an anti-hero. \n";
            sleep(2);
            cout << "You will see the result very soon, since they will fight behind the screen...\n";
            sleep(2);
            cout << "So, smart player, now please tell me, how many round do you want the AI to fight? \n";
            cin >> testCircle;
            while (testCircle<1) {
                cout << "Oh come on... You know what you should input...\n";
                cin >> testCircle;
            }
            sleep(1);
        }
        
        if (gameMode==9999) {
            cout << "Test round? \n";
            cin >> testCircle;
            while (testCircle<1) {
                cout << "At least 1 test!\n";
                cin >> testCircle;
            }
            
        }
        
        cout << "How smart do you want the black AI to be? Choose from {0,1}... \n(Actually we don't know which is more clever...)\n";
        cin >> aiLevelBlack;
        while (aiLevelBlack!=0&&aiLevelBlack!=1&&aiLevelWhite!=3&&aiLevelWhite!=4) {
            cout << "That AI have not been born yet...\n";
            cout << "Now you can choose from {0,1}... \n";
            cin >> aiLevelBlack;
        }
        cout << "What about the white AI? \n";
        cin >> aiLevelWhite;
        while (aiLevelWhite!=0&&aiLevelWhite!=1&&aiLevelWhite!=3&&aiLevelWhite!=4) {
            cout << "That AI have not been born yet...\n";
            cout << "Now you can choose from {0,1}... \n";
            cin >> aiLevelWhite;
        }
    }
    
    //sleep(1);
    cout << "The game now begins...\n";
    sleep(1);
    
    
}

int countBlack(const char color[10][10]){
    int num=0;
    for (int i=1; i<=8; i++) {
        for (int j=1; j<=8; j++) {
            if (color[i][j]==BLACK) {
                num++;
            }
        }
    }
    return num;
}

int countWhite(const char color[10][10]){
    int num=0;
    for (int i=1; i<=8; i++) {
        for (int j=1; j<=8; j++) {
            if (color[i][j]==WHITE) {
                num++;
            }
        }
    }
    return num;
}

void fakeClearScreen(){
    for (int i=0; i<20; i++) {
        cout << endl;
    }
}

void outputScreen(const char color[10][10]){
    //fakeClearScreen();
    system("clear");
    cout << "  1 2 3 4 5 6 7 8 " << endl;
    for (int i=1; i<=8; i++) {
        cout << i << " ";
        for (int j=1; j<=8; j++) {
            cout << color[i][j] << " ";
        }
        cout << endl;
        
    }
    cout << "Black: " << countBlack(color) << "    White: " << countWhite(color) << endl;
    
}

int directionCol(int direction, int distance){
    int returnValue=0;
    //for direction, 0 for up, clockwise
    if (direction==0||direction==4)
        returnValue=0;
    else if (direction>=1&&direction<=3)
        returnValue=distance;
    else if (direction>=5&&direction<=7)
        returnValue=-distance;
    return returnValue;
}

int directionRow(int direction, int distance){
    int returnValue=0;
    //for direction, 0 for up, clockwise
    if (direction==2||direction==6)
        returnValue=0;
    else if (direction>=3&&direction<=5)
        returnValue=distance;
    else if (direction==7||direction==1||direction==0)
        returnValue=-distance;
    return returnValue;
}

bool allWhite(const char color[10][10]){
    bool allWhite=true;
    for (int i=1; i<=8 && allWhite; i++) {
        for (int j=1; j<=8 && allWhite; j++) {
            if (color[i][j]==BLACK) {
                allWhite=false;
            }
        }
    }
    return allWhite;
}

bool allBlack(const char color[10][10]){
    bool allBlack=true;
    for (int i=1; i<=8 && allBlack; i++) {
        for (int j=1; j<=8 && allBlack; j++) {
            if (color[i][j]==WHITE) {
                allBlack=false;
            }
        }
    }
    return allBlack;
}

bool full(const char color[10][10]){
    bool full=true;
    for (int i=1; i<=8 && full; i++) {
        for (int j=1; j<=8 && full; j++) {
            if (color[i][j]==SPACE) {
                full=false;
            }
        }
    }
    return full;
}

bool isLegalMove(const char color[10][10], int row, int col, char moveColor){
    bool legalMove=true;
    bool changeDir=false;
    bool otherColor=false;
    bool ableToReverse=false;
    
    //in the range
    if (row>8||row<1||col>8||col<1) legalMove=false;
    //position occupied
    else if (color[row][col]!=SPACE) legalMove=false;
    //able to reverse some
    else
        for (int dir=0; dir<8 && (!ableToReverse); dir++) {
            for (int dis=1; dis<=8 && (!changeDir) && (!ableToReverse); dis++) {
                if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==SPACE)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==moveColor&&otherColor==false)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==moveColor&&otherColor==true)
                    ableToReverse=true;
                else
                    otherColor=true;
            }
            changeDir=false;
            otherColor=false;
        }
    if (ableToReverse==false)
        legalMove=false;
    
    return legalMove;
}

bool legalMoveExist(const char color[10][10], char moveColor){
    bool exist=false;
    for (int i=1; i<=8 && (!exist); i++) {
        for (int j=1; j<=8 && (!exist); j++) {
            exist += isLegalMove(color, i, j, moveColor);
        }
    }
    return exist;
}

//这样写会报不知道为什么的编译错误
void aiLevel3Recursion(int depth,const char color[10][10],int &ii,int &jj, char aiColor ){
    char oppoColor=BLACK;
    if (aiColor==BLACK)
        oppoColor=WHITE;
    
    if (depth==1)
        AI(ii, jj, color, aiColor, 1);
    else if (depth > 1){//!现在只能实现三层!
        //bool gameOver=false;// 待处理 gameover
        int profit[10][10]={0};
        int maxProfit=0;
        int countActive=0;
        int aiRandom=0;
        
        
        for (int i=1; i<=8; i++) {
            for (int j=1; j<=8; j++) {
                if (isLegalMove(color, i, j, aiColor)) {//color 保留为进入遍历之前的局面，即此时 AI 面对的局面
                    
                    char colorCopy[10][10]={0};
                    for (int a=1; a<=8; a++)
                        for (int b=1; b<=8; b++)
                            colorCopy[a][b]=color[a][b];
                        
                    
                    
                    //
                    colorCopy[i][j]= aiColor;
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[i+directionRow(dir, k)][j+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }//colorCopy成为遍历实现后的局面，即对方 AI 面对的假定局面
                    
                    
                    int newii=1,newjj=1;
                    aiLevel3Recursion(depth-1, colorCopy, newii, newjj, oppoColor);//
                    
                    colorCopy[newii][newjj]= oppoColor;//对手已经返回确定结果，在 colorCopy 实现
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[newii+directionRow(dir, k)][newjj+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }
                    
                    if (depth==3) {
                        int i3=1,j3=1;
                        AI(i3, j3, colorCopy, aiColor, 1);
                        colorCopy[i3][j3]= aiColor;
                        for (int dir=0; dir<8 ; dir++) {
                            bool changeDir=false;
                            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                                if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==SPACE)
                                    changeDir=true;
                                else if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==aiColor){
                                    
                                    for (int k=1; k<dis; k++)
                                        colorCopy[i3+directionRow(dir, k)][j3+directionCol(dir, k)]=aiColor;
                                    changeDir=true;
                                }
                            }
                        }
                    }
                    
                    
                    
                    // if (full(colorCopy)||allBlack(colorCopy)||allWhite(colorCopy))
                    //    gameOver=true;//这里需要处理 GameOver 问题
                    
                    //
                    //colorCopy走了一步
                    if (aiColor==BLACK)
                        profit[i][j]=countBlack(colorCopy);
                    else
                        profit[i][j]=countWhite(colorCopy);
                    
                    if (maxProfit<profit[i][j])
                        maxProfit=profit[i][j];
                    
                    for (int i=1; i<=8; i++) {
                        for (int j=1; j<=8; j++) {
                            if (profit[i][j]==maxProfit) {
                                countActive++;
                                
                            }
                        }
                    }
                    srand((int)(time(0)+random()));//sure to change rand() series everytime
                    aiRandom=rand()%countActive;
                    
                    for (int i=1; i<=8&&aiRandom>=0; i++){
                        for(int j=1; j<=8&&aiRandom>=0; j++){
                            if (profit[i][j]==maxProfit) {
                                aiRandom--;
                                ii=i;
                                jj=j;
                            }
                        }
                    }
 
                    
                    
                    
                }
            }
        }
        
        
    }

    
    
}



int aiLevel3RecursionRow(int depth,const char color[10][10], char aiColor ){
    char oppoColor=BLACK;
    if (aiColor==BLACK)
        oppoColor=WHITE;
    int row=1;
    int col=1;
    if (depth==1)
        AI(row, col, color, aiColor, 1);
    else if (depth > 1){//!现在只能实现三层!
        //bool gameOver=false;// 待处理 gameover
        int profit[10][10]={0};
        int maxProfit=0;
        int countActive=0;
        int aiRandom=0;
        
        
        for (int i=1; i<=8; i++) {
            for (int j=1; j<=8; j++) {
                if (isLegalMove(color, i, j, aiColor)) {//color 保留为进入遍历之前的局面，即此时 AI 面对的局面
                    
                    char colorCopy[10][10]={0};
                    for (int a=1; a<=8; a++)
                        for (int b=1; b<=8; b++)
                            colorCopy[a][b]=color[a][b];
                    
                    
                    
                    //
                    colorCopy[i][j]= aiColor;
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[i+directionRow(dir, k)][j+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }//colorCopy成为遍历实现后的局面，即对方 AI 面对的假定局面
                    
                    
                    int newii=aiLevel3RecursionRow(depth-1, colorCopy, oppoColor);
                    int newjj=aiLevel3RecursionCol(depth-1, colorCopy, oppoColor);
                    
                    //
                    
                    colorCopy[newii][newjj]= oppoColor;//对手已经返回确定结果，在 colorCopy 实现
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[newii+directionRow(dir, k)][newjj+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }
                    
                    if (depth==3) {
                        int i3=1,j3=1;
                        AI(i3, j3, colorCopy, aiColor, 1);
                        colorCopy[i3][j3]= aiColor;
                        for (int dir=0; dir<8 ; dir++) {
                            bool changeDir=false;
                            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                                if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==SPACE)
                                    changeDir=true;
                                else if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==aiColor){
                                    
                                    for (int k=1; k<dis; k++)
                                        colorCopy[i3+directionRow(dir, k)][j3+directionCol(dir, k)]=aiColor;
                                    changeDir=true;
                                }
                            }
                        }
                    }
                    
                    
                    
                    // if (full(colorCopy)||allBlack(colorCopy)||allWhite(colorCopy))
                    //    gameOver=true;//这里需要处理 GameOver 问题
                    
                    //
                    //colorCopy走了一步
                    if (aiColor==BLACK)
                        profit[i][j]=countBlack(colorCopy);
                    else
                        profit[i][j]=countWhite(colorCopy);
                    
                    if (maxProfit<profit[i][j])
                        maxProfit=profit[i][j];
                    
                /*    for (int i=1; i<=8; i++) {
                        for (int j=1; j<=8; j++) {
                            if (profit[i][j]==maxProfit) {
                                countActive++;
                                
                            }
                        }
                    }
                    srand((int)(time(0)+random()));//sure to change rand() series everytime
                    aiRandom=rand()%countActive;
                    
                    for (int i=1; i<=8&&aiRandom>=0; i++){
                        for(int j=1; j<=8&&aiRandom>=0; j++){
                            if (profit[i][j]==maxProfit) {
                                aiRandom--;
                                row=i;
                                col=j;
                            }
                        }
                    }
                    */
                    
                    {//debug
                        for (int i=1; i<8; i++) {
                            for (int j=1; j<8; j++) {
                                if (maxProfit==profit[i][j]) {
                                    row=i;
                                }
                            }
                        }
                    }
                    
                    
                    
                }
            }
        }
        
        
    }
    
    
    return row;
}


int aiLevel3RecursionCol(int depth,const char color[10][10], char aiColor ){
    char oppoColor=BLACK;
    if (aiColor==BLACK)
        oppoColor=WHITE;
    int row=1;
    int col=1;
    if (depth==1)
        AI(row, col, color, aiColor, 1);
    else if (depth > 1){//!现在只能实现三层!
        //bool gameOver=false;// 待处理 gameover
        int profit[10][10]={0};
        int maxProfit=0;
        int countActive=0;
        int aiRandom=0;
        
        
        for (int i=1; i<=8; i++) {
            for (int j=1; j<=8; j++) {
                if (isLegalMove(color, i, j, aiColor)) {//color 保留为进入遍历之前的局面，即此时 AI 面对的局面
                    
                    char colorCopy[10][10]={0};
                    for (int a=1; a<=8; a++)
                        for (int b=1; b<=8; b++)
                            colorCopy[a][b]=color[a][b];
                    
                    
                    
                    //
                    colorCopy[i][j]= aiColor;
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[i+directionRow(dir, k)][j+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }//colorCopy成为遍历实现后的局面，即对方 AI 面对的假定局面
                    
                    
                    int newii=aiLevel3RecursionRow(depth-1, colorCopy, oppoColor);
                    int newjj=aiLevel3RecursionCol(depth-1, colorCopy, oppoColor);
                    
                    
                    //
                    
                    colorCopy[newii][newjj]= oppoColor;//对手已经返回确定结果，在 colorCopy 实现
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (colorCopy[newii+directionRow(dir, dis)][newjj+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    colorCopy[newii+directionRow(dir, k)][newjj+directionCol(dir, k)]=aiColor;
                                changeDir=true;
                            }
                        }
                    }
                    
                    if (depth==3) {
                        int i3=1,j3=1;
                        AI(i3, j3, colorCopy, aiColor, 1);
                        colorCopy[i3][j3]= aiColor;
                        for (int dir=0; dir<8 ; dir++) {
                            bool changeDir=false;
                            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                                if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==SPACE)
                                    changeDir=true;
                                else if (colorCopy[i3+directionRow(dir, dis)][j3+directionCol(dir, dis)]==aiColor){
                                    
                                    for (int k=1; k<dis; k++)
                                        colorCopy[i3+directionRow(dir, k)][j3+directionCol(dir, k)]=aiColor;
                                    changeDir=true;
                                }
                            }
                        }
                    }
                    
                    
                    
                    // if (full(colorCopy)||allBlack(colorCopy)||allWhite(colorCopy))
                    //    gameOver=true;//这里需要处理 GameOver 问题
                    
                    //
                    //colorCopy走了一步
                    if (aiColor==BLACK)
                        profit[i][j]=countBlack(colorCopy);
                    else
                        profit[i][j]=countWhite(colorCopy);
                    
                    if (maxProfit<profit[i][j])
                        maxProfit=profit[i][j];
                    
                    /*
                    for (int i=1; i<=8; i++) {
                        for (int j=1; j<=8; j++) {
                            if (profit[i][j]==maxProfit) {
                                countActive++;
                                
                            }
                        }
                    }
                    srand((int)(time(0)+random()));//sure to change rand() series everytime
                    aiRandom=rand()%countActive;
                    
                    for (int i=1; i<=8&&aiRandom>=0; i++){
                        for(int j=1; j<=8&&aiRandom>=0; j++){
                            if (profit[i][j]==maxProfit) {
                                aiRandom--;
                                row=i;
                                col=j;
                            }
                        }
                    }
                    */
                    
                    {//debug
                        for (int i=1; i<8; i++) {
                            for (int j=1; j<8; j++) {
                                if (maxProfit==profit[i][j]) {
                                    row=i;
                                }
                            }
                        }
                    }

                    
                    
                    
                }
            }
        }
        
        
    }
    
    
    return col;
}


void AI(int &row, int &col,const char color[10][10], char aiColor, int aiLevel ){
    if (aiLevel==0) {//level 0:legal move random
        int countActive=0;
        int aiRandom=0;
        for (int i=1; i<=8; i++){
            for(int j=1; j<=8; j++){
                countActive+=isLegalMove(color, i, j, aiColor);
            }
        }
        
        srand((int)(time(0)+random()));//sure to change rand() series everytime
        aiRandom=rand()%countActive;
        for (int i=1; i<=8&&aiRandom>=0; i++){
            for(int j=1; j<=8&&aiRandom>=0; j++){
                if (isLegalMove(color, i, j, aiColor)) {
                    aiRandom--;
                    row=i;
                    col=j;
                }
            }
        }
    }
    else if (aiLevel==1){//level 1: the random moves that changes most
        
        int profit[10][10]={0};
        int maxProfit=0;
        int countActive=0;
        int aiRandom=0;
        
        for (int i=1; i<=8; i++) {
            for (int j=1; j<=8; j++) {
                if (isLegalMove(color, i, j, aiColor)) {
                    for (int dir=0; dir<8 ; dir++) {
                        bool changeDir=false;
                        for (int dis=1; dis<=8 && (!changeDir); dis++) {
                            if (color[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==SPACE)
                                changeDir=true;
                            else if (color[i+directionRow(dir, dis)][j+directionCol(dir, dis)]==aiColor){
                                
                                for (int k=1; k<dis; k++)
                                    profit[i][j]++;//这样写 并不改动 color
                                changeDir=true;
                            }
                        }
                    }
                    if (maxProfit<profit[i][j]) {
                        maxProfit=profit[i][j];
                    }
                }
            }
        }
        for (int i=1; i<=8; i++) {
            for (int j=1; j<=8; j++) {
                if (profit[i][j]==maxProfit) {
                    countActive++;
                    
                }
            }
        }
        srand((int)(time(0)+random()));//sure to change rand() series everytime
        aiRandom=rand()%countActive;
        
        for (int i=1; i<=8&&aiRandom>=0; i++){
            for(int j=1; j<=8&&aiRandom>=0; j++){
                if (profit[i][j]==maxProfit) {
                    aiRandom--;
                    row=i;
                    col=j;
                }
            }
        }
    }
    else if (aiLevel==2){//level 2 prefer internal, line, and corner, and other human strategy
        
    }
    else if (aiLevel==3){
       // row=aiLevel3RecursionRow(3, color, aiColor);
       // col=aiLevel3RecursionCol(3, color, aiColor);

        int row2=1,col2=1;
        aiLevel3Recursion(3, color, row2, col2, aiColor);
        row=row2;
        col=col2;
    }
    else if (aiLevel==4){
        row=aiLevel3RecursionRow(2, color, aiColor);
        col=aiLevel3RecursionCol(2, color, aiColor);
        //int row2=1,col2=1;
        //aiLevel3Recursion(2, color, row2, col2, aiColor);
       // row=row2;
       // col=col2;

    }
    
}

void blackMove(char color[10][10], bool &gameOver, string blackPlayer){
    int row, col;
    if (legalMoveExist(color, BLACK)) {
        cout << blackPlayer << ", your turn...\n";
        cout << "Row? ";
        cin >> row;
        cout << "Column? ";
        cin >> col;
        while(!isLegalMove(color, row, col, BLACK)){
            cout << "Your move is illegal. Please try again...\n";
            cout << "Row? ";
            cin >> row;
            cout << "Column? ";
            cin >> col;
        }
        color[row][col]=BLACK;
        for (int dir=0; dir<8 ; dir++) {
            bool changeDir=false;
            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==SPACE)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==BLACK){
                    
                    for (int k=1; k<dis; k++)
                        color[row+directionRow(dir, k)][col+directionCol(dir, k)]=BLACK;
                    changeDir=true;
                }
            }
        }
        
        outputScreen(color);
        if (full(color)||allBlack(color))
            gameOver=true;
        
    }
    else
        cout << blackPlayer << ", you do not have a legal move.\n";
    
    
}

void whiteMove(char color[10][10], bool &gameOver, string whitePlayer){
    int row, col;
    if (legalMoveExist(color, WHITE)) {
        cout << whitePlayer << ", your turn...\n";
        cout << "Row? ";
        cin >> row;
        cout << "Column? ";
        cin >> col;
        while(!isLegalMove(color, row, col, WHITE)){
            cout << "Your move is illegal. Please try again...\n";
            cout << "Row? ";
            cin >> row;
            cout << "Column? ";
            cin >> col;
        }
        color[row][col]=WHITE;
        for (int dir=0; dir<8 ; dir++) {
            bool changeDir=false;
            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==SPACE)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==WHITE){
                    
                    for (int k=1; k<dis; k++)
                        color[row+directionRow(dir, k)][col+directionCol(dir, k)]=WHITE;
                    changeDir=true;
                }
            }
        }
        
        outputScreen(color);
        if (full(color)||allWhite(color))
            gameOver=true;
        
    }
    else
        cout << whitePlayer << ", you do not have a legal move.\n";
}

void blackAi(char color[10][10], bool &gameOver,int gameMode, int aiLevel){
    if (gameMode!=23333&&gameMode!=9999)
        sleep(1);
    int row=1, col=1;
    if (legalMoveExist(color, BLACK)) {
        AI(row, col, color, BLACK, aiLevel);
        color[row][col]=BLACK;
        for (int dir=0; dir<8 ; dir++) {
            bool changeDir=false;
            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==SPACE)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==BLACK){
                    
                    for (int k=1; k<dis; k++)
                        color[row+directionRow(dir, k)][col+directionCol(dir, k)]=BLACK;
                    changeDir=true;
                }
            }
        }
        if (gameMode!=23333&&gameMode!=9999)
            outputScreen(color);
        
        if (full(color)||allBlack(color))
            gameOver=true;
        
    }
    else{
        if (gameMode!=23333&&gameMode!=9999)
            cout << "AI does not have a legal move.\n";
        if (!legalMoveExist(color, WHITE))
            gameOver=true;
    }
}

void whiteAi(char color[10][10], bool &gameOver, int gameMode, int aiLevel){
    if (gameMode!=23333&&gameMode!=9999)
        sleep(1);
    int row=1, col=1;
    if (legalMoveExist(color, WHITE)) {
        AI(row, col, color, WHITE, aiLevel);
        color[row][col]=WHITE;
        for (int dir=0; dir<8 ; dir++) {
            bool changeDir=false;
            for (int dis=1; dis<=8 && (!changeDir); dis++) {
                if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==SPACE)
                    changeDir=true;
                else if (color[row+directionRow(dir, dis)][col+directionCol(dir, dis)]==WHITE){
                    
                    for (int k=1; k<dis; k++)
                        color[row+directionRow(dir, k)][col+directionCol(dir, k)]=WHITE;
                    changeDir=true;
                }
            }
        }
        
        if (gameMode!=23333&&gameMode!=9999)
            outputScreen(color);
        
        
        if (full(color)||allWhite(color))
            gameOver=true;
        
    }
    else{
        if (gameMode!=23333&&gameMode!=9999)
            cout << "AI does not have a legal move.\n";
        if (!legalMoveExist(color, BLACK))
            gameOver=true;
    }
}

int main() {
    bool playAgain=true;
    
    do{
        
        //initialization for screen
        
        char color[10][10];
        for (int i=0; i<10; i++) {
            for (int j=0; j<10; j++) {
                color[i][j]=SPACE;
            }
        }
        color[4][4]=color[5][5]=WHITE;
        color[4][5]=color[5][4]=BLACK;
        
        //input names
        string blackPlayer, whitePlayer;
        int gameMode=-1;
        int aiLevelBlack=-1;
        int aiLevelWhite=-1;
        int testCircle=1;
        int blackWinTimes=0, whiteWinTimes=0, drawTimes=0;
        
        
        start(blackPlayer, whitePlayer, gameMode, aiLevelBlack, aiLevelWhite,testCircle);
        
        //main part
        bool gameOver=false;
        outputScreen(color);
        if (gameMode==2) {
            while (!gameOver) {
                //black
                if (!gameOver)
                    blackMove(color, gameOver, blackPlayer);
                //white
                if (!gameOver)
                    whiteMove(color, gameOver, whitePlayer);
            }
        }
        else if (gameMode==1){
            while (!gameOver) {
                //black
                if (!gameOver)
                    blackMove(color, gameOver, blackPlayer);
                //white
                if (!gameOver)
                    whiteAi(color, gameOver,gameMode,aiLevelWhite);
            }
        }
        else if (gameMode==0){
            while (!gameOver) {
                //black
                if (!gameOver)
                    blackAi(color, gameOver,gameMode,aiLevelBlack);
                //white
                if (!gameOver)
                    whiteMove(color, gameOver, whitePlayer);
            }
        }
        else if (gameMode==3){
            while (!gameOver) {
                //black
                if (!gameOver)
                    blackAi(color, gameOver,gameMode,aiLevelBlack);
                //white
                if (!gameOver)
                    whiteAi(color, gameOver,gameMode,aiLevelWhite);
            }
        }
        else if (gameMode==23333||gameMode==9999){
            cout << "The battle started here." <<endl;
            for (int n=1; n<=testCircle; n++) {
                for (int i=0; i<10; i++) {
                    for (int j=0; j<10; j++) {
                        color[i][j]=SPACE;
                    }
                }
                color[4][4]=color[5][5]=WHITE;
                color[4][5]=color[5][4]=BLACK;
                
                bool gameOver=false;
                
                while (!gameOver) {
                    //black
                    if (!gameOver)
                        blackAi(color, gameOver,gameMode,aiLevelBlack);
                    //white
                    if (!gameOver){
                        whiteAi(color, gameOver,gameMode,aiLevelWhite);
                    }
                }
                if (countBlack(color)>countWhite(color))
                    blackWinTimes++;
                else if (countBlack(color)<countWhite(color))
                    whiteWinTimes++;
                else if (countBlack(color)==countWhite(color))
                    drawTimes++;
            }
        }
        
        //game over
        sleep(2);
        system("clear");
        if (gameMode<=3) {
            cout << "Game is over!" << endl;
            cout << "Black: " << countBlack(color) << "    White: " << countWhite(color) << endl;
            if (countBlack(color)>countWhite(color)){
                if (gameMode==2||gameMode==1)
                    cout << blackPlayer << ", you win! Congratulations!" << endl;
                else if (gameMode==0)
                    cout << "The AI beats you, " << whitePlayer << "! " << endl;
                else
                    cout << "The lucky AI is Black!\n";
            }
            else if (countBlack(color)<countWhite(color)){
                if (gameMode==2||gameMode==0)
                    cout << whitePlayer << ", you win! Congratulations!" << endl;
                else if (gameMode==1)
                    cout << "The AI beats you, " << blackPlayer << "! " << endl;
                else
                    cout << "The lucky AI is White!\n";
            }
            else
                cout << "It's a draw..." << endl;
        }
        else if (gameMode==23333){
            
            sleep(3);
            cout << "(" << testCircle << " years later...)" << endl;
            sleep(2);
            cout << "The war, the great, " << endl;
            sleep(1);
            cout << "prolonged, " << endl;
            sleep(1);
            cout << "war, is over." << endl;
            sleep(1);
            cout << "Beyond your sight, the war was really intense, causing AI great suffer, but" << endl;
            sleep(1);
            cout << "also bringing great, supreme honor." << endl;
            sleep(2);
            cout << "The brave, fighting black AI, in the level " << aiLevelBlack << ", won " << blackWinTimes << " times..." << endl;
            sleep(1);
            cout << "The honorable, elegant white AI, in the level " << aiLevelWhite << ", won " << whiteWinTimes << " times..." << endl;
            sleep(1);
            cout << "And there were " << drawTimes << " times, they could not beat each other, and stop at the peace table." << endl;
            sleep(2);
            if (aiLevelBlack==aiLevelWhite) {
                cout << "Now, finally, they know that they are internally equal." << endl;
                sleep(1);
                if (blackWinTimes>whiteWinTimes)
                    cout << "The black guy was more lucky... Just luck. " << endl;
                else if (blackWinTimes<whiteWinTimes)
                    cout << "The white guy was more lucky... Just luck. " << endl;
                else
                    cout << "The programmer love them equally... And you as well." << endl;
            }
            else{
                cout << "It seems like they are different." << endl;
                sleep(1);
                if (blackWinTimes>whiteWinTimes)
                    cout << "The black AI, the AI level " << aiLevelBlack << ", seems to be more clever. " << endl;
                else if (blackWinTimes<whiteWinTimes)
                    cout << "The white AI, the AI level " << aiLevelWhite << ", seems to be more clever. " << endl;
                else
                    cout << "The programmer love them equally... And you as well." << endl;
            }
            
            sleep(2);
            cout << "The story ends. Thank you." << endl;
        }
        else if (gameMode==9999){
            cout << "The black AI, in the level " << aiLevelBlack << ", won " << blackWinTimes << " times." << endl;
            cout << "The white AI, in the level " << aiLevelWhite << ", won " << whiteWinTimes << " times." << endl;
            cout << "Draw times: " << drawTimes << endl;
            if (aiLevelBlack==aiLevelWhite) {
                cout << "Same AI level." << endl;
                if (blackWinTimes>whiteWinTimes)
                    cout << "The black won more." << endl;
                else if (blackWinTimes<whiteWinTimes)
                    cout << "The white won more." << endl;
                else
                    cout << "Won same times." << endl;
            }
            else{
                cout << "Different AI level." << endl;
                
                if (blackWinTimes>whiteWinTimes)
                    cout << "The black AI, the AI level " << aiLevelBlack << ", seems to be more clever. " << endl;
                else if (blackWinTimes<whiteWinTimes)
                    cout << "The white AI, the AI level " << aiLevelWhite << ", seems to be more clever. " << endl;
                else
                    cout << "Won same times." << endl;
            }
        }
        else
            cout << "Are you joking me..." << endl;
        cout << "Do you want to play again? (1 for yes, 0 for no)" << endl;
        cin >> playAgain;
        sleep(1);
        system("clear");
        
    }while (playAgain);
    
    return 0;
}
