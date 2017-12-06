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

struct rcvrp_cfg {
	float max_temp;
	float temp_multiplier;
	unsigned int max_cars;
	unsigned int max_cities;
	unsigned int max_deposites;
	unsigned int max_iter;
	unsigned int max_ms;
	unsigned int max_neighbors;
	unsigned int rd_seed;
	unsigned int risk_threshold;
	unsigned int threads;
};

extern struct rcvrp_cfg ctx;

void parse_cfg(int const argc, char const **argv);

#endif
