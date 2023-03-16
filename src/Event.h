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
    float     m_eRecoBias;    ///< reconstructed energy + bias.  

public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBias(float eRecoBias) { m_eRecoBias = eRecoBias; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
    float eRecoBias() const { return m_eRecoBias; }
};

#endif
