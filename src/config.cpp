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
#include <string>
#include <cstdlib>

using std::stof;
using std::stoul;
using std::thread;
using std::string;
using std::getenv;

struct rcvrp_cfg ctx;

void parse_cfg(int const argc, char const **argv)
{
	(void)argc;
	(void)argv;

	/* Set defaults */
	ctx.risk_threshold = 0.0;
	ctx.temp_multiplier = 0.98;
	ctx.temperature = 128.0;
	ctx.max_iter = 0;
	ctx.max_ms = 256;
	ctx.threads = thread::hardware_concurrency();

	/* Parse environment variables */
	if (getenv("MULTIPLIER"))
		ctx.temp_multiplier = stof(getenv("MULTIPLIER"));
	if (getenv("TEMPERATURE"))
		ctx.temperature = stof(getenv("TEMPERATURE"));
	if (getenv("ITERATIONS"))
		ctx.max_iter = (unsigned int)stoul(getenv("ITERATIONS"));
	if (getenv("LOOPTIME"))
		ctx.max_ms = (unsigned int)stoul(getenv("LOOPTIME"));
	if (getenv("THREADS"))
		ctx.threads = (unsigned int)stoul(getenv("THREADS"));

}
