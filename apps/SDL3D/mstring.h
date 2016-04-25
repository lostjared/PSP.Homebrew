#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// a quick cheat for string
// since WinCE dosent support STL

class mstring {
public:
	mstring() {
		ptr = 0;
	}

	mstring(const char *str) {
		ptr = 0;
		ptr = (char*) realloc(ptr, sizeof(char) * strlen(str) + 2 );
		strncpy(ptr,str,strlen(str));
		ptr[strlen(str)] = 0;
		
	}
	~mstring() {
		if(ptr != 0)
	        free(ptr);
	}
	mstring(const mstring &s) {
		if(s.ptr) {
		ptr = (char*) malloc ( sizeof(char) * (strlen(s.ptr) + 2) );
		strncpy(ptr,s.ptr,strlen(s.ptr));
		ptr[strlen(s.ptr)] = 0;
		}

	}

	const char *c_str() {
		if(ptr)
		return ptr;
		return "";
	}

	void operator=(const mstring &s) {
		if(s.ptr) {
			assign(s.ptr);
		}
	}

	mstring& operator+=(const mstring &s) {
		concat(s.ptr);
		return *this;
	}

	mstring& operator+=(const char *s) {
		concat(s);
		return *this;
	}

	mstring& operator+=(const char c) {
		char buf[2];
		buf[0] = c;
		buf[1] = 0;
		concat(buf);
		return *this;
	}

	mstring& operator+(const mstring &s) {
		concat(s.ptr);
		return *this;
	}

	mstring& operator+(const char *s) {
		concat(s);
		return *this;
	}
	char operator[](size_t i) {
		return ptr[i];
	}

	friend bool operator<(const mstring &s, const mstring &s2) {
		if(strcmp(s.ptr,s2.ptr) < 0)
			return true;
		return false;
	}

	friend bool operator==(const mstring &s, const mstring &s2) {
		if(strcmp(s.ptr, s2.ptr) == 0)
			return true;
		return false;
	}

	friend bool operator>(const mstring &s, const mstring &s2) {
		if(strcmp(s.ptr,s2.ptr) > 0)
			return true;
		return false;
	}

	friend bool operator!=(const mstring &s, const mstring &s2) {
		if(strcmp(s.ptr,s2.ptr))
			return true;
		return false;
	}

	size_t length() {
		return strlen(c_str());
	}

private:
	char *ptr;

	void assign(const char *s) {
		if(ptr) {
			free(ptr);
			ptr = 0;
		}
		ptr = (char*) malloc ( sizeof(char) * (strlen(s)+2));
		strncpy(ptr,s,strlen(s));
		ptr[strlen(s)] = 0;
	}

	void concat(const char *s) {
		if(ptr) {
		char *tptr = (char*) malloc ( sizeof(char) * (strlen(s)+2) );
		strncpy(tptr,ptr,strlen(ptr));
		tptr[strlen(ptr)] = 0;
		if(ptr) {
			free(ptr);
			ptr = 0;
		}
		ptr = (char*) malloc ( sizeof(char) * ( strlen(tptr) + strlen(s) +2 ) );
		strncpy(ptr,tptr, strlen(tptr));
		ptr[strlen(tptr)] = 0;
		strncat(ptr,s,strlen(s));
		ptr[strlen(tptr) + strlen(s)] = 0;
		free(tptr);
		}
		else {
			ptr = (char*) malloc ( sizeof(char) * (strlen(s) + 2));
			strncpy(ptr,s,strlen(s));
		}
	}
};  
