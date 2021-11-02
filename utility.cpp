#include "utility.hpp"

void option_t::dump() {
	std::cerr << "src: " << src_filename << '\n';
	std::cerr << "dst: " << dst_filename << '\n';
	switch (dst_tabtype) {
		case none: {
			std::cerr << "dst tabtype: none" << '\n';
			break;
		}
		case tab: {
			std::cerr << "dst tabtype: tab" << '\n';
			break;
		}
		case spc: {
			std::cerr << "dst tabtype: spc" << '\n';
			break;
		}
		case auto_: {
			std::cerr << "dst tabtype: auto" << '\n';
		}
	}
	std::cerr << "space length: " << spclen << '\n';
}

option_t parse_option(int argc, char const *argv[]) {
	if (argc == 1) {
		return option_t("", "", auto_, 2);
	}else if (argc == 2) {
		if (std::string(argv[1]) == "-t") {
			// to tab, input from the standard input, output to the standard output
			return option_t("", "", tab, 0);
		}
		if (*std::string(argv[1]).begin() == '-') {
			throw std::invalid_argument(std::string("parse_option: ")+argv[1]);
		}
		return option_t(std::string(argv[1]), "", auto_, 0);
	}else if (argc == 3) {
		if (std::string(argv[1]) == "-t") {
			// to tab, input from the file, output to the standard output
			if (*std::string(argv[2]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[2]);
			}
			return option_t(std::string(argv[2]), "", tab, 0);
		}else if (std::string(argv[1]) == "-s") {
			// to space, input from the standard input, output to the standard output
			int tmp = std::stoi(argv[2]);
			return option_t("", "", spc, tmp);
		}else {
			// auto, input from the file, output to the file
			return option_t(std::string(argv[1]), std::string(argv[2]), auto_, 2);
		}
	}else if (argc == 4) {
		if (std::string(argv[1]) == "-t") {
			// to tab, input from the file, output to the file
			if (*std::string(argv[2]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[2]);
			}
			if (*std::string(argv[3]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[3]);
			}
			return option_t(std::string(argv[2]), std::string(argv[3]), tab, 0);
		}else if (std::string(argv[1]) == "-s") {
			// to space, input from the file, output to the standard output
			int tmp = std::stoi(argv[2]);
			if (*std::string(argv[3]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[3]);
			}
			return option_t(std::string(argv[3]), "", spc, tmp);
		}else {
			throw std::invalid_argument(std::string("parse_option: ")+argv[1]);
		}
	}else if (argc == 5) {
		// to space, input from the file, output from the file
		if (std::string(argv[1]) == "-s") {
			int tmp = std::stoi(argv[2]);
			if (*std::string(argv[3]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[3]);
			}
			if (*std::string(argv[4]).begin() == '-') {
				throw std::invalid_argument(std::string("parse_option: ")+argv[4]);
			}
			return option_t(std::string(argv[3]), std::string(argv[4]), spc, tmp);
		} else {
			throw std::invalid_argument(std::string("parse_option: ")+argv[1]);
		}
	}else {
		throw std::invalid_argument("parse_option: Too many command line arguments.");
	}
	return option_t("", "", auto_, 2);
}
