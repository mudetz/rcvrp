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
#include "config.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <limits>
#include <random>

using dl = std::numeric_limits<float>;
using hrc = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using std::chrono::duration_cast;
using std::exp;
using std::fabs;
using std::random_device;
using std::sort;
using std::swap;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::vector;

vector<unsigned int> sa(vector<Node> const &coords)
{
	/* Initial greedy solution by sorting */
	vector<unsigned int> sol;
	sol.reserve(coords.size());
	for (unsigned int i = 0; i < coords.size(); i++)
		sol.push_back(i);
	sort(sol.begin(), sol.end(), [&coords](unsigned &a, unsigned &b) {
		if (fabs(coords.at(a).x - coords.at(b).x) <= dl::epsilon())
			return coords.at(a).y < coords.at(b).y;
		return coords.at(a).x < coords.at(b).x;
	});

	/* Prepare variables for neighbors and PRNGs */
	vector<unsigned int> best{sol};
	vector<unsigned int> neigh{sol};
	Temperature t(ctx.temperature);

	random_device rd;
	uniform_int_distribution<unsigned int>
	    rd_int(0, (unsigned int)coords.size() - 1);
	uniform_real_distribution<double> rd_double(0.0, 1.0);

	/* Iterate through neighbors in a time window */
	hrc::time_point start = hrc::now();
	do {
		/* Create random neighbor by doing 2-opt on random indexes */
		unsigned int m;
		unsigned int n;
		do {
			m = rd_int(rd);
			n = rd_int(rd);
		} while (m == n);
		if (m > n)
			swap(m, n);

		vector<unsigned int> nxt_neigh{neigh};
		reverse(nxt_neigh.begin() + m, nxt_neigh.begin() + n);

		double diff = eval(coords, neigh) - eval(coords, nxt_neigh);

		/* If neighbor is better, switch to it */
		if (diff > 0.0f)
			neigh = nxt_neigh;
		/* Or maybe just switch to it */
		else if (rd_double(rd) < exp(diff / t()))
			neigh = nxt_neigh;
		/* And check if the new one is the best one so far */
		if (eval(coords, neigh) < eval(coords, best))
			best = neigh;
	} while (duration_cast<ms>(hrc::now() - start) <= ms(ctx.max_ms));

	return best;
}
