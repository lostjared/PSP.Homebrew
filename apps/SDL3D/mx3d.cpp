#include "mx3d.h"

float z_pos = 0.0f;
LPDIRECTSOUND8 m_pDS = 0;
LPDIRECTSOUND3DLISTENER g_pDSListener = 0;  
int mxApp::InitLoop() {
	MSG msg;
	go = true;
	while(go == true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else if(active) {
			screen.pd3d_dev->Clear(NULL,NULL,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,NULL);

			this->render(cur_screen);

			screen.pd3d_dev->Present(NULL,NULL,NULL,NULL);

		}
		else if(!active) {
			WaitMessage();
		}
	}

	return (int) msg.wParam;
}


mxHwnd::mxHwnd(const char *title, int x, int y, int w ,int h, bool fullscreen, WNDPROC wndProc, HICON hIcon ) {
	if(Init(title,fullscreen,x,y,w,h,wndProc, hIcon) == true) {
		if(InitDX(fullscreen,32) == true) {

		}
	}
}

mxHwnd::mxHwnd() {
	hwnd = 0, w = h = 0;
}

bool mxHwnd::Init(const char *title, bool full, int x, int y, int w, int h, WNDPROC WndProc, HICON hIcon) {


	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);
	wc.hInstance = GetModuleHandle(0);
	wc.hIcon = hIcon;
	wc.hIconSm = hIcon;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = title;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wc);


	this->hwnd = CreateWindow(title,title,(full == true) ? WS_POPUPWINDOW : WS_SYSMENU | WS_MINIMIZEBOX, x,y,w,h,NULL,NULL,GetModuleHandle(0),NULL);
	if(!hwnd) {
		ErrorMsg("Couldnt create window!.\n");
		return false;
	}
	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	this->w = w;
	this->h = h;
	this->screen.w = w;
	this->screen.h = h;
	return true;
}

bool mxHwnd::InitDX(bool fullscreen, int bpp) {
	screen.pd3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!screen.pd3d) {
		ErrorMsg("Error couldnt create Direct3D Device.");
		return false;
	}


	D3DPRESENT_PARAMETERS dpp;
	ZeroMemory(&dpp, sizeof(dpp));
	dpp.BackBufferCount = 1;
	dpp.BackBufferWidth = this->w;
	dpp.BackBufferHeight = this->h;
	if( bpp == 16 )
		dpp.BackBufferFormat        = D3DFMT_R5G6B5;
	else if( bpp == 24 )
		dpp.BackBufferFormat        = D3DFMT_X8R8G8B8;
	else if( bpp == 32 )
		dpp.BackBufferFormat        = D3DFMT_A8R8G8B8;
	else
		ErrorMsg("Invalid Format for BackBuffer you choose %d", bpp);
	dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	dpp.MultiSampleQuality = 0;
	dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	dpp.hDeviceWindow = this->hwnd;
	dpp.Windowed = (fullscreen == true) ? FALSE : TRUE;
	dpp.EnableAutoDepthStencil = TRUE;
	dpp.AutoDepthStencilFormat = D3DFMT_D16;
	dpp.FullScreen_RefreshRateInHz = (fullscreen == false) ? 0 : D3DPRESENT_RATE_DEFAULT;
	dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	HRESULT rt = screen.pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,hwnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&dpp,&screen.pd3d_dev );
	if(FAILED(rt)) {
		ErrorMsg("Error couldnt create Device.\n");
		return false;
	}
	screen.scr_rc.top = screen.scr_rc.left = 0;
	screen.scr_rc.right = this->w;
	screen.scr_rc.bottom = this->h;
	screen.pd3d_dev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &screen.pback );
	if(!screen.pback) {
		ErrorMsg("Error couldnt retrive the back buffer!\n");
		return false;
	}
	text.Init(&screen);
	paint.init(&screen);
	input.Init(this->hwnd);
	return true;
}



int mxHwnd::InitLoop(void(*render)(int screen)) {

	MSG msg;
	go = true;
	SetFocus(hwnd);
	while(go == true)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);

		}
		else if(active) {
			input.Update();
			screen.pd3d_dev->Clear(NULL,NULL,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0),1.0f,NULL);
			render(cur_screen);

			screen.pd3d_dev->Present(NULL,NULL,NULL,NULL);

		}
		else if(!active)
			WaitMessage();
	}

	input.Free();

	return (int) msg.wParam;
}

