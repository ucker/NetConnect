/*
	Author: netsimpler@163.com
	Date: 2017-4-22
*/
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "QrCode.hpp"
#include "convert_qrcode.h"

std::string convert_qrcode(std::string text) {
	std::string qr_string = "";
	std::cout<<"the context is ";
	std::cout<<text<<std::endl;
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
	std::cout << qr_string << '\n';
	const qrcodegen::QrCode::Ecc &errCorLvl = qrcodegen::QrCode::Ecc::LOW;
	const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(qr_string.c_str(), errCorLvl);
	std::string qr_svg = qr.toSvgString(4);
	return qr_svg;
}
