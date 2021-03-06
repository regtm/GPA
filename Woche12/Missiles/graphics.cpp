//
// based on TinyPTC by Glenn Fiedler
// http://sourceforge.net/projects/tinyptc/
//

#include "graphics.h"
#include <windowsx.h>

static word screen[SCREEN_HEIGHT][SCREEN_WIDTH];

#include <ddraw.h>

static HMODULE library = 0;
static LPDIRECTDRAW lpDD = 0;
static LPDIRECTDRAWSURFACE lpDDS = 0;
static LPDIRECTDRAWSURFACE lpDDS_back;
static WNDCLASS wc;
static HWND wnd;
static int active;
static int dx;
static int dy;

#ifdef __PTC_WINDOWED__
static LPDIRECTDRAWCLIPPER lpDDC = 0;
static LPDIRECTDRAWSURFACE lpDDS_secondary = 0;
#endif

#ifdef __PTC_SYSTEM_MENU__
static int original_window_width;
static int original_window_height;
static HMENU system_menu;
#endif


typedef HRESULT (WINAPI * DIRECTDRAWCREATE) (GUID FAR *lpGUID,LPDIRECTDRAW FAR *lplpDD,IUnknown FAR *pUnkOuter);


#ifdef __PTC_WINDOWED__

static void ptc_paint_primary()
{
	RECT source;
	RECT destination;
	POINT point;

	// check
	if (lpDDS)
	{
		// setup source rectangle
		source.left = 0;
		source.top = 0;
		source.right = dx;
		source.bottom = dy;

		// get origin of client area
		point.x = 0;
		point.y = 0;
		ClientToScreen(wnd,&point);

		// get window client area
		GetClientRect(wnd,&destination);

		// offset destination rectangle
		destination.left += point.x;
		destination.top += point.y;
		destination.right += point.x;
		destination.bottom += point.y;

		// blt secondary to primary surface
		IDirectDrawSurface_Blt(lpDDS,&destination,lpDDS_secondary,&source,DDBLT_WAIT,0);
	}
}

#endif


// menu option identifier
#define SC_ZOOM_MSK 0x400
#define SC_ZOOM_1x1 0x401
#define SC_ZOOM_2x2 0x402
#define SC_ZOOM_4x4 0x404

static LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	// result data
	int result = 0;

	// handle message
	switch (message)
	{
		#ifdef __PTC_WINDOWED__

		case WM_PAINT:
		{
	#ifndef __PTC_WINDOWED__
	if (active)
	#endif
	{
	int y;
	byte *src;
	byte *dst;
	int src_pitch;
	int dst_pitch;
	DDSURFACEDESC descriptor;

		// restore surfaces
		IDirectDrawSurface_Restore(lpDDS);
		#ifdef __PTC_WINDOWED__
		IDirectDrawSurface_Restore(lpDDS_secondary);
		#endif

		// lock back surface
		descriptor.dwSize = sizeof descriptor;
		if (FAILED(IDirectDrawSurface_Lock(lpDDS_back,0,&descriptor,DDLOCK_WAIT,0))) return 0;
	
		// calculate pitches
		src_pitch = dx * 4;
		dst_pitch = descriptor.lPitch;

		// copy screen to back surface
		src = (byte*) screen;
		dst = (byte*) descriptor.lpSurface;
		for (y=0; y<dy; y++)
		{
			// convert line
			memcpy(dst, src, dx * 4);
			src += src_pitch;
			dst += dst_pitch;
		}

		// unlock back surface
		IDirectDrawSurface_Unlock(lpDDS_back,descriptor.lpSurface);

		#ifndef __PTC_WINDOWED__
	
			// flip primary surface
			IDirectDrawSurface_Flip(lpDDS,0,DDFLIP_WAIT);

		#else

			// paint primary
			ptc_paint_primary();

		#endif

		// sleep
		Sleep(0);
	}
	#ifndef __PTC_WINDOWED__
	else
	{
		// sleep
		Sleep(1);
	}
	#endif

			// call default window painting
			return DefWindowProc(hWnd,message,wParam,lParam);
		}
		break;

		#else

		case WM_ACTIVATEAPP:
		{									   
			// update active flag
			active = (BOOL) wParam;
		}
		break;

		case WM_SETCURSOR:
		{
			// hide cursor
			SetCursor(0);
		}
		break;

		#endif


#ifdef __PTC_WINDOWED__
#ifdef __PTC_RESIZE_WINDOW__
#ifdef __PTC_SYSTEM_MENU__

		// check for message from our system menu entry
		case WM_SYSCOMMAND:
		{
			if ((wParam&0xFFFFFFF0)==SC_ZOOM_MSK)
			{
				#ifdef __PTC_CENTER_WINDOW__
					int zoom = wParam & 0x7;
					int x = (GetSystemMetrics(SM_CXSCREEN) - original_window_width*zoom) >> 1;
					int y = (GetSystemMetrics(SM_CYSCREEN) - original_window_height*zoom) >> 1;
					SetWindowPos(hWnd, NULL, x, y,original_window_width*zoom, original_window_height*zoom, SWP_NOZORDER);
				#else
					int zoom = wParam & 0x7;
					SetWindowPos(hWnd, NULL, 0, 0,original_window_width*zoom, original_window_height*zoom, SWP_NOMOVE | SWP_NOZORDER);
				#endif
			}
			// pass everything else to the default (this is rather important)
			else return DefWindowProc(hWnd, message, wParam, lParam);
		}
#endif
#endif
#endif

		case WM_KEYDOWN:
		{
			void key_pressed(int);
			key_pressed(wParam & 0xff);
			break;
		}

		void mouse_pressed(int x, int y, int button);
		case WM_LBUTTONDOWN:
		{
			mouse_pressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 0);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			mouse_pressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 1);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			mouse_pressed(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), 2);
			break;
		}

		case WM_CLOSE:
		{
			#ifdef __PTC_ALLOW_CLOSE__

				// close ptc
				ptc_close();

				// exit process
				ExitProcess(0);

			#endif
		}
		break;

		default:
		{
			// unhandled messages
			result = DefWindowProc(hWnd,message,wParam,lParam);
		}
	}

	// finished
	return result;
}


