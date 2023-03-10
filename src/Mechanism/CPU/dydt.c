#include "header.h"
#include "chem_utils.h"
#include "rates.h"

#if defined(CONP)

void dydt (const double t, const double pres, const double * __restrict__ y, double * __restrict__ dy) {

  // species molar concentrations
  double conc[53];
  double y_N;
  double mw_avg;
  double rho;
  eval_conc (y[0], pres, &y[1], &y_N, &mw_avg, &rho, conc);

  // local arrays holding reaction rates
  double fwd_rates[325];
  double rev_rates[309];
  eval_rxn_rates (y[0], pres, conc, fwd_rates, rev_rates);

  // get pressure modifications to reaction rates
  double pres_mod[50];
  get_rxn_pres_mod (y[0], pres, conc, pres_mod);

  // evaluate species molar net production rates
  double dy_N;
  eval_spec_rates (fwd_rates, rev_rates, pres_mod, &dy[1], &dy_N);
  // local array holding constant pressure specific heat
  double cp[53];
  eval_cp (y[0], cp);

  // constant pressure mass-average specific heat
  double cp_avg = (cp[0] * y[1]) + (cp[1] * y[2]) + (cp[2] * y[3]) + (cp[3] * y[4])
              + (cp[4] * y[5]) + (cp[5] * y[6]) + (cp[6] * y[7]) + (cp[7] * y[8])
              + (cp[8] * y[9]) + (cp[9] * y[10]) + (cp[10] * y[11]) + (cp[11] * y[12])
              + (cp[12] * y[13]) + (cp[13] * y[14]) + (cp[14] * y[15]) + (cp[15] * y[16])
              + (cp[16] * y[17]) + (cp[17] * y[18]) + (cp[18] * y[19]) + (cp[19] * y[20])
              + (cp[20] * y[21]) + (cp[21] * y[22]) + (cp[22] * y[23]) + (cp[23] * y[24])
              + (cp[24] * y[25]) + (cp[25] * y[26]) + (cp[26] * y[27]) + (cp[27] * y[28])
              + (cp[28] * y[29]) + (cp[29] * y[30]) + (cp[30] * y[31]) + (cp[31] * y[32])
              + (cp[32] * y[33]) + (cp[33] * y[34]) + (cp[34] * y[35]) + (cp[35] * y[36])
              + (cp[36] * y[37]) + (cp[37] * y[38]) + (cp[38] * y[39]) + (cp[39] * y[40])
              + (cp[40] * y[41]) + (cp[41] * y[42]) + (cp[42] * y[43]) + (cp[43] * y[44])
              + (cp[44] * y[45]) + (cp[45] * y[46]) + (cp[46] * y[47]) + (cp[47] * y[48])
              + (cp[48] * y[49]) + (cp[49] * y[50]) + (cp[50] * y[51]) + (cp[51] * y[52]) + (cp[52] * y_N);

  // local array for species enthalpies
  double h[53];
  eval_h(y[0], h);
  // rate of change of temperature
  dy[0] = (-1.0 / (rho * cp_avg)) * ((dy[1] * h[0] * 2.0160000000000000e+00)
        + (dy[2] * h[1] * 1.0080000000000000e+00) + (dy[3] * h[2] * 1.5999000000000001e+01)
        + (dy[4] * h[3] * 3.1998000000000001e+01) + (dy[5] * h[4] * 1.7007000000000001e+01)
        + (dy[6] * h[5] * 1.8015000000000001e+01) + (dy[7] * h[6] * 3.3006000000000000e+01)
        + (dy[8] * h[7] * 3.4014000000000003e+01) + (dy[9] * h[8] * 1.2010999999999999e+01)
        + (dy[10] * h[9] * 1.3018999999999998e+01) + (dy[11] * h[10] * 1.4026999999999999e+01)
        + (dy[12] * h[11] * 1.4026999999999999e+01) + (dy[13] * h[12] * 1.5035000000000000e+01)
        + (dy[14] * h[13] * 1.6042999999999999e+01) + (dy[15] * h[14] * 2.8009999999999998e+01)
        + (dy[16] * h[15] * 4.4009000000000000e+01) + (dy[17] * h[16] * 2.9018000000000001e+01)
        + (dy[18] * h[17] * 3.0026000000000000e+01) + (dy[19] * h[18] * 3.1033999999999999e+01)
        + (dy[20] * h[19] * 3.1033999999999999e+01) + (dy[21] * h[20] * 3.2042000000000002e+01)
        + (dy[22] * h[21] * 2.5029999999999998e+01) + (dy[23] * h[22] * 2.6037999999999997e+01)
        + (dy[24] * h[23] * 2.7045999999999999e+01) + (dy[25] * h[24] * 2.8053999999999998e+01)
        + (dy[26] * h[25] * 2.9061999999999998e+01) + (dy[27] * h[26] * 3.0070000000000000e+01)
        + (dy[28] * h[27] * 4.1028999999999996e+01) + (dy[29] * h[28] * 4.2036999999999999e+01)
        + (dy[30] * h[29] * 4.2036999999999999e+01) + (dy[31] * h[30] * 1.4007000000000000e+01)
        + (dy[32] * h[31] * 1.5015000000000001e+01) + (dy[33] * h[32] * 1.6023000000000000e+01)
        + (dy[34] * h[33] * 1.7030999999999999e+01) + (dy[35] * h[34] * 2.9021999999999998e+01)
        + (dy[36] * h[35] * 3.0006000000000000e+01) + (dy[37] * h[36] * 4.6005000000000003e+01)
        + (dy[38] * h[37] * 4.4012999999999998e+01) + (dy[39] * h[38] * 3.1014000000000003e+01)
        + (dy[40] * h[39] * 2.6018000000000001e+01) + (dy[41] * h[40] * 2.7025999999999996e+01)
        + (dy[42] * h[41] * 2.8033999999999999e+01) + (dy[43] * h[42] * 4.1033000000000001e+01)
        + (dy[44] * h[43] * 4.3024999999999999e+01) + (dy[45] * h[44] * 4.3024999999999999e+01)
        + (dy[46] * h[45] * 4.3024999999999999e+01) + (dy[47] * h[46] * 4.2016999999999996e+01)
        + (dy[48] * h[47] * 2.8013999999999999e+01) + (dy[50] * h[49] * 4.3088999999999999e+01)
        + (dy[51] * h[50] * 4.4097000000000001e+01) + (dy[52] * h[51] * 4.3045000000000002e+01)
        + (dy_N * h[52] * 4.4052999999999997e+01));

  // calculate rate of change of species mass fractions
  dy[1] *= (2.0160000000000000e+00 / rho);
  dy[2] *= (1.0080000000000000e+00 / rho);
  dy[3] *= (1.5999000000000001e+01 / rho);
  dy[4] *= (3.1998000000000001e+01 / rho);
  dy[5] *= (1.7007000000000001e+01 / rho);
  dy[6] *= (1.8015000000000001e+01 / rho);
  dy[7] *= (3.3006000000000000e+01 / rho);
  dy[8] *= (3.4014000000000003e+01 / rho);
  dy[9] *= (1.2010999999999999e+01 / rho);
  dy[10] *= (1.3018999999999998e+01 / rho);
  dy[11] *= (1.4026999999999999e+01 / rho);
  dy[12] *= (1.4026999999999999e+01 / rho);
  dy[13] *= (1.5035000000000000e+01 / rho);
  dy[14] *= (1.6042999999999999e+01 / rho);
  dy[15] *= (2.8009999999999998e+01 / rho);
  dy[16] *= (4.4009000000000000e+01 / rho);
  dy[17] *= (2.9018000000000001e+01 / rho);
  dy[18] *= (3.0026000000000000e+01 / rho);
  dy[19] *= (3.1033999999999999e+01 / rho);
  dy[20] *= (3.1033999999999999e+01 / rho);
  dy[21] *= (3.2042000000000002e+01 / rho);
  dy[22] *= (2.5029999999999998e+01 / rho);
  dy[23] *= (2.6037999999999997e+01 / rho);
  dy[24] *= (2.7045999999999999e+01 / rho);
  dy[25] *= (2.8053999999999998e+01 / rho);
  dy[26] *= (2.9061999999999998e+01 / rho);
  dy[27] *= (3.0070000000000000e+01 / rho);
  dy[28] *= (4.1028999999999996e+01 / rho);
  dy[29] *= (4.2036999999999999e+01 / rho);
  dy[30] *= (4.2036999999999999e+01 / rho);
  dy[31] *= (1.4007000000000000e+01 / rho);
  dy[32] *= (1.5015000000000001e+01 / rho);
  dy[33] *= (1.6023000000000000e+01 / rho);
  dy[34] *= (1.7030999999999999e+01 / rho);
  dy[35] *= (2.9021999999999998e+01 / rho);
  dy[36] *= (3.0006000000000000e+01 / rho);
  dy[37] *= (4.6005000000000003e+01 / rho);
  dy[38] *= (4.4012999999999998e+01 / rho);
  dy[39] *= (3.1014000000000003e+01 / rho);
  dy[40] *= (2.6018000000000001e+01 / rho);
  dy[41] *= (2.7025999999999996e+01 / rho);
  dy[42] *= (2.8033999999999999e+01 / rho);
  dy[43] *= (4.1033000000000001e+01 / rho);
  dy[44] *= (4.3024999999999999e+01 / rho);
  dy[45] *= (4.3024999999999999e+01 / rho);
  dy[46] *= (4.3024999999999999e+01 / rho);
  dy[47] *= (4.2016999999999996e+01 / rho);
  dy[48] *= (2.8013999999999999e+01 / rho);
  dy[49] *= (3.9950000000000003e+01 / rho);
  dy[50] *= (4.3088999999999999e+01 / rho);
  dy[51] *= (4.4097000000000001e+01 / rho);
  dy[52] *= (4.3045000000000002e+01 / rho);

} // end dydt

