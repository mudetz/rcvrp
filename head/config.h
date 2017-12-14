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

#ifndef __config_h__
#define __config_h__

/* Store configuration in a struct */
struct rcvrp_cfg {
	double risk_threshold;
	double temp_multiplier;
	double temperature;
	unsigned int max_iter;
	unsigned int max_ms;
	unsigned int threads;
	unsigned int v_cap;
};

/* A static global struct */
extern struct rcvrp_cfg ctx;

/* Parse user configuration */
void parse_cfg(int const argc, char const **argv);

#endif
