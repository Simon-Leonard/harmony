#include <RcppArmadillo.h>
#include <Rcpp.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <progress.hpp>

using namespace Rcpp;
using namespace arma;
// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::depends(RcppProgress)]]

using namespace std;

class harmony;
RCPP_EXPOSED_CLASS(harmony)
  
  
#include "harmony_types.h"
  
class harmony { 
public: 
  /* CONSTRUCTORS etc */
  harmony(int __K);    
  void setup(MATTYPE& __Z, MATTYPE& __Phi, MATTYPE& __Phi_moe, VECTYPE __Pr_b,
             VECTYPE __sigma, VECTYPE __theta, int __max_iter_kmeans, 
             float __epsilon_kmeans, float __epsilon_harmony, 
             int __K, float tau, float __block_size, 
             MATTYPE __lambda, VECTYPE __weights, bool __verbose, bool __use_weights);
  
  /* METHODS */
  void moe_correct_ridge_cpp();
  CUBETYPE moe_ridge_get_betas_cpp();
  MATTYPE compute_Y();
  void init_cluster_cpp(unsigned C);
  int cluster_cpp();
  
  // support for cluster_R_r
  void update_scale_dist();
  void remove_cells();
  void recompute_R();
  void replace_cells();   
  
  void allocate_buffers();
  void compute_objective(); 
  int update_R();
  bool check_convergence(int type);
  
  void set_cells_update(const uvec& new_cells_update);

  /* FIELDS */
  MATTYPE R, Rw, Z_orig, Z_corr, Z_cos, Y, Y_unnormed, Phi, Phi_moe; 
  VECTYPE Pr_b, theta, N_b, sigma, sigma_prior, weights;
  MATTYPE lambda; // diagonal MATTYPErix of ridge regression penalties
  vector<float> objective_harmony;
  vector<float> objective_kmeans, objective_kmeans_dist, objective_kmeans_entropy, objective_kmeans_cross;
  vector<int> kmeans_rounds; // OLD: Kb
  
  //    vector<uvec> phi_map;
  float block_size, epsilon_kmeans, epsilon_harmony, merge_thresh_global;
  int N, K, B, d, max_iter_kmeans, window_size; 

  // buffers
  MATTYPE _scale_dist, dist_mat, O, E, dir_prior, Phi_Rk; // N_k, N_kb, N_b, numerator, denominator, C;
  uvec update_order, cells_update;
  MATTYPE W;
  
  // flags
  bool ran_setup, ran_init, verbose, use_weights; // do_merge_R;
  
};

  