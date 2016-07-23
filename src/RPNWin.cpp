#include "RPNWin.h"
#include "RPNAlert.h"
#include "RPNcommands.h"
#include "RPNutil.h"
#include <string.h>

RPNWin::RPNWin( BRect Frame )
	:BWindow( Frame, "RPNCalc", B_TITLED_WINDOW, B_NOT_RESIZABLE )
{
	//View
	WinView = new RPNView( BRect( 0,17,300,183 ), "WinView" );
	
	//Border
	BBox * BoxBorder = new BBox( BRect( 5,5,295,122 ), "Box", B_FOLLOW_NONE, B_WILL_DRAW );
	
	//Out Field
	OutTxt = new BTextView( BRect( 2,2,288,115 ), "OutTxt", BRect( 5,5,280,109 ), B_FOLLOW_NONE, B_WILL_DRAW );
	OutTxt->MakeEditable( false );
	
	//Input Field
	InTxt = new BTextControl( BRect(5,136,242,157), "InTxt", "Command:", "", new BMessage( INTXT ) );
	InTxt->SetDivider( 50 );
	
	//Btn
	EnterBtn =  new BButton( BRect(250,134,291,157), "Enter", "Enter", new BMessage( ENTER ));
	
	//Menu Bar
	BMenuBar * MainMenu = new BMenuBar( BRect(0,0,0,0), "MainMenuBar" );
	
	//File Menu
	FileMenu = new BMenu( "File" );
	FileQuit = new BMenuItem( "Quit", new BMessage( F_QUIT ) );
	
	FileQuit->SetShortcut( 'Q', B_COMMAND_KEY );
	
	FileMenu->AddItem( FileQuit );
	MainMenu->AddItem( FileMenu );
	
	//Trig Menu
	AngleMenu = new BMenu( "Trig-Mode" );
	Deg = new BMenuItem( "Degrees", new BMessage( DEG ) );
	Rad = new BMenuItem( "Radians", new BMessage( RAD ) );
	
	Deg->SetShortcut( 'D', B_COMMAND_KEY );
	Rad->SetShortcut( 'R', B_COMMAND_KEY );
	Rad->SetMarked( true );
	
	AngleMenu->AddItem( Deg );
	AngleMenu->AddItem( Rad );
	MainMenu->AddItem( AngleMenu );
	
	//Precision Menu
	PrecMenu = new BMenu( "Precision" );
	PSix = new BMenuItem( "6 Places", new BMessage( P6 ) );
	PNine = new BMenuItem( "9 Places", new BMessage( P9 ) );
	PTwelve = new BMenuItem( "12 Places", new BMessage( P12 ) );
	
	PSix->SetShortcut( '6', B_COMMAND_KEY );
	PNine->SetShortcut( '9', B_COMMAND_KEY );
	PTwelve->SetShortcut( '2', B_COMMAND_KEY );
	PTwelve->SetMarked( true );
	
	PrecMenu->AddItem( PSix );
	PrecMenu->AddItem( PNine );
	PrecMenu->AddItem( PTwelve );
	MainMenu->AddItem( PrecMenu );
	
	
	Lock();
	
	//Add Children
	BoxBorder->AddChild( OutTxt );
	WinView->AddChild( BoxBorder );
	WinView->AddChild( EnterBtn );
	WinView->AddChild( InTxt );
	AddChild( WinView );
	AddChild( MainMenu );
	
	//Misc Config
	SetDefaultButton( EnterBtn );
	InTxt->MakeFocus( true );
	
	tmode=rad;
	precision=12;
	
	char output[ 300 ];
	S.Disp( output, 8, precision );
	OutTxt->SetText( output );
	
	Unlock();
}

void RPNWin::Zoom( BPoint LeftTop, float Width, float Height )
{
}

bool RPNWin::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}

void RPNWin::MessageReceived( BMessage * msg )
{	
	switch(msg->what)
	{
		case ENTER:
		strcpy( input, InTxt->Text() );
		InTxt->SetText( "" );
		InTxt->MakeFocus( true );
		if( isnumber( input ) )
		{
			S.Push( atof( input ) );
		}
		else
		{
			makeupper( input );
			int docmderr=docmd( input, S, VarMem, tmode );
			if( docmderr )
				RPNAlert * InvCmd = new RPNAlert( "Error: Invalid Command" );
		}
		char output[ 300 ];
		S.Disp( output, 8, precision );
		OutTxt->SetText( output );
		break;
		case F_QUIT:
		be_app->PostMessage(B_QUIT_REQUESTED);
		break;
		case RAD:
		Rad->SetMarked( true );
		Deg->SetMarked( false );
		tmode=rad;
		break;
		case DEG:
		Rad->SetMarked( false );
		Deg->SetMarked( true );
		tmode=deg;
		break;
		case P6:
		PSix->SetMarked( true );
		PNine->SetMarked( false );
		PTwelve->SetMarked( false );
		precision=6;
		S.Disp( output, 8, precision );
		OutTxt->SetText( output );
		break;
		case P9:
		PSix->SetMarked( false );
		PNine->SetMarked( true );
		PTwelve->SetMarked( false );
		precision=9;
		S.Disp( output, 8, precision );
		OutTxt->SetText( output );
		break;
		case P12:
		PSix->SetMarked( false );
		PNine->SetMarked( false );
		PTwelve->SetMarked( true );
		precision=12;
		S.Disp( output, 8, precision );
		OutTxt->SetText( output );
		break;
	}
}