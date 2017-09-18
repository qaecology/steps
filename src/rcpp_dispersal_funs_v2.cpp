#include "RcppArmadillo.h"
using namespace Rcpp;

// [[Rcpp::depends(RcppArmadillo)]]

// [[Rcpp::export]]]]

//' dispersal function for dynamic metapopulation models
//' @param current_distribution raster of current population distribution.
//' @param habitat_suitability raster of habitat suitability that has been converted to carrying capacity
//' @param barrier_map raster of barriers to the dispersal, 1=barrier; 0=no barrier.
//' @param barrier_type if 0 weak barrier, if 1 strong barriers.
//' @param use_barriers if true use barriers in dispersal analysis.
//' @param dispersal_steps The number of dispersal iterations per C++ call.
//' @param dispersal_distance The maximum number of cells the species can disperse.
//' @param dispersal_kernal a numeric vector of probabilites of dispersing from one to n cells, where n is the dispersal distance.
//' @param dispersal_proportion the proportion of species that will disperse from source cell, needs to be between 0 and 1. e.g 0.2 means that 20% of the cell's population disperses. 
//' @export

NumericMatrix a_dispersal_function(NumericMatrix current_population_state, NumericMatrix potiential_carrying_capacity, NumericMatrix habitat_suitability_map, //raster
						NumericMatrix barriers_map, int barrier_type, bool use_barrier = true, int dispersal_steps,
						int dispersal_distance, NumericVector dispersal_kernal, double dispersal_proportion){

	//arma::mat cps = as<arma::mat>(current_population_state);
	//arma::mat pcc = as<arma::mat>(potiential_carrying_capacity);	
	//arma::mat hsm = as<arma::mat>(habitat_suitability_map);
	//arma::mat barriers = as<arma::mat>(barriers_map);
	int ncols = current_population_state.ncol();
    int nrows = current_population_state.nrow();
    NumericMartix cca(nrows,ncols,NA); // carrying capacity avaliable. 
    NumericMatrix fps(nrows,ncols,NA); // future population size (after dispersal).
    int loopID, nr_step_colonised, nr_step_decolonised, nr_step_colonised, n_dispersal_cells;

	// check how much carrying capacity is free per-cell - this will enable dispersal to these cells if needed.
     for(int i = 0; i < nrows; i++){
         for(int j = 0; j < ncols; j++){
			 if(Rcpp::is_na(current_population_state(i,j))){ 
	            cca(i,j) = potiential_carrying_capacity(i,j) - current_population_state(i,j); // carrying capacity avaliable = potiential carrying capacity - current population state.
	     }
	   }
     }
     
      /* Filter the habitat suitability matrix in three ways:
      **  1. replace any value < 0 by 0 (this removes NoData).
      **  2. set habitat suitability to 0 where barrier = 1.
      **  3. set habitat suitability values to NoData where barrier = NoData. 
      ** and also  */
      NumericMatrix cca_cleaned = clean_matrix(cca, barriers, true, true, true);
      
      
      n_dispersal_cells = total_dispersal_cells(cca_cleaned);
 
      /* Reset number of decolonized cells within current dispersal step pixel counter */
	  nr_step_decolonised = 0;
	    
      /* *********************** */
      /* Dispersal starts here.  */
      /* *********************** */
      loopID = 0;
      for(dispersal_step = 1; dispersal_step <= dispersal_steps; dispersal_step++){
	    
	    /* Set the value of "loopID" for the current iteration of the dispersal loop. */
	    loopID++;
          
	    /* Reset pixel counters that count pixels within the current loop. */
	    nr_step_colonised = 0;
	    if(dispersal_step > 1) nr_step_decolonised = 0;

	    /* Source cell search: Can the sink pixel be colonized? There are four
	    ** conditions to be met for a sink pixel to become colonized:
	    **   1. Sink pixel is currently suitable. 
	    **	 2. Sink pixel has avaliable carrying capacity.
	    **   3. Sink pixel is within dispersal distance of an already colonised cell.
	    **   4. There is no obstacle (barrier) between the pixel to be colonised
	    **      (sink pixel) and the pixel that is already colonised (source
	    **      pixel).
	    **
	    ** Loop through the cellular automaton. */
	    for(i = 0; i < nrows; i++){
	      for(j = 0; j < ncols; j++){
	        
		    //The are boolian calls which indicate if habitat is suitable and if cell can disperse
	        habitat_is_suitable = false;
	        cell_in_dispersal_distance = false;
	        
	        /* 1. Test whether the pixel is a suitable sink (i.e., its habitat
	        **    is suitable, it has avaliable carrying capacity, it's not NA and is not on a barrier). */
	        if((habitat_suitability_map(i,j) > 0) && (cca_cleaned(i,j) > 0) && !Rcpp::is_na(cca_cleaned(i,j))) habitat_is_suitable = true;

	        /* 2. Test whether there is a source cell within the dispersal
	        **    distance. To be more time efficient, this code runs only if
	        **    the answer to the first question is positive. This is a bit slower,
	        **	  especially if you include barriers in dispersal step.
	        **/
	        if(habitat_is_suitable){
		      /* Now we search if there is a suitable source cell to colonize the sink cell. */
	          cell_in_dispersal_distance = can_source_cell_disperse(i, j, cca_cleaned, habitat_suitability_map, barriers_map));
	        }
	        
	        /* Update sink cell status. */
	        if(habitat_is_suitable &&  Rcpp::all(!Rcpp::is_na(cell_in_dispersal_distance))){
				
			  //sink cell = existing population + rbinom(1, population @ source cell, p=prob_of_dispersal)
			  //source cell = source cell population - rbinom realisation. 
	          
		      /* Only if the 2 conditions are fullfilled the cell's is there dispersal to this cell and the population size is changed. */
		      int source_x = cell_is_dispersal_distance[0];
		      int source_y = cell_is_dispersal_distance[1];
		      double source_pop = current_population_state(source_x,source_y);
		      double source_pop_dispersed = as<double>(rbinom(1,source_pop,dispersal_proportion));
	          fps(i,j) = current_population_state(i,j) + source_pop_dispersed;
	          fps(sink_x,sink_y) = current_population_state(source_x,source_y) - source_pop_dispersed;
	          nr_step_colonized++;
	         }
	      }
	   }
	}
   return(wrap(fds));    /* end of dispersal */
}

