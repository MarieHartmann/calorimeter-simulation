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
    float     m_eRecoBiais ;  ///< reconstruction biais.
    float     m_xReco;        ///<  reconstructed x impact position.
    float     m_yReco;        ///< reconstructed y impact position.
    float     m_xTrue;        ///< true x position of the impact.
    float     m_yTrue;        ///< true y position  of the impact.

public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBiais(float eRecoBiais) { m_eRecoBiais = eRecoBiais; }
    void setxReco(float xReco) {m_xReco = xReco; }
    void setyReco(float yReco) {m_yReco = yReco; }
    void setxTrue(float xTrue) {m_xTrue = xTrue; }
    void setyTrue(float yTrue) {m_yTrue = yTrue; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
    float eRecoBiais() const { return m_eRecoBiais; }
    float xReco() const { return m_xReco; }
    float yReco() const { return m_yReco; }
    float xTrue() const { return m_xTrue; }
    float yTrue() const { return m_yTrue; }



};

#endif
