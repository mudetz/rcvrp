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
#include <cmath>

using std::sqrt;

double eval(vector<Node> const &coords, vector<unsigned int> const &sol)
{
	double cost = 0.0;
	unsigned int k = (unsigned int)coords.size();

	for (unsigned int i = 0; i < k; i++) {
		double dx = coords.at(sol.at(i)).x
		    - coords.at(sol.at((i + 1) % k)).x;
		double dy = coords.at(sol.at(i)).y
		    - coords.at(sol.at((i + 1) % k)).y;
		cost += sqrt(dx * dx + dy * dy);
	}

	return cost;
}

unsigned int max_arch(vector<Node> const &coords, vector<unsigned int> &sol)
{
	unsigned int ans = 0;
	double max_cost = 0.0;
	unsigned int k = (unsigned int)coords.size();

	for (unsigned int i = 0; i < k; i++) {
		double dx = coords.at(sol.at(i)).x
		    - coords.at(sol.at((i + 1) % k)).x;
		double dy = coords.at(sol.at(i)).y
		    - coords.at(sol.at((i + 1) % k)).y;
		double dist = sqrt(dx * dx + dy * dy);
		if (dist > max_cost) {
			max_cost = dist;
			ans = i;
		}
	}
	return ans;
}
