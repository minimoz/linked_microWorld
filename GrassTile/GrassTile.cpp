// GrassTile.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GrassTile.hpp"

#include <stdexcept> // after the other includes

// Trace de pas sur les tiles d'herbe pouvant rester 3-4 tours (permettre aux joueurs de se retrouver)
double GrassTile::GrassTile_Divide(double a, double b) {
	if (b == 0) {
		throw std::invalid_argument("b cannot be zero!");
	}

	return a / b;
}
