#include<stdio.h>
#include<strings.h>
#include <windows.h>
#define BLUE SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE )
#define RED SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED)
#define INTENSITY SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY)
#define GREEN SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN)

char arr[100][100];
char arrSaveAction[100]= {0}; 
char arrRestorePlace[100]= {0}; 

int Width , Height , Highscores , numberOfPlay , savePlace , numberOfCol ;
char playerInput[20]  , whichPlayer ;
int restorePlace = 0 , scoreOne = 0 , scoreTwo = 0 , gameOut = 0;
int HighScoreList[50]= {0} , listLength = 0;


void arrInitialization(int Height , int Width) 



      {
    int counter1 , counter2 ; 
    for (counter1 = 0 ; counter1 < Height ; counter1++)
    {
        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            arr[counter1][counter2] = '-' ;
        }
    }
} 
void saveGame()
{
    int counter ,counter2;
    char chose , chose2;
    printf("\nif you save the file you will delete the previous saving file",INTENSITY);
    printf("\nif you want to continue >>enter Y << else >> enter N << ",INTENSITY);
    scanf("%s",&chose);

    if (chose =='Y')
    {
        FILE * file = fopen( "saveGame.txt" , "w");
        fprintf(file,"%d %d %d %d",Width,Height,Highscores,numberOfPlay);
        fprintf(file,"\n%d %d",scoreOne,scoreTwo);
        fprintf(file,"\n%s\n",&whichPlayer);

        for(counter = 0 ; counter < Height ; counter++)
       
	   
	    {
for(counter2 = 0 ; counter2 < Width ; counter2++)
            {
                fprintf(file,"%c ",arr[counter][counter2]);
            }
            fprintf(file,"\n");
        }
        fclose(file);
        printf("\nThe game has been saved if you want to continue playing in the a \n"
               "same game >>Enter Y << else >> Enter N << ",BLUE);
        scanf("%s",&chose2);
        if (chose2 == 'Y')
        {
           
        }
        else
        {
            gameOut = 1;
        }
    }
    if(chose == 'N' || chose2 == 'Y')
    {
        system("cls");
        PrintArrayValue(Height,Width);
if (numberOfPlay % 2 == 0)
        {
            printf("\n ,---.\n/ o o \\ \n\\ \\_/ /\n `---`",INTENSITY);
            printf("\tplayer2<<Enter your play>> = ",BLUE);
            scanf("%s",playerInput);
            player( playerInput , numberOfPlay);
        }
        else
        {
            printf("\n  |||||\n 0 . . 0\n0   ^   0\n0  \\_/  0\n 0     0\n  00000\n   888\n    8",INTENSITY);
            printf("\t player1<<Enter your play>> = ",GREEN);
            scanf("%s",playerInput);
            player(playerInput , numberOfPlay);
        }
    }
}

void HighScoresList(int flag)
{
    int counter , counter1 , temp;

    if (flag == 0)
    {
        FILE * file = fopen( "Highscores.txt" , "r");
        while(fscanf(file,"%d",&HighScoreList[listLength]) != EOF)
        {
            listLength++;
        }
        fclose(file);
    }
HighScoreList[listLength]=scoreOne;
    HighScoreList[listLength+1]=scoreTwo;
    printf("The High Score List\n");

    for (counter = 1 ; counter <= listLength+1 ; counter++)
    {
        counter1 = counter;
        while ( counter1 > 0 && HighScoreList[counter1] > HighScoreList[counter1-1])
        {
            temp   = HighScoreList[counter1];
            HighScoreList[counter1]   = HighScoreList[counter1-1];
            HighScoreList[counter1-1] = temp;
            counter1--;
        }
    }
    if (flag == 1)
    {
        FILE *file = fopen("Highscores.txt" , "w");
        for(counter=0 ; counter < Highscores ; counter++)
        {
            fprintf(file,"%d\n",HighScoreList[counter]);
            printf("\n%d",HighScoreList[counter]);
        }
        fclose(file);
    }
    else
    {
        for(counter = 0 ; counter < listLength ; counter++)
        {
            printf("%d\n",HighScoreList[counter]);
        }
    }
}

void ReadXML();


