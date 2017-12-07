#
# RCVRP
# A Simulated Annealing solver for the Risk-constrained Cash-in-transit VRP
# Copyright (C) 2017  Manuel Weitzman
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#

from random import random as random

N = 1024

print(N)
print(float(N))

print(*[0 for i in range(N)])

for _ in range(N):
	print(N * random(), N * random())