mxScreen::~mxScreen() {
	SafeFree<LPDIRECT3DSURFACE9>(this->pback);
	SafeFree<LPDIRECT3DDEVICE9>(this->pd3d_dev);
	SafeFree<LPDIRECT3D9>(this->pd3d);
}

void __fastcall mxPaint::Lock() {
	mxscr->pback->LockRect(&rect,NULL,NULL);
	data = (DWORD*) rect.pBits;
}

void __fastcall mxPaint::UnLock() {
	mxscr->pback->UnlockRect();
}

void __fastcall mxPaint::fast_sp(int x, int y, int pitch, D3DCOLOR color) {
	if(x >= 0 && x < mxscr->w-1 && y >= 0 && y < mxscr->h-1)
		data[(((pitch/4) * y) + x)] = color;

}

DWORD __fastcall mxPaint::fast_gp(int x, int y) {
	int pitch = this->rect.Pitch;
	return data[((pitch/4) * y) +x];
}

void __fastcall mxPaint::setpixel(int i, int z,D3DCOLOR color) {
	mxscr->pback->LockRect(&rect,NULL,NULL);
	DWORD *pdata = (DWORD*) rect.pBits;
	int pitch = rect.Pitch;
	pdata[(((pitch/4) * z) + i)] = color;
	mxscr->pback->UnlockRect();
}



void Swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Swap(float& a, float& b)
{
	float temp = a;
	a = b;
	b = temp;
}

static int max_clip_x = 640, min_clip_x = 0, max_clip_y = 480, min_clip_y = 0;


void __fastcall mxPaint::drawbottomtri(int x1, int y1, int x2, int y2, int x3, int y3, D3DCOLOR color) {
	float dx_right,dx_left,xs,xe,height;     
	int temp_x,temp_y,right,left;
	if (x3 < x2) {
		temp_x = x2;
		x2     = x3;
		x3     = temp_x;
	}
	height = float(y3-y1);
	dx_left  = (x2-x1)/height;
	dx_right = (x3-x1)/height;

	xs = (float)x1;
	xe = (float)x1;
	if (y1 < min_clip_y) {
		xs = xs+dx_left*(float)(-y1+min_clip_y);
		xe = xe+dx_right*(float)(-y1+min_clip_y);
		y1 = min_clip_y;
	}

	if (y3 > max_clip_y)
		y3 = max_clip_y;

	if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			drawhline(int(xs),(int)xs+(int(xe-xs+1)),temp_y,color);
			xs+=dx_left;
			xe+=dx_right;

		} 
	}
	else
	{
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			left  = (int)xs;
			right = (int)xe;
			xs+=dx_left;
			xe+=dx_right;

			if (left < min_clip_x){
				left = min_clip_x;

				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x)
			{
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			drawhline(int(left),(int)left+(int(right-left+1)),temp_y,color);
		}
	}
}


void __fastcall mxPaint::drawtoptri(int x1, int y1,int x2, int y2, int x3, int y3, D3DCOLOR color) {

	float dx_right,dx_left,xs,xe,height;  

	int temp_x,temp_y,right,left;

	if (x2 < x1) {
		temp_x = x2;
		x2     = x1;
		x1     = temp_x;
	}

	height = float(y3-y1);

	dx_left  = (x3-x1)/height;
	dx_right = (x3-x2)/height;

	xs = (float)x1;
	xe = (float)x2; 
	if (y1 < min_clip_y) {
		xs = xs+dx_left*(float)(-y1+min_clip_y);
		xe = xe+dx_right*(float)(-y1+min_clip_y);
		y1=min_clip_y;
	}

	if (y3>max_clip_y)
		y3=max_clip_y;

	if (x1>=min_clip_x && x1<=max_clip_x && x2>=min_clip_x && x2<=max_clip_x && x3>=min_clip_x && x3<=max_clip_x) {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			drawhline(int(xs),int(xs+(int)xe-xs+1),temp_y,color);
			xs+=dx_left;
			xe+=dx_right;
		} 
	}
	else {
		for (temp_y=y1; temp_y<=y3; temp_y++) {
			left  = (int)xs;
			right = (int)xe;
			xs+=dx_left;
			xe+=dx_right;
			if (left < min_clip_x) {
				left = min_clip_x;
				if (right < min_clip_x)
					continue;
			}

			if (right > max_clip_x) {
				right = max_clip_x;

				if (left > max_clip_x)
					continue;
			}
			drawhline((int)left,(int)left+(int)right-left+1,temp_y,color);
		} 

	}


}

