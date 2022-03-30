#include <stdio.h>
#include <math.h>

#define ETCH "stroke=\"#ff0000\" fill=\"none\" stroke-width=\".05mm\""
#define CUT  "stroke=\"#0000ff\" fill=\"none\" stroke-width=\".05mm\""
#define MATERIAL_THICKNESS 8.6

//CNLohr's Super Basic SVG Toolkit.
int inpath = 0;
int started = 0;
const char * lastcolor = "black";
float centerx, centery;
void StartSVG( float width, float height ) { printf( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" ); printf( "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%fmm\" height=\"%fmm\" x=\"0\" y=\"0\" viewBox=\"0 0 %f %f\">\n", width, height, width, height ); }
void PathClose() { if( !inpath ) return; printf( "Z\" />\n" ); inpath = 0; }
void PathStart( const char * props ) { if( inpath ) PathClose(); lastcolor = props; printf( "<path %s d=\"", props ); inpath = 1; started = 0; }
void PathM( float x, float y ) { if( !inpath ) PathStart(lastcolor); printf( "M%f %f ", x+centerx, y+centery ); started = 1; }
void PathL( float x, float y ) { if( !inpath ) PathStart(lastcolor); printf( "%c%f %f ", started?'L':'M', x+centerx, y+centery ); started = 1; }
void PathQ( float xc, float yc, float x, float y ) { if( !inpath ) PathStart(lastcolor); printf( "Q%f %f, %f %f ", xc+centerx, yc+centery, x+centerx, y+centery ); started = 1; }
void PathAS( float r, float x, float y, int laf, int sf ) { printf( "A%f %f 0 %d %d %f %f ", r, r, laf, sf, x+centerx, y+centery ); }
void Circle( const char * props, float x, float y, float r ) { if( inpath ) PathClose(); printf( "<circle  cx=\"%f\" cy=\"%f\" r=\"%f\" %s />\n", x+centerx, y+centery, r, props ); }
void EndSVG() { PathClose(); printf( "</svg>" ); }

float smooth( float t ) { return t / sqrt(t*t+1.); }
float lerp( float a, float b, float t ) { return a * (1.-t) + b * t; }
void Scale2d( float * out, float * a, float scale ) { out[0] = a[0] * scale; out[1] = a[1] * scale; }
void Sub2d( float * out, float * a, float * b ) { out[0] = a[0] - b[0]; out[1] = a[1] - b[1]; }
void Add2d( float * out, float * a, float * b ) { out[0] = a[0] + b[0]; out[1] = a[1] + b[1]; }
void Normalize2d( float * out, float * in ) { float mag = 1./sqrt( in[0] * in[0] + in[1] * in[1] ); Scale2d( out, in, mag ); }
void Normal2d( float * out, float * in ) { out[0] = -in[1]; out[1] = in[0]; }


#define TOOTH_WIDTH 30
#define EAR 0.5
#define SCREW_WIDTH 3.5
#define SCREW_EXTRA 4.0
#define NUT_WIDTH   10.0
#define NUT_HEIGHT   2.9
#define T_DEPTH     6

void DrawBox( const char * type, float x1, float y1, float x2, float y2, float ear )
{
	PathStart( type );
	PathM( x1, y1 );
	PathL( x1-ear, y1-ear );
	PathL( x1, y1 );
	PathL( x2, y1 );
	PathL( x2+ear, y1-ear );	
	PathL( x2, y1 );
	PathL( x2, y2 );
	PathL( x2+ear, y2+ear );
	PathL( x2, y2 );
	PathL( x1, y2 );
	PathL( x1-ear, y2+ear );
	PathL( x1, y2 );
	PathL( x1, y1 );
	PathClose();
}

void DrawTest();

int main()
{
	DrawTest();
}

