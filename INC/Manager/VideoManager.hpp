#ifndef VIDEO_MANAGER_HPP
#define VIDEO_MANAGER_HPP

#include <iostream>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>
#include "Video/Camera.hpp"
#include "Parser/YAMLParser.hpp"
#include "Sync/LockList.hpp"

#define VIDEO_MANAGER_CONFIG_FILE "config/resolutions.yml"

typedef struct {
  Camera * _camera;
  std::mutex mtx;
  volatile int watcher;
} concurentCamera;

class VideoManager {

    public:

        VideoManager();
        ~VideoManager();
        bool isReady();

        cv::Mat & queryFrame(unsigned int id);
        cv::Mat & getFrame(unsigned int id);

        void waitSync();

        int getWidthById(unsigned int id);
        int getHeightById(unsigned int id);
        int getFpsById(unsigned int id);

        bool run();
        bool loop();

    private:

        bool init();
        bool uninit();
        bool spawn();

        bool grab(unsigned int id);
        bool retrieve(unsigned int id);

        void grabAll();
        void retrieveAll();
        void flipAll();

    private:

        unsigned int            _camerasCount;
        unsigned int            _timeout;
        unsigned int            _treshold;

        bool                    _ready;
        time_t                  _lastGrab;
        std::vector<Camera *>   _cameras;
        LockList *              _lockList;
};

#endif
