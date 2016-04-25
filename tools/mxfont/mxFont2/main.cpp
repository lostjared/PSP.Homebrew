#include<windows.h>
#include<shellapi.h>
#include<shlobj.h>
#include<shlwapi.h>
#include<objbase.h>
#include<commctrl.h>
#include<stdio.h>
#include "mxFont.h"
#include "filedialog.h"
#include "resource.h"


// enumerated constants
enum { ID_EDR = 1, ID_EDG , ID_EDB, ID_GENC, ID_COMBO, ID_NEW };
enum { ERASER = 0, BRUSH , FILL};
// globals
HWND fhwnd;
HWND edfnt,but1;
mxFont m;
HWND edr,edg,edb,genc,comb,htool,st1,st2,st3,lost,habout,hnew,hoptions,hconv;
HBITMAP heraser,heraser_up,hpencil,hpencil_up,hfill,hfill_up,hlogo,hcbmp;
HDC hcdc;
HFONT the_font;

bool eraser_up = false,pencil_up = false,fill_up = false,quit = false;
HFONT under_fnt,reg_fnt;
char str_fname[MAX_PATH];
int cur_color = 0xFF;
int cur_letter = 0;
int the_tool = BRUSH;

// update the windows title
inline void updateTitle() {
	char title_str[1024+50];
	sprintf(title_str, "mxFont Editor - %s", str_fname);
	SendMessage(fhwnd,WM_SETTEXT,1024+50,(LPARAM)(LPCSTR)title_str);
}

// draw a rectangle
inline void drawRect(HDC dc, int x, int y, int x2, int y2, int fill_color, int outline_color) {
	HBRUSH hNewBrush,hOldBrush;
	HPEN hNewPen,hOldPen;

	hNewBrush = (HBRUSH)CreateSolidBrush(fill_color);
	hOldBrush = (HBRUSH)SelectObject(dc,(HBRUSH)hNewBrush);

	hNewPen = CreatePen(PS_SOLID,2,outline_color);
	hOldPen= (HPEN__*)SelectObject(dc,(HPEN__*)hNewPen);

	Rectangle(dc,x,y,x2,y2);

	SelectObject(dc,hOldPen);
	SelectObject(dc,hOldBrush);

	DeleteObject(hNewBrush);
	DeleteObject(hNewPen);
}

// draw the font
void draw_font_win32(HDC dc) {

	int offset_x = 10;
	int offset_y = 20;
	for(int i = 0; i < m.mx; i++) {
		for(int z = 0; z < m.my; z++) {
			drawRect(dc,offset_x,offset_y,offset_x+10,offset_y+10,m.letters[cur_letter].fnt_ptr[i][z],m.letters[cur_letter].fnt_ptr[i][z]);
			offset_y += 10;
		}
		offset_y = 20;
		offset_x += 10;
	}

}
// draw the color bar
inline void drawColorbar(HDC dc) {
	int offset_x = (m.mx * 10)+20;
	int offset_y = 70+25+5+13+5+13+20+30;
	drawRect(dc,offset_x,offset_y,offset_x+100,offset_y+10,cur_color,cur_color);
}

// draw the buttons
inline void drawButtons(HDC dc) {
	HDC dc_mem = CreateCompatibleDC(dc);
	if(eraser_up == false)
		SelectObject(dc_mem,heraser);
	else
		SelectObject(dc_mem,heraser_up);
	StretchBlt(dc,m.mx * 10 + 20,225,25,25,dc_mem,0,0,25,24,SRCCOPY);
	if(pencil_up == false)
		SelectObject(dc_mem,hpencil);
	else
		SelectObject(dc_mem,hpencil_up);
	StretchBlt(dc,m.mx * 10 + 20+30,225,25,24,dc_mem,0,0,25,24,SRCCOPY);
	if(fill_up == false)
		SelectObject(dc_mem,hfill);
	else
		SelectObject(dc_mem,hfill_up);
	StretchBlt(dc,m.mx * 10 + 20+30+30,225,25,24,dc_mem,0,0,25,24,SRCCOPY);

	DeleteDC(dc_mem);

}

// fill color for tool
inline void fillColor(int color, int fill_color) {
	for(int i = 0; i < m.mx; i++)
		for(int z = 0; z < m.my; z++)
			if(m.letters[cur_letter].fnt_ptr[i][z] == color)
				m.letters[cur_letter].fnt_ptr[i][z] = fill_color;
}


