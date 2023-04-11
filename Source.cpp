#include <iostream>
using namespace std;

int main(void)
{
	string x;
	std::cout << ("input a string") << endl;
	std::cin >> x;
	std::cout << x;
	int temp = 0;
	int n = 0;
	for (n; n < 7 || n == NULL, n++;) { //or is ascii value != to 65 through 122
		if (x.at(n + 1) == '\0') { //find lenght of strong without .getstring
			temp = n;
		}
	}
	//temp = x.length();
	std::cout << temp;
	int y = 0;
	for (y; y < temp; y++) {
	
		if (x.at(y) != x.at(temp - y)) {
			cout << x.at(temp) << "   " << x.at(temp - y);
			std::cout << "false";
		}
	}
	for (int y = 0; y < temp; y++) {

			if (x.at(y) == x.at(temp - y)) {
				cout << x.at(temp) << "   " << x.at(temp - y);
				std::cout << "true";
			}
		
	}


	return 0;

}