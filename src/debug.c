#include "debug.h"
void pause ( void ) 
{ 
  printf ( "Press [Enter] to continue . . ." );
  fflush ( stdout );
  getchar();
} 