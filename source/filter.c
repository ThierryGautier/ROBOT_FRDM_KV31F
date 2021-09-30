#if 0 /* TODO */
/******************************* SOURCE LICENSE *********************************
Copyright (c) 2015 MicroModeler.

A non-exclusive, nontransferable, perpetual, royalty-free license is granted to the Licensee to 
use the following Information for academic, non-profit, or government-sponsored research purposes.
Use of the following Information under this License is restricted to NON-COMMERCIAL PURPOSES ONLY.
Commercial use of the following Information requires a separately executed written license agreement.

This Information is distributed WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

******************************* END OF LICENSE *********************************/

// A commercial license for MicroModeler DSP can be obtained at http://www.micromodeler.com/launch.jsp

#include "sensor_fusion.h" //sensor_fusion include
#include "arm_math.h"      //CMSIS filter prototype

#define FILTER_NUM_STAGE 2

arm_biquad_casd_df1_inst_f32 gxfilter_instance[3];
float32_t state[3][8];

#if 0
float32_t filter_coefficients[10] = 
{
// Scaled for floating point
    1.3240316744052347, -2.6480633488104695, 1.3240316744052347, 1.4796742169311934, -0.5558215432824889,// b0, b1, b2, a1, a2
    0.5, -1, 0.5, 1.700964331943526, -0.7884997398152981// b0, b1, b2, a1, a2
};
#endif
float32_t filter_coefficients[10] =
{
// Scaled for floating point

    0.9676948088896711, -1.9353896177793422, 0.9676948088896711, 1.954001961679803, -0.9546192513864591,// b0, b1, b2, a1, a2
    1, -2, 1, 1.980323859118934, -0.9809494641889661// b0, b1, b2, a1, a2

};


float gfAccGlOutput[3];
float gfVelGl[3];
float gfPosition[3];

void filter_filterBlock(SensorFusionGlobals* sfg)
{
	static int WaitInitSensorfusion =0;

	int i;

	if(WaitInitSensorfusion==0)
	{
		for (i = CHX; i <= CHZ; i++)
		{
			arm_biquad_cascade_df1_init_f32(&gxfilter_instance[i],
											FILTER_NUM_STAGE,
											&filter_coefficients[0],
											&state[i][0]);
		}
		WaitInitSensorfusion++;
	}
	else if(WaitInitSensorfusion<40)
	{
        //do noting wait 40 sensor fusion cycle => 1 s *
		WaitInitSensorfusion++;
	}
	else
	{
		for (i = CHX; i <= CHZ; i++)
		{
			arm_biquad_cascade_df1_f32(&gxfilter_instance[i], &(sfg->SV_9DOF_GBY_KALMAN.fAccGl[i]), &gfAccGlOutput[i], 1);
		}

	    // integrate the acceleration to velocity and displacement in the global frame.
	    // Note: integration errors accumulate without limit over time and this code should only be
	    // used for inertial integration of the order of seconds.
	    for (i = CHX; i <= CHZ; i++) {
	        // integrate acceleration (in g) to velocity in m/s
	        gfVelGl[i] += gfAccGlOutput[i] * sfg->SV_9DOF_GBY_KALMAN.fgdeltat;
	        // integrate velocity (in m/s) to displacement (m)
	        gfPosition[i] += gfVelGl[i] * sfg->SV_9DOF_GBY_KALMAN.fdeltat;
	    }
	}
}
#endif
