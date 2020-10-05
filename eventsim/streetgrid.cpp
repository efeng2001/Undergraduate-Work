#include <stdexcept>
#include <algorithm>
#include <iomanip>
#include "streetgrid.h"
#include "derived_events.h"

StreetGrid::StreetGrid(
    const std::vector<unsigned int> rowCapacities,
    const std::vector<unsigned int> colCapacities)
    : rowCapacities_(rowCapacities), colCapacities_(colCapacities)
{
    n = rowCapacities.size();
    m = colCapacities.size();
    expectedVehicles_ = 0;

    // TO BE COMPLETED
    rowOccupancy = new size_t*[n];
    for(size_t i=0; i<n; i++){
        rowOccupancy[i] = new size_t[m-1];
    }

    for(size_t i=0; i<n; i++){
        for(size_t j=0; j<m-1; j++){
            rowOccupancy[i][j] = 0;
        }
    }

    colOccupancy = new size_t*[n-1];
    for(size_t i=0; i<n-1; i++){
        colOccupancy[i] = new size_t[m];
    }

    for(size_t i=0; i<n-1; i++){
        for(size_t j=0; j<m; j++){
            colOccupancy[i][j] = 0;
        }
    }

    rowBlockages = new bool*[n];
    for(size_t i=0; i<n; i++){
        rowBlockages[i] = new bool[m-1];
    }

    for(size_t i=0; i<n; i++){
        for(size_t j=0; j<m-1; j++){
            rowBlockages[i][j] = false;
        }
    }

    colBlockages = new bool*[n-1];
    for(size_t i=0; i<n-1; i++){
        colBlockages[i] = new bool[m];
    }

    for(size_t i=0; i<n-1; i++){
        for(size_t j=0; j<m; j++){
            colBlockages[i][j] = false;
        }
    }

    rowTurn = new int*[n];
    for(size_t i=0; i<n; i++){
        rowTurn[i] = new int[m-1];
    }

    for(size_t i=0; i<n; i++){
        for(size_t j=0; j<m-1; j++){
            rowTurn[i][j] = 0;
        }
    }

    colTurn = new int*[n-1];
    for(size_t i=0; i<n-1; i++){
        colTurn[i] = new int[m];
    }

    for(size_t i=0; i<n-1; i++){
        for(size_t j=0; j<m; j++){
            colTurn[i][j] = 0;
        }
    }
    // Call monitor state to output starting state
    monitorState();
}

StreetGrid::~StreetGrid()
{
    for(size_t i=0; i<n; i++){
        delete[] rowOccupancy[i];
    }
    delete[] rowOccupancy;

    for(size_t i=0; i<n-1; i++){
        delete[] colOccupancy[i];
    }
    delete[] colOccupancy;

    for(size_t i=0; i<n; i++){
        delete[] rowBlockages[i];
    }
    delete[] rowBlockages;

    for(size_t i=0; i<n-1; i++){
        delete[] colBlockages[i];
    }
    delete[] colBlockages;

    for(size_t i=0; i<n; i++){
        delete[] rowTurn[i];
    }
    delete[] rowTurn;

    for(size_t i=0; i<n-1; i++){
        delete[] colTurn[i];
    }
    delete[] colTurn;
}


size_t StreetGrid::numRows() const
{
    return n;
}
size_t StreetGrid::numCols() const
{
    return m;
}
void StreetGrid::setExpected(size_t expectedVehicles)
{
    expectedVehicles_ = expectedVehicles;
}

void StreetGrid::outputCompletedVehicles(std::ostream& ostr) const
{
    for(auto v : completed_) {
        ostr << v.end << " " << v.id << std::endl;
    }
}

bool StreetGrid::allVehiclesArrived() const
{
    return completed_.size() == expectedVehicles_;
}

