#include <string.h>
#include <math.h>
#include "RPNStackC++.h"
#include "RPNCalcMem.h"
#include "RPNTrigMode.h"
#include "RPNcommands.h"

int docmd( const char * buf, Stack & Stk, CalcMem & CMem, TrigMode & trigmode )
{
	const double Pi=3.14159265358979323846;
	
	Err Error=good;
	Stack StkCpy = Stk;
	int invalid=false; 		//Is the command invalid?
	int i=0,n=0 ;			//For whatever they are needed
	double a=0,b=0,x=0,y=0;	//For whatever
	double array[ 100 ];	//For whatever
	
	if( !strcmp( buf,"EXIT" ) )
	{
		be_app->PostMessage(B_QUIT_REQUESTED);
	}
	//-----Constants
	else if( !strcmp( buf,"E") )
	{
		Stk.Push( exp( 1 ) );
	}
	else if( !strcmp( buf,"PI") )
	{
		Stk.Push( Pi );
	}
	//-----Stack Operators
	else if( !strcmp( buf,"" ) )
	{
		x=Stk.Pop();
		Stk.Push( x );
		Stk.Push( x );
	}
	else if( !strcmp( buf,"DUP" ) )
	{
		x=Stk.Pop();
		Stk.Push( x );
		Stk.Push( x );
	}
	else if( !strcmp( buf,"DROP" ) )
	{
		Stk.Pop();
	}
	else if( !strcmp( buf,"CLEAR") )
	{
		n=Stk.Depth();
		for(i=0;i<n;i++)
			Stk.Pop();
	}
	else if( !strcmp( buf,"SWAP") )
	{
		a=Stk.Pop();
		b=Stk.Pop();
		Stk.Push( a );
		Stk.Push( b );
	}
	else if( !strcmp( buf,"OVER") )
	{
		a=Stk.Peek( 2 );
		Stk.Push( a );
	}
	else if( !strcmp( buf,"DEPTH") )
	{
		Stk.Push( Stk.Depth() );
	}
	else if( !strcmp( buf,"PICK") )
	{
		Stk.Push( Stk.Peek( Stk.Pop() ) );
	}
	else if( !strcmp( buf,"ROLL") )
	{
		n=int( Stk.Pop() );
		for(i=0;i<n-1;i++)
			array[ i ]=Stk.Pop();
		x=Stk.Pop();
		for(i=n-2;i>=0;i--)
			Stk.Push( array[ i ] );
		Stk.Push( x );
	}
	//-----Basic Arithmetic Operators
	else if( !strcmp( buf,"+") )
	{
		Stk.Push( Stk.Pop() + Stk.Pop() );
	}
	else if( !strcmp( buf,"-") )
	{
		Stk.Push( Stk.Pop() - Stk.Pop() );	
	}
	else if( !strcmp( buf,"*") )
	{
		Stk.Push( Stk.Pop() * Stk.Pop() );
	}
	else if( !strcmp( buf,"/") )
	{
		Stk.Push( Stk.Pop() / Stk.Pop() );
	}
	//-----Miscellaneous Algebraic Ops
	else if( !strcmp( buf,"INV") )
	{
		Stk.Push( 1/Stk.Pop() );
	}
	else if( !strcmp( buf,"NEG") )
	{
		Stk.Push( -Stk.Pop() );	
	}
	else if( !strcmp( buf,"IP") )
	{
		Stk.Push( float( int( Stk.Pop() ) ) );
	}
	else if( !strcmp( buf,"FP") )
	{
		x=Stk.Pop();
		n=int( x );
		if( n>0 )
			Stk.Push( x-n );
		else
			Stk.Push( n-x );
	}
	else if( !strcmp( buf,"ABS") )
	{
		Stk.Push( fabs( Stk.Pop() ) );
	}
	//-----Exponents and Logs
	else if( !strcmp( buf,"SQ") )
	{
		a=Stk.Pop();
		Stk.Push( a*a );
	}
	else if( !strcmp( buf,"SQRT") )
	{
		Stk.Push( sqrt( Stk.Pop() ) );
	}
	else if( !strcmp( buf,"^") )
	{
		x=Stk.Pop();
		b=Stk.Pop();
		Stk.Push( pow( b, x ) );
	}
	else if( !strcmp( buf,"EXP") )
	{
		Stk.Push( exp( Stk.Pop() ) );
	}
	else if( !strcmp( buf,"LN") )
	{
		Stk.Push( log( Stk.Pop() ) );
	}
	else if( !strcmp( buf,"ALOG") )
	{
		Stk.Push( pow( 10, Stk.Pop() ) );
	}
	else if( !strcmp( buf,"LOG") )
	{
		Stk.Push( log10( Stk.Pop() ) );
	}
	//-----Trig Functions
	else if( !strcmp( buf,"SIN") )
	{
		if( trigmode==rad )
			Stk.Push( sin( Stk.Pop() ) );
		else
			Stk.Push( sin( Stk.Pop()*Pi/180 ) );
	}
	else if( !strcmp( buf,"COS") )
	{
		if( trigmode==rad )
			Stk.Push( cos( Stk.Pop() ) );
		else
			Stk.Push( cos( Stk.Pop()*Pi/180 ) );
	}
	else if( !strcmp( buf,"TAN") )
	{
		if( trigmode==rad )
			Stk.Push( tan( Stk.Pop() ) );
		else
			Stk.Push( tan( Stk.Pop()*Pi/180 ) );
	}
	else if( !strcmp( buf,"ASIN") )
	{
		if( trigmode==rad )
			Stk.Push( asin( Stk.Pop() ) );
		else
			Stk.Push( asin( Stk.Pop() )*180/Pi );
	}
	else if( !strcmp( buf,"ACOS") )
	{
		if( trigmode==rad )
			Stk.Push( acos( Stk.Pop() ) );
		else
			Stk.Push( acos( Stk.Pop() )*180/Pi );
	}
	else if( !strcmp( buf,"ATAN") )
	{
		if( trigmode==rad )
			Stk.Push( atan( Stk.Pop() ) );
		else
			Stk.Push( atan( Stk.Pop() )*180/Pi );
	}
	else if( !strcmp( buf,"R>D") )
	{
		Stk.Push( Stk.Pop()*180/Pi );
	}
	else if( !strcmp( buf,"D>R") )
	{
		Stk.Push( Stk.Pop()*Pi/180 );
	}
	/*  Controlled from Menu
	else if( !strcmp( buf,"RAD") )
	{
		trigmode=rad;
	}
	else if( !strcmp( buf,"DEG") )
	{
		trigmode=deg;
	}*/
	//-----Memory Commands
	else if( !strcmp( buf,"STO") )
	{
		n=int( Stk.Pop() );
		CMem.Set( Stk.Pop(), n );
	}
	else if( !strcmp( buf,"GET") )
	{
		Stk.Push( CMem.Get( int( Stk.Pop() ) ) );
	}
	//-----command isn't good, seterror to true
	else
		invalid=true;
		
	//If there is an error, put the stack back the way it was
	Error = Stk.GetError();
	if( Error!=good )
	{
		Stk.DispError( Error );
		Stk = StkCpy;
	}
		
	return( invalid );
}