void DrawTest()
{
	StartSVG( 300, 300 );
	PathStart( CUT );
	
	centery = 0;
	centerx = 0;

	//Tooth
	PathM( 10, 20 );
	PathL( 30, 20 );
	PathL( 30+EAR, 20+EAR );
	PathL( 30, 20 );
	PathL( 30, 20 - MATERIAL_THICKNESS );
	PathL( 30+TOOTH_WIDTH, 20-MATERIAL_THICKNESS );
	PathL( 30+TOOTH_WIDTH, 20 );
	PathL( 30+TOOTH_WIDTH-EAR, 20+EAR );
	PathL( 30+TOOTH_WIDTH, 20 );
	
	//Insert T
	PathL( 80-(SCREW_WIDTH/2), 20 );
	PathL( 80-(SCREW_WIDTH/2), 20+T_DEPTH );
	PathL( 80-(NUT_WIDTH-SCREW_WIDTH)/2.0, 20+T_DEPTH );
	PathL( 80-(NUT_WIDTH-SCREW_WIDTH)/2.0, 20+T_DEPTH+NUT_HEIGHT );
	PathL( 80-(SCREW_WIDTH/2), 20+T_DEPTH+NUT_HEIGHT );
	PathL( 80-(SCREW_WIDTH/2), 20+T_DEPTH+NUT_HEIGHT+SCREW_EXTRA );
	PathL( 80+(SCREW_WIDTH/2), 20+T_DEPTH+NUT_HEIGHT+SCREW_EXTRA );
	PathL( 80+(SCREW_WIDTH/2), 20+T_DEPTH+NUT_HEIGHT );
	PathL( 80+(NUT_WIDTH-SCREW_WIDTH)/2.0, 20+T_DEPTH+NUT_HEIGHT );
	PathL( 80+(NUT_WIDTH-SCREW_WIDTH)/2.0, 20+T_DEPTH );
	PathL( 80+(SCREW_WIDTH/2), 20+T_DEPTH );
	PathL( 80+(SCREW_WIDTH/2), 20 );
	
	// Other tooth
	PathL( 100, 20 );
	PathL( 100+EAR, 20+EAR );
	PathL( 100, 20 );
	PathL( 100, 20 - MATERIAL_THICKNESS );
	PathL( 100+TOOTH_WIDTH, 20-MATERIAL_THICKNESS );
	PathL( 100+TOOTH_WIDTH, 20 );
	PathL( 100+TOOTH_WIDTH-EAR, 20+EAR );
	PathL( 100+TOOTH_WIDTH, 20 );
	
	PathL( 100+TOOTH_WIDTH+20, 20 );
	PathL( 100+TOOTH_WIDTH+20, 50 );
	PathL( 10, 50 );
	
	PathClose();
	
	// Sockets
	int x;
	int y;
	for( x = 0; x < 4; x++ )
	for( y = 0; y < 4; y++ )
	{
		//.5mm offset
		//Try X and Y offsets of 0.15mm offsets (actually 0.15mm in each direction, so 0.3mm side-to-side clearances
		//
		// Experimentally, I found that a clearance of -0.15 **and** rear socket insertion (make your cut so the receiver (Female) side is face down)
		// Creates a great fit.
		float tx = (x-1)*.15;
		float ty = (y-1)*.15;
		float ox = 0;
		float oy = y * 55 + x*13;
		DrawBox( CUT, ox+30-tx,  oy+60-ty, ox+30+TOOTH_WIDTH+tx,  oy+60+MATERIAL_THICKNESS+ty, EAR );
		DrawBox( CUT, ox+100-tx, oy+60-ty, ox+100+TOOTH_WIDTH+tx, oy+60+MATERIAL_THICKNESS+ty, EAR );
		Circle( CUT, 80, oy+60+(MATERIAL_THICKNESS+ty)/2.0, SCREW_WIDTH/2 );
	}
	
	// LEDs
	for( y = 0; y < 27; y++ )
	{
		float oy = y * 1000.0/144.0;
		float yo = 4.2 + y * .1;
		DrawBox( CUT, 140, y+oy+55, 145, y+oy+55+yo, 0 );
	}
	PathStart( CUT );
	PathM( 155, 0 );
	PathL( 155, 330 );
	PathClose();
		
	EndSVG();
}
