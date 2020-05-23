// This code was used in order to offload and measure computation speed of the FSNT Loop in nco_rgr.c 

double start = omp_get_wtime();
        #pragma omp target data map (to: row_dst_adr[0:lnk_idx], var_val_dbl_in[0: var_sz_in], col_src_adr[0:lnk_idx], wgt_raw[0:lnk_idx]) map(tofrom: var_val_dbl_out[0:var_sz_out])
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

// This code was used in order to offload the multi-level with no missing values in nco_rgr.c

double end = omp_get_wtime();
             (void)fprintf(fp_stdout,"Total time to run single-level fields without missing values: %f seconds\n", end-start);
            }
            else{
             double start = omp_get_wtime();
             #pragma omp target data map (to: row_dst_adr[0:lnk_idx], var_val_dbl_in[0:var_sz_in], col_src_adr[0:lnk_idx], wgt_raw[0:lnk_idx]) map(tofrom: var_val_dbl_out[0:var_sz_out])
              val_in_fst=0L;
              val_out_fst=0L;
              /* Weight multi-level fields without missing values */
              #pragma omp parallel for reduction(+:val_in_fst, val_out_fst)
              for(lvl_idx=0;lvl_idx<lvl_nbr;lvl_idx++){
                //if(nco_dbg_lvl_get() >= nco_dbg_crr) (void)fprintf(fp_stdout,"%s lvl_idx = %d val_in_fst = %li, val_out_fst = %li\n",trv.nm,lvl_idx,val_in_fst,val_out_fst);
              #pragma omp target teams distribute parallel for
                for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
                  var_val_dbl_out[row_dst_adr[lnk_idx]+val_out_fst]+=var_val_dbl_in[col_src_adr[lnk_idx]+val_in_fst]*wgt_raw[lnk_idx];
                val_in_fst+=grd_sz_in;
                val_out_fst+=grd_sz_out;
              }
           /* !lvl_idx */
         double end = omp_get_wtime();
         (void)fprintf(fp_stdout,"Total time to run multi-level fields without missing values: %f seconds\n", end-start);


// Computation Speeds for Offloading the entire dataset

// CPU Computation Speed = 35.282 seconds 
// GPU Computation Speed = 5.577 seconds 
