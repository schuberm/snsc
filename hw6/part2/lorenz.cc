#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

int func (double t, const double y[], double f[], void *params)
{
	double mu = *(double *)params;
	double sigma=10.0;
	double beta=8/3;
	double rho =28.0;
	f[0] = sigma*(y[1]-y[0]);
	f[1] = (rho-y[2])*y[0]-y[1];
	f[2] = y[0]*y[1]-beta*y[2];
	return GSL_SUCCESS;
}

int jac (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
	double mu = *(double *)params;
	double sigma=10.0;
	double beta=8/3;
	double rho =28.0;
	gsl_matrix_view dfdy_mat 
		= gsl_matrix_view_array (dfdy, 3, 3);
	gsl_matrix * m = &dfdy_mat.matrix; 
	gsl_matrix_set (m, 0, 0, -sigma);
	gsl_matrix_set (m, 0, 1, sigma);
	gsl_matrix_set (m, 0, 2, 0);
	gsl_matrix_set (m, 1, 0, rho-y[2]);
	gsl_matrix_set (m, 1, 1, -1.0);
	gsl_matrix_set (m, 1, 2, -y[0]);
	gsl_matrix_set (m, 2, 0, y[1]);
	gsl_matrix_set (m, 2, 1, y[0]);
	gsl_matrix_set (m, 2, 2, -beta);
	dfdt[0] = 0.0;
	dfdt[1] = 0.0;
	dfdt[2] = 0.0;
	return GSL_SUCCESS;
}
int main (void)
{
	double mu = 10;
	gsl_odeiv2_system sys = {func, jac, 3, &mu};

	gsl_odeiv2_driver * d = 
		gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
				1e-6, 1e-6, 0.0);
	int i;
	double t = 0.0, t1 = 100.0;
	double y[3] = { 11,20,30 };

	for (i = 1; i <= 10000; i++)
	{
		double ti = i * t1 / 10000.0;
		int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

		if (status != GSL_SUCCESS)
		{
			printf ("error, return value=%d\n", status);
			break;
		}

		printf ("%.5e\t %.5e\t %.5e\t %.5e\n", t, y[0], y[1], y[2]);
	}

	gsl_odeiv2_driver_free (d);
	return 0;
}
