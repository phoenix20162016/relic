/*
 * RELIC is an Efficient LIbrary for Cryptography
 * Copyright (c) 2021 RELIC Authors
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
 * Implementation of configuration of prime elliptic curves over quartic
 * extensions.
 *
 * @ingroup epx
 */

#include "relic_core.h"

/*============================================================================*/
/* Private definitions                                                        */
/*============================================================================*/

/* See ep/relic_ep_param.c for discussion of MAP_U parameters. */

#if defined(EP_ENDOM) && FP_PRIME == 315
/** @{ */
#define B24_P315_A0		"0"
#define B24_P315_A1		"0"
#define B24_P315_A2		"0"
#define B24_P315_A3		"0"
#define B24_P315_B0		"0"
#define B24_P315_B1		"0"
#define B24_P315_B2		"0"
#define B24_P315_B3		"406CE9FD4AD2B7F7847659DC5909EE3951A263DEBF12A6EFCDF114294C8108BE8893D9CE78B13B2"
#define B24_P315_X0		"143A8108476CD513348A7BB62E823CC0D7F7E367CD75CA2AA6D9D9C4EE375F2204A6EC7171DFDF1"
#define B24_P315_X1		"152D57BA1ED90145569D652D68EBDB752986187DF157B360712A6ADBB2C1B19F9DFA929580FA921"
#define B24_P315_X2		"014E7F7DBA097CAD8A49E978757DE0755B7411812E0DCAA2AB2FC8D16531CFA2091753F07CC6726"
#define B24_P315_X3		"4074100502378B6D65F7C6603DDF2AC771E85417A709280468F91E1006A55B0A1D82B084997DB67"
#define B24_P315_Y0		"138582366AF8207D4E6B8E4D9BAF4CA15E08FCF676647F376FF4FE907627E2579D32AA8E6001DEE"
#define B24_P315_Y1		"0DEAD9C4C30BD897DF10EB443DEF49B5FA667FB8A84C90D1388AC58F993AFA6363D1BDA84CC1C1C"
#define B24_P315_Y2		"1615F1AA7F72E6C275654FD6389AE7382AED0DC06A49BF296317642D6C08A6BDB66EEA7EE76333A"
#define B24_P315_Y3		"36B589D9FE7C4A5F62F00C7B10A7EACB3CAB665DEDE5809BF77AC3313B08E7592D7D4D8C7AA5E18"
#define B24_P315_R		"196DEAC24A9DA12B25FC7EC9CF927A98C8C480ECE644E36419D0C5FD00C00001"
#define B24_P315_H		"142A76791A4ECF9C5E2D1E9744E1A3D20ECD4E893C629F9A3E8F21811C01446602B3EC97C88DB0069213228615137A0DDED7E599B628469C774CB87CD287BF73A8D2CC439FFFFE00FE2B41EFDC3698DD4B373ACDEEE183EB09E6F58E9055CD34EACE3E7E701215B52C02797E31A2C6FE9AC0018B940ADF101E0000000001"
/** @} */
#endif