int ptc_open(const char *title,int width,int height)
{
	#ifdef __PTC_WINDOWED__
	int x;
	int y;
	RECT rect;
	//DEVMODE mode;
	#else
	DDSCAPS capabilities;
	#endif
	DDPIXELFORMAT format;
	DDSURFACEDESC descriptor;
	DIRECTDRAWCREATE DirectDrawCreate;

	// setup data
	dx = width;
	dy = height;

	// load direct draw library
	library = (HMODULE) LoadLibrary("ddraw.dll");
	if (!library) return 0;

	// get directdraw create function address
	DirectDrawCreate = (DIRECTDRAWCREATE) GetProcAddress(library,"DirectDrawCreate");
	if (!DirectDrawCreate) return 0;

	// create directdraw interface
	if (FAILED(DirectDrawCreate(0,&lpDD,0))) return 0;

#ifndef __PTC_WINDOWED__

	// register window class
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
#ifdef __PTC_ICON__
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(wc.hInstance,__PTC_ICON__);
#else
	wc.hInstance = 0;
	wc.hIcon = 0;
#endif
	wc.hCursor = 0;
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = title;
	RegisterClass(&wc);

	// create window
#ifdef __PTC_ICON__
	wnd = CreateWindow(title,title,WS_POPUP | WS_SYSMENU,0,0,0,0,0,0,0,0);
#else
	wnd = CreateWindow(title,title,WS_POPUP,0,0,0,0,0,0,0,0);
#endif

	// enter exclusive mode
	if (FAILED(IDirectDraw_SetCooperativeLevel(lpDD,wnd,DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN))) return 0;

	// enter display mode
	if (FAILED(IDirectDraw_SetDisplayMode(lpDD,width,height,32)))
	{
		if (FAILED(IDirectDraw_SetDisplayMode(lpDD,width,height,24)))
		{
			if (FAILED(IDirectDraw_SetDisplayMode(lpDD,width,height,16)))
			{
				// failure
				return 0;
			}
		}
	}

	// primary with two back buffers
	descriptor.dwSize  = sizeof(descriptor);
	descriptor.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
	descriptor.dwBackBufferCount = 2;
	descriptor.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY | DDSCAPS_COMPLEX | DDSCAPS_FLIP;
	if (FAILED(IDirectDraw_CreateSurface(lpDD,&descriptor,&lpDDS,0)))
	{
		// primary with one back buffer
		descriptor.dwBackBufferCount = 1;
		if (FAILED(IDirectDraw_CreateSurface(lpDD,&descriptor,&lpDDS,0)))
		{
			// primary with no back buffers
			descriptor.dwFlags = DDSD_CAPS;
			descriptor.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY;
			if (FAILED(IDirectDraw_CreateSurface(lpDD,&descriptor,&lpDDS,0)))
			{
				// failure
				return 0;
			}
		}
	}

	// get back surface
	capabilities.dwCaps = DDSCAPS_BACKBUFFER;
	if (FAILED(IDirectDrawSurface_GetAttachedSurface(lpDDS,&capabilities,&lpDDS_back))) return 0;

#else

	// register window class
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
#ifdef __PTC_ICON__
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = LoadIcon(wc.hInstance,__PTC_ICON__);
#else
	wc.hInstance = 0;
	wc.hIcon = 0;
#endif
	wc.hCursor = LoadCursor(0,IDC_ARROW);
	wc.hbrBackground = 0;
	wc.lpszMenuName = 0;
	wc.lpszClassName = title;
	RegisterClass(&wc);

	// calculate window size
	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;
	AdjustWindowRect(&rect,WS_OVERLAPPEDWINDOW,0);
	rect.right -= rect.left;
	rect.bottom -= rect.top;

#ifdef __PTC_CENTER_WINDOW__

	// center window
	x = (GetSystemMetrics(SM_CXSCREEN) - rect.right) >> 1;
	y = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) >> 1;

#else

	// let windows decide
	x = CW_USEDEFAULT;
	y = CW_USEDEFAULT;

#endif

#ifdef __PTC_RESIZE_WINDOW__

	// create resizable window
	wnd = CreateWindow(title,title,WS_OVERLAPPEDWINDOW,x,y,rect.right,rect.bottom,0,0,0,0);

#else

	// create fixed window
	wnd = CreateWindow(title,title,WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,x,y,rect.right,rect.bottom,0,0,0,0);

#endif

	// show window
	ShowWindow(wnd,SW_NORMAL);

#ifdef __PTC_RESIZE_WINDOW__
#ifdef __PTC_SYSTEM_MENU__

	// add entry to system menu to restore original window size
	system_menu = GetSystemMenu(wnd,FALSE);
	AppendMenu(system_menu, MF_STRING, SC_ZOOM_1x1, "Zoom 1 x 1");
	AppendMenu(system_menu, MF_STRING, SC_ZOOM_2x2, "Zoom 2 x 2");
	AppendMenu(system_menu, MF_STRING, SC_ZOOM_4x4, "Zoom 4 x 4");

	// save original window size
	original_window_width = rect.right;
	original_window_height = rect.bottom;

