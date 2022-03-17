#include "CaloCell.h"
#include "CellAddress.h"

// Default constructor needed of containers of the standard template library.
CaloCell::CaloCell(){
    m_energy = -999;
    m_address = CellAddress();
}

// Full constructor.
CaloCell::CaloCell(const CellAddress& ca, float energy){
    m_energy = energy;
    m_address = ca;
}

// Accessors.
float CaloCell::energy() const {
    return(m_energy);
}
CellAddress CaloCell::address() const{
    return(m_address);
}

// Setters.
void CaloCell::setEnergy(float energy) {
    m_energy = energy;
}
