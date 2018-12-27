#include <stdio.h>
//function declaration, need to define the function body in other places
void playgame() { printf("play");};
void loadgame() { printf("loadplay");};
void playmultiplayer() { printf("multiplay");};
int main()
{
  int input;
  printf( "1. Play game\n" );
  printf( "2. Load game\n" );
  printf( "3. Play multiplayer\n" );
  printf( "4. Exit\n" );
  printf( "Selection: " );
  scanf( "%d", &input );
  switch ( input ) {
  case 1:            /* Note the colon, not a semicolon */
    playgame();
    break;         //don't forget the break in each case
  case 2:          
    loadgame();
    break;
  case 3:         
    playmultiplayer();
    break;
  case 4:        
    printf( "Thanks for playing!\n" );
    break;
  default:            
    printf( "Bad input, quitting!\n" );
    break;
  }
  return 0;
}
