// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// barrier_to_dispersal
bool barrier_to_dispersal(int snkX, int snkY, int srcX, int srcY, NumericMatrix barriers_map, int barrier_type);
RcppExport SEXP _dhmpr_barrier_to_dispersal(SEXP snkXSEXP, SEXP snkYSEXP, SEXP srcXSEXP, SEXP srcYSEXP, SEXP barriers_mapSEXP, SEXP barrier_typeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type snkX(snkXSEXP);
    Rcpp::traits::input_parameter< int >::type snkY(snkYSEXP);
    Rcpp::traits::input_parameter< int >::type srcX(srcXSEXP);
    Rcpp::traits::input_parameter< int >::type srcY(srcYSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type barriers_map(barriers_mapSEXP);
    Rcpp::traits::input_parameter< int >::type barrier_type(barrier_typeSEXP);
    rcpp_result_gen = Rcpp::wrap(barrier_to_dispersal(snkX, snkY, srcX, srcY, barriers_map, barrier_type));
    return rcpp_result_gen;
END_RCPP
}
// total_dispersal_cells
int total_dispersal_cells(NumericMatrix habitat_suitability_map);
RcppExport SEXP _dhmpr_total_dispersal_cells(SEXP habitat_suitability_mapSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type habitat_suitability_map(habitat_suitability_mapSEXP);
    rcpp_result_gen = Rcpp::wrap(total_dispersal_cells(habitat_suitability_map));
    return rcpp_result_gen;
END_RCPP
}
// can_source_cell_disperse
IntegerVector can_source_cell_disperse(int i, int j, NumericMatrix carrying_capacity_avaliable, NumericMatrix tracking_population_state, NumericMatrix habitat_suitability_map, NumericMatrix barriers_map, bool use_barrier, int barrier_type, int loopID, int dispersal_distance, NumericVector dispersal_kernel);
RcppExport SEXP _dhmpr_can_source_cell_disperse(SEXP iSEXP, SEXP jSEXP, SEXP carrying_capacity_avaliableSEXP, SEXP tracking_population_stateSEXP, SEXP habitat_suitability_mapSEXP, SEXP barriers_mapSEXP, SEXP use_barrierSEXP, SEXP barrier_typeSEXP, SEXP loopIDSEXP, SEXP dispersal_distanceSEXP, SEXP dispersal_kernelSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type i(iSEXP);
    Rcpp::traits::input_parameter< int >::type j(jSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type carrying_capacity_avaliable(carrying_capacity_avaliableSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type tracking_population_state(tracking_population_stateSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type habitat_suitability_map(habitat_suitability_mapSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type barriers_map(barriers_mapSEXP);
    Rcpp::traits::input_parameter< bool >::type use_barrier(use_barrierSEXP);
    Rcpp::traits::input_parameter< int >::type barrier_type(barrier_typeSEXP);
    Rcpp::traits::input_parameter< int >::type loopID(loopIDSEXP);
    Rcpp::traits::input_parameter< int >::type dispersal_distance(dispersal_distanceSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type dispersal_kernel(dispersal_kernelSEXP);
    rcpp_result_gen = Rcpp::wrap(can_source_cell_disperse(i, j, carrying_capacity_avaliable, tracking_population_state, habitat_suitability_map, barriers_map, use_barrier, barrier_type, loopID, dispersal_distance, dispersal_kernel));
    return rcpp_result_gen;
END_RCPP
}
// clean_matrix
NumericMatrix clean_matrix(NumericMatrix in_matrix, NumericMatrix barriers_map, bool filter_na_data, bool filter_barriers, bool insert_na_data);
RcppExport SEXP _dhmpr_clean_matrix(SEXP in_matrixSEXP, SEXP barriers_mapSEXP, SEXP filter_na_dataSEXP, SEXP filter_barriersSEXP, SEXP insert_na_dataSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type in_matrix(in_matrixSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type barriers_map(barriers_mapSEXP);
    Rcpp::traits::input_parameter< bool >::type filter_na_data(filter_na_dataSEXP);
    Rcpp::traits::input_parameter< bool >::type filter_barriers(filter_barriersSEXP);
    Rcpp::traits::input_parameter< bool >::type insert_na_data(insert_na_dataSEXP);
    rcpp_result_gen = Rcpp::wrap(clean_matrix(in_matrix, barriers_map, filter_na_data, filter_barriers, insert_na_data));
    return rcpp_result_gen;
END_RCPP
}
// proportion_of_population_to_disperse
int proportion_of_population_to_disperse(int source_x, int source_y, NumericMatrix starting_population_state, NumericMatrix current_carrying_capacity, double dispersal_proportion);
RcppExport SEXP _dhmpr_proportion_of_population_to_disperse(SEXP source_xSEXP, SEXP source_ySEXP, SEXP starting_population_stateSEXP, SEXP current_carrying_capacitySEXP, SEXP dispersal_proportionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type source_x(source_xSEXP);
    Rcpp::traits::input_parameter< int >::type source_y(source_ySEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type starting_population_state(starting_population_stateSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type current_carrying_capacity(current_carrying_capacitySEXP);
    Rcpp::traits::input_parameter< double >::type dispersal_proportion(dispersal_proportionSEXP);
    rcpp_result_gen = Rcpp::wrap(proportion_of_population_to_disperse(source_x, source_y, starting_population_state, current_carrying_capacity, dispersal_proportion));
    return rcpp_result_gen;
END_RCPP
}
// na_matrix
NumericMatrix na_matrix(int nr, int nc);
RcppExport SEXP _dhmpr_na_matrix(SEXP nrSEXP, SEXP ncSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type nr(nrSEXP);
    Rcpp::traits::input_parameter< int >::type nc(ncSEXP);
    rcpp_result_gen = Rcpp::wrap(na_matrix(nr, nc));
    return rcpp_result_gen;
END_RCPP
}
// a_dispersal_function
List a_dispersal_function(NumericMatrix starting_population_state, NumericMatrix potiential_carrying_capacity, NumericMatrix habitat_suitability_map, NumericMatrix barriers_map, int barrier_type, bool use_barrier, int dispersal_steps, int dispersal_distance, NumericVector dispersal_kernel, double dispersal_proportion);
RcppExport SEXP _dhmpr_a_dispersal_function(SEXP starting_population_stateSEXP, SEXP potiential_carrying_capacitySEXP, SEXP habitat_suitability_mapSEXP, SEXP barriers_mapSEXP, SEXP barrier_typeSEXP, SEXP use_barrierSEXP, SEXP dispersal_stepsSEXP, SEXP dispersal_distanceSEXP, SEXP dispersal_kernelSEXP, SEXP dispersal_proportionSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type starting_population_state(starting_population_stateSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type potiential_carrying_capacity(potiential_carrying_capacitySEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type habitat_suitability_map(habitat_suitability_mapSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type barriers_map(barriers_mapSEXP);
    Rcpp::traits::input_parameter< int >::type barrier_type(barrier_typeSEXP);
    Rcpp::traits::input_parameter< bool >::type use_barrier(use_barrierSEXP);
    Rcpp::traits::input_parameter< int >::type dispersal_steps(dispersal_stepsSEXP);
    Rcpp::traits::input_parameter< int >::type dispersal_distance(dispersal_distanceSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type dispersal_kernel(dispersal_kernelSEXP);
    Rcpp::traits::input_parameter< double >::type dispersal_proportion(dispersal_proportionSEXP);
    rcpp_result_gen = Rcpp::wrap(a_dispersal_function(starting_population_state, potiential_carrying_capacity, habitat_suitability_map, barriers_map, barrier_type, use_barrier, dispersal_steps, dispersal_distance, dispersal_kernel, dispersal_proportion));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_dhmpr_barrier_to_dispersal", (DL_FUNC) &_dhmpr_barrier_to_dispersal, 6},
    {"_dhmpr_total_dispersal_cells", (DL_FUNC) &_dhmpr_total_dispersal_cells, 1},
    {"_dhmpr_can_source_cell_disperse", (DL_FUNC) &_dhmpr_can_source_cell_disperse, 11},
    {"_dhmpr_clean_matrix", (DL_FUNC) &_dhmpr_clean_matrix, 5},
    {"_dhmpr_proportion_of_population_to_disperse", (DL_FUNC) &_dhmpr_proportion_of_population_to_disperse, 5},
    {"_dhmpr_na_matrix", (DL_FUNC) &_dhmpr_na_matrix, 2},
    {"_dhmpr_a_dispersal_function", (DL_FUNC) &_dhmpr_a_dispersal_function, 10},
    {NULL, NULL, 0}
};

RcppExport void R_init_dhmpr(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
