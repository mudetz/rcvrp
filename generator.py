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

from __future__ import print_function
from random import random as random
from random import randrange as randrange
from sys import argv as argv

N = int(argv[1])

print(N)
print(float(N * (N - 1) // 2))

print(*[randrange(1, N / 2) for i in range(N)])

for _ in range(N):
	print(randrange(1, N / 2) * random(), randrange(1, N / 2) * random())
