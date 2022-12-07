#include "Utils.hpp"
#include "Image.hpp"
#include "opencv2/calib3d.hpp"


struct Pose {
    public:
        cv::Mat R;
        cv::Mat t;
        cv::Mat P;
        int numChierality = 0;
        Pose(cv::Mat R, cv::Mat t, cv::Mat P) {
            this->R = R;
            this->t = t;
            this->P = P;
        }
        Pose() {}
        Pose operator=(const Pose &pose) {
            this->R = pose.R;
            this->t = pose.t;
            this->P = pose.P;
            this->numChierality = pose.numChierality;
            return *this;
        }
};



class _3DHandler {
    private:
    public:
        _3DHandler(std::string calibPath);
        Intrinsics intrinsics;

        // need to have these functions usable without instantiating the class
        void getRT(const Image &img1, const Image &img2);
        bool getFundamentalMatrix(const std::vector<Matches> &matches, cv::Mat &F);
        bool getFRANSAC(std::vector<Matches> matches, cv::Mat &F, 
                      int iterations, double threshold);
        Pose disambiguateRT(const cv::Mat &E, std::vector<Matches> &matches);

        cv::Mat constructNormMatrix(std::vector<double> xVec, std::vector<double> yVec, 
                                                double xMean, double yMean);
        bool checkDepthPositive(cv::Mat &pnts3D, cv::Mat R, cv::Mat t, Pose &pose);
        float unNormalizePoint(float pt, float mean, float var);
        cv::Mat rotateMatrixZ(int rotateAngle);
        double getMeanVar(std::vector<double> &vec);

        ~_3DHandler();
};