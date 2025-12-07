#include<iostream>
#include<conio.h>
#include<Windows.h>
using namespace std;
enum Direction{STOP=0,LEFT,RIGHT,UP,DOWN};
Direction dir;
bool gameOver;
const int height=20;
const int width=20;
int headX,headY,fX,fY,score;// fX=fruit X ,fY= fruit Y
int tail_len,tailx[100],taily[100];

void setup();
void draw();
void input();
void logic();

int main(){
    char start;
    cout<<"\t------------------------------"<<endl;
    cout<<"\t\t :Snake King:"<<endl;
    cout<<"\t------------------------------"<<endl;
    cout<<"\t Press 's' to start the game: ";
    cin>>start;
    if(start=='s'){
        setup();
        while(!gameOver){
            draw();
            input();
            logic();
            Sleep(30);
            system("cls");
        }
    }
    return 0;
}
void setup(){
    gameOver= false;
    dir =STOP;
    headX=width/2;
    headY=height/2;
    fX=rand()%width;
    fY=rand()%height;
    score=0;
}

void draw(){
    system("cls");
    //upper border;
    cout<<"\t\t";
    for(int i=0;i<width-8;i++){
        cout<<"||";
    }
    cout<<endl;
    
    //snake,fruit,side border,space
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            //left border
            if(j==0) cout<<"\t\t||";
            //head
            if( i ==headY&& j==headX) cout<<"O";
            //fruit
            else if(i==fY && j==fX) cout<<"*";
            //tail
            else 
            {
              bool print = false; 
              for(int k=0;k<tail_len;k++){
                if(tailx[k]==j && taily[k]==i){
                    cout<<"O";
                    print=true;
                }
              }
              if(!print) cout<<" ";
            }
            //right border
            if(j==width-1) cout<<"||";
        }
        cout<<endl;
    }



    //lower border;
    cout<<"\t\t";
    for(int i=0;i<width-8;i++){
        cout<<"||";
    }
    cout<<endl;
    cout<<"\t\t\t Score :"<<score<<endl;

}

void input()// used arrows to move the snake instead of awsd
{
    if (_kbhit())  
    {
        int key = _getch();

        if (key == 224)   
        {
            key = _getch(); 
            switch (key)
            {
            case 72:   // UP arrow
                dir = UP;
                break;
            
            case 80:   // DOWN arrow
                dir = DOWN;
                break;

            case 75:   // LEFT arrow
                dir = LEFT;
                break;

            case 77:   // RIGHT arrow
                dir = RIGHT;
                break;
            }
        }
    }

}

void logic(){
    int prevX=tailx[0];
    int prevY=taily[0]; 
    int prev2X,prev2Y;
    tailx[0]=headX;         
    taily[0]=headY;
    for(int i=1;i<tail_len;i++){
        prev2X=tailx[i];
        prev2Y=taily[i];
        tailx[i]=prevX;
        taily[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    //direction logic 
    switch (dir)
    {
    case LEFT:
       headX--;
    break;
    case RIGHT:
       headX++;
    break;
    case UP:
       headY--;
    break;
    case DOWN:
       headY++;
    break;
    default:
        break;
    }
    //touch wall
    if(headX>=width){
        headX=0;
    }
    else if(headX<0){
        headX=width-1;
    }
    if(headY>=height){
        headY=0;
    }
    else if(headY<0){
        headY=height-1;
    }   
    //bite tail
    for(int i=0;i<tail_len;i++){
        if(tailx[i]==headX && taily[i]==headY){
            gameOver=true;
        }
    }
    //fruit eaten
    if(headX==fX && headY==fY){
        score+=10;
        fX=rand()%width;
        fY=rand()%height;
        tail_len++;
    }

}