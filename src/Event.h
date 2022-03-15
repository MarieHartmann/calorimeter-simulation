#ifndef Event_h
#define Event_h

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

public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBiais(float eRecoBiais) { m_eRecoBiais = eRecoBiais; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
    float eRecoBiais() const { return m_eRecoBiais; }

};

#endif
