///////////////////////////////////////////////////////////////////////////////
///
///	\file    TriangularQuadrature.cpp
///	\author  Paul Ullrich
///	\version September 1, 2014
///
///	<remarks>
///		Copyright 2000-2014 Paul Ullrich
///
///		This file is distributed as part of the Tempest source code package.
///		Permission is granted to use, copy, modify and distribute this
///		source code and its documentation under the terms of the GNU General
///		Public License.  This software is provided "as is" without express
///		or implied warranty.
///	</remarks>

#include "TriangularQuadrature.h"

#include <cstring>

///////////////////////////////////////////////////////////////////////////////

TriangularQuadratureRule::TriangularQuadratureRule(
	int nOrder
) {
	// 8th order quadrature rule (16 points)
	if (nOrder == 8) {
		const double TriQuadratureG[16][3] = {
			{0.333333333333333, 0.333333333333333, 0.333333333333333},
			{0.081414823414554, 0.459292588292723, 0.459292588292723},
			{0.459292588292723, 0.081414823414554, 0.459292588292723},
			{0.459292588292723, 0.459292588292723, 0.081414823414554},
			{0.658861384496480, 0.170569307751760, 0.170569307751760},
			{0.170569307751760, 0.658861384496480, 0.170569307751760},
			{0.170569307751760, 0.170569307751760, 0.658861384496480},
			{0.898905543365938, 0.050547228317031, 0.050547228317031},
			{0.050547228317031, 0.898905543365938, 0.050547228317031},
			{0.050547228317031, 0.050547228317031, 0.898905543365938},
			{0.008394777409958, 0.263112829634638, 0.728492392955404},
			{0.008394777409958, 0.728492392955404, 0.263112829634638},
			{0.263112829634638, 0.008394777409958, 0.728492392955404},
			{0.263112829634638, 0.728492392955404, 0.008394777409958},
			{0.728492392955404, 0.263112829634638, 0.008394777409958},
			{0.728492392955404, 0.008394777409958, 0.263112829634638}};

		const double TriQuadratureW[16] =
			{0.144315607677787,
			 0.095091634267285, 0.095091634267285, 0.095091634267285,
			 0.103217370534718, 0.103217370534718, 0.103217370534718,
			 0.032458497623198, 0.032458497623198, 0.032458497623198,
			 0.027230314174435, 0.027230314174435, 0.027230314174435,
			 0.027230314174435, 0.027230314174435, 0.027230314174435};

		m_nPoints = 16;

		m_dG.Initialize(16, 3);
		memcpy(&(m_dG[0][0]), &(TriQuadratureG[0][0]), 16 * 3 * sizeof(double));

		m_dW.Initialize(16);
		memcpy(&(m_dW[0]), &(TriQuadratureW[0]), 16 * sizeof(double));

	// 4th order quadrature rule (6 points)
	} else if (nOrder == 4) {

		const double TriQuadratureG[6][3] = {
			{0.108103018168070, 0.445948490915965, 0.445948490915965},
			{0.445948490915965, 0.108103018168070, 0.445948490915965},
			{0.445948490915965, 0.445948490915965, 0.108103018168070},
			{0.816847572980458, 0.091576213509771, 0.091576213509771},
			{0.091576213509771, 0.816847572980458, 0.091576213509771},
			{0.091576213509771, 0.091576213509771, 0.816847572980458}};

		const double TriQuadratureW[6] =
			{0.223381589678011, 0.223381589678011, 0.223381589678011,
			 0.109951743655322, 0.109951743655322, 0.109951743655322};

		m_nPoints = 6;

		m_dG.Initialize(6, 3);
		memcpy(&(m_dG[0][0]), &(TriQuadratureG[0][0]), 6 * 3 * sizeof(double));

		m_dW.Initialize(6);
		memcpy(&(m_dW[0]), &(TriQuadratureW[0]), 6 * sizeof(double));

	// 1st order quadrature rule (1 point)
	} else if (nOrder == 1) {

		m_dG.Initialize(1, 3);
		m_dG[0][0] = 0.333333333333333;
		m_dG[0][1] = 0.333333333333333;
		m_dG[0][2] = 0.333333333333333;

		m_dW[0] = 1.000000000000000;

	// Unsupported order
	} else {
		_EXCEPTIONT("Unsupported order of TriangularQuadratureRule");
	}
}

///////////////////////////////////////////////////////////////////////////////

