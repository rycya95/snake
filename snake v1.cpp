#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

bool gameover;
int x,y,fruitX,fruitY,score,n=100;
int tailX[100],tailY[100];
int ntail;
const int width=20;
const int height=20;
enum ed {STOP=0,LEFT,RIGHT,UP,DOWN};
ed dir;
void setup(){
    gameover=false;
    dir=STOP;
    x=width/2;
    y=height/2;
    fruitX=rand()%width;
    fruitY=rand()%height;
    score=0;
}
void draw(){
    system("cls");
    for(int i=0;i<width+2;i++) cout<<"#";
    cout<<"    SCORE = "<<score;
    cout<<"\n";
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            if(j==0) cout<<"#";
            if(i==y&&j==x) cout<<"O";
            else if(i==fruitY&&j==fruitX) cout<<"F";
            else{
                bool print=false;
                for(int k=0;k<ntail;k++){
                    if(tailX[k]==j&&tailY[k]==i) cout<<"o",
                    print=true;
                }
                if(!print) cout<<" ";
            }
            if(j==width-1) cout<<"#";
        }cout<<"\n";
    }for(int i=0;i<width+2;i++) cout<<"#";
}
void input(){
    if(_kbhit()){
        switch(_getch()){
            case 'w':
            dir = UP;
            break;
            case 'a':
            dir = LEFT;
            break;
            case 'd':
            dir = RIGHT;
            break;
            case 's':
            dir = DOWN;
            break;
            case 'x':
            gameover = true;
            break;
        }
    }
}
void logic(){
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<ntail;i++){
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir){
        case UP:
        y--;
        break;
        case DOWN:
        y++;
        break;
        case LEFT:
        x--;
        break;
        case RIGHT:
        x++;
        break;
        default:
        break;
    }
    if(x>width||x<0) gameover=true;
    if(y>height||y<0) gameover=true;
    if(x==fruitX&&y==fruitY){
        fruitX=rand()%width;
        fruitY=rand()%height;
        score+=10;
        n-=10;
        ntail++;
    }
}
//================================================================
int main(int argc, char const *argv[]){
    string str;
    setup();
    while(!gameover){
        draw();
        input();
        logic();
        if(n>0) Sleep(n);
    }
    system("cls");
    cout<<"GAME OVER!!!\n";
    cout<<"Your score is "<<score<<".\n";
    cout<<"Input 'Yes' to end the game.";
    while(cin>>str) return 0;
}
//================================================================
