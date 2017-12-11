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

#include "timer.h"

using hrc = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;
using std::chrono::duration_cast;

Timer::Timer(void)
	: start{hrc::now()}
{}

bool Timer::loop_incomplete(unsigned int looptime)
{
	return duration_cast<ms>(hrc::now() - start) < ms(looptime);
}
