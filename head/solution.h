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

#ifndef __solution_h__
#define __solution_h__

#include "node.h"
#include <vector>
#include <random>

class Solution {
private:
	std::uniform_int_distribution<unsigned> r_int;
	std::uniform_real_distribution<float> r_double;

	void flip(void);
	void kopt(void);
public:
	static std::vector<Node> coords;
	static std::vector<unsigned int> demand;
	std::vector<unsigned int> perm;
	std::vector<bool> orig;

	Solution();
	Solution(unsigned int n);
	Solution(Solution const &other);

	void any_neighbor(void);
	double eval(double threshold);
	void greedy_init(void);
	unsigned int size(void);
	void push_back(Node n);
	void print(double threshold);
};


#endif
