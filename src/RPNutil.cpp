#include "RPNutil.h"

int isint( double testdbl )
{
	int n = int( testdbl );
	if( !(n-testdbl) )
		return( 1 );
	else
		return( 0 );
}

int isnumber( const char * instring )
{
	int length=strlen( instring );
	int i=0, test=false;
	
	for(i=0;i<length && i<90;i++)
	{
			if( isdigit(instring[ i ]) )
			test=true;
	}
	if( !isdigit(instring[0]) && instring[0]!='.' && instring[0]!='-' && instring[0]!='+' )
		test=false; 
	
	return( test );
}

void makeupper( char * string )
{
	int length=strlen( string );
	int i=0;
	for(i=0;i<length;i++)
		string[ i ]=toupper( string[i] );
}