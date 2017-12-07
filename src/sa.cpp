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

#include "eval.h"
#include "sa.h"
#include "temperature.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>

using hrc = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::default_random_engine;
using std::exp;
using std::random_shuffle;
using std::swap;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

vector<unsigned int> sa(vector<Node> const &coords)
{
	/* Initial solution by random shuffling */
	vector<unsigned int> sol;
	sol.reserve(coords.size());
	for (unsigned int i = 0; i < coords.size(); i++)
		sol.push_back(i);
	random_shuffle(sol.begin(), sol.end());

	/* Prepare variables for neighbors and PRNGs */
	vector<unsigned int> best{sol};
	vector<unsigned int> neigh{sol};
	Temperature t(100.0f);

	default_random_engine rd;
	uniform_int_distribution<unsigned int>
	    rd_int(0, (unsigned int)coords.size() - 1);
	uniform_real_distribution<float> rd_float(0.0, 1.0);

	/* Iterate through neighbors in a time window */
	hrc::time_point start = hrc::now();
	do {
		/* Create random neighbor by doing 2-opt on random indexes */
		unsigned int m = 0;
		unsigned int n = 0;
		while (m == n) {
			m = rd_int(rd);
			n = rd_int(rd);
		}
		if (m > n)
			swap(m, n);
		vector<unsigned int> nxt_neigh{neigh};
		reverse(nxt_neigh.begin() + m, nxt_neigh.begin() + n);

		float diff = eval(coords, neigh) - eval(coords, nxt_neigh);
		/* If neighbor is better, switch to it */
		if (diff > 0.0f)
			neigh = nxt_neigh;
		/* Or maybe switch to it */
		else if (rd_float(rd) < exp(diff / t()))
			neigh = nxt_neigh;
		/* And maybe the new one is the best one so far */
		if (eval(coords, neigh) > eval(coords, best))
			best = neigh;
	} while (duration_cast<ms>(hrc::now() - start) <= ms(ctx.max_ms));

	return best;
}
