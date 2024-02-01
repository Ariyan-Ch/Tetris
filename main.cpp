/*
	NAME: 		MUHAMMAD ARIYAN CHAUDHARY
	ID:   		i22-1035
	SECTION: 	j	
*/




#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace sf;
using namespace std;
int main(){

    //------------gets the highscore stored in the highscore.txt-----------------//
   /* ofstream myFile;
    ifstream MYFILE;
    string highscore;
    MYFILE.open("highscore.txt",ios::in); //read from this file into this program
    if(MYFILE.is_open()) {
    	getline(MYFILE,highscore);
    	MYFILE.close();
    }
    int highscoreNum;
    string scoreString;
    stringstream ss;  */
    string highscore="100";
    //------------gets the highscore stored in the highscore.txt-----------------//
    
    srand(time(0));
    RenderWindow window(VideoMode(380, 500), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6, obj7, obj8;
    Text scoretext, gamescore, HIGHSCORE; 	//for scoreboard.
    Font font;			//for scoreboard
    Music soundtrack;		//for music
    
    obj1.loadFromFile("img/tiles2.png");
    obj2.loadFromFile("img/tetrisbg.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/startmenu.png");
    obj5.loadFromFile("img/shadow.png");
    obj6.loadFromFile("img/Endgamemenu.png");
    obj7.loadFromFile("img/bombtiles.png");
    obj8.loadFromFile("img/pausingmenu.png");
    font.loadFromFile("fonts/metallord.ttf");			//loads the font for text.
    soundtrack.openFromFile("music/Fluffing-a-Duck.wav");	//opens the music file.
    
   //---------------------------for score board-----------------------------------------//
    scoretext.setFont(font); 			//sets the font type from the font stored in 'font'
    scoretext.setString("Score\n- - - - - -"); 	//the string stored in 'scoretext'
    scoretext.setCharacterSize(45); 		//sets the size of the text.
    scoretext.setFillColor(Color::Black); 	//sets its color as black.
    scoretext.setPosition(230,100); 		//sets it position on the screen.
    HIGHSCORE.setFont(font);
    HIGHSCORE.setString(highscore);
   // HIGHSCORE.setFillColor(Color::Black);
    HIGHSCORE.setCharacterSize(25);
    HIGHSCORE.setPosition(160,455);
   //---------------------------for score board-----------------------------------------//
   
    
    Sprite sprite(obj1), background(obj2), frame(obj3), Smenu(obj4), shadowimg(obj5), Emenu(obj6), bombsprite(obj7), pausing(obj8);
    int delta_x=0, colorNum=1, n=0, Rot=0, lineDestroyed=0, score=0, bombcolor=0;
    float timer=0, delay=0.3;
    bool rotate=0, spaceflag=false, menuflag=true, endgameflag=false, pauseflag=false, HSmenuflag=false;
    int shadowPiece[4][2]={0}, bomb[1][2]={{500,500}};
    
    //-------------------------- makes the first block random as well-------------------//
    	n=rand()%7;
	for (int i=0;i<4;i++)
	{
		point_1[i][0] = BLOCKS[n][i] % 2;
		point_1[i][1] = BLOCKS[n][i] / 2;
	}
    //-------------------------- makes the first block random as well-------------------//
    
    //------------------------- plays music --------------------------------------------//
	soundtrack.setVolume(50);         // reduce the volume
	soundtrack.setLoop(true);         // make it loop
	soundtrack.play();		 // plays moosic
    //------------------------- plays music --------------------------------------------//
    
    Clock clock;
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        if(!endgameflag && !pauseflag)
		timer+=time;


        Event e;
        while (window.pollEvent(e))
        {                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) 
            { 
            	//If any other key (not cross) is pressed
	    	if(e.key.code == Keyboard::H) 			//if starting menu and end game menu is not open AND H key is pressed
	   		if(!menuflag&&!endgameflag&&!pauseflag)	//it will turn on the pause flag.
	  			pauseflag=true;		 
	  		else if(pauseflag)
	  			pauseflag=false;
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                if (e.key.code == Keyboard::Space)	   
                	spaceflag=true;			   // for hard drop.
            }

	}
	
        if (Keyboard::isKeyPressed(Keyboard::Down))   
 		delay=0.05;                                    
	else
		delay=0.3;
	
		

	////////////----Creates a Main Menu----/////////////	
	if(menuflag)
	{
		if(Keyboard::isKeyPressed(Keyboard::Num1))
			menuflag=false;
		else if(Keyboard::isKeyPressed(Keyboard::Num2))
			window.close();

			
	}
	////////////----Creates a Main Menu----/////////////
	
	
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***//
        
        if(!menuflag && !pauseflag && !endgameflag)			//all these functions stop working at the starting menu, pause, and End menu
        {
        	bombing(bomb,timer,bombcolor);				//drops bombs
        	
		n=fallingPiece(timer, delay, colorNum,n,Rot);		//falling function. returns n which is later passed into rotation func.
		
		LeftRightPiece(delta_x);				//left and right movement
		
		rotation(rotate,n,Rot);					//takes n from the falling func to understand what piece is falling
		
		lineDestroyed=lineCheck();				//remove lines and returns how many lines were destroyed at once
		
		if(spaceflag)						//spaceflag is passed by reference to drop the piece 
			drop(spaceflag);				//instantly and then turned off again
			
			
		shadow(shadowPiece);					//the parameter shadwoPiece is an array.
		
		scorecalc(lineDestroyed,score);				//appends to the score when the lines are destroyed.
		
		gameEnd(endgameflag);					//endgameflag is turned on when the first line is reached. passed by
        }
        
        	
        
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
          
       //--------------------------- drawing the shadowPiece ------------------------------//     
       for (int i=0; i<4; i++){
            shadowimg.setTextureRect(IntRect(colorNum*18,0,18,18));
            shadowimg.setPosition(shadowPiece[i][0]*18,shadowPiece[i][1]*18);
            shadowimg.move(28,31);
            window.draw(shadowimg);
          }
       //---------------------------drawing the shadowPiece ------------------------------//  
         
         
         //--------------------------- bomb color -----------------------------------------//  
          bombsprite.setTextureRect(IntRect(bombcolor*18,0,18,18));
          bombsprite.setPosition(bomb[0][0]*18,bomb[0][1]*18);
          bombsprite.move(28,31);
          window.draw(bombsprite);
	//--------------------------- bomb color -----------------------------------------//  
	
	

	//---------------------------for score board-----------------------------------------//      
		gamescore.setFont(font);
		gamescore.setString(std::to_string(score));
		gamescore.setCharacterSize(45);
		gamescore.setFillColor(Color::Black);
		gamescore.setPosition(280,190);
	//---------------------------for score board-----------------------------------------//      
	
	
	
        window.draw(frame);	//grid border.
        window.draw(scoretext);  //Displayethe word "Score" on the screen
        window.draw(gamescore);	 //display the score number as it is updated.
        
        if(menuflag)
        {
        	window.draw(Smenu);	//starting menu is displayed at the start.
        	HIGHSCORE.setString(highscore);
        	window.draw(HIGHSCORE);
        }
        	
        if(endgameflag)		//summons the end game menu and shows the current score.
        {
        	window.draw(Emenu);
        	gamescore.setPosition(170,200);
        	window.draw(gamescore);
        	/*
		ss<<highscore;
		ss>>highscoreNum;

		if(score>highscoreNum) {				//check if score was greater than highscore.
			highscore.clear();				//the previous content of highscore string is erased.
			scoreString=to_string(score);			//the score is converted into string to store in the file.
			myFile.open("./highscore.txt", ios::trunc);	//enters into file to rewrite it.
			if(myFile.is_open()){				//checks if the file opened.
				myFile<<scoreString;
				myFile.close();				//file is closed.
			}
			
			MYFILE.open("./highscore.txt", ios::in); 		//open file to read it
			if(MYFILE.is_open()) {	
				getline(MYFILE,highscore);		//gets the highscore and stores it in highscore string again
				MYFILE.close();				//close the file
			}
			
		}*/
		HIGHSCORE.setString(highscore);	 			//store highscore string in Text HIGHSCORE 
        	window.draw(HIGHSCORE);					//draws the highscore.
        	
        	
        	soundtrack.stop();					//stops the music when the game ends.
		if (Keyboard::isKeyPressed(Keyboard::Num1)) 
		{
			endgameflag=false;
			score=0;
			soundtrack.play();				//starts the music again.
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2)) 
			window.close();					//ends the program.
	}
	if(pauseflag){
		window.draw(pausing);
		window.draw(HIGHSCORE);
		if(Keyboard::isKeyPressed(Keyboard::Num2))
			window.close();
		else if(Keyboard::isKeyPressed(Keyboard::R))
		{
			score=0;
			for(int i=0;i<M;i++)
			{
				for(int j=0;j<N;j++)
					gameGrid[i][j]=0;
			}
			pauseflag=false;
		}
	}
	window.display();
	
    }
    highscore.clear();
    return 0;
}