void loadGame()
{
    int counter , counter1  , flag = 0 ,counterX = 0 , counterO = 0;
    FILE *file = fopen("saveGame.txt" , "r");
    if ( file == NULL )
    {
        flag = 1;
    }
    else
    {
        fscanf(file,"%d %d %d %d",&Width,&Height,&Highscores,&numberOfPlay);
        fscanf(file,"%d %d",&scoreOne,&scoreTwo);
        fscanf(file,"%s",&whichPlayer);

        for(counter = 0; counter < Height ; counter++)
        {
            for(counter1 = 0; counter1 < Width ; counter1++)
            {
                fscanf(file," %c ",&arr[counter][counter1]);
                if (arr[counter][counter1] == 'X')
                {
                    counterX++;
                }
                else if (arr[counter][counter1] == 'O')
                {
                    counterO++;
                }
            }
        }
    }
    fclose(file);
    if (Width < 3 || Width > 12 || Height < 3 || Height > 12)
    {
        flag = 1;
    }
    if ( numberOfPlay % 2 == 0 && (counterX-1 != counterO || counterX*2 != numberOfPlay) )
    {
        flag = 1;
    }
    if ( numberOfPlay % 2 != 0 && (counterX != counterO || counterX*2+1 != numberOfPlay ))
    {
        flag = 1;
    }
    if ( (scoreOne >= 0  && scoreOne <= 50) && (scoreTwo >= 0 && scoreTwo <= 50) )
    {
        
    }
    else
    {
        flag = 1;
    }
    if (flag == 1)
    {
        printf("\n\t >> Human vs. Human << \n OR \n\t >> Human vs. Computer <<\n",BLUE);
        printf("\n>>Enter (H) if two player && (C) if one player\n",GREEN);

        scanf("%s",&whichPlayer);

        while (whichPlayer != 'H' && whichPlayer != 'C')
        {
            printf("\nsome thing error please enter again\n",RED);
            scanf("%s",&whichPlayer);
        }
        numberOfPlay = 1;
        savePlace = 0 , restorePlace = 0 , scoreOne = 0 , scoreTwo = 0;
        ReadXML();
        arrInitialization(Height,Width);
    }
}

void PrintArrayValue(int Height , int Width) 
{
    int counter1 , counter2 ; 
    int flag = 0;

    printf("\n\n\t>> Connect 4 \"Have fun\" <<",BLUE);
    printf("\n\n\tScore one = %d",scoreOne,GREEN);
    printf("\t\t\tScore Two = %d",scoreTwo,BLUE);
    printf("\n\n");

    for (counter1 = 0 ; counter1 < Height ; counter1++)
    {

        for(counter2 = 0 ; counter2 < Width && flag == 0; counter2++)
        {
            printf("[ %d ] ",counter2+1,BLUE);
        }
        printf("\n");

        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            printf("***** ",RED);
        }

        printf("\n");
        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            printf("*   * ",RED);
        }

        printf("\n");
        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            printf("* ",RED);

            if (arr[counter1][counter2] == 'X')
            {
                printf("%c ",arr[counter1][counter2],GREEN);
            }
            else if (arr[counter1][counter2] == 'O')
            {
                printf("%c ",arr[counter1][counter2],BLUE);
            }
            else
            {
                printf("%c ",arr[counter1][counter2],INTENSITY);
            }
            printf("* ",RED);
        }

        printf("\n");
        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            printf("*   * ",RED);
        }

        printf("\n");
        for(counter2 = 0 ; counter2 < Width ; counter2++)
        {
            printf("***** ",RED);
        }

        flag = 1;
    }
    printf("\n\n(U) to make Undo",INTENSITY);
    printf("\n(R) to make Redo ",GREEN);
    printf("\n(S) to save\n",BLUE);
}

