/* 
 * PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 */

/*
	NAME: 		MUHAMMAD ARIYAN CHAUDHARY
	ID:   		i22-1035
	SECTION: 	j	
*/


//---Piece Starts to Fall When Game Starts---//
int fallingPiece(float& timer, float& delay, int& colorNum, int& n, int& Rot){
    if (timer>delay)
    {
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
		Rot=0;       
		n=rand()%7;
            	for(int i=0;i<4;i++)
            		gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            	colorNum =1+rand()%7;
                for (int i=0;i<4;i++)
                {
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
        }
        timer=0;   
    }
	return n;
         
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
//=============================anomaly checker functions 4 rotation===============================//
bool rotRightAnom(int n)
{	
	for(int i=0;i<4;i++)
	{
		if(n==0)
		{
			if ( point_1[i][0]>=N-2) //won't go thru right wall.
				return false;
			else if (gameGrid[point_1[i][1]][point_1[i][0]+2]>gameGrid[point_1[i][1]][point_1[i][0]])  //won't go thru right blocks.
				return false;
		}
		else
		{
			if ( point_1[i][0]>=N-1) //won't go thru right wall.
				return false;
			else if (gameGrid[point_1[i][1]][point_1[i][0]+1]>gameGrid[point_1[i][1]][point_1[i][0]])  //won't go thru right blocks.
				return false;
		}

	}
	return true; 
}

bool rotLeftAnom()
{
	for(int i=0;i<4;i++)
	{
		if(point_1[i][0]<=0) //won't go thru left wall.
			return false;
		if (gameGrid[point_1[i][1]][point_1[i][0]-1]>gameGrid[point_1[i][1]][point_1[i][0]]) //won't go thru left blocks.
			return false;
	}
	return true;
}
bool rotDownAnom(int n)
{
	for(int i=0;i<4;i++)
	if(n==0) // for 
	{
		if ( point_1[i][1]>=M-1) 
			return false;
		else if (gameGrid[point_1[i][1]+2][point_1[i][0]]>gameGrid[point_1[i][1]][point_1[i][0]]) 
			return false;
	}
	else
	{
		if ( point_1[i][0]>=M)
			return false;
		else if (gameGrid[point_1[i][1]+1][point_1[i][0]]>gameGrid[point_1[i][1]][point_1[i][0]]) 
			return false;
	}

	return true;
}

//=============================anomaly checker functions 4 rotation===============================//

//=============================left and right movement===============================//

void LeftRightPiece(int& delta_x)
{
	bool anom=true;  // used as a switch in case of an anomaly.
	
	if(delta_x==0)   //if neither left or right button is pressed, the function exists instantly
		return;
		
	else if(delta_x==1)  //if right button is pressed, this will work.
	{
		for(int i=0;i<4;i++)   
		{
			if ( point_1[i][0]>=N-1) //N is the right most boundary, so it will not move any further once it reaches N-1 place
				anom = false;
			else if (gameGrid[point_1[i][1]][point_1[i][0]+1]>gameGrid[point_1[i][1]][point_1[i][0]]) 
				anom = false;    //checks if there is any block right to it. if there is, then it won't move any more right.
		}
		if(anom)
			for (int i=0;i<4;i++)
			{
				point_1[i][0]+=1;  //this moves all the blocks one space right.
        		}
        	delta_x=0;
	}
	else if(delta_x==-1)
	{
		for(int i=0;i<4;i++)
		{
			if (point_1[i][0]<=0) //0 is the left most boundary, so it will not move any further once it reaches 0th place
				anom = false;
			else if (gameGrid[point_1[i][1]][point_1[i][0]-1]>gameGrid[point_1[i][1]][point_1[i][0]])
				anom = false; //checks if there is any block left to it. if there is, then it won't move any more left.
		}
			if(anom)
				for (int i=0;i<4;i++)
				{
					point_1[i][0]-=1;  //this moves all the blocks one space left.
        			}
        	delta_x=0;
	}
}
//=============================left and right movement===============================//



//=============================rotation===============================//
void rotation(bool& rotate, int &n, int& Rot)
{	
	if(rotate)
	if(n==2)
	{
		rotate = false; return;
	}
	else if(n==0)
	{
		if(Rot%2==0) //Rotation of I block------------------------
		{
			if(rotLeftAnom())
			if(rotRightAnom(n))
			{
			point_1[0][0]-=1; point_1[0][1]+=1;
			point_1[2][0]+=1; point_1[2][1]-=1;
			point_1[3][0]+=2; point_1[3][1]-=2;
			Rot++;
			}
		}
		else
		{
			if(rotDownAnom(n))
			{
			point_1[0][0]+=1; point_1[0][1]-=1;
			point_1[2][0]-=1; point_1[2][1]+=1;
			point_1[3][0]-=2; point_1[3][1]+=2;
			Rot++;}
		}
	}
	else if(n==1)  // Rotation of T block-------------------------------
	{
		if(Rot%4==0)
		{
			if(rotLeftAnom())
			{
			point_1[3][0]-=1;
			point_1[3][1]-=1; Rot++;}
		}
		else if((Rot%4)==1)
		{
			if(rotDownAnom(n))
			{
			point_1[2][1]+=1;
			point_1[2][0]-=1; Rot++;}
		}
		else if(Rot%4==2)
		{
			if(rotRightAnom(n))
			{
			point_1[2][0]+=1; point_1[2][1]-=1; 
			point_1[3][0]+=1; point_1[3][1]+=1;
			point_1[0][0]-=1; point_1[0][1]+=1;
			Rot++;}
		}
		else if(Rot%4==3)
		{
			point_1[0][0]+=1; point_1[0][1]-=1; Rot++;
		}
	}
	else if(n==3) //Rotation for L shape--------------------------------
	{
		if(Rot%4==0)
		{	
			if(rotLeftAnom())
			{
			point_1[1][0]+=1;
			point_1[0][0]-=1;
			point_1[0][1]+=2; Rot++;}
		}
		else if(Rot%4==1)
		{
			point_1[0][1]-=2;
			point_1[1][0]-=1;
			point_1[1][1]-=1;
			point_1[3][1]-=1;
			point_1[3][0]-=1; Rot++;
		}
		else if(Rot%4==2)
		{
			if(rotRightAnom(n))
			{
			point_1[0][1]+=2;
			point_1[1][0]-=1;
			point_1[1][1]+=1;
			point_1[3][0]+=1;
			point_1[2][1]-=1; Rot++;}
		}
		else if(Rot%4==3)
		{
			point_1[3][1]+=1;
			point_1[2][1]+=1;
			point_1[1][0]+=1;
			point_1[0][1]-=2;
			point_1[0][0]+=1; Rot++;
		}
	}
	
	else if(n==4) //Rotation for J shape--------------------------------
	{
		
		if(Rot%4==0)
		{
			if(rotRightAnom(n))
			{
			point_1[0][0]-=1;
			point_1[0][1]+=1;
			point_1[1][0]+=1;
			point_1[1][1]+=1; Rot++;}
		}
		else if(Rot%4==1)
		{
			point_1[0][1]-=1;
			point_1[0][0]+=1;
			point_1[2][1]-=2;
			point_1[3][0]-=1;
			point_1[1][1]-=1;
			point_1[1][0]-=2; Rot++;
		}
		else if(Rot%4==2)
		{
			if(rotRightAnom(n))
			{
			point_1[3][0]+=2;
			point_1[1][0]+=1;
			point_1[2][1]+=1;
			point_1[0][0]+=1;
			point_1[0][1]+=1; Rot++;}
		}
		else if(Rot%4==3)
		{
			point_1[3][0]-=1;
			point_1[2][1]+=1;
			point_1[0][1]-=1;
			point_1[0][0]-=1; Rot++;
		}
	}
	else if(n==5) //rotation for S block---------------------
	{
		
		if(Rot%2==0)
		{
			if(rotRightAnom(n))
			{
			point_1[0][0]+=2;
			point_1[3][1]-=2; Rot++;}
		}
		else
		{
			if(rotDownAnom(n))
			{
			point_1[0][0]-=2;
			point_1[3][1]+=2; Rot++;}
		}
	}
	else  //rotation for Z block-----------------------------
	{
		
		if(Rot%2==0)
		{
			if(rotRightAnom(n)){
			point_1[1][0]+=2;
			point_1[3][1]-=2; Rot++;}
		}
		else
		{
			if(rotDownAnom(n))
			{
			point_1[1][0]-=2;
			point_1[3][1]+=2; Rot++;}
		}
	}
	rotate = false;
	return;
}
//=============================rotation===============================//

//=============================remove line===============================//
int lineCheck()
{
	int lines=0;
	for(int i=M-1;i>0;i--)
	{
		int filled=0;
		for(int j=0;j<N;j++)
		{
			if(gameGrid[i][j])
				filled++;
		}
		if(filled==N)
		{
			lines++;
			for(int k=i;k>0;k--)
			{
				for(int j=0;j<N;j++)
				{
					gameGrid[k][j]=gameGrid[k-1][j];
				}
			}
		}
		if(filled==N)
		{filled=0; i++;}
	}	
	return lines;
}

//=============================\\ remove line \\=============================//

//============================= \\ bombing \\ ===============================//
void bombing(int bomb[1][2], float& timer, int &bombcolor)
{
	int random;
	if(timer>0.15)
		random = rand()%100000;		//for randomly dropping the bomb.
		
	static bool work=false;
	if(bomb[0][0]>11)			//will not repeat if the bomb is inside the grid.
	{
		if(random==10)
		{
			work=true;
			bomb[0][0]=rand()%10;
			bomb[0][1]=1;
			bombcolor=1+rand()%7;
		}
	}
	
	if(work)				
	{
		if (timer>0.3)
			bomb[0][1]++;
		if (bomb[0][1]>19||gameGrid[bomb[0][1]][bomb[0][0]])
		{
			work=false;
			if(gameGrid[bomb[0][1]][bomb[0][0]])
			{
				if(gameGrid[bomb[0][1]][bomb[0][0]]==bombcolor) //if the color of the bomb matches with the color of the box
				{
					for(int i=0;i<M;i++)
					{
						for(int j=0;j<N;j++)
						{
							gameGrid[i][j]=0;	//clears the entire grid.
						}
					}
				}
				else 						//if the color of the bomb does not match.
				{
					if(bomb[0][0]==0)			//if the bomb is on the most left,
					{					//removes 4 blocks, 2 below, 2 from the right.
						gameGrid[bomb[0][1]][bomb[0][0]]=0;
						gameGrid[bomb[0][1]+1][bomb[0][0]]=0;
						gameGrid[bomb[0][1]][bomb[0][0]+1]=0;
						gameGrid[bomb[0][1]+1][bomb[0][0]+1]=0;
					}
					else					//removes 4 blocks. 2 below, 2 from the left.
					{
						gameGrid[bomb[0][1]][bomb[0][0]]=0;
						gameGrid[bomb[0][1]+1][bomb[0][0]]=0;
						gameGrid[bomb[0][1]][bomb[0][0]-1]=0;
						gameGrid[bomb[0][1]+1][bomb[0][0]-1]=0;
					}
						
				}
			}
			bomb[0][0]=500;		//transports the bomb outside the grid again.
			bomb[1][1]=500;
		}
        }

} 
//============================= \\ bombing \\ ===============================//

//=============================\\ hard drop \\===============================//

void drop(bool &spaceflag)
{	
	while(spaceflag)
	{
		for(int i=0;i<4;i++)
		{
			point_2[i][1]=point_1[i][1];
			point_1[i][1]++;
		}
		if(!anamoly())
			spaceflag=false;	
	}
	
	for(int i=0;i<4;i++)
	{
		point_1[i][1]=point_2[i][1];
	}
	
}
//============================= \\hard drop\\ ===============================//

//============================= \\ shadow \\ ===============================//

void shadow(int shadowPiece[][2])
{
	for(int i=0;i<4;i++)
	{
		shadowPiece[i][0]=point_1[i][0];
		shadowPiece[i][1]=point_1[i][1];
	}
	bool anom=true;
	while(anom)
	{	
		for (int i=0;i<4;i++)
		{
			if (shadowPiece[i][1]>M-2||point_1[i][1]>M-2)
				{anom = false; break;}
			else if (gameGrid[shadowPiece[i][1]+1][shadowPiece[i][0]] || gameGrid[point_1[i][1]+1][point_1[i][0]])
				{anom = false; break;}
		}
		if(anom)
			for(int i=0;i<4;i++)
			{
				shadowPiece[i][1]+=1;
			}
		
	
	}
	
}
//============================= \\ shadow \\ ===============================//


//============================= \\ score calculation \\ ===============================//
void scorecalc(int lineDestroyed, int& score)
{
	if(lineDestroyed==0)
		return;
	else if(lineDestroyed==1)
		score+=10;
	else if(lineDestroyed==2)
		score+=30;
	else if(lineDestroyed==3)
		score+=60;
	else if(lineDestroyed==4)
		score+=100;	
}
//============================= \\ score calculation \\ ===============================//

//============================= \\ endgame menu flag \\ ===============================//
void gameEnd(bool &endgameflag)
{
	for(int i=0;i<N;i++)
	{
		if(gameGrid[0][i])
			endgameflag=true;
	}
	if(endgameflag)
	{
		for(int i=0;i<M;i++)
		{
			for(int j=0;j<N;j++)
				gameGrid[i][j]=0;
		}
	}
}
//============================= \\ endgame menu flag \\ ===============================//








///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