void __fastcall mxPaint::drawtoptri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color) {

}
void __fastcall mxPaint::drawbottomtri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color) {


}

void __fastcall mxPaint::drawtri(int x1, int y1,int x2, int y2, int x3, int y3, D3DCOLOR color) {
	int temp_x,temp_y,new_x;

	if ((x1==x2 && x2==x3)  ||  (y1==y2 && y2==y3))
		return;

	if (y2<y1) {
		temp_x = x2;
		temp_y = y2;
		x2     = x1;
		y2     = y1;
		x1     = temp_x;
		y1     = temp_y;
	}

	if (y3<y1) {
		temp_x = x3;
		temp_y = y3;
		x3     = x1;
		y3     = y1;
		x1     = temp_x;
		y1     = temp_y;
	}

	if (y3<y2) {
		temp_x = x3;
		temp_y = y3;
		x3     = x2;
		y3     = y2;
		x2     = temp_x;
		y2     = temp_y;

	} 
	if ( y3<min_clip_y || y1>max_clip_y || (x1<min_clip_x && x2<min_clip_x && x3<min_clip_x) || (x1>max_clip_x && x2>max_clip_x && x3>max_clip_x) )
		return;


	if (y1==y2)  {
		this->drawtoptri(x1,y1,x2,y2,x3,y3,color);
	} 
	else
		if (y2==y3){
			this->drawbottomtri(x1,y1,x2,y2,x3,y3,color);
		} 
		else {
			new_x = x1 + (int)(0.5+(float)(y2-y1)*(float)(x3-x1)/(float)(y3-y1));
			this->drawbottomtri(x1,y1,new_x,y2,x2,y2,color);
			this->drawtoptri(x2,y2,new_x,y2,x3,y3,color);
		} 
}

void __fastcall mxPaint::filltri(POINT &p1, POINT &p2, POINT &p3, D3DCOLOR color) {


}
void __fastcall mxPaint::drawhline(int x,int x2, int y, D3DCOLOR color) {
	for(int p = x; p <= x2; p++)
		fast_sp(p,y,rect.Pitch,color);
}

void __fastcall mxPaint::drawtri2(float x1, float y1, float x2, float y2, float x3, float y3, D3DCOLOR color) {

}

void __fastcall mxPaint::drawgentri(int x0, int y0, int x1, int y1, int x2, int y2, D3DCOLOR color) {

	if( y1 < y0 )
	{
		Swap(y1, y0);
		Swap(x1, x0);
	}
	if( y2 < y0 )
	{
		Swap(y2, y0);
		Swap(x2, x0);
	}

	if( y1 < y2 )
	{
		Swap(y2, y1);
		Swap(x2, x1);
	}


	float xl_edge = (float)x0; 
	float xr_edge = (float)x0;
	float dxldy;
	float dxrdy;
	float dxdy1 = (float)(x2-x0)/(y2-y0);
	float dxdy2 = (float)(x1-x0)/(y1-y0);
	if( dxdy1 < dxdy2 )
	{
		dxldy = dxdy1;
		dxrdy = dxdy2;
	}
	else
	{
		dxldy = dxdy2;
		dxrdy = dxdy1;
	}

	for(int y=y0; y<y2; y++)
	{
		for(int x=int(xl_edge); x<int(xr_edge); x++)
		{
			this->fast_sp(x, y, this->rect.Pitch, color);
		}

		xl_edge = xl_edge + dxldy;
		xr_edge = xr_edge + dxrdy;

	}

	if( dxdy1 < dxdy2 )
	{
		dxldy = (float)(x2-x1)/(y2-y1);
	}
	else
	{
		dxrdy = (float)(x2-x1)/(y2-y1);
	}
	for(int y=y2; y<y1; y++)
	{
		for(int x=int(xl_edge); x<int(xr_edge); x++)
		{
			this->fast_sp(x,y,this->rect.Pitch,color);
		}

		xl_edge = xl_edge + dxldy;
		xr_edge = xr_edge + dxrdy;
	}
}