void updateScore(int row , int col)
{
    int flag = 0 , score = 0;

    if(col+3 <= Width && arr[row][col] == arr[row][col+1] && arr[row][col] ==
            arr[row][col+2] && arr[row][col] == arr[row][col+3] )
    {
        score++;
    }

    if (col-3 >= 0 && arr[row][col] == arr[row][col-1] && arr[row][col] ==
            arr[row][col-2] && arr[row][col] == arr[row][col-3] )
    {
        score++;
    }

    if ( col - 1 >= 0 && col + 2 <= Width && arr[row][col] == arr[row][col-1] &&
            arr[row][col] == arr[row][col+1] && arr[row][col] == arr[row][col+2] )
    {
        score++;
    }

    if (col - 2 >= 0 && col + 1 <= Width && arr[row][col] == arr[row][col-1] &&
            arr[row][col] == arr[row][col-2] && arr[row][col] == arr[row][col+1] )
    {
        score++;
    }

    if(row - 3 >= 0 && arr[row][col] == arr[row-1][col] && arr[row][col] ==
            arr[row-2][col]&& arr[row][col] == arr[row-3][col] )
    {
        score++;
    }

    if (row + 3 <= Height && arr[row][col] == arr[row+1][col] && arr[row][col] ==
            arr[row+2][col] && arr[row][col] == arr[row+3][col] )
    {
        score++;
    }

    if (row - 3 >= 0 && col+3 <= Width && arr[row][col] == arr[row-1][col+1] &&
            arr[row][col] == arr[row-2][col+2] && arr[row][col] == arr[row-3][col+3] )
    {
        score++;
    }
    if (row + 3 <= Height && col+3 <= Width && arr[row][col] == arr[row+1][col+1]
            && arr[row][col] == arr[row+2][col+2] && arr[row][col] == arr[row+3][col+3])
    {
        score++;
    }
    if (col + 1 <= Width && row - 1 >= 0 && col - 2 >=0 && row + 2 <= Height &&
            arr[row][col] == arr[row-1][col+1] && arr[row][col] == arr[row+1][col-1] &&
            arr[row][col] == arr[row+2][col-2])
    {
        score++;
    }
    if(col + 2 <= Width && row - 2 >= 0 && col - 1 >= 0 && row + 1 <= Height &&
            arr[row][col] == arr[row-1][col+1] && arr[row][col] == arr[row-2][col+2] &&
            arr[row][col] == arr[row+1][col-1])
    {
        score++;
    }
    if (col - 3 >= 0 && row - 3 >= 0 && arr[row][col] == arr[row-1][col-1] &&
            arr[row][col] == arr[row-2][col-2] && arr[row][col] == arr[row-3][col-3] )
    {
        score++;
    }
    if (col - 3 >= 0 && row + 3 <= Height && arr[row][col] == arr[row+1][col-1]
            && arr[row][col] == arr[row+2][col-2] && arr[row][col] == arr[row+3][col-3])
    {
        score++;
    }
    if (col + 1 <= Width && row + 1 <= Height && col - 2 >=0 && row - 2 >= 0 &&
            arr[row][col] == arr[row-1][col-1] && arr[row][col] == arr[row-2][col-2] &&
            arr[row][col] == arr[row+1][col+1])
    {
        score++;
    }
    if (col + 2 <= Width && row + 2 <= Height && col - 1 >= 0 && row - 1 >= 0 &&
            arr[row][col] == arr[row-1][col-1] && arr[row][col] == arr[row+1][col+1] &&
            arr[row][col] == arr[row+2][col+2])
    {
        score++;
    }
    if (numberOfPlay % 2 != 0)
    {
        if (playerInput[0] == 'U')
        {
            scoreOne -= score;
        }
        else
        {
            scoreOne += score;
        }
    }
    else
    {
        if (playerInput[0] == 'U')
        {
            scoreTwo -= score;
        }
        else
        {
            scoreTwo += score;
        }
    }
}

void player (char numberOfcol , int numberOfPlay);
void computerPlayer();

