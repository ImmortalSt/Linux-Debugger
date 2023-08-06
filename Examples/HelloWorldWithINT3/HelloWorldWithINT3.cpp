#include <iostream>


int main() {
	while (true) {
		asm ( "INT3" );
		std::cout << "Hello\n";
	}
}