#if defined(EP_ENDOM) && FP_PRIME == 317
/** @{ */
#define B24_P317_A0		"0"
#define B24_P317_A1		"0"
#define B24_P317_A2		"0"
#define B24_P317_A3		"0"
#define B24_P317_B0		"0"
#define B24_P317_B1		"0"
#define B24_P317_B2		"4"
#define B24_P317_B3		"0"
#define B24_P317_X0		"36A6220950C7870B9D42FF09CEFE0520DEAB97207021685B35BA445849CD469D1BE033F82E5F017"
#define B24_P317_X1		"C91F3B3134FB62C277EDDAF617551090B4CE7550B63A7DBDEC4AA7AA4398AC69460650EFC67408B"
#define B24_P317_X2		"1015C5600F61264941003D36E6C44373CFE660B3E58D022CD09022E888C30019F769BF66AA4D5B1D"
#define B24_P317_X3		"5BAD535DA2A42C5D074AF7C66E0A7F455343C891ADD40BE6FBBE7E3AA9AB0D43F72997D40039EA6"
#define B24_P317_Y0		"AF7E47B2C41683B76E545A9124E54500468CB736CF2511BFA4B2A701638DA87CF4DB32A05C28B24"
#define B24_P317_Y1		"19CA14178B54B1F00DFA9F1C2EE3EDAB9AAE97EC0D054B4442AC47F56C08F58E6461943B996D329"
#define B24_P317_Y2		"3CC71F2768CCABDB4E59ED5843672AAD9ED9CC9013FE03DC4385324FB2B89D19F8441EC780193F"
#define B24_P317_Y3		"101A83D160E4CAB745F944FE44506B4CA63098605B00D937EEBF4785587075D552E11033FF12E8F8"
#define B24_P317_R		"196DEAC24A9DA12B25FC7EC9CF927A98C8C480ECE644E36419D0C5FD00C00001"
#define B24_P317_H		"416447847BA373C0307445C51CE3F6794B6A196037B807603DEB0EA8A26CC88F0707D8CD9E96D7EA5C8E850F5306CC3B7285486A4F06BFE651956CC3CD1E6D77AE229D7DC65E3D9D309F43FAC42749B83735FDDD0560F1ECCA197EB86C2167E9522AE151DC5F2AC2703E82BB9F29F280E26EF9C0CFFD37140CE556FCCD6EB"
/** @} */
#endif

#if defined(EP_ENDOM) && FP_PRIME == 509
/** @{ */
#define B24_P509_A0		"0"
#define B24_P509_A1		"0"
#define B24_P509_A2		"0"
#define B24_P509_A3		"0"
#define B24_P509_B0		"0"
#define B24_P509_B1		"0"
#define B24_P509_B2		"AAAAB7FFF9CE54DFE76F95A7CE0767B65C56424AE8C3F4619750081F008485DB13742DFBE0C507867E5AE3038DD69E97731DE83B746C980509E88C6DC5FE956"
#define B24_P509_B3		"AAAAB7FFF9CE54DFE76F95A7CE0767B65C56424AE8C3F4619750081F008485DB13742DFBE0C507867E5AE3038DD69E97731DE83B746C980509E88C6DC5FE955"
#define B24_P509_X0		"4D5AF70D2E605D1691DE7667FF1096AF4537749FD200277E1BC502847F63F4BC2F000FC81571F6E282FD46B96045CD611159ED554AFA95B2B1800A74F6A97C0"
#define B24_P509_X1		"EA0D1E6A2105587ED20E9CA255A777AC78D0A24AEB118B1CE4D1F213BE42F7FFD3F3F5F60F06F902FEE405DF84143D533006D7383C25A7F7C26656440A80A0B"
#define B24_P509_X2		"10E955FAFCA0C3C16D9DA9754859EAF918518C1A3FD0D14F427302CDE750224AD9E337CA12D3824B9E5E1668F94F56A4C2D935C6841C65FF4CA89E62C6A88D34"
#define B24_P509_X3		"A9A981033A3844468D815A18B921C9F7C2B152372F240EAC4848A942FEAA4019B086104AE4F86C929F5B9064B4FE917A327279CEDCE02962FD3E971F9D00CCA"
#define B24_P509_Y0		"C45C4179589584F8D1146550C117E3B452B7789170B7E7C0BEB1E417B5E32845CC1810760585AE0FE07762D94774A311932C100276C7A2EA4304EF7FBAA89F"
#define B24_P509_Y1		"20315B1CE6AEE44F7ADCAE2F0B178DF7574F91380DB5E4A27281D02CC47A24618F995ACC29E611D7BBCE63E8A2CBD783256A1799FFA2A5D061D6872962CBAD"
#define B24_P509_Y2		"20DEE7CA8DF5A616A014D78C0BCC69491116C715DDF5416C52B8A1833F8E4974255FBCCC5C6288DCA9B7CB2F4BB58525AB13D2225590A4A69955A859D36BF67"
#define B24_P509_Y3		"5CD7D6B0C7890DC487A34BE4976767DE0C20BEB43A0EE741A5ED21021EBE5BDC42281008E19C44497E13A38165A36019235BDF7A48E76B6BA79D527024D227C"
#define B24_P509_R		"100000FFFF870FF91CE195DB5B6F3EBD1E08C94C9E193B724ED58B907FF7C311A80D7CABC647746AE3ECB627C943998457FE001"
#define B24_P509_H		"32916E9E0188E2252DA44F42F6DC0E90A66E8C7AFA49D50688A07F362BA18A01F6D9317009D55DAF8CFA9159E35E2736DA6417B31C8550DFC6CD766340D92AB85D629676E78E12D5E76AB9FAC536661EEA6615242264E5F6B46EBA0F95191CD226B0CB144CEC686A846DE323CBE0244A3B6E5FFE49BD01599F13AD869FF3DA2E5551FD9C2D885EF8FB95EB7FFD5460EC84FA36A569BCB5BBBC5A21B025CECEEAD08540C0ACCB87D9136ECB9C2CEDC2D465831D76AC3551EE87BCA06B751C18699A1424FF71E791EB953FA79"
/** @} */
#endif

