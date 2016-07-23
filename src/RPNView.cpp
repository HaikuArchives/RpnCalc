#include "RPNView.h"
#include <stdio.h>

RPNView::RPNView( BRect Frame, const char * name )
	:BView( Frame, name, B_FOLLOW_NONE, B_WILL_DRAW )
{		
		SetViewColor( 220,220,220,0 );
}