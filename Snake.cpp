//----------------------------------------------------------------------------------------------------------------------------
//SNAKE GAME-PROJECT BY CHAITENYA GUPTA XI-A
//----------------------------------------------------------------------------------------------------------------------------

#include <SFML/Graphics.hpp>   //Essential to use SFML Graphics
#include <SFML/Audio.hpp>      //Essential for SFML Audio
#include <iostream>
#include <time.h>              //For Delay (used for snake slowing down)
#include <windows.h>           //For audio
#include <sstream>             //To show SCORE on screen (stringstream)
using namespace std;
using namespace sf;


int A=30,B=20;                 //Variable for controlling the coming back of snake

int size=16;                   //To set up different locations of snake and food

int score=0;                   //For user's total score (Initial=0)

int width = A*size;            //For setting up width of game window (480)

int height = B*size;           //For setting up height of game window (320)

int direction=0;               //Changes its value according to which user has pressed the key on keyboard

int num=2;                     //Determines length of snake (Initial length=2)

int reply=1;                   //Reply is set to 1 so that screen can show the start-up screen

int p=1;                       //Used in if statement for pausing/resuming game

int win=0;                     //Used for checking if a user has won


//-------------------------------------------------------------------------
//  STRUCTURES USED FOR SNAKE AND FOOD
//-------------------------------------------------------------------------

struct Snake
{
    int x,y;
}
snake[100];


struct Food
{
    int x,y;
}
food;
//-------------------------------------------------------------------------





//-------------------------------------------------------------------------
//  FUNCTION
//-------------------------------------------------------------------------

void Logic()
 {
//----------------------------------------------------------------------------------------------------------------------
//KEEPS MOVING THE SNAKES BODY ALONG WITH THE PREVIOUS BODY
//----------------------------------------------------------------------------------------------------------------------

    for (int i=num ; i>0 ; i--)
    {
        snake[i].x=snake[i-1].x;
        snake[i].y=snake[i-1].y;
    }
//----------------------------------------------------------------------------------------------------------------------




//----------------------------------------------------------------------------
//SETTING HOW THE COORDINATES SHOULD CHANGE WHEN A KEY IS PRESSED
//----------------------------------------------------------------------------

    if (direction==0)    //User has pressed DOWN arrow key or 'S' key
        snake[0].y+=1;

    if (direction==1)    //User has pressed LEFT arrow key or 'A' key
        snake[0].x-=1;

    if (direction==2)    //User has pressed RIGHT arrow key or 'D' key
        snake[0].x+=1;

    if (direction==3)    //User has pressed UP arrow key or 'W' key
        snake[0].y-=1;
//----------------------------------------------------------------------------







	if ((snake[0].x==food.x) && (snake[0].y==food.y))                       //To check if location of snake = location of food
        {
            PlaySound(TEXT("coins.wav"), NULL, SND_FILENAME | SND_ASYNC);   //To play sound when snake eats food
            num++;                                                          //After eating food snakes length will increase
            score+=10;
            win+=10;
            food.x=rand()% A;                                               //To randomize food location (X-COORDINATE)
            food.y=rand()% B;                                               //To randomize food location (Y-COORDINATE)
        }





//----------------------------------------------------------
//TO MAKE THE SNAKE COME TO SCREEN IF IT CROSES THE EDGES
//----------------------------------------------------------

    if (snake[0].x>A)
        snake[0].x=0;

    if (snake[0].x<0)
        snake[0].x=A;

    if (snake[0].y>B)
        snake[0].y=0;

    if (snake[0].y<0)
        snake[0].y=B;
//------------------------------------------------------------






//--------------------------------------------------------------------
//FOR DEATH OF SNAKE IF IT HITS ITSELF
//--------------------------------------------------------------------

    for (int i=1;i<num+1;i++)
    {
        if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)     //If any snake location equates to location of head
        {
            PlaySound(TEXT("mariodie.wav"), NULL, SND_SYNC);    //To play sound when snake dies
            num=-1;                                             //Sets num to -1 so that gameover screen can be shown
        }
    }
