// OKAY I THINK: Can I acces the CPU 12V Power? No (Make sure as part of the later step, Mobo moves away from the wall by 0.5mm)
//
// OKAY: Make all T's a little wider. Make hat thin part 0.2mm wider. ACTUAL thickness of stalk is 4.41mm, actual width is 3.21mm.
// OKAY: Tongues on sides don't line up.
// OKAY: Middle brace holder needs to be thinner on both sides.
// OKAY: Add 0.2mm tongue slop side-to-side.  Material thickness Also +0.2mm on tongue
// OKAY: SFP PSU pull mounts 0.3mm more inward,like on each side, pull the pairs of screws more towards the PSU.  Move them up by 0.1mm.
// OKAY: Move the SSD access window in the back towards where the cables plug in by 10mm and more towards the PCI-E bus by 2.5mm
// OKAY: Front T doesn't line up with hole on mobo plate. (Fixed earlier)
// OKAY: GPU card edge connector needs a little more comfort.  Increase GPU Card edge by 1mm
// ????: Make holes that the motherboard CPU connect into a little bit closer?????? <<???
// OKAY: Retract motherboard access plate.
// OKAY: Move mobo back some and towards the GPU

// OKAY: Bump up mobo IO backplate by 4.5mm to 5mm whatever is cleaner.

// OKAY: Tighten up the T's, and mobo studs by 0.1mm?
// OKAY: Tighten up holes for mobo spacers under mobo by 0.1mm?
// OKAY: Make cutout on side where GPU is for power cable.
// OKAY: Consider making joining termination top-with-bottom to be to put T on side so the tongue itself can be screwd in, so that the top can be removed directly.
// OKAY: Consider pushing center brace more towards PSU, and making it top-slot.
// OKAY: For USB, make it rectangular.
// OKAY: Make test swatch with T's and circles.
// OKAY: Move SFX up another 0.5mm
// OKAY: Increase GPU thickness by 0.3mm
// OKAY: Make motherboad back plate have a little more wiggle room.
// OKAY: Make top-plate, able to hold feed for GPU
// TODO: USB type C
// OKAY: Double-Check 12V ATX CPU power access. -- Will be removing back panel mounting for ATX side.
// OKAY: Update T's, Circles, accordingly.  0.1mm wider at widest, 0.05mm thicker. 0.2mm deeper.
// OKAY: Shrink holes for M3 just a hair 0.05mm smaller
// OKAY: Move T 0.5mm toward surface.

// TODO: Consider flipping PSU to front. 
// OKAY: Make it so the back can connect or be pulled off by only pulling upward.
// OKAY: Make sure back piece has a lot of clearance for the CPU power connector.
// OKAY: Increase side height by 10mm
// OKAY: Make top brace brace around CPU cooler + over GPU.
// OKAY: Make Motherboard plate use 120 LEDs/m (or less)
// OKAY: Widen aperture for motherboard LEDs to 4.8mm.
// OKAY: Make back pull-off-able.
// OKAY: Shrink front-part of USB-C connector.
// OKAY: Move power button, maybe tighter with the USB connectors?
// OKAY: Clearance around CPU is 135-140mm
// OKAY: Make top plate mesh with side/top.

// OKAY: Make faceplate go all the way to the front. -> front_plate_top_plate_extend_y 
// OKAY: Why don't front holes line up?

// OKAY: Extend T a bit again
// OKAY?: Fix GPU height

// OKAY: Top plate extends too far forward.
// OKAY: Side panel on left side missing tongue hole

// TODO: Front plate does not quiiiite line up.
// TODO: Side top stub in wrong place?

// Notes:
// * Pre-drill with .118
// * Pre-drill motherboard back as well as all others.

#include <stdio.h>
#include <math.h>

#define ETCH "stroke=\"#ff0000\" fill=\"none\" stroke-width=\".05mm\""
#define CUT  "stroke=\"#0000ff\" fill=\"none\" stroke-width=\".05mm\""

//CNLohr's Super Basic SVG Toolkit.
int inpath = 0;
int started = 0;
const char * lastcolor = "black";
float centerx, centery;
void StartSVG( float width, float height ) { printf( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" ); printf( "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"%fmm\" height=\"%fmm\" x=\"0\" y=\"0\" viewBox=\"0 0 %f %f\">\n", width, height, width, height ); }
void PathClose() { if( !inpath ) return; printf( "Z\" />\n" ); inpath = 0; }
void PathStop() { if( !inpath ) return; printf( "\" />\n" ); inpath = 0; }
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


#define MATERIAL_THICKNESS 8.9
#define TOOTH_WIDTH 30.0
#define EAR 0.5
#define M3_SCREW_WIDTH 3.2 // For PSU+USB connectors
#define M3_MOUNTING_SCREW_WIDTH 4.2 // Inserts for Mobo Mount


#define SCREW_IN_WIDTH 3.1
#define FRONTPLATE_BASEWIDTH 65 // (Actually front-to-back)
#define FRONTPLATE_OFFSET 94
float frontplate_calc_mid_width = 0;

#if 0
// Regular Nuts
#define NUT_WIDTH   8.0
#define NUT_HEIGHT   2.6
#define T_DEPTH     5.2
#define SCREW_EXTRA 3.0
#define SCREW_WIDTH 3.5
// DIN562 THIN Nut M3 (Square)
#elif 0
#define NUT_WIDTH   5.5
#define NUT_HEIGHT   1.7
#define T_DEPTH     5.0
#define SCREW_EXTRA 3.0  // How much further the screw penetrates
#define SCREW_WIDTH 3.1
#else
// Heat insert M3
#define NUT_WIDTH   6
#define NUT_HEIGHT   .9
#define T_DEPTH     5.5
#define SCREW_EXTRA 1.5  // How much further the screw penetrates
#define SCREW_WIDTH 3.05
#define SCREW_WIDTH_T 4.03
#endif

// apply to both sides of inside cuts.
#define CUT_CLEARANCE -.1

// After some experimenting, would just be nice if this was bigger.
#define CUT_CLEARANCE_TONGUE 0.0

#define GHEXSIZE 9.0

#define BACKPLATE_DOES_NOT_GO_BEHIND_CPU 1



#define top_plate_front_panel_max_x 200.0
#define top_plate_front_panel_min_x 131.0


#define BACKPLATE_GOES_UP 1
#define BACKPLATE_PARTIAL_TONGUE MATERIAL_THICKNESS
#define TOP_PLATE_BACK_SCREW_OFFSET 125.0

#define PSU_IS_ON_FRONT 1

#define DO_CASE_1 1
#define DO_CASE_2 1
#define DO_CASE_3 1

#define YES_HANDLE 0

// No mid-plate, instead use a top-plate.
#define nomiddleplate 1

#define NZSIGN( x ) (( x < 0 )?-1:1)

void DrawBox( const char * type, float x1, float y1, float x2, float y2, float ear )
{
	PathStart( type );
	PathM( x1, y1 );
	if( ear > 0 )
	{
		PathL( x1-ear, y1-ear );
		PathL( x1, y1 );
	}
	PathL( x2, y1 );
	if( ear > 0 )
	{
		PathL( x2+ear, y1-ear );	
		PathL( x2, y1 );
	}
	PathL( x2, y2 );
	if( ear > 0 )
	{
		PathL( x2+ear, y2+ear );
		PathL( x2, y2 );
	}
	PathL( x1, y2 );
	if( ear > 0 )
	{
		PathL( x1-ear, y2+ear );
		PathL( x1, y2 );
	}
	PathL( x1, y1 );
	PathClose();
}

	
void PathLXForm( float cx, float cy, float dx, float dy, float dirx, float diry )
{
	float newx = dirx * dy - diry * dx;
	float newy = diry * dy + dirx * dx;

	PathL( cx+newx, cy+newy );
}

