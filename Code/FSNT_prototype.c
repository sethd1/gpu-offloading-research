// Prototype for FSNT loop (single-level without missing values)
// Changed the #pragma statement and was able to run on CPU and E3SM GPU

#include <string.h>
#include <omp.h>
#include <stdio.h>

#define NULL ((void *)0)

int main()
{
    printf("Ping!\n"); // Program Start
    double start = omp_get_wtime();
    unsigned long lnk_idx;
    unsigned long lnk_nbr = 1000;

    double *var_val_dbl_out;
    double output[1000] = {[0 ... 999] = 0.0};
    var_val_dbl_out = output;

    double *var_val_dbl_in;
    double input[1000] = {[0 ... 999] = 10.0};
    var_val_dbl_in = input;

    int *row_dst_adr;
    int row[1000];
    row_dst_adr = row;
    for (int i = 0; i < 1000; ++i)
    {
        row[i] = i;
    }

    int *col_src_adr;
    int col[1000];
    col_src_adr = col;
    for (int i = 0; i < 1000; ++i)
    {
        row[i] = i;
    }

    double *wgt_raw;
    double wgts[1000] = {[0 ... 999] = 25.0};
    wgt_raw = wgts;


#pragma omp parallel for firstprivate(var_val_dbl_out, var_val_dbl_in) private(lnk_idx) shared(lnk_nbr, row_dst_adr, col_src_adr, wgt_raw) 
    for (lnk_idx = 0; lnk_idx < lnk_nbr; lnk_idx++)
    {
        var_val_dbl_out[row_dst_adr[lnk_idx]] += var_val_dbl_in[col_src_adr[lnk_idx]] * wgt_raw[lnk_idx];
    }

    printf("Program ended!\n"); // For loop is done executing 
    double end = omp_get_wtime();
    for (int i = 0; i < 1000; ++i)
    {
        printf("%f\n", output[i]);
    }
    printf("This program took: %f seconds to run\n", end-start);
}

/* CPU/GPU Stats

   CPU: 0.011131 seconds 
   GPU: 0.000356 seconds

   Note: Correct output values generated for both the CPU and GPU tests 
*/ 

// Coded by Dhruv Seth from University of California, Irvine