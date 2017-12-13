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
#include "heuristic.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <random>
#include <vector>

using dl = std::numeric_limits<double>;
using std::all_of;
using std::cout;
using std::fabs;
using std::fixed;
using std::queue;
using std::random_device;
using std::reverse;
using std::sqrt;
using std::swap;
using std::vector;

vector<Node> Solution::coords = vector<Node>{};
vector<unsigned int> Solution::demand = vector<unsigned int>{};
double Solution::avg_dist = 0;

/* Empty constructor */
Solution::Solution()
	: r_int(0, 100)
	, r_double(0.0, 1.0)
	, perm()
	, orig()
{}

/* Copy constructor */
Solution::Solution(Solution const &other)
	: r_int(0, (unsigned int)Solution::coords.size() - 1)
	, r_double(0.0, 1.0)
	, perm(other.perm)
	, orig(other.orig)
{}

/* Parametrized constructor */
Solution::Solution(unsigned int n)
	: r_int(0, n - 1)
	, r_double(0.0, 1.0)
	, perm()
	, orig(n, true)
{
	perm.reserve(n);
	orig.back() = true;

	for (unsigned int i = 0; i < n; i++)
		perm.push_back(i);
}

/* Bit flip for neighbor generation */
void Solution::flip(void)
{
	/* At least one 1 bit is required, so flip until condition is met */
	random_device rd;
	do {
		/* Flip random bit */
		unsigned to_flp = r_int(rd);
		orig.at(to_flp) = !orig.at(to_flp);
	} while (all_of(orig.begin(), orig.end(), [](bool i) { return !i; }));
}

/* 2-opt for neighbor generation */
void Solution::kopt(void)
{
	/* Choose 2 random indexes. Force them to be different. */
	random_device rd;
	unsigned int m;
	unsigned int n;
	do {
		m = r_int(rd);
		n = r_int(rd);
	} while (m == n);

	/* Force m to be smaller than n */
	if (m > n)
		swap(m, n);

	/* Reverse nodes from index m to n, effectively doing 2-opt */
	reverse(perm.begin() + m, perm.begin() + n);
}

/* Find any neighbor */
void Solution::any_neighbor(void)
{
	/* Randomly do bit-flip or 2-opt */
	random_device rd;
	if (r_double(rd) < 0.5)
		flip();
	else
		kopt();
}

/* Evaluate current solution cost */
double Solution::eval(double threshold)
{
	/* Get solution cost. If infesaible, punish evaluation. */
	double cost = 0.0;
	unsigned int k = (unsigned int)Solution::coords.size();

	/* Start from the deposit */
	unsigned int st = 0;
	while (!orig.at(perm.at(st++)));

	/* Store money and risk for each vehicle loop */
	unsigned int v_money = 0;
	double v_risk = 0;

	/* Variables to improve code legibility */
	double dx;
	double dy;
	double dist;

	/* Oterate through each vehicle loop */
	for (unsigned int i = 0; i < k; i++) {
		/* Check if coming from deposit */
		if (orig.at(perm.at((st + i - 1 + k) % k))) {
			v_money = 0;
			v_risk = 0;

			/* Get distance from deposit to current node */
			dx = coords.at(perm.at((i + st) % k)).x;
			dy = coords.at(perm.at((i + st) % k)).y;
			dist = sqrt(dx * dx + dy * dy);

			/* Add cost, update money and risk */
			cost += dist;
			v_risk += 0;
			v_money += demand.at(perm.at((i + st) % k));
		}

		/* Check if going to deposit, else add node-node distance */
		if (orig.at(perm.at((st + i) % k))) {
			/* Distance to deposit */
			dx = coords.at(perm.at((i + st) % k)).x;
			dy = coords.at(perm.at((i + st) % k)).y;
			dist = sqrt(dx * dx + dy * dy);

			/* Add cost, update money and risk */
			cost += dist;
			v_risk += v_money * dist;
			v_money += 0;
		} else {
			/* Distance to next node */
			dx = coords.at(perm.at((i + st) % k)).x;
			dy = coords.at(perm.at((i + st) % k)).y;
			dx -= coords.at(perm.at((i + st + 1) % k)).x;
			dy -= coords.at(perm.at((i + st + 1) % k)).y;
			dist = sqrt(dx * dx + dy * dy);

			/* Add cost, risk and money */
			cost += dist;
			v_risk += v_money * dist;
			v_money += demand.at(perm.at((i + st) % k));
		}

		/*
		 * Check if solution is infeasible and punish it.
		 * Punishment is done by adding the risk of carrying current
		 * money through the average distance between nodes to the cost.
		 */
		if (v_risk > threshold)
			cost += v_money * avg_dist;
	}

	return cost;
}

