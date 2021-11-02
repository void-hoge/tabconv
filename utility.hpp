#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include <iostream>
#include <string>


using tabtype = int;
const tabtype none = -1;
const tabtype tab = 0;
const tabtype spc = 1;
const tabtype auto_ = 4;

struct option_t {
	std::string src_filename;
	std::string dst_filename;
	tabtype dst_tabtype;
	int spclen;
	option_t(): dst_tabtype(none), spclen(0) {}
	option_t(std::string src, std::string dst, tabtype t, int l): src_filename(src), dst_filename(dst), dst_tabtype(t), spclen(l) {}
	void dump();
};

option_t parse_option(int argc, char const *argv[]);

#endif /* end of include guard: UTILITY_HPP_INCLUDED */
