/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2012 RELIC Authors
 *
 * This file is part of RELIC. RELIC is legal property of its developers,
 * whose names are not listed here. Please refer to the COPYRIGHT file
 * for contact information.
 *
 * RELIC is free software; you can redistribute it and/or modify it under the
 * terms of the version 2.1 (or later) of the GNU Lesser General Public License
 * as published by the Free Software Foundation; or version 2.0 of the Apache
 * License as published by the Apache Software Foundation. See the LICENSE files
 * for more details.
 *
 * RELIC is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the LICENSE files for more details.
 *
 * You should have received a copy of the GNU Lesser General Public or the
 * Apache License along with RELIC. If not, see <https://www.gnu.org/licenses/>
 * or <https://www.apache.org/licenses/>.
 */

/**
 * @file
 *
 * Implementation of multiplication in a octodecic extension of a prime field.
 *
 * @ingroup fpx
 */

#include "relic_core.h"
#include "relic_fp_low.h"
#include "relic_fpx_low.h"

/*============================================================================*/
/* Private definitions                                                        */
/*============================================================================*/

#if FPX_RDC == LAZYR || !defined(STRIP)

inline static void fp9_mul_dxs_unr_lazyr(dv9_t c, const fp9_t a, const fp9_t b) {
	dv3_t u0, u1, u2, u3;
	fp3_t t0, t1;

	dv3_null(u0);
	dv3_null(u1);
	dv3_null(u2);
	dv3_null(u3);
	fp3_null(t0);
	fp3_null(t1);

	RLC_TRY {
		dv3_new(u0);
		dv3_new(u1);
		dv3_new(u2);
		dv3_new(u3);
		fp3_new(t0);
		fp3_new(t1);

		fp3_muln_low(u0, a[0], b[0]);
		fp3_muln_low(u1, a[1], b[1]);
		fp3_addm_low(t0, a[0], a[1]);
		fp3_addm_low(t1, b[0], b[1]);

		/* c_1 = (a_0 + a_1)(b_0 + b_1) - a_0b_0 - a_1b_1 */
		fp3_muln_low(u2, t0, t1);
		fp3_subc_low(u2, u2, u0);
		fp3_subc_low(c[1], u2, u1);

		/* c_0 = a_0b_0 + E a_2b_1 */
		fp3_muln_low(u2, a[2], b[1]);
		fp3_nord_low(c[0], u2);
		fp3_addc_low(c[0], u0, c[0]);

		/* c_2 = a_0b_2 + a_1b_1 */
		fp3_muln_low(u2, a[2], b[0]);
		fp3_addc_low(c[2], u1, u2);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		dv3_free(u0);
		dv3_free(u1);
		dv3_free(u2);
		dv3_free(u3);
		fp3_free(t0);
		fp3_free(t1);
	}
}

#endif

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

#if FPX_RDC == BASIC || !defined(STRIP)

void fp18_mul_basic(fp18_t c, const fp18_t a, const fp18_t b) {
	fp9_t t0, t1, t2;

	fp9_null(t0);
	fp9_null(t1);
	fp9_null(t2);

	RLC_TRY {
		fp9_new(t0);
		fp9_new(t1);
		fp9_new(t2);

		/* Karatsuba algorithm. */

		/* t0 = a_0 * b_0. */
		fp9_mul(t0, a[0], b[0]);
		/* t1 = a_1 * b_1. */
		fp9_mul(t1, a[1], b[1]);
		/* t2 = b_0 + b_1. */
		fp9_add(t2, b[0], b[1]);

		/* c_1 = a_0 + a_1. */
		fp9_add(c[1], a[0], a[1]);

		/* c_1 = (a_0 + a_1) * (b_0 + b_1) */
		fp9_mul(c[1], c[1], t2);
		fp9_sub(c[1], c[1], t0);
		fp9_sub(c[1], c[1], t1);

		/* c_0 = a_0b_0 + v * a_1b_1. */
		fp9_mul_art(t1, t1);
		fp9_add(c[0], t0, t1);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		fp9_free(t0);
		fp9_free(t1);
		fp9_free(t2);
	}
}

