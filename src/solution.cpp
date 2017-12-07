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

#include "solution.h"
#include <numeric>
#include <algorithm>
#include <cmath>
#include <limits>
#include <random>

using std::sqrt;
using std::all_of;
using std::swap;
using std::reverse;
using std::sort;
using std::fabs;
using std::random_device;
using dl = std::numeric_limits<double>;

Solution::Solution()
	: r_int(0, 100)
	, r_double(0.0, 1.0)
	, coords()
	, perm()
	, orig()
{}

Solution::Solution(Solution const &other)
	: r_int(0, (unsigned int)other.coords.size() - 1)
	, r_double(0.0, 1.0)
	, coords(other.coords)
	, perm(other.perm)
	, orig(other.orig)
{}

Solution::Solution(unsigned int n)
	: r_int(0, n - 1)
	, r_double(0.0, 1.0)
	, coords()
	, perm()
	, orig(n, false)
{
	coords.reserve(n);
	perm.reserve(n);
	orig.back() = false;

	for (unsigned int i = 0; i < n; i++)
		perm.push_back(i);
}

void Solution::flip(void)
{
	random_device rd;
	do {
		unsigned to_flp = r_int(rd);
		orig.at(to_flp) = !orig.at(to_flp);
	} while (all_of(orig.begin(), orig.end(), [](bool i) { return !i; }));
}

void Solution::kopt(void)
{
	random_device rd;
	unsigned int m;
	unsigned int n;
	do {
		m = r_int(rd);
		n = r_int(rd);
	} while (m == n);

	if (m > n)
		swap(m, n);
	reverse(perm.begin() + m, perm.begin() + n);
}

void Solution::any_neighbor(void)
{
	random_device rd;
	if (r_double(rd) < 0.25)
		flip();
	else
		kopt();
}

double Solution::eval(void)
{
	double cost = 0.0;
	unsigned int k = (unsigned int)coords.size();

	for (unsigned int i = 0; i < k; i++) {
		/* Check if returning to deposit */
		if (orig.at(perm.at(i))) {
			double dx;
			double dy;

			/* Cost to return to deposit from current point */
			dx = coords.at(perm.at(i)).x;
			dy = coords.at(perm.at(i)).y;
			cost += sqrt(dx * dx + dy * dy);

			/* Cost to get from deposit to next point */
			dx = coords.at((i + 1) % k).x;
			dy = coords.at((i + 1) % k).y;
			cost += sqrt(dx * dx + dy * dy);
		} else {
			double dx;
			double dy;

			dx = coords.at(perm.at(i)).x;
			dx -= coords.at(perm.at((i + 1) % k)).x;

			dy = coords.at(perm.at(i)).y;
			dy -= coords.at(perm.at((i + 1) % k)).y;

			/* Cost to next point */
			cost += sqrt(dx * dx + dy * dy);
		}
	}

	return cost;
}

void Solution::greedy_init(void)
{
	sort(perm.begin(), perm.end(), [&](unsigned a, unsigned b) {
		if (fabs(coords.at(a).x - coords.at(b).x) <= dl::epsilon())
			return coords.at(a).y <= coords.at(b).y;
		return coords.at(a).x <= coords.at(b).x;
	});
}

unsigned int Solution::size(void)
{
	return (unsigned int)coords.size();
}

void Solution::push_back(Node n)
{
	coords.push_back(n);
}