/*
** can_source_cell_disperse: This function will search, for a given input location, for a
**            suitable "source" pixel that can lead to the colonization of
**            the input location (sink pixel).
*/

IntegerVector can_source_cell_disperse(int i, 
							  int j,
							  NumericMatrix current_population_state,
							  NumericMatrix initial_population,
							  NumericMatrix habitat_suitability_map,
							  NumericMatrix barriers_map
							  bool use_barrier=true,
							  int barrier_type,
							  int loopID //which dispersal loop are we in.
							  int dispersal_distance,
							  NumericVector dispersal_kernal,
							  double dispersal_proportion){
								  
  	arma::mat cca = as<arma::mat>(carrying_capacity_avaliable); //A matrix of avaliable carrying capacity.
  	arma::mat cps = as<arma::mat>(current_population_state); // the current population (during population step)
  	arma::mat hsm = as<arma::mat>(habitat_suitability_map); // the habitat suitability
	arma::mat barriers = as<arma::mat>(barrier_map);
	int ncols = current_population_state.n_cols;
    int nrows = current_population_state.n_rows;								  
	int    k, l, real_distance;
	double prob_colonisation, rnd;
	IntegerVector source_found(2);
	source_found.fill(NA_REAL);

  /*
  ** For now let's set these paramters to fixed values. Later we can implement
  ** them as variables.
  */
  //source_found = false;
        
  /*
  ** Search for a potential source cell. i and j are the coordinates of the
  ** sink cell. k and l are the coordinates of the potential source cell.
  */
  for (k = i - dispersal_distance; k <= i + dispersal_distance; k++){
    for (l = j - dispersal_distance; l <= j + dispersal_distance; l++){
      /*
      ** 1. Test of basic conditions to see if a pixel could be a potential
      **    source cell:
      **    - The pixel must be within the limits of the matrix's extent.
      **    - The pixel must be colonized, but not during the current loop.
      ** 	- The pixel must have avaliable carrying capacity to allow recruitment.
      */
      if ((k >= 0) && (k < nrows) && (l >= 0) && (l < ncols)){
		  if ((current_population_state(k,l) > 0) && (current_population_state(k,l) != loopID)){
			  if (cca(k,l) > 0){
	    /*
	    ** 2. Compute the distance between sink and (potential) source pixel
	    **    and check if it is <= maximum dispersal distance. The distance
	    **    is computed in pixel units.
	    **    real_distance = round(Sqr((K - I) ^ 2 + (L - J) ^ 2) + 0.5)
	    */
	    real_distance = round(sqrt((k-i)*(k-i) + (l-j)*(l-j)));
	    if ((real_distance > 0) && (real_distance <= dispersal_distance)){
	      /*
	      ** 3. Compute the probability of colonization of the sink pixel.
	      **    This probability depends on several factors:
	      **    - Disance between source and sink cells.
	      */
		  prob_colonisation = disp_kernel[real_distance-1] * (habitat_suitability_map(k,l)/1000.0);
	      rnd = runif(1);
	      if (rnd < prob_colonisation || prob_colonisation == 1.0){
				/*
				** When we reach this stage, the last thing we need to check for
				** is whether there is a "barrier" obstacle between the source
				** and sink pixel. We check this last as it requires significant
				** computing time.
				*/
				if (use_barrier){
				  if (!barrier_to_dispersal(i, j, k, l, barriers_map, barrier_type)){
					source_found[0] = k;
					source_found[1] = l;
					return(source_found);
				  }
				} else {
					source_found[0] = k;
					source_found[1] = l;
				  return(source_found);
				}
			  }
			}
		  }
		}
      }
    }
  }
}


