/* Copyright 2016 Henry Elliott
 *
 * This file is part of cs_add.
 *
 * cs_add is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cs_add is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with cs_add.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include <random>
#include <limits>
#include <chrono>
#include <gmp.h>

#include "cs_add.h"

int main()
{
	std::numeric_limits<mp_limb_t> lim;
	std::mt19937 gen(0x42);
	std::uniform_int_distribution<mp_limb_t> dist(lim.min(), lim.max());

	std::vector<mp_limb_t> a1(400000000);
	auto a2 = a1;
	auto res = a2;

	auto size = a1.size();
	for (decltype(a1.size()) i = 0; i != size; ++i) {
		a1[i] = dist(gen);
		a2[i] = dist(gen);
	}

	std::chrono::time_point<std::chrono::system_clock> start, stop;

	start = std::chrono::system_clock::now();
	mpn_cs_add_n(res.data(), a1.data(), a2.data(), a1.size());
	stop = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = stop - start;
	std::cout << "mpn_cs_add_n time: " << elapsed.count() << "s\n";
	std::cout << res[res.size() - 1] << "\n";

	start = std::chrono::system_clock::now();
	mpn_add_n(res.data(), a1.data(), a2.data(), a1.size());
	stop = std::chrono::system_clock::now();
	elapsed = stop - start;
	std::cout << "mpn_add_n time: " << elapsed.count() << "s\n";
	std::cout << res[res.size() - 1] << "\n";
}
