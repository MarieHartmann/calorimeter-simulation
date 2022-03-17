#include "Event.h"
#include "TRandom.h"
#include "CaloSimulation.h"
#include "CaloConstants.h"

using namespace CalConst;

void simulate(Event& event, CaloSimulation& Calorimeter, float XImpact, float YImpact)
{
    // simulate the event
    event.seteTrue(50.); // fixed true energy

    // simulate the energy deposit
    Calorimeter.SimulateShower(XImpact, YImpact, event.eTrue());


}
