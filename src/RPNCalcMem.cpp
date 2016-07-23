#include "RPNCalcMem.h"
#include "RPNAlert.h"

CalcMem::CalcMem()
{
	int i;
	for(i=0;i<MAX_MEM_SIZE;i++)
		memary[ i ]=0;
}

void CalcMem::Set( double number, int slot )
{
	if( slot>=0 && slot<MAX_MEM_SIZE )
		memary[ slot ]=number;
	else
		RPNAlert * Alert = new RPNAlert( "Error: Memory address out of range" );
}

double CalcMem::Get( int slot )
{
	if( slot>=0 && slot<MAX_MEM_SIZE )
		return( memary[ slot ] );
	else
	{
		RPNAlert * Alert = new RPNAlert( "Error: Memory address out of range" );
		return( -1 );
	}
}