void playAgain()
{
    printf("\n\t>>this move isn't valid \n\n >>do another move<< ",RED);
    scanf("%s",playerInput);
    player( playerInput , numberOfPlay);
}
void Undo()
{
    int counter = 0 , flag = 0 , noOfCol;

    if (savePlace == 0)
    {
       
    }
    else
    {
        savePlace--;
        noOfCol = arrSaveAction[savePlace] ;
        arrRestorePlace[restorePlace] = noOfCol ;
        restorePlace++;

        for (counter = 0 ; counter < Height && flag == 0 ; counter++)
        {
            if (arr[counter][noOfCol] == 'X' ||  arr[counter][noOfCol] == 'O')
            {
                numberOfPlay--;
                updateScore(counter , noOfCol);
                arr[counter][noOfCol] = '-';

                flag = 1;
            }
        }
    }

    system("cls");
    PrintArrayValue(Height,Width);

    if (numberOfPlay % 2 == 0)
    {
        if (whichPlayer == 'H')
        {
            printf("\n ,---.\n/ o o \\ \n\\ \\_/ /\n `---`",INTENSITY);
            printf("\tplayer2<<Enter your play>> = ",BLUE);
            scanf("%s",playerInput);
            player( playerInput , numberOfPlay);
        }
        else
        {
            computerPlayer();
        }
    }
    else
    {
        printf("\n  |||||\n 0 . . 0\n0   ^   0\n0  \\_/  0\n 0     0\n  00000\n   888\n    8",INTENSITY);
        printf("\t player1<<Enter your play>> = ",GREEN);
        scanf("%s",playerInput);
        player(playerInput , numberOfPlay);
    }
} 
void Redo()
{
    int counter = 0 , flag = 0 , noOfCol;

    if (restorePlace == 0)
    {
        
    }
    else
    {
        restorePlace--;
        noOfCol = arrRestorePlace[restorePlace];
        savePlace++;
        for (counter = 0 ; counter < Height && flag == 0 ; counter++)
        {
            if (arr[Height-counter-1][noOfCol] == '-')
            {
                if (numberOfPlay % 2 != 0)
                {
                    arr[Height-counter-1][noOfCol] = 'X';
                }
                else
                {
                    arr[Height-counter-1][noOfCol] = 'O';
                }
                flag = 1;
            }
        }
        updateScore(Height-counter , noOfCol);
        numberOfPlay++;
    }
    system("cls");
    PrintArrayValue(Height,Width);
    if (numberOfPlay % 2 == 0)
    {
        printf("\n ,---.\n/ o o \\ \n\\ \\_/ /\n `---`",INTENSITY);
        printf("\tplayer2<<Enter your play>> = ",BLUE);
        scanf("%s",playerInput);
        player( playerInput , numberOfPlay);
    }
    else
    {
        printf("\n  |||||\n 0 . . 0\n0   ^   0\n0  \\_/  0\n 0     0\n  00000\n   888\n    8",INTENSITY);
        printf("\t player1<<Enter your play>> = ",GREEN);
        scanf("%s",playerInput);
        player(playerInput , numberOfPlay);
    }
} 
void computerPlayer()
{
    int row , randomPlay ; 
    int flag = 0; 

    while (flag == 0)
    {
        randomPlay = rand() % (Width) ;

        for(row = 0 ; row < Height && flag == 0; row++)
        {

            if(arr[Height-row-1][randomPlay]== 'X' || arr[Height-row-1][randomPlay] == 'O')
            {
               
            }

    else
            {
                if (row < Height)
                {
                    restorePlace = 0;
                    arr[Height-row-1][randomPlay] = 'O';
                    arrSaveAction[savePlace] = (randomPlay);
                    savePlace++;
                    updateScore(Height-row-1 , randomPlay);
                    system("cls");
                    PrintArrayValue(Height,Width);
                    flag = 1;
                }
            }
        }
    }
}