#endif
#endif

	// enter cooperative mode
	if (FAILED(IDirectDraw_SetCooperativeLevel(lpDD,wnd,DDSCL_NORMAL))) return 0;

	// primary with no back buffers
	descriptor.dwSize  = sizeof(descriptor);
	descriptor.dwFlags = DDSD_CAPS;
	descriptor.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY;
	if (FAILED(IDirectDraw_CreateSurface(lpDD,&descriptor,&lpDDS,0))) return 0;

	// create secondary surface
	descriptor.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	descriptor.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	descriptor.dwWidth = width;
	descriptor.dwHeight = height;
	if (FAILED(IDirectDraw_CreateSurface(lpDD,&descriptor,&lpDDS_secondary,0))) return 0;
	
	// create clipper
	if (FAILED(IDirectDraw_CreateClipper(lpDD,0,&lpDDC,0))) return 0;

	// set clipper to window
	if (FAILED(IDirectDrawClipper_SetHWnd(lpDDC,0,wnd))) return 0;

	// attach clipper object to primary surface
	if (FAILED(IDirectDrawSurface_SetClipper(lpDDS,lpDDC))) return 0;
	
	// set back to secondary
	lpDDS_back = lpDDS_secondary;

#endif

	// get pixel format
	format.dwSize = sizeof(format);
	if (FAILED(IDirectDrawSurface_GetPixelFormat(lpDDS,&format))) return 0;

	// check that format is direct color
	if (!(format.dwFlags & DDPF_RGB)) return 0;
	
#ifdef __PTC_DISABLE_SCREENSAVER__

	// disable screensaver while ptc is open
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 0, 0, 0);

#endif

	// success
	return 1;
}


void ptc_close()
{
#ifdef __PTC_WINDOWED__

	// check secondary
	if (lpDDS_secondary)
	{
		// release secondary
		IDirectDrawSurface_Release(lpDDS_secondary);
		lpDDS_secondary = 0;
	}

#endif

	// check
	if (lpDDS)
	{
		// release primary
		IDirectDrawSurface_Release(lpDDS);
		lpDDS = 0;
	}

	// check
	if (lpDD)
	{
		// leave display mode
		IDirectDraw_RestoreDisplayMode(lpDD);

		// leave exclusive mode
		IDirectDraw_SetCooperativeLevel(lpDD,wnd,DDSCL_NORMAL);

		// free direct draw
		IDirectDraw_Release(lpDD);
		lpDD = 0;
	}

	// hide window
	DestroyWindow(wnd);

	// check
	if (library)
	{
		// free library
		FreeLibrary(library);
		library = 0;
	}

#ifdef __PTC_DISABLE_SCREENSAVER__

	// enable screensaver now that ptc is closed
	SystemParametersInfo(SPI_SETSCREENSAVEACTIVE, 1, 0, 0);

#endif
}



// GPA additions

#pragma comment(lib, "winmm")

#include <iostream>
#include <pmmintrin.h>
#include <atomic>
#include <thread>

void clear_screen()
{
	memset(screen, 0, SCREEN_SIZE * 4);
}

void draw_pixel(word x, word y, word color)
{
	if ((x < SCREEN_WIDTH) && (y < SCREEN_HEIGHT))
	{
		screen[y][x] = color;
	}
}

void blend_pixel(word x, word y, word color)
{
	if ((x < SCREEN_WIDTH) && (y < SCREEN_HEIGHT))
	{
		__m128i new_pixel = _mm_cvtsi32_si128(color);
		__m128i old_pixel = _mm_cvtsi32_si128(screen[y][x]);
		__m128i sum_pixel = _mm_adds_epu8(new_pixel, old_pixel);
		screen[y][x] = _mm_cvtsi128_si32(sum_pixel);
	}
}

static word scale_color(word color, double scale_factor)
{
	double r = (color >> 16) * scale_factor;
	double g = ((color >> 8) & 0xff) * scale_factor;
	double b = (color & 0xff) * scale_factor;
	return static_cast<word>(r) << 16 | static_cast<word>(g) << 8 | static_cast<word>(b);
}

void blend_aa_pixel(double x, double y, word color)
{
	word x0 = static_cast<word>(x);
	word x1 = x0 + 1;
	word y0 = static_cast<word>(y);
	word y1 = y0 + 1;

	double weight_e = x - x0;
	double weight_w = 1 - weight_e;

	double weight_s = y - y0;
	double weight_n = 1 - weight_s;

	blend_pixel(x0, y0, scale_color(color, weight_w * weight_n));
	blend_pixel(x1, y0, scale_color(color, weight_e * weight_n));
	blend_pixel(x0, y1, scale_color(color, weight_w * weight_s));
	blend_pixel(x1, y1, scale_color(color, weight_e * weight_s));
}

