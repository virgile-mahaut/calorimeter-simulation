#ifndef Event_h
#define Event_h

/**
 * Event
 * Describes an event.
 */

class Event
{
private:
    int       m_eventNumber ; // event number
    float     m_eTrue ; // true energy
    float     m_eReco ; // reconstructed energy

public:
    Event(); // constructor
    virtual ~Event(); // destructor

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
};

#endif