// place a pixel on the grid
inline void PlacePixel(int x, int y, int color) {
	int offset_x = 10, offset_y = 20;
	if(the_tool == ERASER)
		color = m.tcolor;

	if(m.mx != 0 && m.my != 0)
		for(int i = 0; i < m.mx; i++) {
			for(int z = 0; z < m.my; z++) {
				if(x >= offset_x && x <= offset_x+10 && y >= offset_y && y <= offset_y+10) {
					if(m.letters[cur_letter].fnt_ptr[i][z] != color) {
						switch(the_tool) {
						case BRUSH:
						case ERASER: {
							m.letters[cur_letter].fnt_ptr[i][z] = color;
							RECT rc = {offset_x-1,offset_y-1,offset_x+11,offset_y+11};
							InvalidateRect(fhwnd,&rc,TRUE);
							break;
									 }
						case FILL: {
							fillColor(m.letters[cur_letter].fnt_ptr[i][z],color);
							RECT rc1 = { 0,0, m.mx * 10+25, m.my * 10+25 };
							InvalidateRect(fhwnd,&rc1,TRUE);
								   }
								   break;
						}
					}
					return;
				}
				offset_y += 10;
			}
			offset_y = 20;
			offset_x += 10;
		}

}
// add string to combo
inline void addstr(const char *str) {
	SendMessage(comb,CB_ADDSTRING,strlen(str),(LPARAM)(LPCSTR)str);
}

// sizewindow
inline void sizeWindow() {

	RECT rc1;
	GetWindowRect(fhwnd,&rc1);
	SetWindowPos(fhwnd,0,rc1.top,rc1.left,m.mx * 10 + 150,(m.my * 10)+100,0);
	SetWindowPos(edr, 0, (m.mx * 10) + 15,25,100,25,0);
	SetWindowPos(edg, 0, (m.mx * 10) + 15,75,100,25,0);
	SetWindowPos(edb, 0, (m.mx * 10) + 15,70+25+5+13+5,100,25,0);
	SetWindowPos(st1, 0, (m.mx * 10) + 15,5,50,13,0);
	SetWindowPos(st2, 0, (m.mx * 10) + 15,50,50,13,0);
	SetWindowPos(st3, 0, (m.mx * 10) + 15,70+25+5+13+5,50,13,0);
	SetWindowPos(genc, 0, (m.mx * 10) + 15,70+25+5+13+5+13+20,100,25,0);
	SetWindowPos(comb, 0, (m.mx * 10) + 15,70+25+5+13+5+13+20+25+10+10,250,25,0);
	SetWindowPos(lost, 0,10, m.my * 10 + 23, 200,25,0);
	SetWindowPos(htool,0,m.mx * 10+20,225+25+5,60,25,0);
	RECT rc = {0,0,1024,768 };
	InvalidateRect(fhwnd,&rc,TRUE);
}
// update the combo information ( if nessicary display a different letter )
inline void updateCombo() {
	cur_letter = (int) SendMessage(comb,CB_GETCURSEL,0,0);
	RECT rc = { 0,0,1024,768 };
	InvalidateRect(fhwnd,&rc,TRUE);
}

inline void resizeBitmap(HBITMAP hbm, BITMAP bits) {
	HDC dc = GetDC(fhwnd);
	HDC cdc = CreateCompatibleDC(dc);
	HDC cdcc = CreateCompatibleDC(dc);

	HBITMAP hcbm = CreateCompatibleBitmap(cdc,bits.bmWidth,bits.bmHeight);
	SelectObject(cdc,hbm);
	StretchBlt(dc,0,0,m.mx,m.my,cdc,0,0,bits.bmWidth,bits.bmHeight,SRCCOPY);
	for(int i = 0; i < m.mx; i++)
		for(int z = 0; z < m.my; z++) {
			m.letters[cur_letter].fnt_ptr[i][z] = GetPixel(dc,i,z);
		}
		RECT rc1 = {0,0,m.mx * 10 + 10, m.my * 10 + 20 };
		InvalidateRect(fhwnd,&rc1,TRUE);
}


