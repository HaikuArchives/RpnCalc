#define	MAX_MEM_SIZE	100

class CalcMem{
	public:
	CalcMem();
	void Set( double number, int slot );
	double Get( int slot );
	
	private:
	float memary[ MAX_MEM_SIZE ];
};