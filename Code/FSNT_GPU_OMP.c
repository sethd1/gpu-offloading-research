// This code was used in order to offload and measure computation speed of the FSNT Loop in nco_rgr.c 

double start = omp_get_wtime();
        #pragma omp target data map (to: row_dst_adr[0:lnk_idx], var_val_dbl_in[0: var_sz_in*nco_typ_lng(var_typ_rgr)], col_src_adr[0:lnk_idx], wgt_raw[0:lnk_idx]) map(tofrom: var_val_dbl_out[0:var_sz_out*nco_typ_lng(var_typ_rgr)])
        if(!sgs_frc_out){
          /* Apply weights */
          if(!has_mss_val){
            if(lvl_nbr == 1){
              /* Weight single-level fields without missing values */
             #pragma omp target teams distribute parallel for
             for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
             {
                     var_val_dbl_out[row_dst_adr[lnk_idx]]+=var_val_dbl_in[col_src_adr[lnk_idx]]*wgt_raw[lnk_idx];
             }
             double end = omp_get_wtime();
             (void)fprintf(fp_stdout,"Total time to run: %f seconds\n", end-start);

// CPU Computation Speed (on average) = 0.0106422 seconds
// GPU Computation Speed (on average) = 0.0004554 seconds