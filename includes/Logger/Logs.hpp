#ifndef LOGS_HPP
#define LOGS_HPP

#include <iostream>
#include <string>

#define START_SERVER          "Starting ROC Server"
#define START_MANAGER         "Starting ROC Manager..."
#define START_VIDEOMANAGER    "Starting ROC VideoManager..."
#define START_RTSP            "Starting ROC RTSP Server(s)..."
#define START_INTERPRETOR     "Starting ROC Interpretor..."
#define START_CAMERA          "Starting ROC Cameras..."
#define START_CONFIG          "Starting to load ROC Configuration..."

#define STOP_SERVER           "Stopped ROC Server"
#define STOP_MANAGER          "Stopped ROC Manager"
#define STOP_VIDEOMANAGER     "Stopped ROC VideoManager"
#define STOP_RTSP             "Stopped ROC RTSP Server(s)"
#define STOP_INTERPRETOR      "Stopped ROC Interpretor"
#define STOP_CAMERA           "Stopped ROC Cameras"
#define STOP_SYNC_JOB         "Stopped ROC Sync job"

#define INFO_RTSP_URL(url)    ((std::string)"ROC RTSP Server started on url " + url)
#define INFO_TCP_PORT(var)    ((std::string)"ROC TCP Server started on port " + std::to_string(var))
#define INFO_CONFIG(k , v)    ((std::string) k + "\t: " + std::to_string(v))
#define INFO_WAIT_SYNC_JOB    "Waiting for ROC Sync job to finish"

#define WARNING_SYNC_USELESS  "Synchronizing only one camera"
#define WARNING_SYNC_TIMEOUT  "Synchonization timed out"
#define WARNING_EXIT_SIGNAL   "Exit command catched , performing cleanup"
#define WARNING_EXIT_LOGGER   "Stopping logger : no more logs beyond this point"
#define WARNING_MANUAL        "About to set manual exposure , things may break if your device doesn't support it"

#define SUCCESS_MANAGER       "ROC Manager started"
#define SUCCESS_VIDEOMANAGER  "ROC VideoManager started"
#define SUCCESS_RTSP          "ROC RTSP Server(s) started"
#define SUCCESS_INTERPRETOR   "ROC Interpretor started"
#define SUCCESS_CONFIG        "ROC Configuration loaded"
#define SUCCESS_CAMERAS       "ROC Cameras started"
#define SUCCESS_SYNC_JOB      "ROC Sync job started"
#define SUCCESS_WIDTH         "ROC Camera width successfully set"
#define SUCCESS_HEIGHT        "ROC Camera height successfully set"
#define SUCCESS_FPS           "ROC Camera fps successfully set"
#define SUCCESS_TCP           "ROC Client connected"

#define ERROR_ARGS            "Error while getting program arguments : ./Server [PORT]"
#define ERROR_MANAGER         "Error while starting ROC Manager"
#define ERROR_VIDEOMANAGER    "Error while starting ROC VideoManager"
#define ERROR_RTSP            "Error while starting ROC RTSP Server(s)"
#define ERROR_INTERPRETOR     "Error while starting ROC Interpretor"
#define ERROR_CONFIG_OPEN     "Error while opening ROC configuration file"
#define ERROR_CONFIG          "Error while Parsing ROC Configuration"
#define ERROR_CANERAS         "Error while starting ROC Cameras"
#define ERROR_CAMERAS_COUNT   "Error while getting ROC Cameras count : must be a positive integer number"
#define ERROR_TIMEOUT         "Error while setting timeout : must be more than the minimum frame display time"
#define ERROR_WIDTH           "Error while setting width : must be a positive integer"
#define ERROR_HEIGHT          "Error while setting height : must be a positive integer"
#define ERROR_FPS             "Error while setting FPS : must be a positive integer"
#define ERROR_IDs             "Error while setting cameras IDs , mismatch in camera_count and number of ID(s)"
#define ERROR_PORT            "Error while parsing port number : must be a positive integer number"
#define ERROR_CAMERAS_OPEN    "Error while opening ROC Cameras : check that the device(s) are plugged in"
#define ERROR_CAMERAS_INIT    "Error while initializing ROC Cameras : check that the device(s) supports the requirements and is not busy"
#define ERROR_CAMERA_WIDTH    "Error while setting ROC Camera width"
#define ERROR_CAMERA_HEIGHT   "Error while setting ROC Camera height"
#define ERROR_CAMERA_FPS      "Error while setting ROC Camera fps"
#define ERROR_TCP             "Error while establishing TCP connection"

#endif
