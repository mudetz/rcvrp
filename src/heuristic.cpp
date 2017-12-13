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

#include "heuristic.h"
#include "node.h"
#include "geometry.h"
#include <vector>
#include <limits>
#include <algorithm>

using std::swap;
using std::vector;
using dl = std::numeric_limits<double>;

/* Pseudo prim for initial solutions */
void Heuristic::prim(vector<Node> &coords, vector<unsigned int> &perm)
{
	/* For each node, set the next neighbor as the closest remaining node */
	for (unsigned int i = 0; i < perm.size() - 1; i++) {
		unsigned int best_node = (unsigned int)perm.size() - 1;
		double best_dist = dl::infinity();
		for (unsigned int j = i + 1; j < perm.size(); j++) {
			Node &a = coords.at(perm.at(i));
			Node &b = coords.at(perm.at(j));
			if (Geometry::dist(a, b) < best_dist) {
				best_dist = Geometry::dist(a, b);
				best_node = j;
			}
		}
		swap(perm.at(i + 1), perm.at(best_node));
	}
}

/* Get average distance between every node */
double Heuristic::avg_dist(vector<Node> &coords)
{
	unsigned int N = (unsigned int)coords.size();
	double total = 0.0;

	/* Distances to origin */
	Node origin{0, 0};
	for (unsigned int i = 0; i <  N; i++)
		total += Geometry::dist(coords.at(i), origin);

	/* Distances among nodes */
	for (unsigned int i = 0; i < N - 1; i++)
		for (unsigned int j = i + 1; j < N; j++)
			total += Geometry::dist(coords.at(i), coords.at(j));

	return total / (N + (N * (N - 1) / 2));
}
