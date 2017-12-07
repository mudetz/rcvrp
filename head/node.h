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

#ifndef __node_h__
#define __node_h__

class Node {
public:
	double x;
	double y;
	bool orig;
	Node()
		: x(0)
		, y(0)
		, orig(false)
	{}
	Node(double _x, double _y)
		: x(_x)
		, y(_y)
		, orig(false)
	{}
	Node(double _x, double _y, bool _orig)
		: x(_x)
		, y(_y)
		, orig(_orig)
	{}
	~Node() {}
};

#endif