#if defined(EP_ENDOM) && FP_PRIME == 766
/** @{ */
#define K16_P766_A0		"0"
#define K16_P766_A1		"1"
#define K16_P766_A2		"0"
#define K16_P766_A3		"0"
#define K16_P766_B0		"0"
#define K16_P766_B1		"0"
#define K16_P766_B2		"0"
#define K16_P766_B3		"0"
#define K16_P766_X0		"046625D06F8986BE3C9753B2C1EFE694342A81719E3FD95F25113DDD0E379D2B9091A37837D7EF2409E403EAFEFA1BC9A550E45D1FE529578278CE82208ED8C4441B99DAB7CE4F4D890C13A65A5A7D35D34197442598F63E194AEACE8CAD0A2C"
#define K16_P766_X1		"226F60D752706B7187CF7BE954ABA4E8FA68C886E78B5493F888769C75399F4B27D3AF7146B071C49CF5412EBA4D3578F13E790BF3AD286FDAAF30715763300E81C14445946D4BB3C89363EC6D6CE4ED657FADB713AC0AE586357AF3EA2E5350"
#define K16_P766_X2		"301227EE95BEB1F057362840B4A9D857A5FEAAC45E3DC7188ECFA5D9A4C3B1A49C9ED73B2EC04462668E62D27821A2CE082BC4FF80448306870F1CFFD4826D33A7705BFA8E1D72851877363235A7FDD4D9EA5A29C970DBE4ECB6A07E550DE208"
#define K16_P766_X3		"18F8BF4CD828763AC749BDDE904F47F3CE13AF10A7032C34A15213E631D346DB447D595407631B6686E91D630F5534B9045B1EE8788233276731233B838ED9F85225D08FE9FE87E2B55E24A0AB1C8CE254F6864E09D138CED0AAB8CBCFCCA6E2"
#define K16_P766_Y0		"01E3C08059B7D9BAE40717331407E21973A16B493486E759E81AE1DDAB014CB438628FD7C06FB4220BD178FCED35BA2CCB84F06D531154483E7E346BD59A456A081FD6412B98831543FA614FD0F075A1AF3F4F5659007BA0B6C7ECE5D2470097"
#define K16_P766_Y1		"1F884AEF6C14F3FA64AB8E623B0E744B2DA52E70232D9D99BBB340F31807EB83F5468E2DF572D1252ED80FA3D85015E8D70BCF6A1AB44960DA100FB3A2C4C97D4377B8F5A90AFD7A7CDB0953AEB808F6C2F6B12D6684BC1114C1785BD50A5698"
#define K16_P766_Y2		"0FCEA9ED03B8A349CC53570098541D3B3BD21F6D7BD56C63240FC55420BD430E1B59AB8023A7D44CFF4817F7C9F7FD01B60A3A93E44E0932820AC9E9B3228C967DB11B21010A15426AB6F01DFF53ABE1BBBDA8D7D7C3DD66D802623B996A88AF"
#define K16_P766_Y3		"33637FB4F612428616BFA45E61351D0D00087FA6CB30551C73E4DD78D7963F872E3138FBC8248CA184875C549E242402E1A312F5888003E258F8269D41807FE85D8D5F6DFB5F7EFD87E9433283E46698F478CAAE61D5459829CBC8236EB0A649"
#define K16_P766_R		"1B6C1BFC8E56CCE359E1D8A9B94553D096A506CE2ECF4A33C5D526AC5F3B61CB0A6D76FCD8487EDEE0B0F9BA2DFA29D5AB0B164B8792C233ED1E6EB350BA9F4D37112A98DE816BEB1EA8DDB1"
#define K16_P766_H		"755986B96E4AAB1797EAEDDCB714FA0EC4E13C9AF468746FEE467D8D27293EF56C4CFA83CC6DD8774B03009353D93F100EC1314BAB5764E3D32F3DA621C7B3DDACB086098C31F7999CA8F4EA67165C3595BFAD8DBE5B7951091040E97CC5A27149F16A9A960F2557EC038032C876E49E4C40E56C1BD543BD910CB3BAABFA2F9179D2B1711E168A6472FCC1A8D8AF3415559DBF3108029DB68CC8343D397F78577E9EF7DFE8E239D9F5D9EBC1011B8F9E6043DD53C1B98C12BFA48E8A17B3BB0F5DE92DEEA7C9088EA9A643C66D4016BF81616AE20C609045A3EBA6AF3F7BEDC6AE78ABBF788F36CA894B789C84C484B4D31B83DB5CC95783DA34FC601EF7D7F07F60128E0F0E007AE29AB2F98C7A483F0E4CA614E4E45650D3E210A2EB030A6C339DB66CC198FE0EAC1CA827A8A975D094B7862"
/** @} */
#endif

