#include "CaloGeometry.h"
#include "CellAddress.h"
#include "CaloConstants.h"

using namespace CalConst;


// Return false if the (x,y,z) point is not located in the calorimeter
// volume otherwise return true and fill the CellAddress variables with the
// address of the cell that contains this point.
bool CaloGeometry::IsInside(double xyz[3], CellAddress& cellAddress){
    double x = xyz[0], y = xyz[1], z = xyz[2];

    if ( x <= XYMax && XYMin <= x &&
         y <= XYMax && XYMin <= y &&
         z <= ZMax && ZMin <= z )
       {
           // We add, half the length of the XY cell because of the
           // definition of the origin of x, y
           cellAddress = CellAddress(int( ( x + XYSize/2.) / XYSize ),
                                     int( ( y + XYSize/2.) / XYSize ),
                                     int( z / ZSize );
           return true;
       }

    return false;

}

// Give the position of the cell center.
double CaloGeometry::xCentre(const CellAddress& cellAddress){
    int x = cellAddress.ix();
    return x*XYSize;
}
double CaloGeometry::yCentre(const CellAddress& cellAddress){
    int y = cellAddress.iy();
    return y*XYSize;
}
