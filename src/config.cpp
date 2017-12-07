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

#include "config.h"
#include <thread>

using std::thread;

struct rcvrp_cfg ctx;

void parse_cfg(int const argc, char const **argv)
{
	(void)argc;
	(void)argv;

	/* Set defaults */
	ctx.max_temp = 100.0;
	ctx.risk_threshold = 1024.0;
	ctx.temperature = 128.0;
	ctx.temp_multiplier = 0.98;
	ctx.max_cars = 64;
	ctx.max_cities = 64;
	ctx.max_deposites = 1;
	ctx.max_iter = 0;
	ctx.max_ms = 1024;
	ctx.max_neighbors = 8;
	ctx.rd_seed = 0;
	ctx.threads = thread::hardware_concurrency();

	/* Parse argument vector */

	/* Parse environment variables */

}