int mymax(int a, int b)
{
	return (a < b) ? b : a;
}

void draw_line(int x1, int y1, int x2, int y2, word color)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int hops = mymax(abs(dx), abs(dy));
	float x = x1 + 0.5f;
	float y = y1 + 0.5f;
	float rhops = 1.0f / hops;
	for (int i = 0; i <= hops; ++i)
	{
		float t = i * rhops;
		blend_pixel(word(x + t * dx), word(y + t * dy), color);
	}
}

double fast_reciprocal(double x)
{
	float f = static_cast<float>(x);
	_mm_store_ss(&f, _mm_rcp_ss(_mm_load_ss(&f)));
	return f;
}

double fast_reciprocal_sqrt(double x)
{
	float f = static_cast<float>(x);
	_mm_store_ss(&f, _mm_rsqrt_ss(_mm_load_ss(&f)));
	return f;
}

double ipart(double x)
{
	return floor(x);
}

double my_round(double x)
{
	return ipart(x + 0.5);
}

double fpart(double x)
{
	return x - floor(x);
}

double rfpart(double x)
{
	return 1 - fpart(x);
}

void plot(double x, double y, word color, double c)
{
	blend_pixel(int(x), int(y), scale_color(color, c));
}

//
// http://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
//
void draw_aa_line(double x0, double y0, double x1, double y1, word color)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	double dx = x1 - x0;
	double dy = y1 - y0;
	double gradient = dy / dx;
	
	double xend = my_round(x0);
	double yend = y0 + gradient * (xend - x0);
	double xgap = rfpart(x0 + 0.5);
	double xpxl1 = xend;
	double ypxl1 = ipart(yend);

	if (steep)
	{
		plot(ypxl1,   xpxl1, color, rfpart(yend) * xgap);
		plot(ypxl1+1, xpxl1, color,  fpart(yend) * xgap);
	}
	else
	{
		plot(xpxl1, ypxl1  , color, rfpart(yend) * xgap);
		plot(xpxl1, ypxl1+1, color,  fpart(yend) * xgap);
	}
	double intery = yend + gradient;
	
	xend = my_round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = fpart(x1 + 0.5);
	double xpxl2 = xend;
	double ypxl2 = ipart(yend);

	if (steep)
	{
		plot(ypxl2  , xpxl2, color, rfpart(yend) * xgap);
		plot(ypxl2+1, xpxl2, color,  fpart(yend) * xgap);
	}
	else
	{
		plot(xpxl2, ypxl2,   color, rfpart(yend) * xgap);
		plot(xpxl2, ypxl2+1, color,  fpart(yend) * xgap);
	}
	
	for (int x = int(xpxl1) + 1; x < xpxl2; ++x)
	{
		if (steep)
		{
			plot(ipart(intery)  , x, color, rfpart(intery));
			plot(ipart(intery)+1, x, color,  fpart(intery));
		}
		else
		{
			plot(x, ipart (intery),   color, rfpart(intery));
			plot(x, ipart (intery)+1, color,  fpart(intery));
		}
		intery = intery + gradient;
	}
}

void processMessages()
{
	MSG message;
	while (PeekMessage(&message,wnd,0,0,PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void initialize();
void render();
void update();

int current_time;

int main()
{
	if (!ptc_open("GPA Graphics based on TinyPTC", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		std::cerr << "unable to open window :(\n";
		std::cin.peek();
		return 1;
	}
	current_time = timeGetTime();
	initialize();
	while (true)
	{
		clear_screen();
		render();
		InvalidateRect(wnd, 0, FALSE);
		processMessages();
		current_time = timeGetTime();
		update();
	}
}