// Insert a T bolt
void InsertT( float cx, float cy, float dirx, float diry, float screw_width, float nut_width, float nut_height, float tdepth, float screw_extra )
{
	PathLXForm( cx, cy, -(screw_width/2), 0, dirx, diry );
	PathLXForm( cx, cy, -(screw_width/2), tdepth, dirx, diry );
	PathLXForm( cx, cy, -(nut_width)/2.0, tdepth, dirx, diry  );
	PathLXForm( cx, cy, -(nut_width)/2.0, tdepth+nut_height, dirx, diry  );
	if( screw_extra > 0.00001 )
	{
		PathLXForm( cx, cy, -(screw_width/2), tdepth+nut_height, dirx, diry  );
		PathLXForm( cx, cy, -(screw_width/2), tdepth+nut_height+screw_extra, dirx, diry  );
		PathLXForm( cx, cy, +(screw_width/2), tdepth+nut_height+screw_extra, dirx, diry  );
		PathLXForm( cx, cy, +(screw_width/2), tdepth+nut_height, dirx, diry  );
	}
	PathLXForm( cx, cy, +(nut_width)/2.0, tdepth+nut_height, dirx, diry  );
	PathLXForm( cx, cy, +(nut_width)/2.0, tdepth, dirx, diry  );
	PathLXForm( cx, cy, +(screw_width/2), tdepth, dirx, diry  );
	PathLXForm( cx, cy, +(screw_width/2), 0, dirx, diry );
}
	
void FillHexagons( const char * path, float cx, float cy, float sx, float sy, float HEXSIZE, int alternate )
{
	const float bufferH = 0.5;
	const float bufferW = 0.5;
	const float wspace = 1.732 * HEXSIZE;
	const float hspace = 2 * HEXSIZE;
	float fx, fy;
	int nrhexx = (int)((sx)/wspace);
	int nrhexxandahalf = (int)((sx)/wspace+0.5)-nrhexx;
	int nrhexy = (int)((sy)/hspace);
	int ix, iy;
	for( iy = -nrhexy/2; iy < (nrhexy+1)/2; iy++ )
	for( ix = -nrhexx/2; ix < (nrhexx+1)/2; ix++ )
	{
		int is_alternate = (iy&1);
		float altval = 1;
		float altspace = 0;
		if( (( iy & 1 )^alternate) && (ix == ((nrhexx+1)/2-1) && !nrhexxandahalf ) ) continue;
		float tx = cx + ix * (hspace+bufferW) + (is_alternate?hspace*.5*altval:0) + ((alternate && !is_alternate)?hspace:0);
		float ty = cy + iy * (wspace+bufferH);
		PathStart( path );
		float wx, wy;
		wx = tx-wspace/2; wy = ty-hspace/4; PathM( wx, wy );
		wx = tx; wy = ty-hspace/2;          PathL( wx, wy );
		wx = tx+wspace/2; wy = ty-hspace/4; PathL( wx, wy );

		wx = tx+wspace/2; wy = ty+hspace/4; PathL( wx, wy );
		wx = tx; wy = ty+hspace/2;          PathL( wx, wy );
		wx = tx-wspace/2; wy = ty+hspace/4; PathL( wx, wy );

		PathClose();
	}
}
//Holes for PSU
void DrawPSU( float cx, float cy, float whole_crossbrace_height, float mb_tray_length, float sfx_psu_offset_y, int flip, float ox, float oy )
{
	if( flip )
	{
		Circle( CUT, cy-6.4, cx-6.3, M3_SCREW_WIDTH/2 );
		Circle( CUT, cy-6.4, cx-32.1, M3_SCREW_WIDTH/2 );
		Circle( CUT, cy-6.4, cx-57.9, M3_SCREW_WIDTH/2 ); // This one was covered in previous design
		Circle( CUT, cy-119.1, cx-6.3, M3_SCREW_WIDTH/2 );
		Circle( CUT, cy-119.1, cx-32.1, M3_SCREW_WIDTH/2 );
		Circle( CUT, cy-119.1, cx-57.9, M3_SCREW_WIDTH/2 );
		cx = whole_crossbrace_height-64/2+ox;
		cy = mb_tray_length - 125.5/2 + sfx_psu_offset_y+oy;
		DrawBox( CUT, cy-104/2, cx-56/2, cy+104/2, cx+56/2, 0 );
	}
	else
	{
		Circle( CUT, cx-6.3, cy-6.4, M3_SCREW_WIDTH/2 );
		Circle( CUT, cx-32.1, cy-6.4, M3_SCREW_WIDTH/2 );
		Circle( CUT, cx-57.9, cy-6.4, M3_SCREW_WIDTH/2 ); // This one was covered in previous design
		Circle( CUT, cx-6.3, cy-119.1, M3_SCREW_WIDTH/2 );
		Circle( CUT, cx-32.1, cy-119.1, M3_SCREW_WIDTH/2 );
		Circle( CUT, cx-57.9, cy-119.1, M3_SCREW_WIDTH/2 );
		cx = whole_crossbrace_height-64/2;
		cy = mb_tray_length - 125.5/2 + sfx_psu_offset_y;
		DrawBox( CUT, cx-56/2, cy-104/2, cx+56/2, cy+104/2, 0 );
	}
}

void DrawTest();
void DrawCase();

int main()
{
	//DrawTest();
	DrawCase();
}

