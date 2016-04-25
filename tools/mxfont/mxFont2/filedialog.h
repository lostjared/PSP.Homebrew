#ifndef __THE_DIALOG__H_
#define __THE_DIALOG__H_
#include<windows.h>
#include<commdlg.h>
#include<stdio.h>

bool openfile(char* cFile)
{
	char szFile[MAX_PATH];
	char title[MAX_PATH];
	sprintf(title,"Open Mx Font");


	OPENFILENAME ofn;       // common dialog box structure

	strcpy(szFile, "*.mxf");

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetForegroundWindow();
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "mx font\0*.mxf\0ALL\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = title;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.hInstance = GetModuleHandle(0);
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetOpenFileName(&ofn)==TRUE)
	{
		strcpy(cFile, ofn.lpstrFile);
		return true;
	}
	else
	{
		return false;
	}

}

extern HWND fhwnd;

bool openbitmap(char* cFile)
{
	char szFile[MAX_PATH];
	char title[MAX_PATH];
	sprintf(title,"Open Bitmap");



	OPENFILENAME ofn;       // common dialog box structure

	int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep);
		strcpy(szFile, "*.bmp\0\0");

		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = "Bitmap\0*.bmp\0ALL\0*.*\0\0";
		ofn.nFilterIndex = 2;
		ofn.lpstrFileTitle = title;
		ofn.nMaxFileTitle = MAX_PATH;
		ofn.lpstrInitialDir = NULL;
		ofn.hInstance = GetModuleHandle(0);
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetOpenFileName(&ofn)==TRUE)
		{
			strcpy(cFile, ofn.lpstrFile);
			return true;
		}
		else
		{
			return false;
		}

	
	return false;

}

inline DWORD chooseColor() {

	CHOOSECOLOR cc;
	static COLORREF acrCustClr[16]; 

	HBRUSH hbrush;                 
	static DWORD rgbCurrent;        


	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = fhwnd;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc)==TRUE) {
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult; 
		return rgbCurrent;

	}
	else
		return -1;
}

extern int cur_color;

inline HFONT chooseFont(int *rgb) {                

	CHOOSEFONT cf;            
	static LOGFONT lf;        
	static DWORD rgbCurrent;  
	HFONT hfont;
	// Initialize CHOOSEFONT
	ZeroMemory(&cf, sizeof(cf));
	cf.lStructSize = sizeof (cf);
	cf.hwndOwner = fhwnd;
	cf.lpLogFont = &lf;
	cf.rgbColors = cur_color;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

	if (ChooseFont(&cf)==TRUE) {
		hfont = CreateFontIndirect(cf.lpLogFont);
		rgbCurrent= cf.rgbColors;
		*rgb = rgbCurrent;
		return hfont;
	}
	return NULL;
}
int filter(unsigned int code, struct _EXCEPTION_POINTERS *ep) {



	if (code == 0x7c809eec) {
		MessageBox(0,"HERE","HERE",MB_OK);
		return EXCEPTION_EXECUTE_HANDLER;

	}

	else {

		return EXCEPTION_CONTINUE_SEARCH;

	};

}

bool savefile(char* cFile)
{

	char szFile[MAX_PATH];
	char szTitle[MAX_PATH];

	OPENFILENAME ofn;// common dialog box structure
	sprintf(szTitle,"Save Mx Font");
	strcpy(szFile, "*.mxf");

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = GetForegroundWindow();
	ofn.lpstrFile = szFile;
	ofn.hInstance = GetModuleHandle(0);
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "mx font\0*.mxf\0ALL\0*.*\0\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = szTitle;
	ofn.nMaxFileTitle = MAX_PATH;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


	if (GetSaveFileName(&ofn)==TRUE)
	{
		strcpy(cFile, ofn.lpstrFile);
		return true;
	}
	else
	{
		return false;
	}


}

#endif
