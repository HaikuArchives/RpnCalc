#include "RPNApp.h"
#include "RPNWin.h"

int main()
{
	RPNApp * app = new RPNApp();
	app->Run();
	
	delete app;
	return(0);
}

RPNApp::RPNApp()
	:BApplication( "application/x-reinecke-RPNA" )
{
}

void RPNApp::ReadyToRun()
{
	RPNWin * MainWin = new RPNWin( BRect( 100,100,400,283 ) );
	MainWin->Show();
}