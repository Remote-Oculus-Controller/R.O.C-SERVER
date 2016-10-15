#include "Encoder/x265Encoder.hpp"

x265Encoder::x265Encoder(int width, int height, int fps) 
{
	this->_width = width;
	this->_height = height;
	this->_fps = fps;
}

x265Encoder::~x265Encoder(void)
{

}


void x265Encoder::initialize()
{
  parameters = x265_param_alloc();
  x265_param_default_preset(parameters, "ultrafast" ,"zerolatency");

  parameters->fpsNum = _fps;
  parameters->fpsDenom = 1;
  parameters->sourceWidth = _width;
  parameters->sourceHeight = _height;
  parameters->bRepeatHeaders = 1;
  parameters->keyframeMax = _fps;
  parameters->bIntraRefresh = 1;
  parameters->logLevel = X265_LOG_INFO;
  parameters->numaPools = "none";
  parameters->bAnnexB = 1;

  x265_param_apply_profile(parameters, "baseline");
  encoder = x265_encoder_open(parameters);

  picture_in = x265_picture_alloc();
  picture_out = x265_picture_alloc();

  x265_picture_init(parameters , picture_in);
  picture_in->colorSpace = X265_CSP_I420;
  picture_in->sliceType = X265_TYPE_AUTO;

  x265_picture_init(parameters , picture_out);

  convertContext = sws_getContext(_width,
                                  _height,
                                  AV_PIX_FMT_BGR24,
                                  _width,
                                  _height,
                                  AV_PIX_FMT_YUV420P,
                                  SWS_FAST_BILINEAR,
                                  NULL,
                                  NULL,
                                  NULL);

}

void x265Encoder::unInitialize()
{
  x265_picture_free(picture_in);
  x265_picture_free(picture_out);
	x265_encoder_close(encoder);
  x265_param_free(parameters);
	sws_freeContext(convertContext);
}

void x265Encoder::encodeFrame(cv::Mat & image)
{
    int srcStride = parameters->sourceWidth * 3;
    sws_scale(convertContext, &(image.data), &srcStride, 0, parameters->sourceHeight, (uint8_t* const*)picture_in->planes, picture_in->stride);
    x265_nal * nals ;
    unsigned int i_nals = 0;
    int frameSize = -1;

    frameSize = x265_encoder_encode(encoder, &nals, &i_nals, picture_in, picture_out);
    if(frameSize > 0)
    {
        for(int i = 0; i< i_nals; i++)
        {
            outputQueue.push(nals[i]);
        }
    }
}

bool x265Encoder::isNalsAvailableInOutputQueue()
{
	return (!outputQueue.empty());
}

x265_nal x265Encoder::getNalUnit()
{
	x265_nal nal;
	nal = outputQueue.front();
	outputQueue.pop();
	return nal;
}

int x265Encoder::set(x265_param * parameters , const char * param , const char * value)
{
  int result;

  result = x265_param_parse(parameters , param , value);
  if (result != 0)
    logger::log(ERROR_265(param) , logger::logType::WARNING);
  return result;
}