void player(char numberOfCol , int numberOfPlay) 
{
    int row; 
    int flag = 0 , counter ; 
    int convert;

    convert = atoi(playerInput);

    if (convert == 0)
    {
        numberOfCol = 0;
    }
    else
    {
        numberOfCol = convert;
    }

    if(numberOfCol > 0 && numberOfCol <= Width)
    {
        
    }
    else if (playerInput[0] == 'U')
    {
        Undo();
        flag = 1;
    }
    else if (playerInput[0] == 'R')
    {
        Redo();
        flag = 1;
    }
    else if(playerInput[0] == 'S')
    {
        saveGame();
        flag = 1;
    }
    else
    {
        flag = 2;
    }

    for(row = 0 ; row < Height && flag == 0; row++)
    {
if(arr[Height-row-1][numberOfCol-1]== 'X' || arr[Height-row-1][numberOfCol-1] == 'O')
        {
           
        }
        else
        {
            if (row < Height)
            {
                restorePlace = 0;
                if (numberOfPlay % 2 != 0)
                {
                    arr[Height-row-1][numberOfCol -1] = 'X';
                    arrSaveAction[savePlace] = (numberOfCol- 1);
                    savePlace++;
                    updateScore(Height-row-1 , numberOfCol - 1);
                }
                else
                {
                    if (whichPlayer == 'H')
                    {
                        arr[Height-row-1][numberOfCol - 1] = 'O';
                        arrSaveAction[savePlace] = (numberOfCol- 1);
                        savePlace++;
                        updateScore(Height-row-1 , numberOfCol - 1);
                    }
                    else
                    {
                        computerPlayer();
                    }
                }

                system("cls");
                PrintArrayValue(Height,Width);
                flag = 1;
            }
        }
    }
    if (flag == 0 || flag == 2) //if flag = this mean row "counter" is bigger than Height <<all the row is fulled
    {
        playAgain();
    }
}
/*function reads values from a file*/
void ReadXML()
{
    char str[555];
    char str2[20][20];
    char s[4] = "<>";
    char *token;
    int counter;
    int counter1;
    int counter3;
    int found = 0;
    int savePlace = 0; 
    int colmun = 0;
    int row = 0;
    int list = 0;
    int flag = 0;

    FILE * file = fopen( "data.xml" , "r" );

	while ( fscanf(file, "%s", str)!=EOF && flag == 0 ) {

		counter = 0;
		found = 0;

		if (strlen(str) > 3) {

			if  (str[counter] == '<'&& ( str[strlen(str) - 1] == '>'
	        || str[strlen(str) - 2] == '>'|| str[strlen(str) - 3] == '>' 
	        || str[strlen(str) - 4] == '>') ) {

	        	counter++;

			}
			else if (str[counter+1] == '<' && str[strlen(str) - 1] == '>') {

				counter +=2 ;

			}
			else if (str[counter+2] == '<' &&  str[strlen(str) - 1] == '>') {

				counter+=3;

			}
			else if (str[counter+3] == '<' &&  str[strlen(str) - 1] == '>'){

				counter += 4;

			}

			else {

				found = 1;

		}

		if (found == 0) {

			while(counter < strlen(str)-2) {

				if((str[counter] >= 'A' && str[counter] <= 'z') || str[counter] == '<'
                  || str[counter] == '>' || str[counter] == '/') {

                    /*do nothing*/

                }

                else if (found == 0) {

                    if (str[counter+1] == '\0' || str[counter+2] =='\0' || str[counter+3] =='\0' 
                    	||str[counter+4] == '\0') {

                        if(str[counter-1] != '>') {

                                flag = 1;
                        }
                    }
                    else if(str[counter-1] == '>' && str[counter+1] == '<') {

                    	/*Do nothing*/
                            
                    }
                    else if (str[counter-1] == '>' && str[counter+2] == '<') {
                           
                    	/*do nothing*/ 

                    }
                    else if (str[counter-1] == '>' && str[counter+3] == '<') {

                    	/*do nothing*/

                    }
                            
                }
                else {

                	flag = 1;

            	}

                	found = 1;

            }

                	counter++;

        }

    }

    else {

		flag = 1;

	}

    }

	token = strtok(str,s);

	counter = 0;

	if (str[counter] == '<') {

            counter = 1;

    }

	if (token == NULL)
	{
		flag = 1;
	}

	found = 0;

	while(token != NULL && flag == 0) {

		counter3 = 0 ;
		counter1 = 0;

		if (str[counter] == '<') {

			counter++;

		}

        while (strlen(token) > counter1) {

                if ((strlen(str) == 1 || strlen(str) == 2 || strlen(str) == 3) && found == 0) {

                    counter = 0;
                    found = 1;

                }

                if (str[counter] == token[counter1]) {

                    counter3++;

                }

                counter1++;
                counter++;

        }

        if (str[counter +1 ] == '>' || str[counter+1] == '<') {

                flag = 1;

        }

        if (counter3 == strlen(token)) {

        	strcpy(str2[savePlace],token);
                savePlace++;

		}

        else {

            flag = 1;

        }

        counter++;

        token = strtok(NULL,s);

        }

    }

    if (flag == 0) {

        counter = 0;
        counter3 = 0;

        while (str2[counter][counter3] != '\0' && flag == 0) {

            if(str2[counter][counter3] == str2[savePlace-1][counter3+1]) {

                counter3++;

            }

            else {

                flag = 1;

            }
        }

        if (str2[savePlace-1][0] != '/' || strcmp(str2[counter] , "Configurations") != 0) {

            flag = 1;

        }

        counter++;

        while(counter < savePlace-2 && flag == 0) {

            counter3 = 0;

            while (str2[counter][counter3] != '\0' && flag == 0) {

                if (str2[counter][counter3] == str2[counter+2][counter3 + 1]) {

                    counter3++;

                }

                else {

                    flag = 1;

                }
            }

            if (flag == 0 && str2[counter+2][0] =='/'){

                if (strcmp(str2[counter] , "Width") == 0 ){

                    colmun = atoi(str2[counter+1]);

                }

                else if (strcmp(str2[counter] , "Height") == 0){

                    row = atoi(str2[counter+1]);

                }
                else if (strcmp(str2[counter] , "Highscores" ) == 0){

                    list = atoi(str2[counter+1]);

                }
                else {

                    flag = 1;

                }

            }
            else {

                flag = 1;

            }

        } /*closes while loop on 832*/ 

        counter += 3;

    } /*closes if statement on 804 */ 
    if (colmun > 3  && colmun < 13 && row > 3 && row < 13
         && list >= 0 && list < 13){

        Width = colmun , Height = row , Highscores = list;

    }

    else {

        flag = 1;

    }

    if (flag == 1) {

        Width =  7  , Height =  6 , Highscores = 5;

    }
    return;

}