void fp18_mul_dxs_basic(fp18_t c, const fp18_t a, const fp18_t b) {
	fp9_t t0, t1, t2;

	fp9_null(t0);
	fp9_null(t1);
	fp9_null(t2);

	RLC_TRY {
		fp9_new(t0);
		fp9_new(t1);
		fp9_new(t2);

		/* Karatsuba algorithm. */

		/* t0 = a_0 * b_0. */
		fp9_mul_dxs(t0, a[0], b[0]);
#if EP_ADD == BASIC
		/* t1 = a_1 * b_1. */
		fp_mul(t2[0][0], a[1][2][0], b[1][1][0]);
		fp_mul(t2[0][1], a[1][2][1], b[1][1][0]);
		fp3_mul_nor(t1[0], t2[0]);
		fp_mul(t1[1][0], a[1][0][0], b[1][1][0]);
		fp_mul(t1[1][1], a[1][0][1], b[1][1][0]);
		fp_mul(t1[2][0], a[1][1][0], b[1][1][0]);
		fp_mul(t1[2][1], a[1][1][1], b[1][1][0]);
		/* t2 = b_0 + b_1. */
		fp3_copy(t2[0], b[0][0]);
		fp_add(t2[1][0], b[0][1][0], b[1][1][0]);
		fp_copy(t2[1][1], b[0][1][1]);
#elif EP_ADD == PROJC || EP_ADD == JACOB
		/* t1 = a_1 * b_1. */
		fp3_mul(t2[0], a[1][2], b[1][1]);
		fp3_mul_nor(t1[0], t2[0]);
		fp3_mul(t1[1], a[1][0], b[1][1]);
		fp3_mul(t1[2], a[1][1], b[1][1]);
		/* t2 = b_0 + b_1. */
		fp3_copy(t2[0], b[0][0]);
		fp3_add(t2[1], b[0][1], b[1][1]);
#endif
		/* c_1 = a_0 + a_1. */
		fp9_add(c[1], a[0], a[1]);

		/* c_1 = (a_0 + a_1) * (b_0 + b_1) - a_0 * b_0 - a_1 * b_1. */
		fp9_mul_dxs(c[1], c[1], t2);
		fp9_sub(c[1], c[1], t0);
		fp9_sub(c[1], c[1], t1);

		/* c_0 = a_0b_0 + v * a_1b_1. */
		fp9_mul_art(t1, t1);
		fp9_add(c[0], t0, t1);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		fp9_free(t0);
		fp9_free(t1);
		fp9_free(t2);
	}
}

#endif

#if FPX_RDC == LAZYR || !defined(STRIP)

void fp18_mul_unr(dv18_t c, const fp18_t a, const fp18_t b) {
	fp9_t t0, t1;
	dv9_t u0, u1, u2, u3;

	dv9_null(u0);
	dv9_null(u1);
	dv9_null(u2);
	dv9_null(u3);
	fp9_null(t0);
	fp9_null(t1);

	RLC_TRY {
		dv9_new(u0);
		dv9_new(u1);
		dv9_new(u2);
		dv9_new(u3);
		fp9_new(t0);
		fp9_new(t1);

		/* Karatsuba algorithm. */

		/* u0 = a_0 * b_0. */
		fp9_mul_unr(u0, a[0], b[0]);
		/* u1 = a_1 * b_1. */
		fp9_mul_unr(u1, a[1], b[1]);
		/* t1 = a_0 + a_1. */
		fp9_add(t0, a[0], a[1]);
		/* t0 = b_0 + b_1. */
		fp9_add(t1, b[0], b[1]);
		/* u2 = (a_0 + a_1) * (b_0 + b_1) */
		fp9_mul_unr(u2, t0, t1);
		/* c_1 = u2 - a_0b_0 - a_1b_1. */
		for (int i = 0; i < 3; i++) {
			fp3_addc_low(u3[i], u0[i], u1[i]);
			fp3_subc_low(c[1][i], u2[i], u3[i]);
		}
		/* c_0 = a_0b_0 + v * a_1b_1. */
		fp3_nord_low(u2[0], u1[2]);
		fp3_addc_low(c[0][0], u0[0], u2[0]);
		fp3_addc_low(c[0][1], u0[1], u1[0]);
		fp3_addc_low(c[0][2], u0[2], u1[1]);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		dv9_free(u0);
		dv9_free(u1);
		dv9_free(u2);
		dv9_free(u3);
		fp9_free(t0);
		fp9_free(t1);
	}
}

void fp18_mul_lazyr(fp18_t c, const fp18_t a, const fp18_t b) {
	dv18_t t;

	dv18_null(t);

	RLC_TRY {
		dv18_new(t);
		fp18_mul_unr(t, a, b);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				fp3_rdcn_low(c[i][j], t[i][j]);
			}
		}
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		dv18_free(t);
	}
}

