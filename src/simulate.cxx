#include "Event.h"
#include "TRandom.h"
#include "CaloSimulation.h"
#include "CaloConstants.h"
#include <math.h>


using namespace CalConst;

void simulate(Event& event, CaloSimulation& Calorimeter, float XImpact, float YImpact)
{
    // simulate the event
    event.seteTrue(50.); // fixed true energy
    float EnergyTrue = event.eTrue();
    float E0 = 1;
    float sigma = 0.1*sqrt(EnergyTrue/E0);
    float eTrueFluc = gRandom->Gaus(event.eTrue(), sigma);
    event.seteTrue(eTrueFluc);

    //simulate the energy deposit (pure electromagnetic)
    Calorimeter.SimulateShower(XImpact, YImpact, event.eTrue());

    // simulate the energy deposit (mixed)
    //float f = gRandom->Uniform(1.);
    //float f=0.; //test with only EM as before to check if it is the same
    //float f = 0.5;
    //Calorimeter.SimulateHadShower(XImpact, YImpact, event.eTrue(), f);


}