void DrawCase()
{
	float cy = 0;
	float cx = 0;
	int i;
	//Motherboard Tray
	centerx = MATERIAL_THICKNESS+CUT_CLEARANCE+1;
	centery = 1;

	const float tongue_offset = 5; // Only for front- and back- of case.
	const float crossbrace_panel_screw_offset = MATERIAL_THICKNESS;
	const float right_justify = 2.5;
	const float mb_tongue_mm = 40;
	const float mb_tray_length = 314;
	const float itx_x_offset = 143-6 - right_justify;
	const float itx_y_offset = 1.0;
	const float mb_tray_width = 314-2 - right_justify;  // was 172
	const int num_mb_tongues = 3;
	const float bottom_tongue_offset = mb_tray_length-MATERIAL_THICKNESS/2-tongue_offset;
	const float top_tongue_offset = MATERIAL_THICKNESS/2+tongue_offset;
	const float  face_plate_height = mb_tray_length + tongue_offset*2;

	const float middle_tongue_offset = 24;
	const int num_leds_edge = 30;
	const float led_mb_center_x = itx_x_offset+17;
	const float led_mb_center_y = 155;
	const float led_spacing = 8.33;
	const float led_width = 5.1;
	const float led_lateral = 5.8;
	const float led_nooj = 134;
	const float led_noojy = 14;
	
	const float foot_height = 10;
	const float sfx_width = 125;
	const float sfx_height = 64;
	const float sfx_length = 100;
	const float sfx_slop = 0.5;
	float sfx_side_offset = mb_tray_width - sfx_height - 37; //For outline
	const float back_plate_height_from_tray = 0;
	const float sfx_psu_offset_y = -14;
	
	const float crossbrace_tongue_offset_y = -5;
	
	// Hole ready for use but not used in current design.
	const float hole_center_plate_for_mobox = mb_tray_width - 10;
	const float hole_center_plate_for_moboy = 175; //Also used for placment.

	// Middle bracket not used anymore.
	const float middle_bracket_offset = (top_tongue_offset + bottom_tongue_offset + middle_tongue_offset)/2;
	
	const float back_valence_width = 12.3;
	const float back_valence_depth = 35;
	
	const float sfx_slide_offset = 5.25;
	
	// Note GPU cutout does not contain compensation.
	const float gpu_thick = 53.5+10;     //Not actually GPU thickness.  More like offset from whole_crossbrace_height
	const float gpu_height = 123.5;
	const float material_above_gpu = 30; // This has more to do with GPU thickness.
	const float gpu_offset_x = 2.6-right_justify; // Was 18
	const float gpu_rail_mount_from_top = 30.4;
	const float gpu_brace_bar_width = gpu_thick+MATERIAL_THICKNESS-12.75; /// why 12.75???
	
	float whole_crossbrace_height = 9 + 54.1 /* This is more like GPU height */ + 85-64+10; // Works with gpu_thick
	float sidescrew_offset_y = 10;
	float mb_tongue_spacing = (mb_tray_length - (num_mb_tongues*mb_tongue_mm)) / num_mb_tongues;

	float insert_brace_t_x = sfx_length+sfx_slop*2+mb_tongue_mm-6.5-right_justify;
	float insert_brace_t_x_bp_offset = -3.2;
	// For GPU holder / bracket.
	float backplate_mount_lateral = gpu_height + gpu_offset_x - gpu_rail_mount_from_top - MATERIAL_THICKNESS/2 - 64;
	float front_plate_top_plate_extend_y = 0;

	float crossbrace_tongue_center = whole_crossbrace_height/2+crossbrace_tongue_offset_y;


	StartSVG( 809.6+300, 457 );
	
	if( DO_CASE_1 )
	{
		
		//MOTHERBOARD 
		
		// PSU
		//DrawBox( ETCH, sfx_slop + sfx_side_offset, 
		//	mb_tray_length - sfx_slop - sfx_width - MATERIAL_THICKNESS - sfx_slide_offset, 
		//	sfx_slop + sfx_length + sfx_side_offset,
		//	mb_tray_length - sfx_slop - MATERIAL_THICKNESS - sfx_slide_offset, 0 );

		// https://www.silverstonetek.com/techtalk/11008/pic-9.png
		Circle( CUT, itx_x_offset+6.35, itx_y_offset+10.16, M3_MOUNTING_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35+157.48, itx_y_offset+10.16+22.86, M3_MOUNTING_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35+157.48, itx_y_offset+10.16+154.94, M3_MOUNTING_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35, itx_y_offset+10.16+154.94, M3_MOUNTING_SCREW_WIDTH/2 );

		Circle( CUT, insert_brace_t_x, bottom_tongue_offset, SCREW_WIDTH/2 );
		//Circle( CUT, insert_brace_t_x + insert_brace_t_x_bp_offset, middle_bracket_offset, SCREW_WIDTH/2 );  // No middle bracket
		Circle( CUT, insert_brace_t_x + insert_brace_t_x_bp_offset, top_tongue_offset, SCREW_WIDTH/2 );

		float hexagon_y_offset = -2;
		
		FillHexagons( CUT, 84+itx_x_offset-66-74.0, 103+hexagon_y_offset, 112, 160, GHEXSIZE, 1 );
		FillHexagons( CUT, 84+itx_x_offset-66+74.0, 103+hexagon_y_offset, 80, 170, GHEXSIZE, 1 );
		FillHexagons( CUT, 84+itx_x_offset-66, 232+hexagon_y_offset, 220, 130, GHEXSIZE, 1 );
		//Row between mobo and psu
		//FillHexagons( CUT, 95, 174, 125, 20 );
//		FillHexagons( CUT, 84+itx_x_offset-66, 38.6, 60, 30, GHEXSIZE, 1 ); // Back above access panel
		FillHexagons( CUT, 84+itx_x_offset-66+18.6, 167.6+hexagon_y_offset, 44, 40, GHEXSIZE, 1 );

		FillHexagons( CUT, 84+itx_x_offset-66-74.0, 167.6+hexagon_y_offset, 94, 30, GHEXSIZE, 1 );

		
		// Door for flash SSD Access window
		float doorw = 30;
		float doorh = 95;
		float doorx = 33+itx_x_offset;
		float doory = 86;
		DrawBox( CUT, doorx-doorw/2, doory-doorh/2, doorx+doorw/2, doory+doorh/2, 0 );
		FillHexagons( CUT, doorx-13.5, doory+hexagon_y_offset, 30, 100, GHEXSIZE, 1 );


		// Add LEDs
		int j;
		for( j = 0; j < 4; j++ )
		for( i = 0; i < num_leds_edge; i++ )
		{
			float leda = i * led_spacing;
			float ledb = leda + led_width;
			float led_line_width = (num_leds_edge-1) * led_spacing + led_width;
			float led_extra_bottom = 4;
			//if( ( j == 2 && i < 10 ) || ( j == 1 && i >= 16 ) ) continue;
			switch( j )
			{
			case 0:
				DrawBox( CUT, led_mb_center_x-led_line_width/2+leda, led_mb_center_y-led_lateral/2-led_nooj, 
							  led_mb_center_x-led_line_width/2+ledb, led_mb_center_y+led_lateral/2-led_nooj, 0 );
				break;
			case 1:
				DrawBox( CUT, led_mb_center_x+led_line_width/2-led_lateral/2+led_noojy, led_mb_center_y-led_line_width/2+leda+(led_spacing-led_width)/2, 
							  led_mb_center_x+led_line_width/2+led_lateral/2+led_noojy, led_mb_center_y-led_line_width/2+ledb+(led_spacing-led_width)/2, 0 );
				break;
			case 2:
				DrawBox( CUT, led_mb_center_x+led_line_width/2-leda, led_extra_bottom+led_mb_center_y-led_lateral/2+led_nooj, 
							  led_mb_center_x+led_line_width/2-ledb, led_extra_bottom+led_mb_center_y+led_lateral/2+led_nooj, 0 );
				break;
			case 3:
				DrawBox( CUT, led_mb_center_x-led_line_width/2-led_lateral/2-led_noojy, led_mb_center_y+led_line_width/2-leda+(led_spacing-led_width)/2, 
							  led_mb_center_x-led_line_width/2+led_lateral/2-led_noojy, led_mb_center_y+led_line_width/2-ledb+(led_spacing-led_width)/2, 0 );
				break;
			}
		}

		// Screw for bottom sheet.
		//Circle( CUT,  sfx_length+sfx_slop*2+mb_tongue_mm+10, bottom_tongue_offset, SCREW_WIDTH/2 );
		//DrawBox( CUT, sfx_length+sfx_slop*2-CUT_CLEARANCE, bottom_tongue_offset - MATERIAL_THICKNESS/2.0-CUT_CLEARANCE, 
		//			  sfx_length+sfx_slop*2+mb_tongue_mm+CUT_CLEARANCE, bottom_tongue_offset + MATERIAL_THICKNESS/2.0+CUT_CLEARANCE, EAR );


		PathStart( CUT );
		PathM( cx = 0, cy = 0 );
		PathL( cx, cy+=mb_tongue_spacing/2 );
		for( i = cx; i < num_mb_tongues; i++ )
		{
			PathL( cx+EAR, cy+EAR );
			PathL( cx, cy );
			PathL( cx-MATERIAL_THICKNESS, cy );
			PathL( cx-MATERIAL_THICKNESS, cy += mb_tongue_mm );
			PathL( cx, cy );
			PathL( cx+EAR, cy-EAR );
			PathL( cx, cy );
			if( i != num_mb_tongues-1 )
			{
				cy += mb_tongue_spacing/2;
				InsertT( cx, cy, 1, 0, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy += mb_tongue_spacing/2;
			}
			else
				cy += mb_tongue_spacing/2;
			PathL( cx, cy );
		}
		
		// Add center tongue for rear holding tonuge.
		// This was when I thought we'd have an end-mate.  This is probably
		// a bad idea, as it requires orthogonal screws to maintain capture.
		/*
		PathL( cx = sfx_length+sfx_slop-CUT_CLEARANCE, cy );
		PathL( cx, cy-=MATERIAL_THICKNESS+CUT_CLEARANCE );
		PathL( cx-EAR, cy-EAR );
		PathL( cx, cy );
		PathL( cx+=CUT_CLEARANCE*2+mb_tongue_mm, cy );
		PathL( cx+EAR, cy-EAR );
		PathL( cx, cy );
		PathL( cx, cy+=MATERIAL_THICKNESS+CUT_CLEARANCE );
		*/

		// For holding GPU in in the front.
		cx += backplate_mount_lateral;
		InsertT( cx,    cy, 0, -1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
		cx += 35;
		PathL( cx, cy );
		cx += 35;
		InsertT( cx, cy, 0, -1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );

		PathL( cx = mb_tray_width, cy );
		PathL( cx, cy-=mb_tongue_spacing/2 );
		for( i = 0; i < num_mb_tongues; i++ )
		{
			PathL( cx-EAR, cy-EAR );
			PathL( cx, cy );
			cx += MATERIAL_THICKNESS;
			PathL( cx, cy );
			cy -= mb_tongue_mm;
			PathL( cx, cy );
			cx -= MATERIAL_THICKNESS;
			PathL( cx, cy );
			PathL( cx-EAR, cy+EAR );
			PathL( cx, cy );
			if( i != num_mb_tongues-1 )
			{
				cy -= mb_tongue_spacing/2;
				InsertT( cx, cy, -1, 0, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy -= mb_tongue_spacing/2;
			}
			else
				cy -= mb_tongue_spacing/2;
			PathL( cx, cy );
		}

		// In-baseplate-T for holding motherboard back brace bracket.
		InsertT( backplate_mount_lateral, cy, 0, 1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
		PathL( 0, 0 );
		PathClose( );
	}
	
	if( DO_CASE_2 )
	{
		int plate;
		for( plate = 0; plate < 3; plate++ )
		{

			// Bottom plate.
			if( plate == 0 )
			{
				centerx = mb_tray_width+MATERIAL_THICKNESS*3+.5+1;
				centery = 30;
				if( BACKPLATE_DOES_NOT_GO_BEHIND_CPU ) { centerx = 520; centery = 30; }
			}
			else if( plate == 1 )
			{
				centerx = mb_tray_width+MATERIAL_THICKNESS*3+.5+1;
				centery = 115;
			}
			else
			{
				centerx = mb_tray_width+MATERIAL_THICKNESS*3+.5+1;
				centery = 320;
			}

			// No more middle plate.  Instead draw a crossbrace.
			if( plate == 1 && nomiddleplate )
			{
				continue;
			}

			const float handle_bump = 29;
			const float handle_width = 56;
			const float handle_radius = 11;
			const float handle_offset = 1;

			if( YES_HANDLE )
			{
				// Handle
				if( plate != 1 && (!BACKPLATE_DOES_NOT_GO_BEHIND_CPU || plate != 0 ) )
				{
					float phi = 0;
					PathStart( CUT );
					for( ; phi < 3.14159*2; phi += 0.001 )
					{
						float cx = cos( phi )*handle_radius;
						float cy = sin( phi )*handle_radius+handle_offset;
						if( cx < 0 )
							cx -= handle_width/2;
						else
							cx += handle_width/2;
						PathL( cx + mb_tray_width/2, cy - 10 );
					}
					PathClose();
				}
			}

			
			if( plate == 0 || plate == 2 )
			{
				
				// material_above_gpu and gpu_thick
				float gpu_center_line = gpu_thick-23-4;

				Circle( CUT, backplate_mount_lateral, gpu_center_line, SCREW_WIDTH/2 );
				if( plate == 2 )
					Circle( CUT, backplate_mount_lateral+70, gpu_center_line, SCREW_WIDTH/2 );
				//Circle( CUT, backplate_mount_lateral, gpu_center_line+gpu_brace_bar_width/2, SCREW_WIDTH/2 );

			}

			if( plate == 0 )
			{
				if( !BACKPLATE_DOES_NOT_GO_BEHIND_CPU )
					FillHexagons( CUT, centerx-274, centery-15, 230, 18, GHEXSIZE, 0 );
				else
					FillHexagons( CUT, 75, centery-6, 100, 18, GHEXSIZE, 0 );
			}
			if( plate == 1 )
			{
				FillHexagons( CUT, centerx-258, centery-100, 100, 18,GHEXSIZE, 0 );
			}
			if( plate == 2 )
			{
				if( !PSU_IS_ON_FRONT )
				{
					FillHexagons( CUT, centerx-182.5, 15.5, 240, 18, GHEXSIZE, 0 );
					FillHexagons( CUT, centerx-100, 64, 110, 75, GHEXSIZE, 0 );
				}
				else
				{
					FillHexagons( CUT, centerx-263.5, 20.5, 100, 18, GHEXSIZE, 0 );
					FillHexagons( CUT, centerx-84.5, 20.5, 100, 18, GHEXSIZE, 0 );
				}
			}


			#if PSU_IS_ON_FRONT
			if( plate == 2 )
			{
				float ox = 0;
				float oy = 9;
				DrawPSU( whole_crossbrace_height-0.5 + ox, mb_tray_length + sfx_psu_offset_y + oy, whole_crossbrace_height, mb_tray_length, sfx_psu_offset_y, 1, ox, oy );
			}
			#endif


			// Front plate.
			if( plate == 2 )
			{

				// Power button
				Circle( CUT, 157, 35, 16.1/2 );

				// Add USB Type C Mount TODO.
				float ucx = 157;
				float ucy = 57;
				cx = ucx-18.6/2;
				cy = ucy;
				Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );
				cx = ucx+18.6/2;
				cy = ucy;
				Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );

				// Aperture of 12mmx6mm
				const float uround_width = 8.6;
				const float uround_height = 5.6;
				const float uround_radius = 2;

				float phi = 0;
				PathStart( CUT );
				for( ; phi < 3.14159*2; phi += 0.001 )
				{
					float cx = cos( phi )*uround_radius;
					float cy = sin( phi )*uround_radius;
					if( cx < 0 )
						cx -= uround_width/2;
					else
						cx += uround_width/2;
					if( cy < 0 )
						cy -= uround_height/2;
					else
						cy += uround_height/2;
					PathL( cx + ucx, cy + ucy );
				}
				PathClose();


				int uq = 0;
				for( uq = 0; uq < 2; uq++ )
				{
					for( ucy = 70; ucy < 70+16; ucy += 10 )
					{
						ucx = 157;
						cx = ucx-21.5/2 - (uq*100);
						cy = ucy-(uq*18);
						Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );
						cx = ucx+21.5/2- (uq*100);
						cy = ucy-(uq*18);
						Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );
						cx =ucx - (uq*100);
						
						float revmargin = uq==0?.5:0;

						DrawBox( CUT, cx-15/2.0+revmargin, cy-8/2.0+revmargin, cx+15/2.0-revmargin, cy+8/2.0-revmargin, 0 );

					}
				}

				// Draw outline around extra USB spacer
				{
					PathStart( CUT );
					cx = 57;
					cy = 57;
					PathL( cx + -18, cy -14 );
					PathL( cx + 18, cy -14 );
					PathL( cx + 18, cy + 14 );
					PathL( cx + -18, cy + 14 );
					PathClose();
				}

				//FillHexagons( CUT, 74, 71, 115, 20, GHEXSIZE, 0 );
			}
			else if( plate == 1 )
			{
				//FillHexagons( CUT, 90, 71, 140, 20, GHEXSIZE, 0 );
			}
			else
			{
				// Back tray
				//FillHexagons( CUT, 75, 77, 115, 20, GHEXSIZE, 1 );
				//FillHexagons( CUT, 48, 71, 110, 24, GHEXSIZE, 1 );
			}

			PathStart( CUT );
			PathM( cx = 0, cy = 0 );

			if( BACKPLATE_GOES_UP && plate == 0 )
			{
				PathL( cx, cy );
				PathL( cx-=MATERIAL_THICKNESS, cy );
				frontplate_calc_mid_width = -cx;
				PathL( cx, cy += BACKPLATE_PARTIAL_TONGUE ); // Not
				PathL( cx+=MATERIAL_THICKNESS, cy );
				
				cy+=crossbrace_tongue_center/2-sidescrew_offset_y;
				InsertT( cx, cy, 1, 0, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy+=sidescrew_offset_y;
			}
			else
			{
				cy+=crossbrace_tongue_center/2-sidescrew_offset_y;
				InsertT( cx, cy, 1, 0, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy+=sidescrew_offset_y;
				cy += crossbrace_tongue_center/2-mb_tongue_mm/2;
				PathL( cx, cy );
				PathL( cx+EAR, cy+EAR );
				PathL( cx, cy );
				PathL( cx-=MATERIAL_THICKNESS, cy );
				PathL( cx, cy += mb_tongue_mm );
				PathL( cx+=MATERIAL_THICKNESS, cy );
			}

			float height_from_board_bottom;
			if( plate == 0 )
			{
				height_from_board_bottom = back_plate_height_from_tray;
			}
			else
			{
					// was sfx_height
				height_from_board_bottom = back_plate_height_from_tray;
			}
			
			//PathL( cx, cy = whole_crossbrace_height - height_from_board_bottom );
			

			
			// This has a large cutout for the GPU and the PSU and slots into the sides.
			{
				const float edge_card_offset_y = 7;
				const float edge_card_depth = 14;
				const float edge_card_bottom_bump = 6;
				const float edge_card_top_bump = 5;

				//PathStart( CUT );
				//cx = gpu_offset_x;
				//cy = material_above_gpu;
				//PathM( cx, cy );
				cy = gpu_thick-material_above_gpu+edge_card_offset_y;
				PathL( cx, cy );

				cx += gpu_height;
				PathL( cx, cy );
#if !BACKPLATE_DOES_NOT_GO_BEHIND_CPU
				if( plate == 0 )
				{
					cy += edge_card_offset_y-edge_card_top_bump;
					PathL( cx, cy );
					cx += edge_card_depth;
					PathL( cx, cy );
					cy += edge_card_offset_y-edge_card_bottom_bump + edge_card_top_bump;
					PathL( cx, cy );
					cx -= edge_card_depth;
					PathL( cx, cy );
					cy += edge_card_bottom_bump;
					PathL( cx, cy );
				}
				else
#endif
				{
					cy += edge_card_offset_y;
					PathL( cx, cy );
					cy += edge_card_offset_y;
					PathL( cx, cy );
				}
		
				//PathClose();

			}
//			else
//			{
				//DrawBox( CUT, gpu_offset_x, material_above_gpu, 
				//		  gpu_offset_x+gpu_height, material_above_gpu+gpu_thick, 0 );
	//		}

			PathL( cx, cy = whole_crossbrace_height - height_from_board_bottom );
			

			if( plate == 1 ) // Mid plate
			{
				InsertT( insert_brace_t_x+insert_brace_t_x_bp_offset, cy, 0, -1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cx = insert_brace_t_x+2;
				PathL( cx, cy );
				PathL( cx, cy-=68 );
				cx+=145;
				PathL( cx, cy );
				cx+=28;
				cy+=41;
				PathL( cx, cy );
				// Dont' draw material below tongue.
//				cy-=23;
//				cy-=8/.5;
//				cy-=16;
//				PathL( cx, cy+=68 );
			}
			else if( plate == 0 ) // Back plate
			{

				//cx += 136.5-right_justify;
				//PathL( cx, cy );
				InsertT( insert_brace_t_x+insert_brace_t_x_bp_offset, cy, 0, -1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cx = insert_brace_t_x+ 2;
				PathL( cx, cy );
				
				frontplate_calc_mid_width += cx;
#if !BACKPLATE_DOES_NOT_GO_BEHIND_CPU
				cy -= 31.0; //
				PathL( cx, cy );
				cx += 9.5+3.0;
				PathL( cx, cy );
				PathL( cx, cy-=22.5 );
				cx+=163;
				PathL( cx, cy );
				PathL( cx, cy+=10 );
#else



#endif

			}
			else
			{
				InsertT( insert_brace_t_x/*+insert_brace_t_x_bp_offset Not on last one */, cy, 0, -1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
			}

			if( plate == 0 && BACKPLATE_DOES_NOT_GO_BEHIND_CPU )
			{

				PathL( cx, cy );
				
				cy = crossbrace_tongue_center/2 - sidescrew_offset_y;
				cy += sidescrew_offset_y;
				cy = 0;
				PathL( cx, cy );

				float mcx = cx / 2;
				
				PathL( mcx+mb_tongue_mm/2.0, cy  );
				PathL( mcx+mb_tongue_mm/2.0, cy+MATERIAL_THICKNESS  );
				PathL( mcx+mb_tongue_mm/2.0+EAR, cy+MATERIAL_THICKNESS+EAR  );
				PathL( mcx+mb_tongue_mm/2.0, cy+MATERIAL_THICKNESS  );
				InsertT( mcx, cy+MATERIAL_THICKNESS, 0, 1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				PathL( mcx-mb_tongue_mm/2.0, cy+MATERIAL_THICKNESS  );
				PathL( mcx-mb_tongue_mm/2.0-EAR, cy+MATERIAL_THICKNESS+EAR  );
				PathL( mcx-mb_tongue_mm/2.0, cy+MATERIAL_THICKNESS  );
				PathL( mcx-mb_tongue_mm/2.0, cy );
			}
			else
			{
				PathL( cx = mb_tray_width, cy );

				PathL( cx, cy=crossbrace_tongue_center+mb_tongue_mm/2 );

				PathL( cx +=MATERIAL_THICKNESS, cy );
				PathL( cx, cy-=mb_tongue_mm );
				PathL( cx -=MATERIAL_THICKNESS, cy );
				PathL( cx-EAR, cy+EAR );
				PathL( cx, cy );
				
				cy = crossbrace_tongue_center/2 - sidescrew_offset_y;
				InsertT( cx, cy, -1, 0, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy += sidescrew_offset_y;
				cy = 0;
				PathL( cx, cy );

				cx = top_plate_front_panel_max_x-MATERIAL_THICKNESS;
				PathL( cx, cy );
				cy = MATERIAL_THICKNESS;
				PathL( cx, cy );
//				cx -= ((float)top_plate_front_panel_max_x - (float)top_plate_front_panel_min_x)/2;
//				InsertT( cx, cy, 0, 1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cx -= 10;
				InsertT( cx, cy, 0, 1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cx -= ((float)top_plate_front_panel_max_x - (float)top_plate_front_panel_min_x) - 20;
				InsertT( cx, cy, 0, 1, SCREW_WIDTH_T, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );

				cx = (float)top_plate_front_panel_min_x-MATERIAL_THICKNESS;
				PathL( cx, cy );
				cy = 0;
				PathL( cx, cy );
				
				if( YES_HANDLE )
				{
					if( plate != 1 )
					{
						float handle_hang = 0;
						cx-=handle_hang;
						PathL( cx, cy );
						cx-=handle_bump;
						cy-=handle_bump;
						PathL( cx, cy );
						cx-=mb_tray_width-handle_bump*2-handle_hang*2;
						PathL( cx, cy );
						cx-=handle_bump;
						cy+=handle_bump;
						PathL( cx, cy );
					}
				}
			}

			PathClose( );
		}
		
		
		// GPU Mounting Bar / Bracket
		int mb = 0;
		for( mb = 0; mb < 2; mb++ )
		{
			centerx = 590;
			centery = 72+mb*30;
			
			float support_material_outside_t = 7;
			float mounting_bar_thick = 12.5;
			float mounting_bar_extraA = 4.5;
			float mounting_bar_extraB = 0;
			
			// 11.5 and 32 from edge of GPU.
			float gpu_center_line = gpu_brace_bar_width/2;
			float gpu_edge = gpu_center_line - gpu_thick/2;
			//Circle( CUT, mounting_bar_thick/2, gpu_edge, SCREW_WIDTH/2 );
			if(mb == 0 )
			{
				Circle( CUT, -(gpu_edge+11.5),mounting_bar_thick/2, SCREW_IN_WIDTH/2 );
				Circle( CUT, -(gpu_edge+32  ),mounting_bar_thick/2, SCREW_IN_WIDTH/2 );
			}

			PathStart( CUT );
			cx = 0;
			cy = 0;
			PathM( -cy, cx );
			cy = gpu_brace_bar_width+support_material_outside_t;
			PathL( -cy, cx );
			cx += mounting_bar_thick;  // crossbar depth
			cx += mounting_bar_extraA*1; //(mb==0?0:1);
			PathL( -cy, cx );
			cy -= support_material_outside_t;
			//InsertT( -cy, cx, 0, -1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH+5, 2.5 );
			PathL( -cy, cx );			
			cx -= 1;
			PathL( -cy, cx );
			cx += 1;
			PathL( -cy, cx );
			
			
			cy -= 4.8;
			PathL( -cy, cx );
			cx -= mounting_bar_extraA*1; //*(mb==0?0:1);
			PathL( -cy, cx );
			cy -= gpu_brace_bar_width-4.8*2;
			PathL( -cy, cx );
			cx += mounting_bar_extraB;
			PathL( -cy, cx );
			cy -= 4.8;
			//InsertT( -cy, cx, 0, -1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH+5, 2.5 );
			PathL( -cy, cx );
			cx -= 1;
			PathL( -cy, cx );
			cx += 1;
			PathL( -cy, cx );

			cy -= support_material_outside_t;
			PathL( -cy, cx );
			cx -= mounting_bar_thick; // crossbar depth
			cx -= mounting_bar_extraB;
			PathL( -cy, cx );
			cx = 0;
			cy = 0;
			PathL( -cy, cx );
			PathClose();
		}

	}


	// The sides of the case.
	if( DO_CASE_3 )
	{
		int side;
		for( side = 0; side < 2; side++ )
		{
			//if( side == 1 || side == 0 )
			{
				printf( "<g transform=\"rotate(90)\">" );
			}
			float cx = 0;
			float cy = 0;
			centerx = (side==0)?316:316;//+side*(whole_crossbrace_height+25)+300;
			centery = (side==0)?-1040:-318;

			Circle( CUT, whole_crossbrace_height+MATERIAL_THICKNESS/2, (mb_tongue_mm+mb_tongue_spacing)*4/4, SCREW_WIDTH/2 );
			Circle( CUT, whole_crossbrace_height+MATERIAL_THICKNESS/2, (mb_tongue_mm+mb_tongue_spacing)*8/4, SCREW_WIDTH/2 );
			
			for( i = 0; i < num_mb_tongues; i++ )
			{
				float ts = (mb_tray_length) / num_mb_tongues;
				cy = (ts/2) + ts * i;
				cx = whole_crossbrace_height;
				float matplusclear = MATERIAL_THICKNESS/2 + CUT_CLEARANCE_TONGUE;
				float twplusclear = mb_tongue_mm/2 + CUT_CLEARANCE_TONGUE;
				DrawBox( CUT, cx, cy-twplusclear, cx+matplusclear*2, cy+twplusclear, EAR );
			}

			// Change to 4 for alternate slotting patterns.
			for( i = 0; i < 3; i++ )
			{
				if( i == 2 && nomiddleplate ) continue;
				const char * material = CUT;
				float yplace = 0;
				switch( i )
				{
					case 0: yplace = top_tongue_offset; break;
					case 1: yplace = bottom_tongue_offset; break;
					case 3: yplace = hole_center_plate_for_moboy; break; // Not used now.
					case 2: yplace = middle_bracket_offset; break;
				}
				float matplusclear = tongue_offset;//MATERIAL_THICKNESS/2 + CUT_CLEARANCE_TONGUE;
				float twplusclear = mb_tongue_mm/2 + CUT_CLEARANCE_TONGUE;
				cx = whole_crossbrace_height/2+crossbrace_tongue_offset_y;
				cy = yplace;

				if( BACKPLATE_GOES_UP && i == 0 )
				{
					if( side == 1 || !BACKPLATE_DOES_NOT_GO_BEHIND_CPU)
					{
						//crossbrace_tongue_center/2-sidescrew_offset_y; 
						//DrawBox( material, cx-twplusclear, cy-matplusclear, cx+0, cy+matplusclear, EAR );
						Circle( material, crossbrace_tongue_center/2 -sidescrew_offset_y + BACKPLATE_PARTIAL_TONGUE, cy, SCREW_WIDTH/2 );
					}
				}
				else
				{
					if( BACKPLATE_GOES_UP && i == 0 && side == 1 )
					{
						// Nudge screw down a tad on the right side.
						Circle( material, crossbrace_tongue_center/2 , cy, SCREW_WIDTH/2 );
					}
					else
					{
						Circle( material, crossbrace_tongue_center/2 -sidescrew_offset_y, cy, SCREW_WIDTH/2 );
						DrawBox( material, cx-twplusclear, cy-matplusclear, cx+twplusclear, cy+matplusclear, EAR );
					}
				}
			}
			
			if( side == 0 )
			{
				if( !PSU_IS_ON_FRONT )
				{
					DrawPSU( whole_crossbrace_height-0.5, mb_tray_length + sfx_psu_offset_y, whole_crossbrace_height, mb_tray_length, sfx_psu_offset_y, 0, 0, 0 );
				}
			}
			
			if( side == 1 )
			{
				FillHexagons( CUT, (whole_crossbrace_height)/2.0-4+14, (top_tongue_offset+(top_tongue_offset + bottom_tongue_offset)/2)/2+8, 70, 150, GHEXSIZE, 0 );
				FillHexagons( CUT, (whole_crossbrace_height)/2.0+3, (hole_center_plate_for_moboy+bottom_tongue_offset)/2-2+14, 70, 90, GHEXSIZE, 1 );
			}
			else
			{
				FillHexagons( CUT, (whole_crossbrace_height)/2.0-4+14, (top_tongue_offset+(top_tongue_offset + bottom_tongue_offset)/2)/2+6, 70, 150, GHEXSIZE, 0 );
				FillHexagons( CUT,
					(whole_crossbrace_height)/2.0-4+4.8+(PSU_IS_ON_FRONT?-9.5:0),
					(top_tongue_offset+(top_tongue_offset + bottom_tongue_offset)/2)/2+86+(PSU_IS_ON_FRONT?17.5:0),
					PSU_IS_ON_FRONT?60:50, PSU_IS_ON_FRONT?100:40, GHEXSIZE, 1 );
				if( PSU_IS_ON_FRONT )
				{
					FillHexagons( CUT, (whole_crossbrace_height)/2.0-4+4.5, +267, 70, 80, GHEXSIZE, 1 );
				}
			}
			//FillHexagons( CUT, (whole_crossbrace_height)/2.0-4, 177-1, 30, 30, GHEXSIZE, 0 );
			
			cx = 0;
			cy = 0;
			//whole_crossbrace_height
			PathStart( CUT );


			if( BACKPLATE_GOES_UP && side == 1 )
			{
				cx = MATERIAL_THICKNESS;
				cy = tongue_offset + MATERIAL_THICKNESS;
				PathM( cx, cy );
				cx = BACKPLATE_PARTIAL_TONGUE;
				PathL( cx, cy );
				cy -= MATERIAL_THICKNESS;
				PathL( cx, cy );
				cx = 0;//BACKPLATE_PARTIAL_TONGUE;
				PathL( cx, cy );
				cy = 0;
				PathL( cx, cy );
			}
			else
			{
				PathM( cx, cy );
			}
		
			cx=whole_crossbrace_height + MATERIAL_THICKNESS;
			PathL( cx, cy );
			cy += mb_tongue_spacing/2;
			cy += foot_height/2;
			for( i = 0; i < num_mb_tongues; i++ )
			{
				//mb_tongue_mm
				//mb_tongue_spacing
				// const float foot_height = 20;
				// const float foot_length = 30;
				cy -= foot_height*1.5;
				PathL( cx, cy );
				cx += foot_height;
				cy += foot_height;
				PathL( cx, cy );
				cy += mb_tongue_mm;
				PathL( cx, cy );
				cx -= foot_height;
				cy += foot_height;
				PathL( cx, cy );
				cy -= foot_height/2;
				
				cy += mb_tongue_spacing;
			}
			cy -= foot_height/2;
			cy -= mb_tongue_spacing/2;
			PathL( cx, cy );
			cx=0;

			PathL( cx, cy );
			
			#if defined( FRONTPLATE_BASEWIDTH ) && ( !defined( nomiddleplate ) || !nomiddleplate )
			#error Cant have a crossbrace with a middle plate
			#endif
			//if( side == 0 )


			{
				cy -= FRONTPLATE_OFFSET;
				front_plate_top_plate_extend_y = FRONTPLATE_OFFSET  - (tongue_offset);
				//matplusclear = MATERIAL_THICKNESS/2 + CUT_CLEARANCE_TONGUE
				// But instead let's pretend it's tongue_offset
				PathL( cx, cy );
				cx += MATERIAL_THICKNESS;
				PathL( cx, cy );
				PathL( cx+EAR, cy+EAR );
				PathL( cx, cy );

				cy -= crossbrace_panel_screw_offset;
				InsertT( cx, cy, 1, 0, -SCREW_WIDTH_T, -NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy += crossbrace_panel_screw_offset;

				if( side == 1 )
				{
					// Power for GPU
					float savecy = cy;
					float savecx = cx;
					cy -= 22;
					PathL( cx, cy );
					cx += gpu_thick + 4; // How far down to cut
					PathL( cx, cy );
					cy -= 43;
					PathL( cx, cy );
					cx -= 35;
					PathL( cx, cy );
					cy += 22;
					PathL( cx, cy );
					cx = savecx;
					PathL( cx, cy );
					cy = savecy;
				}
				
				cy -= FRONTPLATE_BASEWIDTH - crossbrace_panel_screw_offset;
				InsertT( cx, cy, 1, 0, -SCREW_WIDTH_T, -NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );

				if( BACKPLATE_GOES_UP && side == 1 )
				{
					float mcx = cy - TOP_PLATE_BACK_SCREW_OFFSET/2.0;
					
					PathL( cx, mcx + mb_tongue_mm/2.0  );
					PathL( cx+EAR, mcx + mb_tongue_mm/2.0-EAR );
					PathL( cx, mcx + mb_tongue_mm/2.0  );
					PathL( cx-MATERIAL_THICKNESS, mcx + mb_tongue_mm/2.0 );
					PathL( cx-MATERIAL_THICKNESS, mcx - mb_tongue_mm/2.0 );
					PathL( cx, mcx - mb_tongue_mm/2.0  );
					PathL( cx+EAR, mcx - mb_tongue_mm/2.0+EAR );
					PathL( cx, mcx - mb_tongue_mm/2.0  );

					cy -= TOP_PLATE_BACK_SCREW_OFFSET;

					InsertT( cx, cy, 1, 0, -SCREW_WIDTH_T, -NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
					cy -= crossbrace_panel_screw_offset;
				}
				else
				{
					cy -= crossbrace_panel_screw_offset;
					PathL( cx, cy );
					PathL( cx+EAR, cy-EAR );
					PathL( cx, cy );
					cx -= MATERIAL_THICKNESS;
				}
				PathL( cx, cy );
			}
			
			PathClose();
			
			//if( side == 1 )
			{
				printf( "</g>" );
			}

		}
	}


	if( nomiddleplate ) // face plate
	{
		centerx = 337.7;
		centery = 150;
		
		float correction_from_incorrect_values_above = tongue_offset - MATERIAL_THICKNESS/2;
		float back_of_plate_y = -face_plate_height+FRONTPLATE_BASEWIDTH+front_plate_top_plate_extend_y + MATERIAL_THICKNESS*2 + tongue_offset*2 + correction_from_incorrect_values_above*2;
		float front_of_plate_y = front_plate_top_plate_extend_y+FRONTPLATE_BASEWIDTH - correction_from_incorrect_values_above*0;
		
		//Signature
		float lateral_width = mb_tray_length  + MATERIAL_THICKNESS*1.5;

#if 0
		printf( "<g transform=\"translate(182,305)\">" );
		printf( "<g transform=\"rotate(-45)\">" );
		PathStart( ETCH );
		cx =-10;

		cy =-10;
		float tx, ty;
		float ixsx = .2;
		float ixsy = .2;
		float ixsx2 = .355;
		float ixsx21 = .28;
		tx = cx - 20*ixsx21; ty = cy;  PathM( tx, ty );
		tx = cx - 10*ixsx2; ty = cy - 10*ixsy;  PathL( tx, ty );
		tx = cx; ty = cy - 10*ixsy;  PathL( tx, ty );
		tx = cx + 20*ixsx; ty = cy + 10*ixsy;  PathL( tx, ty );
		tx = cx + 20*ixsx; ty = cy - 10*ixsy;  PathL( tx, ty );
		tx = cx; ty = cy + 10*ixsy;  PathL( tx, ty );
		tx = cx - 10*ixsx2; ty = cy + 10*ixsy;  PathL( tx, ty );
		tx = cx - 20*ixsx21; ty = cy;  PathL( tx, ty );

		PathClose();
		printf( "</g>" );
		printf( "</g>" );
#else
		int logo[15] = {
			1, 0, 1, 1, 0,
			0, 1, 0, 0, 1,
			1, 0, 1, 1, 0 };
		int lx, ly;
		float ss = 12.54; // Overall size, per
		float ssa = 2.27; // Edge size
		float ssb = 4.0; // Square size.
		float edgesqueeze = 0.0;
		float sig_offset_x = -3;
		for( ly = 0; ly < 3; ly++ )
		{
			float ssplace = -ss*2.5;
			for( lx = 0; lx < 5; lx++ )
			{
				float usessplace = ssplace;
				float oldsignx = 0;
				float oldsigny = 0;

				ssplace += ss;//(lx == 0 || lx == 2 || lx == 3 ) ? (ss-edgesqueeze) : ss;
				if( logo[lx+ly*5] == 0 ) continue;
				float tx =    lateral_width/2.0 + usessplace  +sig_offset_x;
				float ty = FRONTPLATE_BASEWIDTH/2.0 + (ly-1) * (ss-edgesqueeze);
				
				PathStart( ETCH );
				float theta;
				float lastdx = 0;
				float lastdy = 0;
				for( theta = 0; theta < 3.141592*2; theta += 3.14159/12 )
				{
					float dx = sin( theta ) * ssa;
					float dy = cos( theta ) * ssa;
					if( ( NZSIGN( dx ) != oldsignx || NZSIGN( dy ) != oldsigny )  && oldsignx != 0 && oldsigny != 0 )
					{
						//fprintf( stderr, "%f %f  %f %f\n", oldsignx, oldsigny, NZSIGN( dx ), NZSIGN( dy ) );
						PathL( lastdx + NZSIGN( dx ) * ssb + tx, lastdy + NZSIGN( dy ) * ssb + ty );
					}
					lastdx = dx;
					lastdy = dy;
					oldsignx = NZSIGN( dx );
					oldsigny = NZSIGN( dy );
					dx += NZSIGN( dx ) * ssb;
					dy += NZSIGN( dy ) * ssb;
					PathL( dx + tx, dy + ty );
				}
				PathClose();
			}
		}

		// Interconnection
		int mirror;
		for( mirror = 0; mirror < 2; mirror++ )
		{
			float fm = mirror ? -1 : 1;

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss* -2, FRONTPLATE_BASEWIDTH/2.0 + ss*fm*0.5 - fm * ssa );
			PathL( sig_offset_x+lateral_width/2.0 + ss* -2, FRONTPLATE_BASEWIDTH/2.0 + ss*fm*0.5 + fm * ssa );
			PathStop();

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss* -2 + ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathL( sig_offset_x+lateral_width/2.0 + ss* -2 - ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathStop();


			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss* 1, FRONTPLATE_BASEWIDTH/2.0 +ss*fm*0.5 - fm * ssa );
			PathL( sig_offset_x+lateral_width/2.0 + ss* 1, FRONTPLATE_BASEWIDTH/2.0 +ss*fm*0.5 + fm * ssa );
			PathStop();

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss* 1 - ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathL( sig_offset_x+lateral_width/2.0 + ss* 1 + ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathStop();

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss*-1, FRONTPLATE_BASEWIDTH/2.0 +ss*fm*0.5 - fm * ssa );
			PathL( sig_offset_x+lateral_width/2.0 + ss*-1, FRONTPLATE_BASEWIDTH/2.0 +ss*fm*0.5 + fm * ssa );
			PathStop();

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss*-1 - ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathL( sig_offset_x+lateral_width/2.0 + ss*-1 + ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathStop();

			PathStart( ETCH );
			PathL( sig_offset_x+lateral_width/2.0 + ss*0 - ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathL( sig_offset_x+lateral_width/2.0 + ss*0 + ssa, FRONTPLATE_BASEWIDTH/2.0 +ss/2*fm );
			PathStop();

		}

#endif


		centerx -= MATERIAL_THICKNESS;
		
		float screwycenter = ((crossbrace_panel_screw_offset - TOP_PLATE_BACK_SCREW_OFFSET) + crossbrace_panel_screw_offset)/2.0;
		Circle( CUT, MATERIAL_THICKNESS/2, crossbrace_panel_screw_offset - TOP_PLATE_BACK_SCREW_OFFSET, SCREW_WIDTH/2 );
		Circle( CUT, MATERIAL_THICKNESS/2, crossbrace_panel_screw_offset, SCREW_WIDTH/2 );
		Circle( CUT, MATERIAL_THICKNESS/2, FRONTPLATE_BASEWIDTH-crossbrace_panel_screw_offset, SCREW_WIDTH/2 );
		
		Circle( CUT, lateral_width-MATERIAL_THICKNESS*.5, FRONTPLATE_BASEWIDTH-crossbrace_panel_screw_offset, SCREW_WIDTH/2 );
		Circle( CUT, lateral_width-MATERIAL_THICKNESS*.5, crossbrace_panel_screw_offset, SCREW_WIDTH/2 );

		// BAck plate hole.
		Circle( CUT, frontplate_calc_mid_width/2 + MATERIAL_THICKNESS/2, back_of_plate_y- MATERIAL_THICKNESS/2, SCREW_WIDTH/2 );

		// Hole to front plate.
		Circle( CUT, top_plate_front_panel_min_x + 10, front_of_plate_y-MATERIAL_THICKNESS/2, SCREW_WIDTH/2 );
		Circle( CUT, top_plate_front_panel_max_x - 10, front_of_plate_y-MATERIAL_THICKNESS/2, SCREW_WIDTH/2 );
				
		PathStart( CUT );
		PathM( cx = frontplate_calc_mid_width, cy = 0 );
		cx = lateral_width;
		PathL( cx, cy );
		cy += FRONTPLATE_BASEWIDTH;
		PathL( cx, cy );			
		cx -= lateral_width;
		//PathL( cx, cy );	
		float ocy = cy;
		
		cx = top_plate_front_panel_max_x; // Where the top plate fits into the front panel.
		PathL( cx, cy );	
		cy = front_of_plate_y;
		PathL( cx, cy );	
		cx = top_plate_front_panel_min_x;
		PathL( cx, cy );	
		cy = ocy;
		PathL( cx, cy );	


		cx = 0;
		PathL( cx, cy );
		
		PathL( cx, screwycenter + mb_tongue_mm/2.0 );
		PathL( cx+MATERIAL_THICKNESS, screwycenter + mb_tongue_mm/2.0 );
		PathL( cx+MATERIAL_THICKNESS+EAR, screwycenter + mb_tongue_mm/2.0+EAR );
		PathL( cx+MATERIAL_THICKNESS, screwycenter + mb_tongue_mm/2.0 );
		PathL( cx+MATERIAL_THICKNESS, screwycenter - mb_tongue_mm/2.0 );
		PathL( cx+MATERIAL_THICKNESS+EAR, screwycenter - mb_tongue_mm/2.0-EAR );
		PathL( cx+MATERIAL_THICKNESS, screwycenter - mb_tongue_mm/2.0 );

		PathL( cx, screwycenter - mb_tongue_mm/2.0 );
		
		//cy += face_plate_height- MATERIAL_THICKNESS/2;
		cy = back_of_plate_y;
		//tongue_offset
		
		PathL( cx, cy );
		
		float mcx = frontplate_calc_mid_width/2 + MATERIAL_THICKNESS/2;
		PathL( mcx- mb_tongue_mm/2.0, cy  );
		PathL( mcx- mb_tongue_mm/2.0+EAR, cy+EAR  );
		PathL( mcx- mb_tongue_mm/2.0, cy  );
		PathL( mcx- mb_tongue_mm/2.0, cy -MATERIAL_THICKNESS );
		PathL( mcx+ mb_tongue_mm/2.0, cy -MATERIAL_THICKNESS );
		PathL( mcx+ mb_tongue_mm/2.0, cy  );
		PathL( mcx+ mb_tongue_mm/2.0-EAR, cy+EAR  );
		PathL( mcx+ mb_tongue_mm/2.0, cy  );

		cx = frontplate_calc_mid_width;
		PathL( cx, cy );

		PathClose();
	}			


	EndSVG();	
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
		float oy = y * 6.95;
		float yo = 4.40;//4.2 + y * .1;
		DrawBox( CUT, 140, y+oy+55, 144, y+oy+55+yo, 0 );
	}
	PathStart( CUT );
	PathM( 155, 0 );
	PathL( 155, 330 );
	PathClose();
		
	EndSVG();
}