//---------------------------------------------------------------------



//----------------------------------------------------------------------
//THIS PART IS FOR GAME OVER SCREEN
//----------------------------------------------------------------------
    if(num==-2)
    {
        PlaySound(TEXT("gameover.wav"), NULL, SND_SYNC);
        exit(1);
    }
//-----------------------------------------------------------------------



//-----------------------------------------------------------------------
//THIS PART IS FOR USER WINNING THE GAME
//-----------------------------------------------------------------------
    if(win==110)
    {
        PlaySound(TEXT("win.wav"), NULL, SND_SYNC);
        exit(1);
    }
//-----------------------------------------------------------------------

 }



int main()
{
//-----------------------------------------------------------------------------
//TO PUT BACKGROUND SOUND
//-----------------------------------------------------------------------------


    SoundBuffer buffer;
    if (!buffer.loadFromFile("jungle.wav"))
    return -1;
    Sound sound;
    sound.setBuffer(buffer);
    sound.setLoop(true);

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
//TO PUT SCORE ON SCREEN
//-----------------------------------------------------------------------------


    Font font;
    if (!font.loadFromFile("arcon.otf"))
    {
            // error...
    }
    Text mytext;
    mytext.setFont(font);
    mytext.setCharacterSize(20);



//-----------------------------------------------------------------------------




    char ans;      //Variable to store (Y/N)


    cout<<"WELCOME T0 THE SNAKE GAME"<<endl;
    cout<<"Use Your Cursor Keys: Up, Left, Right, And Down"<<endl;
    cout<<"You Can Also Use Your Keyboard Keys: W, A, S, D"<<endl;
    cout<<"You Can Pause The Game By Pressing P And Resume The Game By Pressing R"<<endl;
    cout<<"The Snake Is White And The Food Is Red"<<endl;
    cout<<"Don't Run The Snake Into Its Own Tail Or Change Its Direction Directly: You Die"<<endl;
    cout<<"Score 100 Points To Win!!!!"<<endl<<endl;
    cout<<"WOULD YOU LIKE TO PLAY THE GAME (Y/N)"<<endl;
    cin>>ans;
    cout<<"Game By Chaitenya Gupta"<<endl;
    cout<<"V 1.0";

    sound.play();               //Plays the background sound

	if(ans=='Y' || ans=='y')
    {

    RenderWindow window(VideoMode(width , height), "Snake Game by Chaitenya Gupta XI-A");


	Texture t1,t2,t3,t4,t5,t6,t7;
	t1.loadFromFile("Snake Game/snakes.png");
	t2.loadFromFile("Snake Game/red.png");
	t3.loadFromFile("Snake Game/white.png");
	t4.loadFromFile("Snake Game/mario.png");
	t5.loadFromFile("Snake Game/start.png");
	t6.loadFromFile("Snake Game/pause.png");
    t7.loadFromFile("Snake Game/win.png");

	Sprite sprite1(t1);
	Sprite sprite2(t2);
	Sprite sprite3(t3);
	Sprite sprite4(t4);
	Sprite sprite5(t5);
	Sprite sprite6(t6);
	Sprite sprite7(t7);


	Clock clock;
    float timer=0, delay=0.1;

	food.x=10;  //INITIAL POSITION
    food.y=10;

    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
        timer=timer+time;


        Event e;                  //Used to help close window
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
		}


//------------------------------------------------------------------------------------------------------------
//GETTING INPUT FROM THE KEYBOARD
//------------------------------------------------------------------------------------------------------------


		if (Keyboard::isKeyPressed(Keyboard::Left))     direction=1;
	    if (Keyboard::isKeyPressed(Keyboard::Right))    direction=2;
	    if (Keyboard::isKeyPressed(Keyboard::Up))       direction=3;
		if (Keyboard::isKeyPressed(Keyboard::Down))     direction=0;


        if (Keyboard::isKeyPressed(Keyboard::A))        direction=1;
	    if (Keyboard::isKeyPressed(Keyboard::D))        direction=2;
	    if (Keyboard::isKeyPressed(Keyboard::W))        direction=3;
		if (Keyboard::isKeyPressed(Keyboard::S))        direction=0;


		if (Keyboard::isKeyPressed(Keyboard::P))        reply=3;            //For pausing the game
		if (Keyboard::isKeyPressed(Keyboard::R))        reply=4;            //For resuming the game
		if (Keyboard::isKeyPressed(Keyboard::Space))    reply=2;            //For starting the game
		if (Keyboard::isKeyPressed(Keyboard::Escape))   window.close();     //To exit the game from keyboard
//------------------------------------------------------------------------------------------------------------



    if (timer>delay)
        {
            {
                timer=0;
                Logic();
            }

//--------------------------------------------------------------------------------
//DRAWING ON SCREEN
//---------------------------------------------------------------------------------
    if(reply==2)                        //For SPACEBAR (STARTUP SCREEN)

    {

    for (int i=0; i<A; i++)   //A loop to cover entire screen with background
    {
        for (int j=0; j<B; j++)
		{
		    sprite1.setPosition(i*size,j*size); //COVERS THE ENTIRE SCREEN
		    window.draw(sprite1);
        }
    }


	for (int i=0;i<num;i++)
	    {
	        sprite3.setPosition(snake[i].x*size, snake[i].y*size); //FOR SNAKE it will put new body after 16 units
	        window.draw(sprite3);
        }

        sprite2.setPosition(food.x*size,  food.y*size); //FOR FOOD
        window.draw(sprite2);

    }


//-----------------------------------
// GAME OVER SCREEN
//-----------------------------------
        if(num==-1)
		{
            sound.pause();                //Pauses background sound
            window.clear();
            sprite4.setPosition((width/5)+20,(height/5)-30);
            window.draw(sprite4);
            num=num-1;                   //Sets num to -2 so that gameover sound can be played
        }
 //----------------------------------



//----------------------------------------
//PLAYER WINS SCREEN
//----------------------------------------

        if(win==100)
        {
            sound.pause();
            window.clear();
            sprite7.setPosition((width/5)-10,(height/5));
            window.draw(sprite7);
            win=win+10;
        }
//-----------------------------------------



//-----------------------------------
// FOR PROGRAMS START-UP SCREEN
//-----------------------------------

        if(reply==1)                    //Reply id initially 1
		{
            sprite5.setPosition(-60,0);
            window.draw(sprite5);
        }



//-----------------------------------
// FOR PROGRAMS PAUSING/RESUMING SCREEN
//-----------------------------------
        if(reply==3)
        {
            if(p==1)  //p is initially 1 only
            {
                sound.pause();
                PlaySound(TEXT("pause.wav"), NULL, SND_FILENAME | SND_ASYNC);   //To play sound when user presses P (PAUSE)
                p++;
            }

            sprite6.setPosition(-30,0);
            window.draw(sprite6);
        }

        if(reply==4)
        {
            if(p==2)  //p had already become 2 above (p++)
            {
                PlaySound(TEXT("pause.wav"), NULL, SND_FILENAME | SND_ASYNC);   //To play sound when user presses R (RESUME)
                p--; //This is done so that the person can again pause and resume the game i.e. the initial value of p is again 0
            }
            reply=2;  //Again reply will be equal to 2 so that game can resume
            sound.play();
        }
//-----------------------------------------



//------------------------------------------
//TO DISPLAY SCORE ON SCREEN
//------------------------------------------
    stringstream ss;
    ss <<"SCORE:"<< score;
    mytext.setString( ss.str().c_str() );
    window.draw(mytext);
//-------------------------------------------


            window.display();
        }
    }

    return 0;
    }
}
