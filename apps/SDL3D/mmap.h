#pragma once 

#include"mvector.h"

// a quick cheat for a map
// this is not really a map since I didnt know how to implement it
// feel free to *PROPER* me :)

template<class type1, class type2>
class m_map {
public:
	struct m_pair {
		type1 t;
		type2 t2;
		m_pair() { t = ""; t2 = type2(); }
		m_pair(type1 &s, type2 s2) {
			t = s;
			t2 = s2;
		}
		m_pair(const m_pair &p) {
			t = p.t;
			t2 = p.t2;
		}
	};

	type2 &operator[](type1 &t) {
		for(i = 0; i < m.size(); i++)
			if(m[i].t == t)
				return m[i].t2;
		return m.push_back( *new m_pair(t,type2())).t2;
	}
		
private:
	mvector<m_pair> m; 
	size_t i;

};