// windows callback function
LRESULT CALLBACK WndProc(HWND hwnd,UINT msg, WPARAM wParam, LPARAM lParam) {

	switch(msg) {
		case WM_DESTROY:
			if(!quit)
				PostQuitMessage(0);
			break;
		case WM_CREATE: {
			edr = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", "255", WS_CHILD | WS_VISIBLE , (m.mx * 10)+20, 25, 100,25,hwnd,(HMENU)ID_EDR,GetModuleHandle(0),0);
			st1 = CreateWindow("Static","Red value", WS_CHILD | WS_VISIBLE,(m.mx * 10) + 20, 5,50,13,hwnd,0,GetModuleHandle(0),0);
			st2 = CreateWindow("Static","Green value", WS_CHILD | WS_VISIBLE,(m.mx *10) + 20,50,50,13,hwnd,0,GetModuleHandle(0),0);
			edg = CreateWindowEx(WS_EX_CLIENTEDGE,"Edit", "0", WS_CHILD | WS_VISIBLE , (m.mx * 10)+20,70,100,25,hwnd,0,GetModuleHandle(0),0);
			st3 = CreateWindow("Static", "Blue value", WS_CHILD | WS_VISIBLE, (m.mx *10) + 20,70+25+5,50,13,hwnd,0,GetModuleHandle(0),0);
			edb = CreateWindowEx(WS_EX_CLIENTEDGE,"Edit","0", WS_CHILD | WS_VISIBLE ,(m.mx*10)+20,70+25+5+13+5,100,25,hwnd,0,GetModuleHandle(0),0);
			genc = CreateWindow("Button","Set Color", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,(m.mx*10)+20,70+25+5+13+5+13+20,100,25,hwnd,(HMENU)ID_GENC,GetModuleHandle(0),0);
			comb = CreateWindow("ComboBox","NULL", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL | CBS_DISABLENOSCROLL, (m.mx * 10) + 20,70+25+5+13+5+13+20+25+10+10,100,25,hwnd,(HMENU)ID_COMBO,GetModuleHandle(0),0);
			char c = 0;
			for(c = 0; c < 127; c++) {
				char dat[2];
				dat[0] = c;
				dat[1] = 0;
				SendMessage(comb,CB_ADDSTRING,strlen(dat),(LPARAM)(LPCSTR)dat);
			}
			SendMessage(comb,CB_SETCURSEL,'a',0);
			htool = CreateWindow("Static","[ Pencil ]", WS_CHILD | WS_VISIBLE, m.mx * 10+20,225+25+5,60,25,hwnd,0,GetModuleHandle(0),0);
			lost = CreateWindow("Static", "http://www.lostsidedead.com", WS_CHILD | WS_VISIBLE | WS_DISABLED, 10, m.my * 10 + 23, 200,25,hwnd,0,GetModuleHandle(0),0);
			HDC dc = GetDC(hwnd);
			hcdc = CreateCompatibleDC(dc);
			RECT rc;
			GetWindowRect(hwnd,&rc);
			hcbmp = CreateCompatibleBitmap(dc,rc.right,rc.bottom);
			SelectObject(hcdc,hcbmp);
						}
						break;
		case WM_PAINT: {

			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd,&ps);

			RECT rc1 = { 0,0,(m.mx * 10)+10, (m.my * 10)+20 };
			FillRect(hcdc,&rc1,(HBRUSH)(COLOR_3DFACE+1));
			draw_font_win32(hcdc);
			drawColorbar(dc);
			drawButtons(dc);
			RECT rc;
			GetWindowRect(hwnd,&rc);
			BitBlt(dc,0,0,m.mx * 10+10,m.my * 10+20,hcdc,0,0,SRCCOPY);
			EndPaint(hwnd, &ps);
					   }
					   break;
		case WM_LBUTTONDOWN: {
			int x = LOWORD(lParam), y = HIWORD(lParam);
			PlacePixel(LOWORD(lParam), HIWORD(lParam),cur_color);
			if(x >= m.mx * 10+20 && x <= m.mx * 10+20+25 && y >= 225 && y <= 225+25) {
				eraser_up = true;
				RECT rc = {m.mx * 10+20,225,m.mx * 10+20+25, 255+25 };
				InvalidateRect(hwnd,&rc,TRUE);
			}
			if(x >= m.mx * 10+20+30 && x <= m.mx * 10+20+30+25 && y >= 225 && y <= 225+25) {
				pencil_up = true;
				RECT rc = {m.mx * 10+20+30,225,m.mx * 10+20+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
			}

			if(x >= m.mx * 10 + 20+30+30 && x <= m.mx * 10 + 20+30+30+25 && y >= 225 && y <= 225+25)
			{
				fill_up = true;
				RECT rc = { m.mx * 10+20+30+30,225,m.mx * 10+20+30+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
			}

			int offset_x = (m.mx * 10)+20;
			int offset_y = 70+25+5+13+5+13+20+30;
			if(x >= offset_x && x <= offset_x+100 && y >= offset_y && y <= offset_y+10) {
				int color = chooseColor();
				if(color != -1)
					cur_color = color;
				drawColorbar(GetDC(hwnd));
			}

		 }
		 break;
		case WM_LBUTTONUP: {
			int x = LOWORD(lParam), y = HIWORD(lParam);
			if(x >= m.mx * 10+20 && x <= m.mx * 10+20+25 && y >= 225 && y <= 225+25) {
				eraser_up = false;
				RECT rc = {m.mx * 10+20,225,m.mx * 10+20+25, 255+25 };
				InvalidateRect(hwnd,&rc,TRUE);
				the_tool = ERASER;
				SendMessage(htool,WM_SETTEXT,255,(LPARAM)(LPCSTR)"[ Eraser ]");
			}
			else {
				eraser_up = false;
				RECT rc = {m.mx * 10+20,225,m.mx * 10+20+25, 255+25 };
				InvalidateRect(hwnd,&rc,TRUE);
			}

			if(x >= m.mx * 10+20+30 && x <= m.mx * 10+20+30+25 && y >= 225 && y <= 225+25) {
				pencil_up = false;
				RECT rc = {m.mx * 10+20+30,225,m.mx * 10+20+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
				the_tool = BRUSH;
				SendMessage(htool,WM_SETTEXT,255,(LPARAM)(LPCSTR)"[ Pencil ]");
			}
			else {
				RECT rc = {m.mx * 10+20+30,225,m.mx * 10+20+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
				pencil_up = false;
			}

			if(x >= m.mx * 10 + 20+30+30 && x <= m.mx * 10 + 20+30+30+25 && y >= 225 && y <= 225+25) {
				fill_up = false;
				the_tool = FILL;
				RECT rc = { m.mx * 10+20+30+30,225,m.mx * 10+20+30+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
				SendMessage(htool,WM_SETTEXT,255,(LPARAM)(LPCSTR)"[ Fill ]");
			}
			else {
				fill_up = false;
				RECT rc = { m.mx * 10+20+30+30,225,m.mx * 10+20+30+30+25, 225+25 };
				InvalidateRect(hwnd,&rc,TRUE);
			}

						   }
						   break;
		case WM_MOUSEMOVE: {
			if(wParam & MK_LBUTTON) {
				PlacePixel(LOWORD(lParam), HIWORD(lParam), cur_color);
			}
						   }
						   break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
		case BN_CLICKED:
			switch(LOWORD(wParam)) {
		case ID_GENC: {
			char datar[256];
			char datag[256];
			char datab[256];
			SendMessage(edr,WM_GETTEXT,256,(LPARAM)(LPCSTR)datar);
			SendMessage(edg,WM_GETTEXT,256,(LPARAM)(LPCSTR)datag);
			SendMessage(edb,WM_GETTEXT,256,(LPARAM)(LPCSTR)datab);
			cur_color = RGB(atoi(datar),atoi(datag),atoi(datab));
			int offset_x = (m.mx * 10)+20;
			int offset_y = 70+25+5+13+5+13+20+30;
			RECT rc = { offset_x-1, offset_y-1, offset_x+101,offset_y+11 };
			InvalidateRect(hwnd,&rc,TRUE);

					  }
					  break;


			}
			break;
		case CBN_SELCHANGE:
			switch(LOWORD(wParam)) {
		case ID_COMBO: {
			updateCombo();
			break;
					   }
			}
			break;
			}

			switch(wParam) {
		case ID_FILE_EXIT:
			PostQuitMessage(0);
			break;
		case ID_HELP_ABOUT:
			ShowWindow(habout,SW_SHOW);
			break;
		case ID_FILE_NEW40003:
			if(MessageBox(hwnd,"Are you sure you wish to create a new Font?", "New Font", MB_YESNO | MB_ICONQUESTION) == IDYES) {
				ShowWindow(hnew,SW_SHOW);
			}
			break;
		case ID_FILE_SAVE40005:
			if(strcmp(str_fname, "Untitled.mxf") == 0)
				SendMessage(hwnd,WM_COMMAND,ID_FILE_SAVEAS,0);
			else
				write_font(&m, str_fname);
			break;
		case ID_FILE_SAVEAS: {
			char str_new_name[MAX_PATH];
			if(savefile(str_new_name) == true) {
				strcpy(str_fname,str_new_name);
				write_font(&m,str_fname);
				updateTitle();
			}
							 }
							 break;
		case ID_FILE_OPEN40004: {
			char str_new_name[MAX_PATH];
			if(openfile(str_new_name) == true) {
				strcpy(str_fname,str_new_name);
				free_font(&m);
				read_font(&m, str_fname);
				updateTitle();
				RECT rc = {0,0,1024,768 };
				InvalidateRect(hwnd,&rc,TRUE);
				SendMessage(comb,CB_SETCURSEL,0,0);
				updateCombo();
			}
								}
								break;
		case ID_EDIT_OPTIONS:
			ShowWindow(hoptions,SW_SHOW);
			break;
		case ID_EDIT_SETTRANSPARENTCOLOR: {
			char dat[255];
			sprintf(dat,"Transparent color set to %x",cur_color);
			m.tcolor = cur_color;
			MessageBox(hwnd,dat,"Set Color",MB_OK | MB_ICONINFORMATION);

										  }
										  break;
	   case ID_EDIT_CONVERTFONT : {
		       the_font = chooseFont(&cur_color);
			   if(the_font != 0) {
				   HDC dc = GetDC(hwnd);
				   SelectObject(dc,the_font);
				   char fntName[MAX_PATH];
				   GetTextFace(dc, LF_FULLFACESIZE, fntName);
				   SendMessage(edfnt,WM_SETFONT,(WPARAM)(HFONT)the_font,FALSE);
				   SendMessage(edfnt, WM_SETTEXT, (int)strlen(fntName),(LPARAM)(LPCSTR)fntName);
				   ShowWindow(hconv,SW_SHOW);
			   }
		    }
		    break;
			
		case ID_EDIT_INSERTBITMAP:
			{
				char bmp_file[MAX_PATH];
				if(openbitmap(bmp_file)) {
					HBITMAP hbm;
					BITMAP bm;
					hbm = (HBITMAP)LoadImage(NULL, bmp_file, IMAGE_BITMAP,0,0,LR_LOADFROMFILE | LR_CREATEDIBSECTION);

					if(hbm == NULL) { MessageBox(hwnd,"Error Couldnt Load Bitmap!", "Error", MB_ICONERROR | MB_OK); break; }
					GetObject(hbm, sizeof(bm), &bm);
					if(bm.bmHeight != m.my || bm.bmWidth != m.mx) {
						if(MessageBox(hwnd,"Image not same size would you like to resize?", "Resize Bitmap", MB_YESNO | MB_ICONQUESTION) == IDYES) {
							resizeBitmap(hbm,bm);
						}
					}
					else
						resizeBitmap(hbm,bm);
				}
			}
			break;
			}
			}
			break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}


// about callback function
LRESULT CALLBACK AboutProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {

	static bool under_lined = false;
	static HCURSOR hCurCursor = LoadCursor(NULL,IDC_HAND);
	static HCURSOR hPrevCursor = 0;

	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE: {
			under_fnt = CreateFont(17,0, 0, 0, FW_NORMAL, FALSE, TRUE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Arial");
			reg_fnt = CreateFont(17,0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,VARIABLE_PITCH,"Arial");
			char txtstr[] = "This software is complety free\r\nYou may use it and distrubite it as you please\r\nOnly it is at your own risk\r\n written by Jared Bruni\r\n\r\n\r\n Special Thanks go to:\r\nPlanetSourceCode.com\r\nOpcodeVoid and EmuPaul\r\nBeta testers\r\nSkater\r\n All the girlys\r\n";
			HWND ed = CreateWindowEx(WS_EX_STATICEDGE,"Edit",txtstr,WS_CHILD | WS_VISIBLE | ES_MULTILINE | WS_VSCROLL | ES_READONLY,10,160,380,400-114-100,hwnd,0,GetModuleHandle(0),0);

			}
			break;
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC dc = BeginPaint(hwnd,&ps);
			HDC dc_mem = CreateCompatibleDC(dc);
			SelectObject(dc_mem,hlogo);
			StretchBlt(dc,5,5,385,114,dc_mem,0,0,339,114,SRCCOPY);
			if(!under_lined)
				SelectObject(dc,(HFONT)reg_fnt);
			else
				SelectObject(dc,(HFONT)under_fnt);
			SetBkColor(dc,RGB(168,172,177));
			SetTextColor(dc,RGB(0,0,255));
			char str[] = "visit LostSideDead.com";
			TextOut(dc,20,125,(char*)str, (int)strlen(str));
			EndPaint(hwnd,&ps);
			DeleteDC(dc_mem);
			 }
			  break;
		case WM_MOUSEMOVE: {
			int x = LOWORD(lParam) , y = HIWORD(lParam);
			if(x >= 20 && x <= 175 && y >= 125 && y <= 150) {
				under_lined = true;
				hPrevCursor = SetCursor(hCurCursor);
				RECT rc = { 20,125, 175,150 };
				InvalidateRect(hwnd,&rc,TRUE);
			}
			else if(under_lined == true) {
				under_lined = false;
				RECT rc = { 20,125, 175,150 };
				InvalidateRect(hwnd,&rc,TRUE);
				SetCursor(hPrevCursor);
			}
						   }
						   break;
		case WM_LBUTTONDOWN: {
			int x = LOWORD(lParam) , y = HIWORD(lParam);
			if(x >= 20 && x <= 175 && y >= 125 && y <= 150) {
				ShellExecute(NULL,"open","http://www.lostsidedead.com",NULL,NULL,SW_SHOW);
			}
							 }
							 break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}

// create new font callback
LRESULT CALLBACK NewProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	static HWND hcreate,heditw,hedith;
	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE: {
			hcreate = CreateWindow("Button", "Create", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 250-100-10,250-65,100,25,hwnd,(HMENU)ID_NEW,GetModuleHandle(0),0);
			HWND st4 = CreateWindow("Static", "Width", WS_CHILD | WS_VISIBLE,10,45-25,100,25,hwnd,0,GetModuleHandle(0),0);
			heditw = CreateWindow("Edit","20", WS_CHILD | WS_VISIBLE | WS_BORDER, 10,45,225,25,hwnd,0,GetModuleHandle(0),0);
			HWND st5 = CreateWindow("Static", "Height", WS_CHILD | WS_VISIBLE, 10,45+30,225,25,hwnd,0,GetModuleHandle(0),0);
			hedith = CreateWindow("Edit","25",WS_CHILD | WS_VISIBLE | WS_BORDER,10,45+30+25,225,25,hwnd,0,GetModuleHandle(0),0);
						}
						break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
		case BN_CLICKED: {
			switch(LOWORD(wParam)) {
		case ID_NEW:
			char datw[255];
			char dath[255];
			SendMessage(heditw, WM_GETTEXT,255,(LPARAM)(LPCSTR)datw);
			SendMessage(hedith, WM_GETTEXT,255,(LPARAM)(LPCSTR)dath);
			int w = atoi(datw);
			int h = atoi(dath);
			if(w == 0 || h == 0 || w < 20 || h < 20 || w > 40 || h > 40 ) {
				MessageBox(hwnd,"Invalid Width/Height", "Invalid Input", MB_OK | MB_ICONERROR);
				break;
			}

			init_font(&m,w,h,0x0);
			ShowWindow(hwnd,SW_HIDE);
			sizeWindow();
			strcpy(str_fname,"Untitled.mxf");
			updateTitle();
			break;
			}
						 }
						 break;
		 }
						 }
						 break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}