// This function cleans up the habitat martix before dispersal.

NumericMatrix clean_matrix(NumericMatrix in_matrix,
						   NumericMatrix barriers_map,
						   bool filter_na_data = true,
						   bool filter_barriers = true,
						   bool insert_na_data = true){
	int i, j;
	//arma::mat inmat = as<arma::mat>(in_matrix);
	//arma::mat barriers = as<arma::mat>(barrier_map);
	int ncols = in_matrix.ncol();
	int nrows = in_matrix.nrow();
	  // set any value < 0 to 0, removes nan data and data where carrying  capacity is */
	  if(filter_na_data){
		for (i = 0; i < nrows; i++){
			for (j = 0; j < ncols; j++){
				if (in_matrix(i,j) < 0) in_matrix(i,j) = 0;
			}
		 }
	  }

	  /* Turn barrier cells into zero. */
	  if(filter_barriers){
		for (i = 0; i < nrows; i++){
			for (j = 0; j < ncols; j++){
				if (barriers_map(i,j) == 1) in_matrix(i,j) = 0;
			}
		 }
	  }
	  
	  /* turn NA in barrier_matrix into NA . */
	  if(insert_na_data){
		for (i = 0; i < nrows; i++){
			for (j = 0; j < ncols; j++){
				if (barriers_map(i,j) == NA_REAL) in_matrix(i,j) = NA_REAL;
			}
		 }
	  }
     return(in_matrix)
}


//' is there a barrier to dispersal?

