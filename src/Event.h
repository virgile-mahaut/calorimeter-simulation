#ifndef Event_h
#define Event_h

/**
 * @bried Event class.
 * @details This class describes an event.
 */

#include "CaloSimulation.h"

class Event {
private:
    int                     m_eventNumber ; ///< event number.
    float                   m_eTrue ;       ///< true energy.
    float                   m_eReco ;       ///< reconstructed energy.
    float                   m_eRecoBias;    ///< reconstructed energy + bias.
    float                   m_x;            ///< Impact position (y axis)
    float                   m_y;            ///< Impact position (y axis)
    float                   m_xReco;        ///< Reconstructed impact position (x axis)
    float                   m_yReco;        ///< Reconstructed impact position (y axis)
    float                   m_xRecoBar;     ///< Reconstructed impact position (x axis) (barycentre)
    float                   m_yRecoBar;     ///< Reconstructed impact position (y axis) (barycentre)
    std::vector<CaloCell>   m_caldata;      ///< Vector of calorimeter cells

public:
    Event(); ///< Constructor.
    virtual ~Event(); ///< Destructor.

    void build(int eventNumber); // initialize

    // setters
    void setEventNumber(int eventNumber) { m_eventNumber = eventNumber; }
    void seteTrue(float eTrue) { m_eTrue = eTrue; }
    void seteReco(float eReco) { m_eReco = eReco; }
    void seteRecoBias(float eRecoBias) { m_eRecoBias = eRecoBias; }
    void setx(float x0) { m_x = x0; }
    void sety(float y0) { m_y = y0; }
    void setxReco(float x0) { m_xReco = x0; }
    void setyReco(float y0) { m_yReco = y0; }
    void setxRecoBar(float x0) { m_xRecoBar = x0; }
    void setyRecoBar(float y0) { m_yRecoBar = y0; }
    void setCalData(std::vector<CaloCell>   caldat) { m_caldata = caldat; }

    // getters
    int eventNumber() const { return m_eventNumber; }
    float eTrue() const { return m_eTrue; }
    float eReco() const { return m_eReco; }
    float eRecoBias() const { return m_eRecoBias; }
    float x() const { return m_x; }
    float y() const { return m_y; }
    float xReco() const { return m_xReco; }
    float yReco() const { return m_yReco; }
    float xRecoBar() const { return m_xRecoBar; }
    float yRecoBar() const { return m_yRecoBar; }
    std::vector<CaloCell> calData() const { return m_caldata; }

};

#endif
