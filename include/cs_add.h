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
#ifndef CS_ADD_H
#define CS_ADD_H
#include <gmp.h>
#ifdef __cplusplus
extern "C" {
#endif
mp_limb_t mpn_cs_add_n(mp_limb_t *rp, const mp_limb_t *s1p,
                       const mp_limb_t *s2p, mp_size_t n);
#ifdef __cplusplus
}
#endif
#endif
