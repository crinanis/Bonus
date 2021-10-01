/* MALLOC.C: This program allocates memory with
 * malloc, then frees the memory with free.
 */

#include <stdlib.h>         /* For _MAX_PATH definition */
#include <stdio.h>
#include <malloc.h>

void main( void )
{
	char *string;

	/* Allocate space for a path name */
	string = malloc( _MAX_PATH );
	if( string == NULL )
		printf( "Insufficient memory available\n" );
	else
		{
		printf( "Memory space allocated for path name\n" );
		free( string );
		printf( "Memory freed\n" );
		}
}
