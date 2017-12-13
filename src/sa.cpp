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

#include "sa.h"
#include "temperature.h"
#include "config.h"
#include "timer.h"
#include <chrono>
#include <cmath>
#include <random>

using std::exp;
using std::fabs;
using std::random_device;
using unif_dbl_d = std::uniform_real_distribution<double>;

#if BENCHMARK
#include <iostream>
using std::fixed;
using std::cerr;
#endif

Solution sa(Solution sol, double risk)
{
	/* Initial greedy solution */
	sol.greedy_init();

	/* Prepare variables for neighbors, PRNGs and thermometer */
	Solution best{sol};
	Solution neigh{sol};
	Temperature t(ctx.temperature);

	random_device rd;
	unif_dbl_d rd_double(0.0, 1.0);

	/* Iterate through neighbors in a time window */
	Timer timer;

/* Maybe we want to see the value of each neightbor */
#if BENCHMARK
		cerr.precision(6);
#endif
	do {
#if BENCHMARK
			cerr << fixed << neigh.eval(risk) << '\n';
#endif
		/* Copy current solution and generate a neighbor from it */
		Solution nneigh{neigh};
		nneigh.any_neighbor();

		/* Evaluate them and get the difference */
		double diff = neigh.eval(risk) - nneigh.eval(risk);

		/* If neighbor is better, switch to it */
		if (diff > 0.0f)
			neigh = nneigh;
		/* Or maybe just switch to it randomly */
		else if (rd_double(rd) < exp(diff / t()))
			neigh = nneigh;
		/* And check if the new one is the best one so far */
		if (neigh.eval(risk) < best.eval(risk))
			best = neigh;
	/* Until time is up */
	} while (timer.loop_incomplete(ctx.max_ms));

	return best;
}