void StreetGrid::monitorState()
{
    std::cout << "State: " << std::endl;
    std::cout << std::setw(4) << " ";

    // Print header row with column capacities
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << colCapacities_[cidx] << " " <<  std::setw(4) << " ";
    }
    std::cout << std::endl;
    std::cout << "    ";
    for(size_t cidx = 0; cidx < m; ++cidx) {
        std::cout <<  std::setw(4) << "====="  << "=====";
    }
    std::cout << std::endl;

    // Start printing grid data
    for(size_t ridx = 0; ridx < n; ++ridx) {
        // Print row capacity
        std::cout << std::setw(2) << rowCapacities_[ridx] << " |";
        // Print row occupancies
        for(size_t cidx = 0; cidx < m; ++cidx) {
            std::cout << std::setw(4) << "+" << " ";
            if(cidx < m-1) {
                if(isBlocked(ridx,cidx,true)) {
                    std::cout << std::setw(3) << getRowOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getRowOccupancy(ridx,cidx);
                }
            }
        }
        std::cout << std::endl;
        std::cout <<  "   |";
        // Print column occupancies
        if(ridx < n-1) {
            for(size_t cidx = 0; cidx < m; ++cidx) {
                if(isBlocked(ridx,cidx,false)) {
                    std::cout << std::setw(3) << getColOccupancy(ridx,cidx);
                    std::cout << "B";
                }
                else {
                    std::cout << std::setw(4) << getColOccupancy(ridx,cidx);
                }
                std::cout << std::setw(4) << " " << " " ;
            }
        }
        std::cout << std::endl;

    }
}

size_t StreetGrid::getRowOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    return rowOccupancy[row][col];
}

size_t StreetGrid::getColOccupancy(size_t row, size_t col) const
{
    // TO BE COMPLETED
    return colOccupancy[row][col];
}

bool StreetGrid::isBlocked(size_t row, size_t col, bool rowDir) const
{
    // TO BE COMPLETED
    if(rowDir){
        return rowBlockages[row][col];
    }else{
        return colBlockages[row][col];
    }
}

bool StreetGrid::shouldChooseRow(size_t row, size_t col)
{
    // TO BE COMPLETED
    //  time = max(1, (1+num_vehicles) / street_capacity) * SCALE_FACTOR
    if(row == n-1){
        return true;
    }else if(col == m-1){
        return false;
    }else if(rowBlockages[row][col] == true){
        return false;
    }else if(colBlockages[row][col] == true){
        return true;
    }else{
        int rowTime = std::max((double)1, ((1 + getRowOccupancy(row, col)) / (double)rowCapacities_[row])) * SCALE_FACTOR;
        int colTime = std::max((double)1, ((1 + getColOccupancy(row, col)) / (double)colCapacities_[col])) * SCALE_FACTOR;
        if(rowTime > colTime){
            return false;
        }else if(rowTime < colTime){
            return true;
        }else{
            if(rowTurn[row][col] > colTurn[row][col]){
                colTurn[row][col]++; 
                return false;
            }else{
                rowTurn[row][col]++; 
                return true;
            }
        }
    }
}

void StreetGrid::setBlockage(size_t row, size_t col, bool rowDir, bool val)
{
    // TO BE COMPLETED
    if(rowDir){
        if(row < n && row >= 0){
            if(val == true && colBlockages[row][col] == true){
                return;
            }else{
                rowBlockages[row][col] = val;                
            }
        }
    }else{
        if(col < m && col >= 0){
            if(val == true && rowBlockages[row][col] == true){
                return;
            }else{
                colBlockages[row][col] = val;                
            }
        }
    }
}

