#include "Encoder/x264Encoder.hpp"


x264Encoder::x264Encoder(int width , int height, int fps)
{
    this->_width = width;
    this->_height = height;
    this->_fps = fps;
}


x264Encoder::~x264Encoder(void)
{

}

void x264Encoder::initilize()
{
    x264_param_default_preset(&parameters, "ultrafast", "zerolatency");

    parameters.i_log_level = X264_LOG_INFO;
    parameters.i_threads = 1;
    parameters.i_width = this->_width;
    parameters.i_height = this->_height;
    parameters.i_fps_num = this->_fps;
    parameters.i_fps_den = 1;
    parameters.i_keyint_max = this->_fps;
    parameters.b_intra_refresh = 1;
    parameters.rc.i_rc_method = X264_RC_CRF;
    parameters.rc.f_rf_constant = this->_fps - 5;
    parameters.rc.f_rf_constant_max = this->_fps + 5;
    parameters.i_sps_id = 7;
    parameters.i_log_level = X264_LOG_NONE;


    // the following two value you should keep 1
    parameters.b_repeat_headers = 1;    // to get header before every I-Frame
    parameters.b_annexb = 1; // put start code in front of nal. we will remove start code later
    x264_param_apply_profile(&parameters, "baseline");

    encoder = x264_encoder_open(&parameters);
    x264_picture_alloc(&picture_in, X264_CSP_I420, parameters.i_width, parameters.i_height);
    picture_in.i_type = X264_TYPE_AUTO;
    picture_in.img.i_csp = X264_CSP_I420;

    // i have initilized my color space converter for BGR24 to YUV420 because my opencv video capture gives BGR24 image. You can initilize according to your input pixelFormat
    convertContext = sws_getContext(parameters.i_width,
                                    parameters.i_height,
                                    AV_PIX_FMT_BGR24,
                                    parameters.i_width,
                                    parameters.i_height,
                                    AV_PIX_FMT_YUV420P,
                                    SWS_FAST_BILINEAR,
                                    NULL,
                                    NULL,
                                    NULL);
}

void x264Encoder::unInitilize()
{
    x264_encoder_close(encoder);
    sws_freeContext(convertContext);
}

void x264Encoder::encodeFrame(cv::Mat& image)
{
    int srcStride = parameters.i_width * 3;
    sws_scale(convertContext, &(image.data), &srcStride, 0, parameters.i_height, picture_in.img.plane, picture_in.img.i_stride);
    x264_nal_t* nals ;
    int i_nals = 0;
    int frameSize = -1;

    frameSize = x264_encoder_encode(encoder, &nals, &i_nals, &picture_in, &picture_out);
    if(frameSize > 0)
    {
        for(int i = 0; i< i_nals; i++)
        {
            outputQueue.push(nals[i]);
        }
    }
}

bool x264Encoder::isNalsAvailableInOutputQueue()
{
    return (!outputQueue.empty());
}

x264_nal_t x264Encoder::getNalUnit()
{
    x264_nal_t nal;
    nal = outputQueue.front();
    outputQueue.pop();
    return nal;
}
