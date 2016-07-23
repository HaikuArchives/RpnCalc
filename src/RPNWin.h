#include <Window.h>
#include <Button.h>
#include "RPNView.h"
#include "RPNStackC++.h"
#include "RPNCalcMem.h"
#include "RPNTrigMode.h"

#define	ENTER	'ENTR'
#define	INTXT	'ITXT'

#define RAD		'RADS'
#define	DEG		'DEGS'

#define	P6		'PR06'
#define	P9		'PR09'
#define P12		'PR12'

#define	F_QUIT	'FLQT'

class RPNWin
	:public BWindow
{
	public:
	RPNWin( BRect Frame );
	virtual void Zoom( BPoint LeftTop, float Width, float Height );
	virtual bool QuitRequested();
	virtual void MessageReceived( BMessage * msg );
	
	private:
	RPNView * WinView;
	
	BTextView * OutTxt;
	BButton * EnterBtn;
	BTextControl * InTxt;
	
	BMenu * FileMenu;
	BMenuItem * FileQuit;
	
	BMenu * AngleMenu;
	BMenuItem * Deg;
	BMenuItem * Rad;
	
	BMenu * PrecMenu;
	BMenuItem * PSix;
	BMenuItem * PNine;
	BMenuItem * PTwelve;
	
	char input[ 100 ];
	Stack S;
	CalcMem VarMem;
	TrigMode tmode;
	int precision;
};