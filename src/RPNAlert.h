#include <Alert.h>

 class RPNAlert
 	:public BAlert
 {
 	public:
	RPNAlert( const char * text, alert_type type );
	RPNAlert( const char * text );
 };