/* Initialize solution by a greedy method */
void Solution::greedy_init(void)
{
	/* Calculate average distance between nodes. */
	avg_dist = Heuristic::avg_dist(coords);
	/* Generate initial solution using a pseudo-prim algorithm */
	Heuristic::prim(coords, perm);
}

/* Method to get solution size  */
unsigned int Solution::size(void)
{
	return (unsigned int)Solution::coords.size();
}

/* Methods to add coordinates to solution */
void Solution::push_back(Node n)
{
	Solution::coords.push_back(n);
}

/* Print a solution sub-circuits */
void Solution::print(double threshold)
{
	/* Total cost */
	cout.precision(6);
	cout << fixed << eval(threshold) << '\n';

	/* Required cars*/
	unsigned int cars = (unsigned int)count(orig.begin(), orig.end(), true);
	cout << cars << '\n';

	/* Queue of print-pending circuits (each represented as a vector) */
	queue< vector<unsigned int> > circuits;

	/* Move to the start of a circuit */
	unsigned int n = (unsigned int)orig.size();
	unsigned int st = 0;
	while (!orig.at(perm.at(st++)));

	/* Iterate through and add each circuit to queue */
	for (unsigned int i = 0; i < n; i++) {
		if (orig.at(perm.at((st + i - 1 + n) % n)))
			circuits.push(vector<unsigned int>{});
		circuits.back().push_back(perm.at((st + i) % n));
	}

	/* For each circuit print cost, risk and nodes */
	while (!circuits.empty()) {
		vector<unsigned int> circuit = circuits.front();
		circuits.pop();
		unsigned int m = (unsigned int)circuit.size();

		/* Temporary variables */
		double risk = 0.0;
		double cost = 0.0;
		unsigned int money = 0;

		/* Useful variables (improve legibility) */
		double dx;
		double dy;
		double dist;

		/* Distance & risk from deposit to first node */
		dx = coords.at(circuit.at(0)).x;
		dy = coords.at(circuit.at(0)).y;
		dist = sqrt(dx * dx + dy * dy);

		/* Move from deposit to first node */
		cost += dist;
		risk += dist * money;
		money += demand.at(circuit.at(0));

		/* Distance & risk among nodes */
		for (unsigned int i = 0; i < m - 1; i++) {
			dx = coords.at(circuit.at(i)).x;
			dy = coords.at(circuit.at(i)).y;
			dx -= coords.at(circuit.at(i + 1)).x;
			dy -= coords.at(circuit.at(i + 1)).y;
			dist = sqrt(dx * dx + dy * dy);

			cost += dist;
			risk += money * dist;
			money += demand.at(circuit.at(i));
		}

		/* Distance & risk from last node to deposit */
		dx = coords.at(circuit.at(m - 1)).x;
		dy = coords.at(circuit.at(m - 1)).y;
		dist = sqrt(dx * dx + dy * dy);

		cost += dist;
		risk += money * dist;

		/* Print cost, risk & route */
		cout << fixed << cost << '\t' << fixed << risk << "\t0";
		for (unsigned int i = 0; i < m; i++)
			cout << "->" << circuit.at(i) + 1;
		cout << "->0" << '\n';
	}
}
