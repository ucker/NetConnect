#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "get_url.h"
using namespace std;
string get_url(string text) {
	string qr_string = "";
	//cout<<"the context is ";
	//cout<<text<<endl;
	for (auto it = text.begin(); it != text.end(); it++)
	{
		if (*it == 'p')
		{
			if (*(it + 1) == 'a' & *(it + 2) == 's' & *(it + 3) == 's' & *(it + 4) == 'w' & *(it + 5) == 'o')
			{
				if (*(it + 6) == 'r' & *(it + 7) == 'd' )
				{
					it += 7;
					while (*(++it) != '"');
					while (*(++it) != '"');
					while (*(++it) != '"')
					{
						qr_string += *it;
					}
					break;
				}
			}
		}
	}
	return qr_string;
}
