// TODO: To be completed.

#include "Event.h"

//______________________________________________________________________________
Event::Event()
{
}

//______________________________________________________________________________
Event::~Event()
{
}

//______________________________________________________________________________
void Event::build(int eventNumber)
{
    // set event number
    m_eventNumber = eventNumber;

    // initialize data member to invalid values
    m_eTrue = -999.;
    m_eReco = -999.;
    m_eRecoBiais = -999.;

    m_XImpact = -999.;
    m_YImpact = -999.;
    //m_CaloSimu = CaloSimulation();


}