EventList StreetGrid::processArrival(const std::string& vehicleID, const TimeStamp& ts)
{
    // TO BE COMPLETED
    if(vehicles_.find(vehicleID) == vehicles_.end()){
        throw std::logic_error("vehicle ID not find");
    }

    EventList rtn;
    Vehicle vehicle = vehicles_.find(vehicleID) -> second;

    if(vehicle.rowDir){
            rowOccupancy[vehicle.rowIndex][vehicle.colIndex-1] --;
        }else{
            colOccupancy[vehicle.rowIndex-1][vehicle.colIndex] --;
        }

    if(vehicle.rowIndex == n-1 && vehicle.colIndex == m-1){
        completed_.push_back(vehicle);
        vehicles_[vehicle.id] = vehicle;
        return rtn;
    }else{
        if(shouldChooseRow(vehicle.rowIndex, vehicle.colIndex)){
            vehicle.rowDir = true;
            TimeStamp time = std::max((double)1, ((1 + getRowOccupancy(vehicle.rowIndex, vehicle.colIndex)) / (double)rowCapacities_[vehicle.rowIndex])) * SCALE_FACTOR;
            vehicle.end += time;
            // std::cout << "vehicle end time " << vehicle.end << std::endl;
            rtn.push_back(new ArrivalEvent(vehicle.end, *this, vehicle.id));
            rowOccupancy[vehicle.rowIndex][vehicle.colIndex] ++;
            vehicle.colIndex++;
            vehicles_[vehicle.id] = vehicle;
        }else{
            vehicle.rowDir = false;
            TimeStamp time = std::max((double)1, ((1 + getColOccupancy(vehicle.rowIndex, vehicle.colIndex)) / (double)colCapacities_[vehicle.colIndex])) * SCALE_FACTOR;
            // std::cout << "added time " << time << std::endl;
            vehicle.end += time;
            // std::cout << "vehicle end time " << vehicle.end << std::endl;
            rtn.push_back(new ArrivalEvent(vehicle.end, *this, vehicle.id));
            colOccupancy[vehicle.rowIndex][vehicle.colIndex] ++;
            vehicle.rowIndex++;
            vehicles_[vehicle.id] = vehicle;
        }
    }

    return rtn; 
}

EventList StreetGrid::addVehicle(const Vehicle& v)
{
    // TO BE COMPLETED
    if(vehicles_.find(v.id) != vehicles_.end()){
        throw std::logic_error("vehicle ID alreadt added");
    }
    vehicles_[v.id] = v;

    Vehicle vehicle = vehicles_.find(v.id) -> second;
    EventList rtn;

    //std::cout << "id " << vehicle.id << std::endl;
    
    if(vehicle.rowIndex == n-1 && vehicle.colIndex == m-1){
        vehicles_[v.id] = vehicle;
        completed_.push_back(vehicle);
        return rtn;
    }else{
        if(shouldChooseRow(vehicle.rowIndex, vehicle.colIndex)){
            vehicle.rowDir = true;
            TimeStamp time = std::max((double)1, ((1 + getRowOccupancy(vehicle.rowIndex, vehicle.colIndex)) / (double)rowCapacities_[vehicle.rowIndex])) * SCALE_FACTOR;
            vehicle.end = vehicle.start + time;
            //std::cout << "vehicle end time " << vehicle.end << std::endl;
            rtn.push_back(new ArrivalEvent(vehicle.end, *this, vehicle.id));
            rowOccupancy[vehicle.rowIndex][vehicle.colIndex] ++;
            vehicle.colIndex++;
            vehicles_[v.id] = vehicle;
        }else{
            vehicle.rowDir = false;
            TimeStamp time = std::max((double)1, ((1 + getColOccupancy(vehicle.rowIndex, vehicle.colIndex)) / (double)colCapacities_[vehicle.colIndex])) * SCALE_FACTOR;
            vehicle.end = vehicle.start + time;
            //std::cout << "vehicle end time " << vehicle.end << std::endl;
            rtn.push_back(new ArrivalEvent(vehicle.end, *this, vehicle.id));
            colOccupancy[vehicle.rowIndex][vehicle.colIndex] ++;
            vehicle.rowIndex++;
            vehicles_[v.id] = vehicle;
        }
    }

    return rtn;
}


