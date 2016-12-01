/**
* moz
*/

#ifndef								IITEM_HPP__
# define							IITEM_HPP__

# include							<iostream>

class								Iitem {

public:
	// ?
	enum IitemType {

	};

	~Iitem() {};

	virtual void					setQuantity(int) = 0;

};

#endif								/* IITEM_HPP__ */
