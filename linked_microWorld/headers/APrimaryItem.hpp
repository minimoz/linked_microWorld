/**
* moz
*/

#ifndef								APRIMARYITEM_HPP__
# define							APRIMARYITEM_HPP__

# include							<iostream>

# include							"Iitem.hpp"
# include							"PersonBody.hpp"

class								Iitem;
class								PersonBody;

class								APrimaryItem : public Iitem {
private:
	typedef void					(PersonBody::*methodPtrType)(const APrimaryItem &);

	methodPtrType					_methodPtr;
	int								_quantity;

public:
	APrimaryItem();
	APrimaryItem(methodPtrType, int);
	~APrimaryItem();

	void							setQuantity(int);

	int								getQuantity();

};

#endif								/* APRIMARYITEM_HPP__ */