/**
 * Assigns a set of ordinary elliptic curve parameters.
 *
 * @param[in] CURVE		- the curve parameters to assign.
 */
#define ASSIGN(CURVE)														\
	RLC_GET(str, CURVE##_A0, sizeof(CURVE##_A0));							\
	fp_read_str(a[0][0], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_A1, sizeof(CURVE##_A1));							\
	fp_read_str(a[0][1], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_A2, sizeof(CURVE##_A2));							\
	fp_read_str(a[1][0], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_A3, sizeof(CURVE##_A3));							\
	fp_read_str(a[1][1], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_B0, sizeof(CURVE##_B0));							\
	fp_read_str(b[0][0], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_B1, sizeof(CURVE##_B1));							\
	fp_read_str(b[0][1], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_B2, sizeof(CURVE##_B2));							\
	fp_read_str(b[1][0], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_B3, sizeof(CURVE##_B3));							\
	fp_read_str(b[1][1], str, strlen(str), 16);								\
	RLC_GET(str, CURVE##_X0, sizeof(CURVE##_X0));							\
	fp_read_str(g->x[0][0], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_X1, sizeof(CURVE##_X1));							\
	fp_read_str(g->x[0][1], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_X2, sizeof(CURVE##_X2));							\
	fp_read_str(g->x[1][0], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_X3, sizeof(CURVE##_X3));							\
	fp_read_str(g->x[1][1], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_Y0, sizeof(CURVE##_Y0));							\
	fp_read_str(g->y[0][0], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_Y1, sizeof(CURVE##_Y1));							\
	fp_read_str(g->y[0][1], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_Y2, sizeof(CURVE##_Y2));							\
	fp_read_str(g->y[1][0], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_Y3, sizeof(CURVE##_Y3));							\
	fp_read_str(g->y[1][1], str, strlen(str), 16);							\
	RLC_GET(str, CURVE##_R, sizeof(CURVE##_R));								\
	bn_read_str(r, str, strlen(str), 16);									\
	RLC_GET(str, CURVE##_H, sizeof(CURVE##_H));								\
	bn_read_str(h, str, strlen(str), 16);									\

/**
 * Detects an optimization based on the curve coefficients.
 */
static void detect_opt(int *opt, fp4_t a) {
	fp4_t t;
	fp4_null(t);

	RLC_TRY {
		fp4_new(t);
		fp4_set_dig(t, 3);
		fp4_neg(t, t);

		if (fp4_cmp(a, t) == RLC_EQ) {
			*opt = RLC_MIN3;
		} else if (fp4_is_zero(a)) {
			*opt = RLC_ZERO;
		} else if (fp4_cmp_dig(a, 1) == RLC_EQ) {
			*opt = RLC_ONE;
		} else if (fp4_cmp_dig(a, 2) == RLC_EQ) {
			*opt = RLC_TWO;
		} else if ((fp_bits(a[0][0]) <= RLC_DIG) && fp_is_zero(a[0][1]) &&
				fp2_is_zero(a[1])) {
			*opt = RLC_TINY;
		} else {
			*opt = RLC_HUGE;
		}
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		fp4_free(t);
	}
}

/*============================================================================*/
/* Public definitions                                                         */
/*============================================================================*/

void ep4_curve_init(void) {
	ctx_t *ctx = core_get();

#ifdef EP_PRECO
	for (int i = 0; i < RLC_EP_TABLE; i++) {
		ctx->ep4_ptr[i] = &(ctx->ep4_pre[i]);
	}
#endif

#if ALLOC == DYNAMIC
	ep4_new(ctx->ep4_g);
	fp4_new(ctx->ep4_a);
	fp4_new(ctx->ep4_b);
#endif

#ifdef EP_PRECO
#if ALLOC == DYNAMIC
	for (int i = 0; i < RLC_EP_TABLE; i++) {
		fp4_new(ctx->ep4_pre[i].x);
		fp4_new(ctx->ep4_pre[i].y);
		fp4_new(ctx->ep4_pre[i].z);
	}
#endif
#endif
	ep4_set_infty(ctx->ep4_g);
	bn_make(&(ctx->ep4_r), RLC_FP_DIGS);
	bn_make(&(ctx->ep4_h), RLC_FP_DIGS);
}

void ep4_curve_clean(void) {
	ctx_t *ctx = core_get();
	if (ctx != NULL) {
#ifdef EP_PRECO
		for (int i = 0; i < RLC_EP_TABLE; i++) {
			fp4_free(ctx->ep4_pre[i].x);
			fp4_free(ctx->ep4_pre[i].y);
			fp4_free(ctx->ep4_pre[i].z);
		}
#endif
		bn_clean(&(ctx->ep4_r));
		bn_clean(&(ctx->ep4_h));
		ep4_free(ctx->ep4_g);
		fp4_free(ctx->ep4_a);
		fp4_free(ctx->ep4_b);
	}
}

int ep4_curve_opt_a(void) {
	return core_get()->ep4_opt_a;
}

int ep4_curve_opt_b(void) {
	return core_get()->ep4_opt_b;
}

int ep4_curve_is_twist(void) {
	return core_get()->ep4_is_twist;
}

void ep4_curve_get_gen(ep4_t g) {
	ep4_copy(g, core_get()->ep4_g);
}

void ep4_curve_get_a(fp4_t a) {
	fp4_copy(a, core_get()->ep4_a);
}

void ep4_curve_get_b(fp4_t b) {
	fp4_copy(b, core_get()->ep4_b);
}

void ep4_curve_get_ord(bn_t n) {
	ctx_t *ctx = core_get();
	if (ctx->ep4_is_twist) {
		ep_curve_get_ord(n);
	} else {
		bn_copy(n, &(ctx->ep4_r));
	}
}

void ep4_curve_get_cof(bn_t h) {
	bn_copy(h, &(core_get()->ep4_h));
}

#if defined(EP_PRECO)

ep4_t *ep4_curve_get_tab(void) {
#if ALLOC == AUTO
	return (ep4_t *)*(core_get()->ep4_ptr);
#else
	return core_get()->ep4_ptr;
#endif
}

#endif

void ep4_curve_set_twist(int type) {
	char str[8 * RLC_FP_BYTES + 1];
	ctx_t *ctx = core_get();
	ep4_t g;
	fp4_t a, b;
	bn_t r, h;

	ep4_null(g);
	fp4_null(a);
	fp4_null(b);
	bn_null(r);
	bn_null(h);

	ctx->ep4_is_twist = 0;
	if (type == RLC_EP_MTYPE || type == RLC_EP_DTYPE) {
		ctx->ep4_is_twist = type;
	} else {
		return;
	}

	RLC_TRY {
		ep4_new(g);
		fp4_new(a);
		fp4_new(b);
		bn_new(r);
		bn_new(h);

		switch (ep_param_get()) {
#if FP_PRIME == 315
			case B24_P315:
				ASSIGN(B24_P315);
				break;
#elif FP_PRIME == 317
			case B24_P317:
				ASSIGN(B24_P317);
				break;
#elif FP_PRIME == 509
			case B24_P509:
				ASSIGN(B24_P509);
				break;
#elif FP_PRIME == 766
			case K16_P766:
				ASSIGN(K16_P766);
				break;
#endif
			default:
				(void)str;
				RLC_THROW(ERR_NO_VALID);
				break;
		}

		fp4_zero(g->z);
		fp4_set_dig(g->z, 1);
		g->coord = BASIC;

		ep4_copy(ctx->ep4_g, g);
		fp4_copy(ctx->ep4_a, a);
		fp4_copy(ctx->ep4_b, b);

		detect_opt(&(ctx->ep4_opt_a), ctx->ep4_a);
		detect_opt(&(ctx->ep4_opt_b), ctx->ep4_b);

		bn_copy(&(ctx->ep4_r), r);
		bn_copy(&(ctx->ep4_h), h);

		if (type == RLC_EP_MTYPE) {
			fp2_zero(a[0]);
			fp_copy(a[1][0], ctx->fp4_p1[0]);
			fp_copy(a[1][1], ctx->fp4_p1[1]);
			fp4_inv(a, a);
			fp_copy(ctx->fp4_p1[0], a[1][0]);
			fp_copy(ctx->fp4_p1[1], a[1][1]);
		}

#if defined(WITH_PC)
		/* Compute pairing generator. */
		pc_core_calc();
#endif

#if defined(EP_PRECO)
		ep4_mul_pre((ep4_t *)ep4_curve_get_tab(), ctx->ep4_g);
#endif
	}
	RLC_CATCH_ANY {
		RLC_THROW(ERR_CAUGHT);
	}
	RLC_FINALLY {
		ep4_free(g);
		fp4_free(a);
		fp4_free(b);
		bn_free(r);
		bn_free(h);
	}
}

void ep4_curve_set(const fp4_t a, const fp4_t b, const ep4_t g, const bn_t r, const bn_t h) {
	ctx_t *ctx = core_get();
	ctx->ep4_is_twist = 0;

	fp4_copy(ctx->ep4_a, a);
	fp4_copy(ctx->ep4_b, b);

	ep4_norm(ctx->ep4_g, g);
	bn_copy(&(ctx->ep4_r), r);
	bn_copy(&(ctx->ep4_h), h);

#if defined(EP_PRECO)
	ep4_mul_pre((ep4_t *)ep4_curve_get_tab(), ctx->ep4_g);
#endif
}