inline void convertFont() {
	HDC dc = GetDC(hconv);
	SelectObject(dc,the_font);
	SetBkColor(dc,RGB(0,0,0));
	SetTextColor(dc,cur_color);
	int cur_letters = 0;
	RECT rc = {0,0,200,200};
	for(int p = 0; p < 127; p++) {
		char dat[2];
		dat[0] = p;
		dat[1] = 0;
		FillRect(dc,&rc,(HBRUSH) GetStockObject(BLACK_BRUSH));
		TextOut(dc,0,0,dat,(int)strlen(dat));
		if(cur_letters != -1)
	for(int i = 0; i < m.mx; i++)
		for(int z = 0; z < m.my; z++)
		{
			int pixel = GetPixel(dc,i,z);
			m.letters[p].fnt_ptr[i][z] = pixel;
		}
	}
	RECT rc1 = {0,0,640,480};
	InvalidateRect(hconv,&rc,TRUE);
	InvalidateRect(fhwnd,&rc1,TRUE);
	SendMessage(comb,CB_SETCURSEL,'a',0);
}



LRESULT CALLBACK ConvertProc(HWND hwnd, UINT msg,WPARAM wParam, LPARAM lParam) {

	

	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE: {
			edfnt = CreateWindow("Edit","Font Name", WS_CHILD | WS_VISIBLE | WS_BORDER |ES_READONLY, 10,10,170,25,hwnd,0,GetModuleHandle(0),0);
			but1 = CreateWindow("Button", "Create", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 80,40,100,25,hwnd,(HMENU)1,GetModuleHandle(0),0);

			}
			break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
			case BN_CLICKED:
				switch(LOWORD(wParam)) {
				case 1:
					convertFont();
					updateCombo();
					ShowWindow(hwnd,SW_HIDE);
					SendMessage(comb,WM_SETFONT,(WPARAM)(HFONT)the_font,0);
				break;
				}
			break;
			}
		}
	    break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}

	return 0;
}
// from Shell Tutorial on PSC
inline void associateMXF() {
	bool ret = TRUE;
	HKEY hKey;
	SECURITY_ATTRIBUTES sa = {sizeof(sa), 0,1};
	DWORD state = 0;
	char *szTitle = "mxFont.Open";
	char szAppName[256];
	GetModuleFileName(NULL, szAppName, 256);


	RegCreateKeyEx(HKEY_CLASSES_ROOT, ".mxf",0,NULL,0,KEY_ALL_ACCESS, 0, &hKey, &state);
	if (state != 2) {
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)szTitle, (DWORD)strlen(szTitle));
		RegCloseKey(hKey);
	}
	else {
		RegCloseKey(hKey);
		ret = FALSE;
	}
	state=0;
	RegCreateKeyEx(HKEY_CLASSES_ROOT, szTitle, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);


	RegCreateKeyEx(hKey, "DefaultIcon", 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);
	if (state != 2) {
		strcat(szAppName, ",0");
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)szAppName, (DWORD)strlen(szAppName));
		RegCloseKey(hKey);
	}
	else {
		RegCloseKey(hKey);
		ret = FALSE;
	}

	state = 0;


	RegCreateKeyEx(HKEY_CLASSES_ROOT, szTitle, 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);
	RegCreateKeyEx(hKey, "shell", 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);
	RegCreateKeyEx(hKey, "open", 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);
	RegCreateKeyEx(hKey, "command", 0, NULL, 0, KEY_ALL_ACCESS, 0, &hKey, &state);
	if (state != 2) {
		GetModuleFileName(NULL, szAppName, 256);
		RegSetValueEx(hKey, NULL, 0, REG_SZ, (BYTE*)szAppName, (DWORD) strlen(szAppName));
		RegCloseKey(hKey);
	}
	else {
		RegCloseKey(hKey);
		ret = FALSE;
	}
	state = 0;
	SHChangeNotify(SHCNE_ASSOCCHANGED , SHCNF_IDLIST, NULL, NULL);
	MessageBox(fhwnd,"Successfully Associated this application with .mxf files.\n", "Worked", MB_ICONINFORMATION);

}
// from PSC Shell Tutorial
inline void unassociateMXF() {
	if(SHDeleteKey(HKEY_CLASSES_ROOT, "mxFont.Open\\") != ERROR_SUCCESS)
		MessageBox(NULL, "Error Couldnt Delete Registry Entry", "Error...", MB_OK | MB_ICONERROR);
	if(SHDeleteKey(HKEY_CLASSES_ROOT, ".mxf\\") != ERROR_SUCCESS) {
		MessageBox(NULL, "Error: Could not delete file extension registry entry", "Error...", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	SHChangeNotify(SHCNE_ASSOCCHANGED , SHCNF_IDLIST, NULL, NULL);
	MessageBox(fhwnd,"Successfully UnAssociated this application with .mxf files.\n", "Worked", MB_ICONINFORMATION);
}

// option callback function
LRESULT CALLBACK OptProc(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam) {
	static HWND hbt1, hbt2;
	switch(msg) {
		case WM_CLOSE:
			ShowWindow(hwnd,SW_HIDE);
			break;
		case WM_CREATE: {
			hbt1 = CreateWindow("Button", "Assosciate .mxf", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,10,10,150,25,hwnd,(HMENU)1,GetModuleHandle(0),0);
			hbt2 = CreateWindow("Button", "Unassociate .mxf", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,10,35,150,25,hwnd,(HMENU)2,GetModuleHandle(0),0);
						}
						break;
		case WM_COMMAND: {
			switch(HIWORD(wParam)) {
		case BN_CLICKED:
			switch(LOWORD(wParam)) {
		case 1: {
			associateMXF();
			ShowWindow(hwnd,SW_HIDE);
				}
				break;
		case 2: {
			unassociateMXF();
			ShowWindow(hwnd,SW_HIDE);
				}
				break;
			}
			break;
			}
						 }
						 break;
		default:
			return DefWindowProc(hwnd,msg,wParam,lParam);
	}
	return 0;
}
// load bitmaps
inline void Load() {
	heraser = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP1));
	heraser_up = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP2));
	hpencil = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP3));
	hpencil_up = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP4));
	hfill = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP5));
	hfill_up = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP6));
	hlogo = LoadBitmap(GetModuleHandle(0),MAKEINTRESOURCE(IDB_BITMAP7));
}

