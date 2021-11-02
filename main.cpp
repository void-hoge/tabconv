#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <fstream>

#include "utility.hpp"

void input(std::vector<std::string>& data, std::istream& is = std::cin) {
	std::string tmp;
	while (std::getline(is, tmp)) {
		data.push_back(tmp);
	}
}

void dump(std::vector<std::string>& data, std::ostream& os = std::cout) {
	for (const auto& a: data) {
		os << a << '\n';
	}
	os << '\n';
}

std::string tab_to_spc(const std::string& src, const int tabnum) {
	std::string tmp;
	std::size_t tabcount = 0;
	while (tabcount < src.length() && src.at(tabcount) == '\t') {
		tabcount++;
	}
	for (std::size_t j = 0; j < tabnum*tabcount; j++) {
		tmp.append(" ");
	}
	tmp.append(src.substr(tabcount, src.size()-tabcount));
	return tmp;
}

std::string spc_to_tab(const std::string& src, const int tablen) {
	std::string tmp;
	std::size_t spccount = 0;
	while (spccount < src.length() && src.at(spccount) == ' ') {
		spccount++;
	}
	for (std::size_t j = 0; j < (spccount/tablen)+((spccount%tablen)!=0); j++) {
		tmp.append("\t");
	}
	tmp.append(src.substr(spccount, src.size()-spccount));
	return tmp;
}

std::string spc_to_spc(const std::string& src, const int srcspc, const int dstspc) {
	std::string tmp;
	std::size_t spccount = 0;
	while (spccount < src.length() && src.at(spccount) == ' ') {
		spccount++;
	}
	for (std::size_t i = 0; i < ((spccount/srcspc)+((spccount%srcspc)!=0))*dstspc; i++) {
		tmp.append(" ");
	}
	tmp.append(src.substr(spccount, src.size()-spccount));
	return tmp;
}

int spc_analyze(const std::vector<std::string>& src) {
	std::size_t result = 0;
	if (src.size() > 0) {
		std::size_t spccount = 0;
		while (spccount < src.at(0).length() && src.at(0).at(spccount) == ' ') {
			spccount++;
		}
		result = spccount;
		for (std::size_t i = 1; i < src.size(); i++) {
			spccount = 0;
			while (spccount < src.at(i).length() && src.at(i).at(spccount) == ' ') {
				spccount++;
			}
			int tmp = std::gcd(result, spccount);
			if (tmp == 1) {
				std::cerr << "Line " << i+1 << " ignored. (Probably incorrect tab length)" << '\n';
			}else {
				result = tmp;
			}
		}
	}
	return result;
}

tabtype spc_or_tab(const std::vector<std::string>& src) {
	for (const auto& line: src) {
		if (line != "") {
			if (*line.begin() == ' ') {
				return spc;
			} else if (*line.begin() == '\t') {
				return tab;
			}
		}
	}
	return none;
}

int main(int argc, char const *argv[]) {
	auto opt = parse_option(argc, argv);
	std::vector<std::string> data;
	if (opt.src_filename != "") {
		std::ifstream ifs(opt.src_filename);
		if (ifs.is_open()) {
			input(data, ifs);
		}else {
			throw std::invalid_argument(std::string("cannot open ")+opt.src_filename);
		}
		ifs.close();
	}else {
		input(data);
	}
	if (opt.dst_tabtype == auto_) {
		opt.dst_tabtype = 1-spc_or_tab(data);
		if (opt.dst_tabtype == spc) {
			opt.spclen = 2;
		}else if (opt.dst_tabtype == tab) {
			opt.spclen = spc_analyze(data);
		}
	}else if (opt.dst_tabtype == tab) {
		opt.spclen = spc_analyze(data);
	}
	// opt.dump();
	if (opt.dst_filename != "") {
		std::ofstream ofs(opt.dst_filename);
		if (ofs.is_open()) {
			if (opt.dst_tabtype == tab) {
				for (const auto& line: data) {
					ofs << spc_to_tab(line, opt.spclen) << '\n';
				}
			}else if (opt.dst_tabtype == spc && spc_or_tab(data)){
				int tmp = spc_analyze(data);
				for (const auto& line: data) {
					ofs << spc_to_spc(line, tmp, opt.spclen) << '\n';
				}
			}else {
				for (const auto& line: data) {
					ofs << tab_to_spc(line, opt.spclen) << '\n';
				}
			}
		}else {
			throw std::invalid_argument(std::string("cannot open ")+opt.dst_filename);
		}
	}else {
		if (opt.dst_tabtype == tab) {
			for (const auto& line: data) {
				std::cout << spc_to_tab(line, opt.spclen) << '\n';
			}
		}else if (opt.dst_tabtype == spc && spc_or_tab(data)){
			int tmp = spc_analyze(data);
			// std::cout << tmp << '\n';
			for (const auto& line: data) {
				std::cout << spc_to_spc(line, tmp, opt.spclen) << '\n';
			}
		}else {
			for (const auto& line: data) {
				std::cout << tab_to_spc(line, opt.spclen) << '\n';
			}
		}
	}
	return 0;
}