int main()
{
    int flag = 0;
    

    char chose = 'C';
    char option ;

    while (chose =='C')
    {
        system("color 0A");
        printf("\nIf You Want To Load The Saved Game >> Enter L <<Else Enter Any thing ");
        scanf("%s",&option);

        if (option == 'L')
        {
            loadGame();
        }
        else
        {
            printf("\n\t >> Human vs. Human << \n OR \n\t >> Human vs. Computer <<\n",BLUE);
            printf("\n>>Enter (H) if two player && (C) if one player\n",GREEN);

            scanf("%s",&whichPlayer);

            while (whichPlayer != 'H' && whichPlayer != 'C')
            {
                printf("\nsome thing error please enter again\n",RED);
                scanf("%s",&whichPlayer);
            }

            numberOfPlay = 1;
            savePlace = 0 , restorePlace = 0 , scoreOne = 0 , scoreTwo = 0;
            ReadXML();
            arrInitialization(Height,Width);
        }

        system("cls");
        gameOut = 0;

        while ( Width*Height >= numberOfPlay && gameOut != 1)
        {
            system("cls");
            PrintArrayValue(Height , Width);

if (numberOfPlay % 2 != 0)
    {
                printf("\n  |||||\n 0 . . 0\n0   ^   0\n0  \\_/  0\n 0     0\n  00000\n   888\n    8",INTENSITY);
                printf("\t player1<<Enter your play>> = ",GREEN);
                scanf("%s",playerInput);
                player(playerInput,numberOfPlay);
                numberOfPlay++;
            }
    else
       {
                if (whichPlayer == 'H')
                {
                    printf("\n ,---.\n/ o o \\ \n\\ \\_/ /\n `---`",INTENSITY);
                    printf("\tplayer2<<Enter your play>> = ",BLUE);
                    scanf("%s",playerInput);
                    player(playerInput,numberOfPlay);
                }
                else
                {
                    computerPlayer();
                }

                numberOfPlay++;
            }
        }

        system("cls");
        PrintArrayValue(Height , Width);
        system("color 2A");
        if (numberOfPlay-1 == Width*Height)
        {
    if (scoreOne > scoreTwo)
    {
                printf("\n\n\t***player One is winner***");
                printf(" \n\t **Hard luck player Two**\n");
            }
            else if (scoreOne < scoreTwo)
            {
                printf("\n\n\t***player Two is winner***");
                printf(" \n\t **Hard luck player One**\n");
            }
            else
    {
                printf("\n\n\t***The two score is equivalent***\n\n");
            }
            flag = 1;
            HighScoresList(flag);
        }
        printf("\n\nYou Want To Continue Enter C else Enter any thing ");
scanf("\n%s",&chose);
        system("cls");
    }
    return 0;
}