void __fastcall mxPaint::drawrect(int x, int y, int w , int h, D3DCOLOR color) {
	D3DRECT rc = { x,y,w,h };
	mxscr->pd3d_dev->Clear(1,&rc,D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, color,1.0f,NULL);
}

void __fastcall mxPaint::drawroundrect(int x, int y, int x2, int y2, int ch, int cw, COLORREF fill, COLORREF outline) {

	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	RoundRect(dc,x,y,x2,y2,cw,ch);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpie(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2, COLORREF fill, COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Pie(dc,x,y,x2,y2,nx,ny,nx2,ny2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawchord(int x, int y, int x2, int y2, int nx, int ny, int nx2, int ny2,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Chord(dc,x,y,x2,y2,nx,ny,nx2,ny2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawellipse(int x, int y, int x2, int y2,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Ellipse(dc,x,y,x2,y2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpolygon(CONST POINT* point,int n_points,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Polygon(dc,point,n_points);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawanglearc(int x, int y, long radius, float startangle,float sweepangle,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	AngleArc(dc,x,y,radius,startangle,sweepangle);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawarc(int x1, int x2, int x3, int x4,int x5, int x6,int x7, int x8,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	Arc(dc,x1,x2,x3,x4,x5,x6,x7,x8);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawlineto(int x, int y,COLORREF fill,COLORREF outline) {
	HDC dc;
	mxscr->pback->GetDC(&dc);
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen; 

	hNewBrush = (HBRUSH)CreateSolidBrush(fill); 
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline); 
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen); 

	LineTo(dc,x,y);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
	mxscr->pback->ReleaseDC(dc);
}

void __fastcall mxPaint::drawpixel(int x, int y, COLORREF color) {
	HDC dc;
	this->mxscr->pback->GetDC(&dc);
	SetPixel(dc,x,y,color);
	this->mxscr->pback->ReleaseDC(dc);

}

COLORREF __fastcall mxPaint::drawgetpixel(int x, int y) {
	HDC dc;
	this->mxscr->pback->GetDC(&dc);
	COLORREF color = GetPixel(dc,x,y);
	this->mxscr->pback->ReleaseDC(dc);
	return color;
}

void __fastcall mxPaint::drawline(int start_x, int start_y, int stop_x, int stop_y, D3DCOLOR color) {

	//Lock(); assumes its locked

	int y_unit,x_unit;
	int ydiff = stop_y-start_y;
	if(ydiff<0)
	{
		ydiff = -ydiff;
		y_unit=-1;
	}
	else
	{
		y_unit =1;
	}
	int xdiff=stop_x-start_x;
	if(xdiff<0)
	{
		xdiff=-xdiff;
		x_unit = -1;
	}
	else
	{
		x_unit = 1;
	}

	int error_term=0;
	if(xdiff>ydiff)
	{
		int length=xdiff+1;
		for(int i = 0; i <length; i++)
		{
			//SetPixel(dc,start_x,start_y,color);
			fast_sp(start_x,start_y,rect.Pitch,color);
			start_x += x_unit;
			error_term+=ydiff;
			if(error_term>xdiff)
			{
				error_term-=xdiff;
				start_y+=y_unit;
			}
		}
	}
	else
	{
		int length = ydiff+1;
		for(int i = 0; i < length; i++)
		{
			//SetPixel(dc,start_x,start_y,color);
			fast_sp(start_x,start_y,rect.Pitch,color);
			start_y += y_unit;
			error_term+=xdiff;
			if(error_term>0)
			{
				error_term-=ydiff;
				start_x += x_unit;
			}

		}
	}

}

LPDIRECTINPUTDEVICE8 p_joy = 0;
LPDIRECTINPUT8 pdi = 0;
bool joy_exisits;
char joy_name[256];