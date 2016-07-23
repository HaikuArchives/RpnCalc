#include "RPNAlert.h"

RPNAlert::RPNAlert( const char * text, alert_type type )
	:BAlert( "alert", text, "OK", NULL, NULL, B_WIDTH_FROM_WIDEST, type )
{
	Go();
}

RPNAlert::RPNAlert( const char * text )
	:BAlert( "alert", text, "OK", NULL, NULL, B_WIDTH_FROM_WIDEST, B_WARNING_ALERT )
{
	Go();
}