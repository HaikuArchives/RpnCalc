#define	MAX_DEPTH	100

enum Err { good=0, underflow=1, overflow=2, unknown=4 };

class Stack{
	public:
	Stack();
	double Pop( void );
	void Push( double input );
	int Depth( void );
	double Peek( int depth );
	Err GetError( void );
	void DispError( void );
	void DispError( Err error );
	void DispError( int error );
	void Disp( char * buf, int levels, int precision );
	
	private:
	double TheStack[ MAX_DEPTH ];
	int Level;
	Err ErrorMsg;
	
};