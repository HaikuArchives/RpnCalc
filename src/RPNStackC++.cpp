#include "RPNStackC++.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "RPNAlert.h"
#include "RPNutil.cpp"

Stack::Stack()
{
	int i;
	
	Level=0;
	ErrorMsg=good;
	
	for(i=0;i<MAX_DEPTH;i++)
		TheStack[ i ]=0;
}

double Stack::Pop( void )
{
	if( Level<=0 )
	{
		ErrorMsg=underflow;
		//DispError();
		return( -1 );
	}
	else
	{	
		Level--;
		return( TheStack[ Level ] );
	}
}

void Stack::Push( double input )
{
	if( Level>=MAX_DEPTH )
	{
		ErrorMsg=overflow;
		//DispError();
	}
	else
	{
		TheStack[ Level ] = input;
		Level++;
	}
}

int Stack::Depth( void )
{
	return( Level );
}

double Stack::Peek( int depth )
{
	if( depth<=Level && depth>0 )
		return( TheStack[ Level-depth ] );
	else
	{
		ErrorMsg=unknown;
		RPNAlert * Alert = new RPNAlert( "Error in Stack::Peek( int depth ): int level is out of range" );
		return( -1 );
	}
}

Err Stack::GetError( void )
{
	return( ErrorMsg );
}

void Stack::DispError( void )
{
	switch(ErrorMsg)
	{
		case good:
			RPNAlert * AlertG = new RPNAlert( "Error ID 0: good" );
			break;
		case underflow:
			RPNAlert * AlertU = new RPNAlert( "Error ID 1: underflow" );
			break;
		case overflow:
			RPNAlert * AlerO = new RPNAlert( "Error ID 2: overflow" );
			break;
		case unknown:
			RPNAlert * AlertUK = new RPNAlert( "Error ID 4: unknown" );
			break;
	}
}

void Stack::DispError( Err error )
{
	switch(error)
	{
		case good:
			RPNAlert * AlertG = new RPNAlert( "Error ID 0: good" );
			break;
		case underflow:
			RPNAlert * AlertU = new RPNAlert( "Error ID 1: underflow" );
			break;
		case overflow:
			RPNAlert * AlerO = new RPNAlert( "Error ID 2: overflow" );
			break;
		case unknown:
			RPNAlert * AlertUK = new RPNAlert( "Error ID 3: unknown" );
			break;
	}
}

void Stack::DispError( int error )
{
	switch(error)
	{
		case 1:
			RPNAlert * AlertG = new RPNAlert( "Error ID 0: good" );
			break;
		case 2:
			RPNAlert * AlertU = new RPNAlert( "Error ID 1: underflow" );
			break;
		case 4:
			RPNAlert * AlerO = new RPNAlert( "Error ID 2: overflow" );
			break;
		case 8:
			RPNAlert * AlertUK = new RPNAlert( "Error ID 4: unknown" );
			break;
	}
}

void Stack::Disp( char * buf, int levels, int precision )
{
	char string[ 50 ] = "\0";
	int i,n=levels;
	double big = pow( 10, precision );
	double small = pow( 10, -precision );
	
	buf[ 0 ] = '\0';
		
	if( levels<MAX_DEPTH && levels>0 )
	{		
		for(i=Level-levels;i<Level;i++)
		{
			if( i<0 )
			{
				sprintf( string, "\n" );
			}
			else if( TheStack[i] > big || TheStack[i] < -big )
			{
				sprintf( string, "%d:   %.*E\n", n, precision, TheStack[i] );
			}
			else if( isint( TheStack[i] ) )
			{
				sprintf( string, "%d:   %d\n", n, int(TheStack[i]) );
			}
			else if( TheStack[i] < small && TheStack[i] > -small )
			{
				sprintf( string, "%d:   %.*E\n", n, precision, TheStack[i] );
			}
			else
			{
				sprintf( string, "%d:   %.*f\n", n, precision, TheStack[i] );
			}
			
			strcat( buf, string );
			n--;
		}
	}		
	else
	{
		ErrorMsg=unknown;
		RPNAlert * Alert = new RPNAlert( "Error in Stack::Disp( int levels ): int levels is out of range"  );
	}
}