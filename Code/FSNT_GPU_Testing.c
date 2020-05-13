/*

1st trial: Explicitally declared omp parallel statment over FSNT loop

double start = omp_get_wtime();
        if(!sgs_frc_out){
          /* Apply weights *//*
          if(!has_mss_val){
            if(lvl_nbr == 1){
              /* Weight single-level fields without missing values *//*
             #pragma omp parallel for firstprivate(var_val_dbl_out, var_val_dbl_in) private(lnk_idx) shared(lnk_nbr,row_dst_adr, col_src_adr, wgt_raw) 
             for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
             {
                     var_val_dbl_out[row_dst_adr[lnk_idx]]+=var_val_dbl_in[col_src_adr[lnk_idx]]*wgt_raw[lnk_idx];
             }
             double end = omp_get_wtime();
             (void)fprintf(fp_stdout,"Total time to run: %f seconds\n", end-start);

Computation Speeds (on average of 11 runs (1st omitted))

CPU Time: 0.0004312 seconds
GPU Time: 0.0003198 seconds

--------------------------------------------------------------------------------------------------

2nd trial: In the #pragma statement, it is only a omp parallel w/o declaration of varibale privacy

double start = omp_get_wtime();
        if(!sgs_frc_out){
          /* Apply weights *//*
          if(!has_mss_val){
            if(lvl_nbr == 1){
              /* Weight single-level fields without missing values *//*
             #pragma omp parallel for
             for(lnk_idx=0;lnk_idx<lnk_nbr;lnk_idx++)
             {
                     var_val_dbl_out[row_dst_adr[lnk_idx]]+=var_val_dbl_in[col_src_adr[lnk_idx]]*wgt_raw[lnk_idx];
             }
             double end = omp_get_wtime();
             (void)fprintf(fp_stdout,"Total time to run: %f seconds\n", end-start);


Computation Speeds (on average of 11 runs (1st omitted))

CPU Time: 0.0003189 seconds
GPU Time: 0.0002476 seconds

Observation: May be experiencing slight faster speeds due to the fact that variables 
             are not being re-declared in the #pragma statement before the for loop

--------------------------------------------------------------------------------------------------




*/

