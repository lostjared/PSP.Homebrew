#pragma once
#include<stdio.h>
#include<stdlib.h>
// a quick cheat for vector
template<typename type>
class mvector {
public:
	mvector() {

		offset = 0;
		data = 0;
	}
	~mvector() {


		if(data) {
			free(data);
			offset = 0;
			data = 0;
		}

	}

	void clean() {
		if(data) {
			free(data);
			offset = 0;
			data = 0;
		}
	}

	void push_back(type t) {

		data = (type*) realloc(data, sizeof(type) * (++offset) );
		memcpy(data+(offset-1), &t, sizeof(t));

	}

	type &operator[](int i) {
		return data[i];
	}

	void erase(unsigned int , unsigned int) {
		clean();
	}

	unsigned int begin() { return 0; }
	unsigned int end() { return offset; }
	unsigned int size() { return offset; }
	unsigned int empty() { if(data) return 1; return 0; }

private:
	int offset;
	type *data;
};