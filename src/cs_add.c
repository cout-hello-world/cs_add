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
#include "cs_add.h"

#include <gmp.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct addition {
	const mp_limb_t *first;
	const mp_limb_t *second;
	mp_limb_t *res;
	mp_size_t size;
	mp_limb_t carry;
};

static void *add_zero(void *param)
{
	struct addition *zero = param;
	zero->carry =
	    mpn_add_n(zero->res, zero->first, zero->second, zero->size);
	return NULL;
}

static void *add_one(void *param)
{
	mp_limb_t carry0, carry1;
	struct addition *one = param;
	carry0 = mpn_add_1(one->res, one->first, one->size, 1);
	carry1 = mpn_add_n(one->res, one->first, one->second, one->size);
	one->carry = (carry0 > carry1) ? carry0 : carry1;
	return NULL;
}

mp_limb_t mpn_cs_add_n(mp_limb_t *rp, const mp_limb_t *s1p,
	               const mp_limb_t *s2p, mp_size_t n)
{
	mp_size_t first_size = n / 2;
	mp_size_t second_size = n - first_size;
	pthread_t one_thread, zero_thread;
	mp_limb_t *one_buffer = malloc(second_size * sizeof(mp_limb_t));
	mp_limb_t ret_val = 0;
	mp_limb_t carry;
	struct addition zero, one;

	zero.first = s1p + first_size;
	zero.second = s2p + first_size;
	zero.res = rp + first_size;
	zero.size = second_size;
	zero.carry = 0;

	one.first = s1p + first_size;
	one.second = s2p + first_size;
	one.res = one_buffer;
	one.size = second_size;
	one.carry = 0;

	pthread_create(&zero_thread, NULL, &add_zero, &zero);
	pthread_create(&one_thread, NULL, &add_one, &one);

	carry = mpn_add_n(rp, s1p, s2p, first_size);

	pthread_join(zero_thread, NULL);
	pthread_join(one_thread, NULL);

	if (carry) {
		memcpy(rp + first_size, one_buffer,
		       second_size * sizeof(mp_limb_t));
		ret_val = one.carry;
	} else {
		ret_val = zero.carry;
	}

	free(one_buffer);
	return ret_val;
}
