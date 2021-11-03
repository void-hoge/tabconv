# TAB CONVERTER
tabconv: A simple tab and space converter.

## Usage
```
$ tabconv src dst
$ tabconv [-s <num of spc> | -t] src dst
```
- -s \<num of spc\>
  - Convert to space
- -t
  - Convert to tab
- (none)
  - Auto

## Example
```
$ cat main.cpp
#include <iostream>

int main(int argc, char const *argv[]) {
	if (argc == 1) {
		std::cout << "hello world" << '\n';
	}else {
		std::cout << "hello" << '\n';
	}
	return 0;
}
$ tabconv main.cpp
#include <iostream>

int main(int argc, char const *argv[]) {
  if (argc == 1) {
    std::cout << "hello world" << '\n';
  }else {
    std::cout << "hello" << '\n';
  }
  return 0;
}
$ tabconv -s 4 main.cpp spc.cpp
$ cat spc.cpp
#include <iostream>

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        std::cout << "hello world" << '\n';
    }else {
        std::cout << "hello" << '\n';
    }
    return 0;
}
$ cat spc.cpp | tabconv
#include <iostream>

int main(int argc, char const *argv[]) {
	if (argc == 1) {
		std::cout << "hello world" << '\n';
	}else {
		std::cout << "hello" << '\n';
	}
}
$
```
