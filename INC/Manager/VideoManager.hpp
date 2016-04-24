#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

#include <iostream>
#include <ctime>
#include <mutex>
#include <vector>

#include "Video/Camera.hpp"
#include "Parser/YAMLParser.hpp"

#define VIDEO_MANAGER_CONFIG_FILE "config/resolutions.yml"

class VideoManager {

    public:

        VideoManager();
        ~VideoManager();
        bool isReady();

        cv::Mat & queryFrame(unsigned int id);
        bool grab(unsigned int id);
        bool retrieve(unsigned int id);

    private:

        bool init();
        bool uninit();

    private:

        unsigned int            _camerasCount;
        unsigned int            _timeout;
        unsigned int            _treshold;

        bool                    _ready;
        std::mutex              _grabLock;
        time_t                  _lastGrab;
        std::vector<Camera *>   _cameras;
};

#endif
