#include "Event.h"
#include "TRandom.h"
#include "CaloSimulation.h"
#include "CaloConstants.h"

using namespace CalConst;

void simulate(Event& event)
{
    // simulate the event

    event.seteTrue(50.); // fixed true energy

    // draw randomly the impact point
    float XImpact = gRandom->Uniform(XYMax - XYMin) + XYMin;
    float YImpact = gRandom->Uniform(XYMax - XYMin) + XYMin;

    // simulate the energy deposit
    CaloSimulation CaloSimu;
    CaloSimu.SimulateShower(XImpact, YImpact, event.eTrue());








}