bool barrier_to_dispersal(int snkX, int snkY, int srcX, int srcY, NumericMatrix barrier_map, int barrier_type){
  int  dstX, dstY, i, pxlX, pxlY, distMax, barCounter;
  bool barrier_found;
  barrier_found = false;
  arma::mat barriers = as<arma::mat>(barrier_map);
  
  /*
  ** Calculate the distance in both dimensions between the source and sink
  ** pixels and take the largest of the two.
  */
  dstX = srcX - snkX;
  dstY = srcY - snkY;
  if (abs (dstX) >= abs (dstY)){
    distMax = abs(dstX);
  } else {
    distMax = abs(dstY);
  }

  /*
  ** Check the possible paths from source to sink and see if there is a path
  ** without barriers.
  */
  if (barrier_type == 0){
    /*
    ** Weak barrier: If there is at least one free path we're good.
    **
    ** BARRIER MIDDLE
    */
    barrier_found = false;
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX + (1.0 * i / distMax * dstX));
      pxlY = round(snkY + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1) {
		  barrier_found = true;
		  break;
      }
    }
    if (!barrier_found){
      return(barrier_found);
    }
    /*
    ** BARRIER TOP_LEFT
    */
    barrier_found = false;
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX - 0.49 + (1.0 * i / distMax * dstX));
      pxlY = round(snkY - 0.49 + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1){
		barrier_found = true;
		break;
      }
    }
    if (!barrier_found){
      return(barrier_found);
    }
    /*
    ** BARRIER TOP_RIGHT
    */
    barrier_found = false;
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX + 0.49 + (1.0 * i / distMax * dstX));
      pxlY = round(snkY - 0.49 + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1){
	barrier_found = true;
	break;
      }
    }
    if (!barrier_found)
    {
     return(barrier_found);
    }
    /*
    ** Barrier DOWN_LEFT
    */
    barrier_found = false;
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX - 0.49 + (1.0 * i / distMax * dstX));
      pxlY = round(snkY + 0.49 + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1){
	barrier_found = true;
	break;
      }
    }
    if (!barrier_found)
    {
     return(barrier_found);
    }
    /*
    ** Barrier DOWN_RIGHT
    */
    barrier_found = false;
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX + 0.49 + (1.0 * i / distMax * dstX));
      pxlY = round(snkY + 0.49 + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1){
	barrier_found = true;
	break;
      }
    }
    if (!barrier_found){
     return(barrier_found);
         }
  }
  else if (barrier_type == 1){
    /*
    ** Strong barrier: If more than one way is blocked by a barrier then
    **                 colonization fails.
    */
    barCounter = 0;
    barrier_found = false;
    /*
    ** BARRIER MIDDLE
    */
    for (i = 1; i <= distMax; i++){
      pxlX = round(snkX + (1.0 * i / distMax * dstX));
      pxlY = round(snkY + (1.0 * i / distMax * dstY));
      if (barriers_map(pxlX,pxlY) == 1){
	barCounter++;
	break;
      }
    }
    /*
    ** BARRIER TOP_LEFT
    */
    for (i = 1; i <= distMax; i++){
	  pxlX = round(snkX - 0.49 + (((i-1.0) / distMax * dstX) +
					((1.0 / distMax * dstX) / 2.0)));
      pxlY = round(snkY - 0.49 + (((i-1.0) / distMax * dstY) +
					((1.0 / distMax * dstY) / 2.0)));
      if (barriers_map(pxlX,pxlY) == 1){
	barCounter++;
	break;
      }
    }
    if (barCounter > 1){
      barrier_found = true;
      return(barrier_found);
    }
    /*    
    ** BARRIER TOP_RIGHT
    */
    for (i = 1; i <= distMax; i++){
      pxlX = round (snkX + 0.49 + (((i-1.0) / distMax * dstX) +
					((1.0 / distMax * dstX) / 2.0)));
      pxlY = round (snkY - 0.49 + (((i-1.0) / distMax * dstY) +
					((1.0 / distMax * dstY) / 2.0)));
      if (barriers_map(pxlX,pxlY) == 1){
	barCounter++;
	break;
      }
    }
    if (barCounter > 1){
      barrier_found = true;
     return(barrier_found);
    }
    /*
    ** BARRIER DOWN_LEFT
    */
    for (i = 1; i <= distMax; i++){
      pxlX = round (snkX - 0.49 + (((i-1.0) / distMax * dstX) +
					((1.0 / distMax * dstX) / 2.0)));
      pxlY = round (snkY + 0.49 + (((i-1.0) / distMax * dstY) +
					((1.0 / distMax * dstY) / 2.0)));
      if (barriers_map(pxlX,pxlY) == 1){
		barCounter++;
		break;
      }
    }
    if (barCounter > 1){
      barrier_found = true;
     return(barrier_found);
    }
    /*
    ** BARRIER DOWN_RIGHT
    */
    for (i = 1; i <= distMax; i++){
      pxlX = round (snkX + 0.49 + (((i-1.0) / distMax * dstX) +
					((1.0 / distMax * dstX) / 2.0)));
      pxlY = round (snkY + 0.49 + (((i-1.0) / distMax * dstY) +
					((1.0 / distMax * dstY) / 2.0)));
      if (barriers_map(pxlX,pxlY) == 1){
	barCounter++;
	break;
      }
    }
    if (barCounter > 1){
      barrier_found = true;
      return(barrier_found);
    }
  }        
}


int total_dispersal_cells(NumericMatrix habitat_suitability_map){  
	int i, j, count;
	arma::mat hsm = as<arma::mat>(habitat_suitability_map);
	int ncols = habitat_suitability_map.n_cols;
	int nrows = habitat_suitability_map.n_rows;

   // Count the number of dispersable pixels.
	  count = 0;
	  for (i = 0; i < nrows; i++){
		for (j = 0; j < ncols; j++){
		  if (habitat_suitability_map(i,j) > 0) count++;
		}
	  }
  return (count);
}