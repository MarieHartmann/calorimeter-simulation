#ifndef Event_h
#define Event_h

#include "CaloSimulation.h"

/**
 * @bried Event class.
 * @details This class describes an event.
 */
class Event {

private:
    int       m_eventNumber ; ///< event number.
    float     m_eTrue ;       ///< true energy.
    float     m_eReco ;       ///< reconstructed energy.
    float     m_eRecoBiais ;  ///< reconstruction biais
    float     m_XImpact ;     ///< x coordinate of the impact
    float     m_YImpact ;     ///< y coordinate of the impact
    CaloSimulation  m_CaloSimu; ///< calorimeter cells

public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBiais(float eRecoBiais) { m_eRecoBiais = eRecoBiais; }
    void setXImpact(float XImpact) { m_XImpact = XImpact; }
    void setYImpact(float YImpact) { m_YImpact = YImpact; }
    void setCaloSimu(CaloSimulation CaloSimu)  { m_CaloSimu = CaloSimu; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
    float eRecoBiais() const { return m_eRecoBiais; }
    float XImpact () const { return m_XImpact; }
    float YImpact () const { return m_YImpact; }
    CaloSimulation CaloSimu () const { return m_CaloSimu; }
};

#endif