void fp18_mul_dxs_lazyr(fp18_t c, const fp18_t a, const fp18_t b) {
	fp9_t t0;
	dv9_t u0, u1, u2;

	fp9_null(t0);
	dv9_null(u0);
	dv9_null(u1);
	dv9_null(u2);

	RLC_TRY {
		fp9_new(t0);
		dv9_new(u0);
		dv9_new(u1);
		dv9_new(u2);

		if (ep3_curve_is_twist() == RLC_EP_DTYPE) {
#if EP_ADD == BASIC
			/* t0 = a_0 * b_0. */
			fp_muln_low(u0[0][0], a[0][0][0], b[0][0][0]);
			fp_muln_low(u0[0][1], a[0][0][1], b[0][0][0]);
			fp_muln_low(u0[1][0], a[0][1][0], b[0][0][0]);
			fp_muln_low(u0[1][1], a[0][1][1], b[0][0][0]);
			fp_muln_low(u0[2][0], a[0][2][0], b[0][0][0]);
			fp_muln_low(u0[2][1], a[0][2][1], b[0][0][0]);
			/* t2 = b_0 + b_1. */
			fp_add(t0[0][0], b[0][0][0], b[1][0][0]);
			fp_copy(t0[0][1], b[1][0][1]);
			fp3_copy(t0[1], b[1][1]);
#elif EP_ADD == PROJC || EP_ADD == JACOB
			/* t0 = a_0 * b_0. */
			fp3_muln_low(u0[0], a[0][0], b[0][0]);
			fp3_muln_low(u0[1], a[0][1], b[0][0]);
			fp3_muln_low(u0[2], a[0][2], b[0][0]);

			/* t2 = b_0 + b_1. */
			fp3_add(t0[0], b[0][0], b[1][0]);
			fp3_copy(t0[1], b[1][1]);
#endif
			/* t1 = a_1 * b_1. */
			fp9_mul_dxs_unr_lazyr(u1, a[1], b[1]);
		} else {
			/* t0 = a_0 * b_0. */
			fp9_mul_dxs_unr_lazyr(u0, a[0], b[0]);
#if EP_ADD == BASIC
			/* t0 = a_0 * b_0. */
			fp_muln_low(u1[1][0], a[1][2][0], b[1][1][0]);
			fp_muln_low(u1[1][1], a[1][2][1], b[1][1][0]);
			fp3_nord_low(u1[0], u1[1]);
			fp_muln_low(u1[1][0], a[1][0][0], b[1][1][0]);
			fp_muln_low(u1[1][1], a[1][0][1], b[1][1][0]);
			fp_muln_low(u1[2][0], a[1][1][0], b[1][1][0]);
			fp_muln_low(u1[2][1], a[1][1][1], b[1][1][0]);
			/* t2 = b_0 + b_1. */
			fp3_copy(t0[0], b[0][0]);
			fp_add(t0[1][0], b[0][1][0], b[1][1][0]);
			fp_copy(t0[1][1], b[0][1][1]);
#elif EP_ADD == PROJC || EP_ADD == JACOB
			/* t1 = a_1 * b_1. */
			fp3_muln_low(u1[1], a[1][2], b[1][1]);
			fp3_nord_low(u1[0], u1[1]);
			fp3_muln_low(u1[1], a[1][0], b[1][1]);
			fp3_muln_low(u1[2], a[1][1], b[1][1]);
			/* t2 = b_0 + b_1. */
			fp3_copy(t0[0], b[0][0]);
			fp3_add(t0[1], b[0][1], b[1][1]);
#endif
		}
		/* c_1 = a_0 + a_1. */
		fp9_add(c[1], a[0], a[1]);
		/* c_1 = (a_0 + a_1) * (b_0 + b_1) */
		fp9_mul_dxs_unr_lazyr(u2, c[1], t0);
		for (int i = 0; i < 3; i++) {
			fp3_subc_low(u2[i], u2[i], u0[i]);
			fp3_subc_low(u2[i], u2[i], u1[i]);
		}
		fp3_rdcn_low(c[1][0], u2[0]);
		fp3_rdcn_low(c[1][1], u2[1]);
		fp3_rdcn_low(c[1][2], u2[2]);

		fp3_nord_low(u2[0], u1[2]);
		fp3_addc_low(u0[0], u0[0], u2[0]);
		fp3_addc_low(u0[1], u0[1], u1[0]);
		fp3_addc_low(u0[2], u0[2], u1[1]);
		/* c_0 = a_0b_0 + v * a_1b_1. */
		fp3_rdcn_low(c[0][0], u0[0]);
		fp3_rdcn_low(c[0][1], u0[1]);
		fp3_rdcn_low(c[0][2], u0[2]);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		fp9_free(t0);
		dv9_free(u0);
		dv9_free(u1);
		dv9_free(u2);
	}
}


#endif

void fp18_mul_art(fp18_t c, const fp18_t a) {
	fp9_t t0;

	fp9_null(t0);

	RLC_TRY {
		fp9_new(t0);

		/* (a_0 + a_1 * v) * v = a_0 * v + a_1 * v^9 */
		fp9_copy(t0, a[0]);
		fp9_mul_art(c[0], a[1]);
		fp9_copy(c[1], t0);
	} RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	} RLC_FINALLY {
		fp9_free(t0);
	}
}
