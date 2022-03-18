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
    float RecoEnergy = gRandom->Gaus(event.eTrue(), sigma);
    event.seteReco(RecoEnergy);

    // simulate the energy deposit
    Calorimeter.SimulateShower(XImpact, YImpact, event.eTrue());


}
