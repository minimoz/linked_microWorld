/**
* moz
*/

#include						"APrimaryItem.hpp"

APrimaryItem::APrimaryItem() {
	_methodPtr = nullptr;
	_quantity = 0;
}

APrimaryItem::APrimaryItem(methodPtrType methodPtr, int quantity) {
	_methodPtr = methodPtr;
	_quantity = quantity;
}

APrimaryItem::~APrimaryItem() {
}

void							APrimaryItem::setQuantity(int quantity) {
	_quantity = quantity;
}

int								APrimaryItem::getQuantity() {
	return (_quantity);
}