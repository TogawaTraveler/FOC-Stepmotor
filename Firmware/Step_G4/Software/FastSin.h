#ifndef __FASTSIN_H__
#define __FASTSIN_H__
#include "main.h"
const int16_t sin_mp[1024] = {
    0, 25, 50, 75, 101, 126, 151, 176, 201, 226, 251, 276, 301, 326, 351, 376, 401, 426, 451, 476, 501, 526,
    551, 576, 601, 626, 651, 675, 700, 725, 750, 774,
    799, 824, 848, 873, 897, 922, 946, 971, 995, 1020, 1044, 1068, 1092, 1117, 1141, 1165, 1189, 1213, 1237,
    1261, 1285, 1309, 1332, 1356, 1380, 1404, 1427, 1451, 1474, 1498, 1521, 1544,
    1567, 1591, 1614, 1637, 1660, 1683, 1706, 1729, 1751, 1774, 1797, 1819, 1842, 1864, 1886, 1909, 1931,
    1953, 1975, 1997, 2019, 2041, 2062, 2084, 2106, 2127, 2149, 2170, 2191, 2213, 2234, 2255,
    2276, 2296, 2317, 2338, 2359, 2379, 2399, 2420, 2440, 2460, 2480, 2500, 2520, 2540, 2559, 2579, 2598,
    2618, 2637, 2656, 2675, 2694, 2713, 2732, 2751, 2769, 2788, 2806, 2824, 2843, 2861, 2878,
    2896, 2914, 2932, 2949, 2967, 2984, 3001, 3018, 3035, 3052, 3068, 3085, 3102, 3118, 3134, 3150, 3166,
    3182, 3198, 3214, 3229, 3244, 3260, 3275, 3290, 3305, 3320, 3334, 3349, 3363, 3378, 3392,
    3406, 3420, 3433, 3447, 3461, 3474, 3487, 3500, 3513, 3526, 3539, 3551, 3564, 3576, 3588, 3600, 3612,
    3624, 3636, 3647, 3659, 3670, 3681, 3692, 3703, 3713, 3724, 3734, 3745, 3755, 3765, 3775,
    3784, 3794, 3803, 3812, 3822, 3831, 3839, 3848, 3857, 3865, 3873, 3881, 3889, 3897, 3905, 3912, 3920,
    3927, 3934, 3941, 3948, 3954, 3961, 3967, 3973, 3979, 3985, 3991, 3996, 4002, 4007, 4012,
    4017, 4022, 4027, 4031, 4036, 4040, 4044, 4048, 4052, 4055, 4059, 4062, 4065, 4068, 4071, 4074, 4076,
    4079, 4081, 4083, 4085, 4087, 4088, 4090, 4091, 4092, 4093, 4094, 4095, 4095, 4096, 4096,
    4096, 4096, 4096, 4095, 4095, 4094, 4093, 4092, 4091, 4090, 4088, 4087, 4085, 4083, 4081, 4079, 4076,
    4074, 4071, 4068, 4065, 4062, 4059, 4055, 4052, 4048, 4044, 4040, 4036, 4031, 4027, 4022,
    4017, 4012, 4007, 4002, 3996, 3991, 3985, 3979, 3973, 3967, 3961, 3954, 3948, 3941, 3934, 3927, 3920,
    3912, 3905, 3897, 3889, 3881, 3873, 3865, 3857, 3848, 3839, 3831, 3822, 3812, 3803, 3794,
    3784, 3775, 3765, 3755, 3745, 3734, 3724, 3713, 3703, 3692, 3681, 3670, 3659, 3647, 3636, 3624, 3612,
    3600, 3588, 3576, 3564, 3551, 3539, 3526, 3513, 3500, 3487, 3474, 3461, 3447, 3433, 3420,
    3406, 3392, 3378, 3363, 3349, 3334, 3320, 3305, 3290, 3275, 3260, 3244, 3229, 3214, 3198, 3182, 3166,
    3150, 3134, 3118, 3102, 3085, 3068, 3052, 3035, 3018, 3001, 2984, 2967, 2949, 2932, 2914,
    2896, 2878, 2861, 2843, 2824, 2806, 2788, 2769, 2751, 2732, 2713, 2694, 2675, 2656, 2637, 2618, 2598,
    2579, 2559, 2540, 2520, 2500, 2480, 2460, 2440, 2420, 2399, 2379, 2359, 2338, 2317, 2296,
    2276, 2255, 2234, 2213, 2191, 2170, 2149, 2127, 2106, 2084, 2062, 2041, 2019, 1997, 1975, 1953, 1931,
    1909, 1886, 1864, 1842, 1819, 1797, 1774, 1751, 1729, 1706, 1683, 1660, 1637, 1614, 1591,
    1567, 1544, 1521, 1498, 1474, 1451, 1427, 1404, 1380, 1356, 1332, 1309, 1285, 1261, 1237, 1213, 1189,
    1165, 1141, 1117, 1092, 1068, 1044, 1020, 995, 971, 946, 922, 897, 873, 848, 824,
    799, 774, 750, 725, 700, 675, 651, 626, 601, 576, 551, 526, 501, 476, 451, 426, 401, 376, 351, 326, 301,
    276, 251, 226, 201, 176, 151, 126, 101, 75, 50, 25,
    0, -25, -50, -75, -101, -126, -151, -176, -201, -226, -251, -276, -301, -326, -351, -376, -401, -426,
    -451, -476, -501, -526, -551, -576, -601, -626, -651, -675, -700, -725, -750, -774,
    -799, -824, -848, -873, -897, -922, -946, -971, -995, -1020, -1044, -1068, -1092, -1117, -1141, -1165,
    -1189, -1213, -1237, -1261, -1285, -1309, -1332, -1356, -1380, -1404, -1427, -1451, -1474, -1498, -1521,
    -1544,
    -1567, -1591, -1614, -1637, -1660, -1683, -1706, -1729, -1751, -1774, -1797, -1819, -1842, -1864, -1886,
    -1909, -1931, -1953, -1975, -1997, -2019, -2041, -2062, -2084, -2106, -2127, -2149, -2170, -2191, -2213,
    -2234, -2255,
    -2276, -2296, -2317, -2338, -2359, -2379, -2399, -2420, -2440, -2460, -2480, -2500, -2520, -2540, -2559,
    -2579, -2598, -2618, -2637, -2656, -2675, -2694, -2713, -2732, -2751, -2769, -2788, -2806, -2824, -2843,
    -2861, -2878,
    -2896, -2914, -2932, -2949, -2967, -2984, -3001, -3018, -3035, -3052, -3068, -3085, -3102, -3118, -3134,
    -3150, -3166, -3182, -3198, -3214, -3229, -3244, -3260, -3275, -3290, -3305, -3320, -3334, -3349, -3363,
    -3378, -3392,
    -3406, -3420, -3433, -3447, -3461, -3474, -3487, -3500, -3513, -3526, -3539, -3551, -3564, -3576, -3588,
    -3600, -3612, -3624, -3636, -3647, -3659, -3670, -3681, -3692, -3703, -3713, -3724, -3734, -3745, -3755,
    -3765, -3775,
    -3784, -3794, -3803, -3812, -3822, -3831, -3839, -3848, -3857, -3865, -3873, -3881, -3889, -3897, -3905,
    -3912, -3920, -3927, -3934, -3941, -3948, -3954, -3961, -3967, -3973, -3979, -3985, -3991, -3996, -4002,
    -4007, -4012,
    -4017, -4022, -4027, -4031, -4036, -4040, -4044, -4048, -4052, -4055, -4059, -4062, -4065, -4068, -4071,
    -4074, -4076, -4079, -4081, -4083, -4085, -4087, -4088, -4090, -4091, -4092, -4093, -4094, -4095, -4095,
    -4096, -4096,
    -4096, -4096, -4096, -4095, -4095, -4094, -4093, -4092, -4091, -4090, -4088, -4087, -4085, -4083, -4081,
    -4079, -4076, -4074, -4071, -4068, -4065, -4062, -4059, -4055, -4052, -4048, -4044, -4040, -4036, -4031,
    -4027, -4022,
    -4017, -4012, -4007, -4002, -3996, -3991, -3985, -3979, -3973, -3967, -3961, -3954, -3948, -3941, -3934,
    -3927, -3920, -3912, -3905, -3897, -3889, -3881, -3873, -3865, -3857, -3848, -3839, -3831, -3822, -3812,
    -3803, -3794,
    -3784, -3775, -3765, -3755, -3745, -3734, -3724, -3713, -3703, -3692, -3681, -3670, -3659, -3647, -3636,
    -3624, -3612, -3600, -3588, -3576, -3564, -3551, -3539, -3526, -3513, -3500, -3487, -3474, -3461, -3447,
    -3433, -3420,
    -3406, -3392, -3378, -3363, -3349, -3334, -3320, -3305, -3290, -3275, -3260, -3244, -3229, -3214, -3198,
    -3182, -3166, -3150, -3134, -3118, -3102, -3085, -3068, -3052, -3035, -3018, -3001, -2984, -2967, -2949,
    -2932, -2914,
    -2896, -2878, -2861, -2843, -2824, -2806, -2788, -2769, -2751, -2732, -2713, -2694, -2675, -2656, -2637,
    -2618, -2598, -2579, -2559, -2540, -2520, -2500, -2480, -2460, -2440, -2420, -2399, -2379, -2359, -2338,
    -2317, -2296,
    -2276, -2255, -2234, -2213, -2191, -2170, -2149, -2127, -2106, -2084, -2062, -2041, -2019, -1997, -1975,
    -1953, -1931, -1909, -1886, -1864, -1842, -1819, -1797, -1774, -1751, -1729, -1706, -1683, -1660, -1637,
    -1614, -1591,
    -1567, -1544, -1521, -1498, -1474, -1451, -1427, -1404, -1380, -1356, -1332, -1309, -1285, -1261, -1237,
    -1213, -1189, -1165, -1141, -1117, -1092, -1068, -1044, -1020, -995, -971, -946, -922, -897, -873, -848,
    -824,
    -799, -774, -750, -725, -700, -675, -651, -626, -601, -576, -551, -526, -501, -476, -451, -426, -401,
    -376, -351, -326, -301, -276, -251, -226, -201, -176, -151, -126, -101, -75, -50, -25,
    
};


#endif
