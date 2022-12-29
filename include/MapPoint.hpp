#ifndef MAPPOINT_H
#define MAPPOINT_H


#include "Utils.hpp"
#include "Feature.hpp"
#include "MapPoint.hpp"
#include <Eigen/Core>

typedef Eigen::Matrix<double, 3, 1> Vec3;

class Feature;
class MapPoint;
class MapPoint {
    public:
        unsigned long ptID;
        int obsCount;
        std::shared_ptr<MapPoint> ptr;
        std::mutex mapPointMutex;
        Vec3 position;
        std::vector<std::shared_ptr<Feature>> observations;
        MapPoint(){}
        MapPoint(unsigned long _ptID, Vec3 _pos);
        void setPos(const Vec3 &pos);
        Vec3 getPos();

};

#endif // TODOITEM_H
