//XXX TODO: 
//  Measure riser height, for wher RTX3090 will live.
//    Change gpu_base_over_mobo_plate = 47; // *****
// Make sure the x/y location of the GPU makes sense with the riser.
// Figure out how high the gap in the back must go.

// TODO: add access window for SSD on back of case.
//    Rectangle, centered 31mm from side, 90mm from back. 30mm wide 95mm long.

// Make sure the Mobo will fit --> 6.75mm center of holes to right side of case, don't change anything there.

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
#define TOOTH_WIDTH 30
#define EAR 0.5
#define M3_SCREW_WIDTH 2.7
#define SCREW_WIDTH 3.5
#define SCREW_IN_WIDTH 3.1
#define SCREW_EXTRA 3.0
#define NUT_WIDTH   8.0
#define NUT_HEIGHT   2.6
#define T_DEPTH     5.2

// apply to both sides of inside cuts.
#define CUT_CLEARANCE -.1

#define DO_CASE_1 1
#define DO_CASE_2 1
#define DO_CASE_3 1

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
	PathLXForm( cx, cy, -(screw_width/2), tdepth+nut_height, dirx, diry  );
	PathLXForm( cx, cy, -(screw_width/2), tdepth+nut_height+screw_extra, dirx, diry  );
	PathLXForm( cx, cy, +(screw_width/2), tdepth+nut_height+screw_extra, dirx, diry  );
	PathLXForm( cx, cy, +(screw_width/2), tdepth+nut_height, dirx, diry  );
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
	
	const float right_justify = 2.5;
	const float mb_tongue_mm = 40;
	const float mb_tray_length = 314;
	const float itx_x_offset = 143-4 - right_justify;
	const float itx_y_offset = 4.0;
	const float mb_tray_width = 314-2 - right_justify;  // was 172
	const int num_mb_tongues = 3;
	const float bottom_tongue_offset = mb_tray_length-MATERIAL_THICKNESS/2-5;
	const float top_tongue_offset = MATERIAL_THICKNESS/2+5;
	const float middle_tongue_offset = 24;
	const int num_leds_edge = 36;
	const float led_mb_center_x = itx_x_offset+18;
	const float led_mb_center_y = 155;
	const float led_spacing = 6.95;
	const float led_width = 4.1;
	const float led_nooj = 135;
	const float led_noojy = 10;
	
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
	const float middle_bracket_offset = (top_tongue_offset + bottom_tongue_offset + middle_tongue_offset)/2;
	
	const float back_valence_width = 12.3;
	const float back_valence_depth = 35;
	
	const float sfx_slide_offset = 5.25;
	
	// Note GPU cutout does not contain compensation.
	const float gpu_thick = 54;     //XXX TODO: Add padding around GPU?
	const float gpu_height = 123.5;
	const float material_above_gpu = 30;
	const float gpu_offset_x = 2.6-right_justify; // Was 18
	const float gpu_rail_mount_from_top = 30.4;
	const float gpu_brace_bar_width = 64;
	
	const float gpu_base_over_mobo_plate = 47; // Measured
	float whole_crossbrace_height = 9+gpu_thick + 85-64;
	float sidescrew_offset_y = 10;
	float mb_tongue_spacing = (mb_tray_length - (num_mb_tongues*mb_tongue_mm)) / num_mb_tongues;

	float insert_brace_t_x = sfx_length+sfx_slop*2+mb_tongue_mm-6.5-right_justify;
	float insert_brace_t_x_bp_offset = -2;
	// For GPU holder
	float backplate_mount_lateral = gpu_height + gpu_offset_x - gpu_rail_mount_from_top - MATERIAL_THICKNESS/2 - 80;
				

	StartSVG( 809.6, 457 );
	
	if( DO_CASE_1 )
	{
		
		//MOTHERBOARD 
		
		// PSU
		DrawBox( ETCH, sfx_slop + sfx_side_offset, 
			mb_tray_length - sfx_slop - sfx_width - MATERIAL_THICKNESS - sfx_slide_offset, 
			sfx_slop + sfx_length + sfx_side_offset,
			mb_tray_length - sfx_slop - MATERIAL_THICKNESS - sfx_slide_offset, 0 );

		// https://www.silverstonetek.com/techtalk/11008/pic-9.png
		Circle( CUT, itx_x_offset+6.35, itx_y_offset+10.16, M3_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35+157.48, itx_y_offset+10.16+22.86, M3_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35+157.48, itx_y_offset+10.16+154.94, M3_SCREW_WIDTH/2 );
		Circle( CUT, itx_x_offset+6.35, itx_y_offset+10.16+154.94, M3_SCREW_WIDTH/2 );

		Circle( CUT, insert_brace_t_x, bottom_tongue_offset, SCREW_WIDTH/2 );
		Circle( CUT, insert_brace_t_x + insert_brace_t_x_bp_offset, middle_bracket_offset, SCREW_WIDTH/2 );
		Circle( CUT, insert_brace_t_x + insert_brace_t_x_bp_offset, top_tongue_offset, SCREW_WIDTH/2 );



		FillHexagons( CUT, 84+itx_x_offset-66, 100, 220, 160, 9, 1 );
		FillHexagons( CUT, 84+itx_x_offset-94, 232, 160, 130, 9, 0 );
		//Row between mobo and psu
		//FillHexagons( CUT, 95, 174, 125, 20 );
		
		// Add LEDs
		int j;
		for( j = 0; j < 4; j++ )
		for( i = 0; i < num_leds_edge; i++ )
		{
			float leda = i * led_spacing;
			float ledb = leda + led_width;
			float led_line_width = (num_leds_edge-1) * led_spacing + led_width;
			float led_extra_bottom = 4;
			if( ( j == 2 && i < 12 ) || ( j == 1 && i >= 18 ) ) continue;
			switch( j )
			{
			case 0:
				DrawBox( CUT, led_mb_center_x-led_line_width/2+leda, led_mb_center_y-led_width/2-led_nooj, 
							  led_mb_center_x-led_line_width/2+ledb, led_mb_center_y+led_width/2-led_nooj, 0 );
				break;
			case 1:
				DrawBox( CUT, led_mb_center_x+led_line_width/2-led_width/2+led_noojy, led_mb_center_y-led_line_width/2+leda+(led_spacing-led_width)/2, 
							  led_mb_center_x+led_line_width/2+led_width/2+led_noojy, led_mb_center_y-led_line_width/2+ledb+(led_spacing-led_width)/2, 0 );
				break;
			case 2:
				DrawBox( CUT, led_mb_center_x+led_line_width/2-leda, led_extra_bottom+led_mb_center_y-led_width/2+led_nooj, 
							  led_mb_center_x+led_line_width/2-ledb, led_extra_bottom+led_mb_center_y+led_width/2+led_nooj, 0 );
				break;
			case 3:
				DrawBox( CUT, led_mb_center_x-led_line_width/2-led_width/2-led_noojy, led_mb_center_y+led_line_width/2-leda+(led_spacing-led_width)/2, 
							  led_mb_center_x-led_line_width/2+led_width/2-led_noojy, led_mb_center_y+led_line_width/2-ledb+(led_spacing-led_width)/2, 0 );
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
				InsertT( cx, cy, 1, 0, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
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
				InsertT( cx, cy, -1, 0, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cy -= mb_tongue_spacing/2;
			}
			else
				cy -= mb_tongue_spacing/2;
			PathL( cx, cy );
		}

				InsertT( backplate_mount_lateral, cy, 0, 1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
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
			}
			else if( plate == 1 )
			{
				centerx = mb_tray_width+MATERIAL_THICKNESS*3+.5+1;
				centery = 115;
			}
			else
			{
				centerx = mb_tray_width+MATERIAL_THICKNESS*3+.5+1;
				centery = 230;
			}
			
			const float handle_bump = 29;
			const float handle_width = 56;
			const float handle_radius = 11;
			const float handle_offset = 1;
			// Handle
			if( plate != 1 )
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
			
			// This has a large cutout for the GPU and the PSU and slots into the sides.
			if( plate == 0 )
			{
				const float edge_card_offset_y = 7;
				const float edge_card_depth = 13;
				const float edge_card_bottom_bump = 1;
				PathStart( CUT );
				cx = gpu_offset_x;
				cy = material_above_gpu;
				PathM( cx, cy );
				cy += gpu_thick;
				PathL( cx, cy );
				cx += gpu_height;
				PathL( cx, cy );

				cy -= gpu_thick-edge_card_offset_y;
				PathL( cx, cy );
				cx += edge_card_depth;
				PathL( cx, cy );
				cy -= edge_card_offset_y-edge_card_bottom_bump;
				PathL( cx, cy );
				cx -= edge_card_depth;
				PathL( cx, cy );
				cy -= edge_card_bottom_bump;
				PathL( cx, cy );
		
				PathClose();
				
				// material_above_gpu and gpu_thick
				float gpu_center_line = material_above_gpu+gpu_thick/2;

				Circle( CUT, backplate_mount_lateral, gpu_center_line-gpu_brace_bar_width/2, SCREW_WIDTH/2 );
				//Circle( CUT, backplate_mount_lateral, gpu_center_line+gpu_brace_bar_width/2, SCREW_WIDTH/2 );
			}
			else
			{
				DrawBox( CUT, gpu_offset_x, material_above_gpu, 
						  gpu_offset_x+gpu_height, material_above_gpu+gpu_thick, 0 );
			}

			if( plate == 2 )
			{

				Circle( CUT, 185, 50, 25/2 );

				// Add USB Mount
				float ucx = 145;
				float ucy = 65;
				cx = ucx-7.5;
				cy = ucy;
				Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );
				cx = ucx+7.5;
				cy = ucy;
				Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );


				const float uround_width = 6;
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
					PathL( cx + ucx, cy + ucy );
				}
				PathClose();



				for( ucy = 30; ucy < 45; ucy += 14 )
				{
					ucx = 145;
					cx = ucx-15;
					cy = ucy;
					Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );
					cx = ucx+15;
					cy = ucy;
					Circle( CUT, cx, cy, M3_SCREW_WIDTH/2 );


					const float uround3_width = 10;
					const float uround3_radius = 5;

					phi = 0;
					PathStart( CUT );
					for( ; phi < 3.14159*2; phi += 0.001 )
					{
						float cx = cos( phi )*uround3_radius;
						float cy = sin( phi )*uround3_radius;
						if( cx < 0 )
							cx -= uround3_width/2;
						else
							cx += uround3_width/2;
						PathL( cx + ucx, cy + ucy );
					}
					PathClose();
				}



				printf( "<g transform=\"translate(110,380)\">" );
				printf( "<g transform=\"rotate(-45)\">" );

				//Signature
				PathStart( ETCH );
				cx = 0;
				cy = 0;
				float tx, ty;
				float ixsx = .3;
				float ixsy = .25;
				tx = cx - 20*ixsx; ty = cy;  PathM( tx, ty );
				tx = cx - 10*ixsx; ty = cy - 10*ixsy;  PathL( tx, ty );
				tx = cx; ty = cy - 10*ixsy;  PathL( tx, ty );
				tx = cx + 20*ixsx; ty = cy + 10*ixsy;  PathL( tx, ty );
				tx = cx + 20*ixsx; ty = cy - 10*ixsy;  PathL( tx, ty );
				tx = cx; ty = cy + 10*ixsy;  PathL( tx, ty );
				tx = cx - 10*ixsx; ty = cy + 10*ixsy;  PathL( tx, ty );
				tx = cx - 20*ixsx; ty = cy;  PathL( tx, ty );
				PathClose();
				printf( "</g>" );
				printf( "</g>" );

				//FillHexagons( CUT, 74, 71, 115, 20, 8, 0 );
			}
			else if( plate == 1 )
			{
				//FillHexagons( CUT, 90, 71, 140, 20, 8, 0 );
			}
			else
			{
				// Back tray
				//FillHexagons( CUT, 75, 77, 115, 20, 8, 1 );
				//FillHexagons( CUT, 48, 71, 110, 24, 12, 1 );
			}

			PathStart( CUT );
			float crossbrace_tongue_center = whole_crossbrace_height/2+crossbrace_tongue_offset_y;
			PathM( cx = 0, cy = 0 );
			cy+=crossbrace_tongue_center/2-sidescrew_offset_y;
			InsertT( cx, cy, 1, 0, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
			cy+=sidescrew_offset_y;
			cy += crossbrace_tongue_center/2-mb_tongue_mm/2;
			PathL( cx, cy );
			PathL( cx+EAR, cy+EAR );
			PathL( cx, cy );
			PathL( cx-=MATERIAL_THICKNESS, cy );
			PathL( cx, cy += mb_tongue_mm );
			PathL( cx+=MATERIAL_THICKNESS, cy );
			
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
			
			PathL( cx, cy = whole_crossbrace_height - height_from_board_bottom );


			if( plate == 1 ) // Mid plate
			{
				InsertT( insert_brace_t_x+insert_brace_t_x_bp_offset, cy, 0, -1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				cx += 139-right_justify;
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
				InsertT( insert_brace_t_x+insert_brace_t_x_bp_offset, cy, 0, -1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
				PathL( cx, cy );
				cx += 139.0-right_justify;
				PathL( cx, cy );
				cy -= 20.0;
				PathL( cx, cy );
				cx += 10.5;
				PathL( cx, cy );
				PathL( cx, cy-=37 );
				cx+=162.5;
				PathL( cx, cy );
				PathL( cx, cy+=10 );
			}
			else
			{
				InsertT( insert_brace_t_x, cy, 0, -1, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
			}
			
			PathL( cx = mb_tray_width, cy );


			PathL( cx, cy=crossbrace_tongue_center+mb_tongue_mm/2 );

			PathL( cx +=MATERIAL_THICKNESS, cy );
			PathL( cx, cy-=mb_tongue_mm );
			PathL( cx -=MATERIAL_THICKNESS, cy );
			PathL( cx-EAR, cy+EAR );
			PathL( cx, cy );
			
			cy = crossbrace_tongue_center/2 - sidescrew_offset_y;
			InsertT( cx, cy, -1, 0, SCREW_WIDTH, NUT_WIDTH, NUT_HEIGHT, T_DEPTH, SCREW_EXTRA );
			cy += sidescrew_offset_y;
			cy = 0;
			PathL( cx, cy );
			
			if( plate != 1 )
			{
				//Add handle.
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
			
			PathClose( );
		}
		
		
		// GPU Mounting Bar
		{
			centerx = 590;
			centery = 160;
			
			float support_material_outside_t = 7;
			float mounting_bar_thick = 12.5;
			float mounting_bar_extra = 6.7;
			
			// 11.5 and 32 from edge of GPU.
			float gpu_center_line = gpu_brace_bar_width/2;
			float gpu_edge = gpu_center_line - gpu_thick/2;
			//Circle( CUT, mounting_bar_thick/2, gpu_edge, SCREW_WIDTH/2 );
			Circle( CUT, -(gpu_edge+11.5),mounting_bar_thick/2, SCREW_IN_WIDTH/2 );
			Circle( CUT, -(gpu_edge+32  ),mounting_bar_thick/2, SCREW_IN_WIDTH/2 );

			PathStart( CUT );
			cx = 0;
			cy = 0;
			PathM( -cy, cx );
			cy = gpu_brace_bar_width+support_material_outside_t;
			PathL( -cy, cx );
			cx += mounting_bar_thick;  // crossbar depth
			cx += mounting_bar_extra;
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
			cx -= mounting_bar_extra;
			PathL( -cy, cx );
			cy -= gpu_brace_bar_width-4.8*2;
			PathL( -cy, cx );
			cx += mounting_bar_extra;
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
			cx -= mounting_bar_extra;
			PathL( -cy, cx );
			cx = 0;
			cy = 0;
			PathL( -cy, cx );
			PathClose();
		}

	}
	
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
			centery = (side==0)?-640:-318;

			Circle( CUT, whole_crossbrace_height+MATERIAL_THICKNESS/2, (mb_tongue_mm+mb_tongue_spacing)*4/4, SCREW_WIDTH/2 );
			Circle( CUT, whole_crossbrace_height+MATERIAL_THICKNESS/2, (mb_tongue_mm+mb_tongue_spacing)*8/4, SCREW_WIDTH/2 );
			
			for( i = 0; i < num_mb_tongues; i++ )
			{
				float ts = (mb_tray_length) / num_mb_tongues;
				cy = (ts/2) + ts * i;
				cx = whole_crossbrace_height;
				float matplusclear = MATERIAL_THICKNESS/2 + CUT_CLEARANCE;
				float twplusclear = mb_tongue_mm/2 + CUT_CLEARANCE;
				DrawBox( CUT, cx, cy-twplusclear, cx+matplusclear*2, cy+twplusclear, EAR );
			}

			// Change to 4 for alternate slotting patterns.
			for( i = 0; i < 3; i++ )
			{
				float yplace = 0;
				switch( i )
				{
					case 0: yplace = top_tongue_offset; break;
					case 1: yplace = bottom_tongue_offset; break;
					case 3: yplace = hole_center_plate_for_moboy; break; // Not used now.
					case 2: yplace = middle_bracket_offset; break;
				}
				float matplusclear = MATERIAL_THICKNESS/2 + CUT_CLEARANCE;
				float twplusclear = mb_tongue_mm/2 + CUT_CLEARANCE;
				cx = whole_crossbrace_height/2;
				cy = yplace;
				DrawBox( CUT, cx-twplusclear, cy-matplusclear, cx+twplusclear, cy+matplusclear, EAR );
				Circle( CUT, whole_crossbrace_height/4-sidescrew_offset_y, cy, SCREW_WIDTH/2 );
			}
			
			if( side == 0 )
			{
				//Holes for PSU
				float cx = whole_crossbrace_height;
				float cy = mb_tray_length + sfx_psu_offset_y;
				Circle( CUT, cx-5.9, cy-6.2, M3_SCREW_WIDTH/2 );
				Circle( CUT, cx-32, cy-6.2, M3_SCREW_WIDTH/2 );
				Circle( CUT, cx-58.1, cy-6.2, M3_SCREW_WIDTH/2 ); // This one was covered in previous design
				Circle( CUT, cx-5.9, cy-119.2, M3_SCREW_WIDTH/2 );
				Circle( CUT, cx-32, cy-119.2, M3_SCREW_WIDTH/2 );
				Circle( CUT, cx-58.1, cy-119.2, M3_SCREW_WIDTH/2 );
				cx = whole_crossbrace_height-64/2;
				cy = mb_tray_length - 125.5/2 + sfx_psu_offset_y;
				DrawBox( CUT, cx-56/2, cy-104/2, cx+56/2, cy+104/2, 0 );
			}
			
			FillHexagons( CUT, (whole_crossbrace_height)/2.0-4+14, (top_tongue_offset+(top_tongue_offset + bottom_tongue_offset)/2)/2+6, 70, 170, 9, 0 );
			if( side == 1 )
			{
				FillHexagons( CUT, (whole_crossbrace_height)/2.0+10, (hole_center_plate_for_moboy+bottom_tongue_offset)/2-2, 70, 130, 9, 0 );
			}
			//FillHexagons( CUT, (whole_crossbrace_height)/2.0-4, 177-1, 30, 30, 9, 0 );
			
			cx = 0;
			cy = 0;
			//whole_crossbrace_height
			PathStart( CUT );
			PathM( cx, cy );
			cx+=whole_crossbrace_height + MATERIAL_THICKNESS;
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
			PathClose();
			
			//if( side == 1 )
			{
				printf( "</g>" );
			}

		}
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