#elif defined(CONV)

void dydt (const double t, const double rho, const double * __restrict__ y, double * __restrict__ dy) {

  // species molar concentrations
  double conc[53];
  double y_N;
  double mw_avg;
  double pres;
  eval_conc_rho (y[0]rho, &y[1], &y_N, &mw_avg, &pres, conc);

  // local arrays holding reaction rates
  double fwd_rates[325];
  double rev_rates[309];
  eval_rxn_rates (y[0], pres, conc, fwd_rates, rev_rates);

  // get pressure modifications to reaction rates
  double pres_mod[50];
  get_rxn_pres_mod (y[0], pres, conc, pres_mod);

  // evaluate species molar net production rates
  double dy_N;  eval_spec_rates (fwd_rates, rev_rates, pres_mod, &dy[1], &dy_N);

  double cv[53];
  eval_cv(y[0], cv);

  // constant volume mass-average specific heat
  double cv_avg = (cv[0] * y[1]) + (cv[1] * y[2]) + (cv[2] * y[3]) + (cv[3] * y[4])
              + (cv[4] * y[5]) + (cv[5] * y[6]) + (cv[6] * y[7]) + (cv[7] * y[8])
              + (cv[8] * y[9]) + (cv[9] * y[10]) + (cv[10] * y[11]) + (cv[11] * y[12])
              + (cv[12] * y[13]) + (cv[13] * y[14]) + (cv[14] * y[15]) + (cv[15] * y[16])
              + (cv[16] * y[17]) + (cv[17] * y[18]) + (cv[18] * y[19]) + (cv[19] * y[20])
              + (cv[20] * y[21]) + (cv[21] * y[22]) + (cv[22] * y[23]) + (cv[23] * y[24])
              + (cv[24] * y[25]) + (cv[25] * y[26]) + (cv[26] * y[27]) + (cv[27] * y[28])
              + (cv[28] * y[29]) + (cv[29] * y[30]) + (cv[30] * y[31]) + (cv[31] * y[32])
              + (cv[32] * y[33]) + (cv[33] * y[34]) + (cv[34] * y[35]) + (cv[35] * y[36])
              + (cv[36] * y[37]) + (cv[37] * y[38]) + (cv[38] * y[39]) + (cv[39] * y[40])
              + (cv[40] * y[41]) + (cv[41] * y[42]) + (cv[42] * y[43]) + (cv[43] * y[44])
              + (cv[44] * y[45]) + (cv[45] * y[46]) + (cv[46] * y[47]) + (cv[47] * y[48])
              + (cv[48] * y[49]) + (cv[49] * y[50]) + (cv[50] * y[51]) + (cv[51] * y[52])(cv[52] * y_N);

  // local array for species internal energies
  double u[53];
  eval_u (y[0], u);

  // rate of change of temperature
  dy[0] = (-1.0 / (rho * cv_avg)) * ((dy[1] * u[0] * 2.0160000000000000e+00)
        + (dy[2] * u[1] * 1.0080000000000000e+00) + (dy[3] * u[2] * 1.5999000000000001e+01)
        + (dy[4] * u[3] * 3.1998000000000001e+01) + (dy[5] * u[4] * 1.7007000000000001e+01)
        + (dy[6] * u[5] * 1.8015000000000001e+01) + (dy[7] * u[6] * 3.3006000000000000e+01)
        + (dy[8] * u[7] * 3.4014000000000003e+01) + (dy[9] * u[8] * 1.2010999999999999e+01)
        + (dy[10] * u[9] * 1.3018999999999998e+01) + (dy[11] * u[10] * 1.4026999999999999e+01)
        + (dy[12] * u[11] * 1.4026999999999999e+01) + (dy[13] * u[12] * 1.5035000000000000e+01)
        + (dy[14] * u[13] * 1.6042999999999999e+01) + (dy[15] * u[14] * 2.8009999999999998e+01)
        + (dy[16] * u[15] * 4.4009000000000000e+01) + (dy[17] * u[16] * 2.9018000000000001e+01)
        + (dy[18] * u[17] * 3.0026000000000000e+01) + (dy[19] * u[18] * 3.1033999999999999e+01)
        + (dy[20] * u[19] * 3.1033999999999999e+01) + (dy[21] * u[20] * 3.2042000000000002e+01)
        + (dy[22] * u[21] * 2.5029999999999998e+01) + (dy[23] * u[22] * 2.6037999999999997e+01)
        + (dy[24] * u[23] * 2.7045999999999999e+01) + (dy[25] * u[24] * 2.8053999999999998e+01)
        + (dy[26] * u[25] * 2.9061999999999998e+01) + (dy[27] * u[26] * 3.0070000000000000e+01)
        + (dy[28] * u[27] * 4.1028999999999996e+01) + (dy[29] * u[28] * 4.2036999999999999e+01)
        + (dy[30] * u[29] * 4.2036999999999999e+01) + (dy[31] * u[30] * 1.4007000000000000e+01)
        + (dy[32] * u[31] * 1.5015000000000001e+01) + (dy[33] * u[32] * 1.6023000000000000e+01)
        + (dy[34] * u[33] * 1.7030999999999999e+01) + (dy[35] * u[34] * 2.9021999999999998e+01)
        + (dy[36] * u[35] * 3.0006000000000000e+01) + (dy[37] * u[36] * 4.6005000000000003e+01)
        + (dy[38] * u[37] * 4.4012999999999998e+01) + (dy[39] * u[38] * 3.1014000000000003e+01)
        + (dy[40] * u[39] * 2.6018000000000001e+01) + (dy[41] * u[40] * 2.7025999999999996e+01)
        + (dy[42] * u[41] * 2.8033999999999999e+01) + (dy[43] * u[42] * 4.1033000000000001e+01)
        + (dy[44] * u[43] * 4.3024999999999999e+01) + (dy[45] * u[44] * 4.3024999999999999e+01)
        + (dy[46] * u[45] * 4.3024999999999999e+01) + (dy[47] * u[46] * 4.2016999999999996e+01)
        + (dy[48] * u[47] * 2.8013999999999999e+01) + (dy[50] * u[49] * 4.3088999999999999e+01)
        + (dy[51] * u[50] * 4.4097000000000001e+01) + (dy[52] * u[51] * 4.3045000000000002e+01)
        + (dy_N * u[52] * 4.4052999999999997e+01));

  // calculate rate of change of species mass fractions
  dy[1] *= (2.0160000000000000e+00 / rho);
  dy[2] *= (1.0080000000000000e+00 / rho);
  dy[3] *= (1.5999000000000001e+01 / rho);
  dy[4] *= (3.1998000000000001e+01 / rho);
  dy[5] *= (1.7007000000000001e+01 / rho);
  dy[6] *= (1.8015000000000001e+01 / rho);
  dy[7] *= (3.3006000000000000e+01 / rho);
  dy[8] *= (3.4014000000000003e+01 / rho);
  dy[9] *= (1.2010999999999999e+01 / rho);
  dy[10] *= (1.3018999999999998e+01 / rho);
  dy[11] *= (1.4026999999999999e+01 / rho);
  dy[12] *= (1.4026999999999999e+01 / rho);
  dy[13] *= (1.5035000000000000e+01 / rho);
  dy[14] *= (1.6042999999999999e+01 / rho);
  dy[15] *= (2.8009999999999998e+01 / rho);
  dy[16] *= (4.4009000000000000e+01 / rho);
  dy[17] *= (2.9018000000000001e+01 / rho);
  dy[18] *= (3.0026000000000000e+01 / rho);
  dy[19] *= (3.1033999999999999e+01 / rho);
  dy[20] *= (3.1033999999999999e+01 / rho);
  dy[21] *= (3.2042000000000002e+01 / rho);
  dy[22] *= (2.5029999999999998e+01 / rho);
  dy[23] *= (2.6037999999999997e+01 / rho);
  dy[24] *= (2.7045999999999999e+01 / rho);
  dy[25] *= (2.8053999999999998e+01 / rho);
  dy[26] *= (2.9061999999999998e+01 / rho);
  dy[27] *= (3.0070000000000000e+01 / rho);
  dy[28] *= (4.1028999999999996e+01 / rho);
  dy[29] *= (4.2036999999999999e+01 / rho);
  dy[30] *= (4.2036999999999999e+01 / rho);
  dy[31] *= (1.4007000000000000e+01 / rho);
  dy[32] *= (1.5015000000000001e+01 / rho);
  dy[33] *= (1.6023000000000000e+01 / rho);
  dy[34] *= (1.7030999999999999e+01 / rho);
  dy[35] *= (2.9021999999999998e+01 / rho);
  dy[36] *= (3.0006000000000000e+01 / rho);
  dy[37] *= (4.6005000000000003e+01 / rho);
  dy[38] *= (4.4012999999999998e+01 / rho);
  dy[39] *= (3.1014000000000003e+01 / rho);
  dy[40] *= (2.6018000000000001e+01 / rho);
  dy[41] *= (2.7025999999999996e+01 / rho);
  dy[42] *= (2.8033999999999999e+01 / rho);
  dy[43] *= (4.1033000000000001e+01 / rho);
  dy[44] *= (4.3024999999999999e+01 / rho);
  dy[45] *= (4.3024999999999999e+01 / rho);
  dy[46] *= (4.3024999999999999e+01 / rho);
  dy[47] *= (4.2016999999999996e+01 / rho);
  dy[48] *= (2.8013999999999999e+01 / rho);
  dy[49] *= (3.9950000000000003e+01 / rho);
  dy[50] *= (4.3088999999999999e+01 / rho);
  dy[51] *= (4.4097000000000001e+01 / rho);
  dy[52] *= (4.3045000000000002e+01 / rho);

} // end dydt

#endif
