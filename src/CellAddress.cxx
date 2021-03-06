#include "CellAddress.h"
#include "CaloConstants.h"

using namespace CalConst;

// Default constructor, gives you an invalid address.
CellAddress::CellAddress(){
    m_ix = -999;
    m_iy = -999;
    m_layer = -999;
}

// Full constructor.
// We choose the cell (0,0) to be on the bottom left of the calorimeter
CellAddress::CellAddress(int ix, int iy, int layer){
    m_ix = ix;
    m_iy = iy;
    m_layer = layer;
}

// Is the address valid.
bool CellAddress::IsValid() const  {
    return  (m_ix <= NbCellsInXY && 0 <= m_ix &&
       m_iy <= NbCellsInXY && 0 <= m_iy &&
       m_layer <= NbLayers && 0 <= m_layer );
}

// Accessors.
int CellAddress::ix() const{
    return m_ix;
}
int CellAddress::iy() const{
    return m_iy;
}
int CellAddress::layer() const{
    return m_layer;
}