// inititilzation
void Init() {
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH) (COLOR_3DFACE+1);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_ICON1));
	wc.hInstance = GetModuleHandle(0);
	wc.lpfnWndProc = (WNDPROC) WndProc;
	wc.lpszClassName = "mxFontEditor";
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);

	wc.lpszMenuName = NULL;
	wc.lpszClassName = "mxAbout";
	wc.lpfnWndProc = (WNDPROC) AboutProc;
	RegisterClassEx(&wc);

	wc.lpszClassName = "mxNew";
	wc.lpfnWndProc = (WNDPROC) NewProc;
	RegisterClassEx(&wc);

	wc.lpszClassName = "mxOptions";
	wc.lpfnWndProc = (WNDPROC) OptProc;
	RegisterClassEx(&wc);

	wc.lpszClassName = "mxConvert";
	wc.lpfnWndProc = (WNDPROC) ConvertProc;

	RegisterClassEx(&wc);

	InitCommonControls();

	Load();
	fhwnd = CreateWindow("mxFontEditor", "Mx Font Editor", WS_SYSMENU | WS_MINIMIZEBOX,CW_USEDEFAULT,CW_USEDEFAULT,m.mx * 10 + 150,m.my * 10 + 100,0,0,GetModuleHandle(0),0);
	habout = CreateWindow("mxAbout","About this software",  WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,400,400,0,0,GetModuleHandle(0),0);
	hnew = CreateWindow("mxNew", "Create New mxFont",  WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,250,250,0,0,GetModuleHandle(0),0);
	hoptions = CreateWindow("mxOptions", "Options", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,180,100,0,0,GetModuleHandle(0),0);
	hconv = CreateWindow("mxConvert", "Convert Font", WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT,CW_USEDEFAULT,200,110,0,0,GetModuleHandle(0),0);
	updateTitle();
	ShowWindow(fhwnd,SW_SHOW);
	UpdateWindow(fhwnd);

}
// clean up
void Clean() {
	free_font(&m);
	DeleteObject(heraser);
	DeleteObject(the_font);
	DeleteObject(heraser_up);
	DeleteObject(hpencil);
	DeleteObject(hpencil_up);
	DeleteObject(hfill);
	DeleteObject(hfill_up);
	DeleteObject(hlogo);
	DeleteObject(hcbmp);
	DeleteDC(hcdc);
}
// Loop
int Loop() {
	MSG msg;
	while(GetMessage(&msg,0,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Clean();
	return (int)msg.wParam;
}

// windows entry point
int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpszLine, int nCmdShow) {
	if(strlen(lpszLine) == 0) {
		strcpy(str_fname, "Untitled.mxf");
		init_font(&m, 20,25, 0);
	}
	else {
		if(lpszLine[0] == '\"')
			lpszLine++;
		if(lpszLine[strlen(lpszLine)-1] == '\"')
			lpszLine[strlen(lpszLine)-1] = 0;
		strcpy(str_fname, lpszLine);
		read_font(&m,str_fname);
	}
	Init();
	return Loop();
}
