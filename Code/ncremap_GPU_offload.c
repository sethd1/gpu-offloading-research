// Code for both single level and multi level OMP loops that support GPU Offloading

/* This first block is for "normal" variables without sub-gridscale fractions */
#pragma omp target data map (to: row_dst_adr[0:lnk_idx], var_val_dbl_in[0:var_sz_in], col_src_adr[0:lnk_idx], wgt_raw[0:lnk_idx]) map(tofrom: var_val_dbl_out[0:var_sz_out])
if(!sgs_frc_out){
    /* Apply weights */
    if(!has_mss_val){
    if(lvl_nbr == 1){
        /* Weight single-level fields without missing values */
        for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
        {
                var_val_dbl_out[row_dst_adr[lnk_idx]]+=var_val_dbl_in[col_src_adr[lnk_idx]]*wgt_raw[lnk_idx];
        }
    }
    else{
        #pragma omp target data map (to: row_dst_adr[0:lnk_idx], var_val_dbl_in[0:var_sz_in], col_src_adr[0:lnk_idx], wgt_raw[0:lnk_idx]) map(tofrom: var_val_dbl_out[0:var_sz_out])
        val_in_fst=0L;
        val_out_fst=0L;
        /* Weight multi-level fields without missing values */
        for(lvl_idx=0;lvl_idx<lvl_nbr;lvl_idx++){
        //if(nco_dbg_lvl_get() >= nco_dbg_crr) (void)fprintf(fp_stdout,"%s lvl_idx = %d val_in_fst = %li, val_out_fst = %li\n",trv.nm,lvl_idx,val_in_fst,val_out_fst);
        for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
            var_val_dbl_out[row_dst_adr[lnk_idx]+val_out_fst]+=var_val_dbl_in[col_src_adr[lnk_idx]+val_in_fst]*wgt_raw[lnk_idx];
        val_in_fst+=grd_sz_in;
        val_out_fst+=grd_sz_out;
        }

// Computation Speeds for CPU/GPU for the entire data set (on average of 11 runs omitting the 1st run)
// CPU Computation Speed = 35.282 seconds 
// GPU Computation Speed = 5.577 seconds
