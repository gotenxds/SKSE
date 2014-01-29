#ifndef __SKSE_VERSION_H__
#define __SKSE_VERSION_H__

// these have to be macros so they can be used in the .rc
#define SKSE_VERSION_INTEGER		1
#define SKSE_VERSION_INTEGER_MINOR	7
#define SKSE_VERSION_INTEGER_BETA	0
#define SKSE_VERSION_VERSTRING		"0, 1, 7, 0"
#define SKSE_VERSION_PADDEDSTRING	"0001"
#define SKSE_VERSION_RELEASEIDX		45

#define MAKE_SKYRIM_VERSION_EX(major, minor, build, sub)	(((major & 0xFF) << 24) | ((minor & 0xFF) << 16) | ((build & 0xFFF) << 4) | (sub & 0xF))
#define MAKE_SKYRIM_VERSION(major, minor, build)			MAKE_SKYRIM_VERSION_EX(major, minor, build, 0)

// assume the major version number is 1.x
#define RUNTIME_VERSION_1_1_21_0	MAKE_SKYRIM_VERSION(1, 21, 0)		// 0x01150000
#define RUNTIME_VERSION_1_2_12_0	MAKE_SKYRIM_VERSION(2, 12, 0)		// 0x020C0000
#define RUNTIME_VERSION_1_3_7_0		MAKE_SKYRIM_VERSION(3, 7, 0)		// 0x03070000
#define RUNTIME_VERSION_1_3_10_0	MAKE_SKYRIM_VERSION(3, 10, 0)		// 0x030A0000
#define RUNTIME_VERSION_1_4_15_0	MAKE_SKYRIM_VERSION(4, 15, 0)		// 0x040F0000
#define RUNTIME_VERSION_1_4_20_0	MAKE_SKYRIM_VERSION(4, 20, 0)		// 0x04140000
#define RUNTIME_VERSION_1_4_21_0	MAKE_SKYRIM_VERSION(4, 21, 0)		// 0x04150000
#define RUNTIME_VERSION_1_4_25_0	MAKE_SKYRIM_VERSION(4, 25, 0)		// 0x04190000
#define RUNTIME_VERSION_1_4_26_0	MAKE_SKYRIM_VERSION(4, 26, 0)		// 0x041A0000
#define RUNTIME_VERSION_1_4_27_0	MAKE_SKYRIM_VERSION(4, 27, 0)		// 0x041B0000
#define RUNTIME_VERSION_1_5_24_0	MAKE_SKYRIM_VERSION(5, 24, 0)		// 0x05180000
#define RUNTIME_VERSION_1_5_26_0	MAKE_SKYRIM_VERSION(5, 26, 0)		// 0x051A0000
#define RUNTIME_VERSION_1_6_86_0	MAKE_SKYRIM_VERSION(6, 86, 0)		// 0x06560000
#define RUNTIME_VERSION_1_6_87_0	MAKE_SKYRIM_VERSION(6, 87, 0)		// 0x06570000
#define RUNTIME_VERSION_1_6_89_0	MAKE_SKYRIM_VERSION(6, 89, 0)		// 0x06590000
#define RUNTIME_VERSION_1_7_7_0		MAKE_SKYRIM_VERSION(7, 7, 0)		// 0x07070000
#define RUNTIME_VERSION_1_8_145_0	MAKE_SKYRIM_VERSION(8, 145, 0)		// 0x08910000
#define RUNTIME_VERSION_1_8_151_0	MAKE_SKYRIM_VERSION(8, 151, 0)		// 0x08970000
#define RUNTIME_VERSION_1_9_26_0	MAKE_SKYRIM_VERSION(9, 26, 0)		// 0x091A0000
#define RUNTIME_VERSION_1_9_29_0	MAKE_SKYRIM_VERSION(9, 29, 0)		// 0x091D0000
#define RUNTIME_VERSION_1_9_32_0	MAKE_SKYRIM_VERSION(9, 32, 0)		// 0x09200000

#define EDITOR_VERSION_1_9_32_0		MAKE_SKYRIM_VERSION(9, 32, 0)		// 0x09200000

#define PACKED_SKSE_VERSION		MAKE_SKYRIM_VERSION(SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA)

#endif /* __SKSE_VERSION_H__ */
