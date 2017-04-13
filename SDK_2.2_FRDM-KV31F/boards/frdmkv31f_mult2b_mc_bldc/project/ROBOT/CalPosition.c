


// Sensor Fusion Headers
#include "sensor_fusion.h"      // top level magCal and sensor fusion interfaces

//CMSIS DSP
#include "arm_math.h"

// add Fir filter to remove continue part of acceleration
// used to reduce integration errors accumulation

#define NUMBER_OF_STAGE 4
#define BLOCK_SIZE      1

// parameters calculated with http://www.micromodeler.com/dsp/

static arm_iir_lattice_instance_f32 filterIIR;
static float afkCoeffs[NUMBER_OF_STAGE];
static float afvCoeffs[NUMBER_OF_STAGE-1];
static float afState[NUMBER_OF_STAGE+BLOCK_SIZE];

static float gfAccGl[3];

void CalculatePosition (struct SV_9DOF_GBY_KALMAN *pthisSV)
{
    static uint8 IsInitialized= 0;

    if(IsInitialized == 0)
    {
        arm_iir_lattice_init_f32(&filterIIR,
	                             NUMBER_OF_STAGE,
	                             &afkCoeffs[0],
	                             &afvCoeffs[0],
	                             &afState[0],
	                             BLOCK_SIZE);
        IsInitialized = 1;
    }
    else
    {
        arm_iir_lattice_f32(&filterIIR,
		                    &pthisSV->fAccGl[CHX],
                            &gfAccGl[CHX],
	   		                BLOCK_SIZE);
    }
}

#if 0
// integrate the acceleration to velocity and displacement in the global frame.
// Note: integration errors accumulate without limit over time and this code should only be
// used for inertial integration of the order of seconds.
for (i = CHX; i <= CHZ; i++) {

    // integrate acceleration (in g) to velocity in m/s
    pthisSV->fVelGl[i] += pthisSV->fAccGl[i] * pthisSV->fgdeltat;
    // integrate velocity (in m/s) to displacement (m)
    pthisSV->fDisGl[i] += pthisSV->fVelGl[i] * pthisSV->fdeltat;
}

     }
}

#endif



