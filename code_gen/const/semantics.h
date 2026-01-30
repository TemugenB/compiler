#ifndef SEMANTICS_H
#define SEMANTICS_H

#include<iostream>
#include<string>
#include<map>
#include<sstream>

enum type { integer, boolean };

struct expression_descriptor {
	type expr_type;
	std::string expr_code;
	expression_descriptor(type t, std::string s) {
		expr_type = t;
		expr_code = s;
	}
};

struct var_data {
	int decl_row;
	type decl_type;
    std::string label;
    // 0 = mutable, 1 = const (unassigned), 2 = const (assigned)
    int const_state;

    var_data(){}
    
    // Default c to 0 (regular variable)
    var_data(int i, type t, std::string l, int c = 0)
    {
        decl_row = i;
        decl_type = t;
        label = l;
        const_state = c;
    }

};

#endif
