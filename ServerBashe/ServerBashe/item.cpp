#include "item.h"
#include <iostream>

using namespace std;

Item::Item(int itemCount) {
	iCount = itemCount;
}

void Item::plusItem(int plusI) {
	iCount += plusI;
}

void Item::minusItem(int minusI) {
	iCount -= minusI;

	if (iCount < 0) {
		iCount = 0;
	}
}

int Item::amountItem() {
	return iCount;
}

string Item::Print() {

	string str;

	if (iCount > 0) {
		for (int i = 0; i < iCount; i++) str += "***  ";
		str += "\n";
		for (int i = 0; i < iCount; i++) str += "* *  ";
		str += "\n";
		for (int i = 0; i < iCount; i++) str += "***  ";
		str += "\n";
	}
	return str;
}