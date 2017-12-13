/*
 * RCVRP
 * A Simulated Annealing solver for the Risk-constrained Cash-in-transit VRP
 * Copyright (C) 2017  Manuel Weitzman
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "temperature.h"
#include "config.h"

double Temperature::operator() (void)
{
	/* Update temperature every fixed amount of iterations. */
	double r = this->curr;
	if (this->curr > 1 && this->it++ % ctx.max_iter == 0) {
		this->curr *= ctx.temp_multiplier;
		this->it = 0;
	}
	return r;
}
