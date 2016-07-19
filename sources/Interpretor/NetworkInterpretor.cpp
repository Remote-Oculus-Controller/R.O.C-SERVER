#include "Interpretor/NetworkInterpretor.hpp"

NetworkInterpretor::NetworkInterpretor(Manager * parent)
{
  this->_parent = parent;
  this->_keepAlive = false;
  this->_isAsyncRunning = false;
}

NetworkInterpretor::~NetworkInterpretor()
{
    if (this->_isAsyncRunning == true)
    {
      this->_keepAlive = false;
      waitRunner();
    }
}

void NetworkInterpretor::run()
{
  this->_keepAlive = true;

  std::thread * reader = new std::thread(&NetworkInterpretor::runner , this);
  reader->detach();
}

void NetworkInterpretor::waitRunner()
{
  std::unique_lock<std::mutex> _lock(this->_lockMain);
  while (this->_isAsyncRunning == true)
    this->_conditionMain.wait(_lock);
}

void NetworkInterpretor::runner()
{
  this->_isAsyncRunning = true;
  protocol::Packet * message;

  while (this->_keepAlive == true)
  {
      while (this->_parent->isInputAvailable())
      {
        message = this->_parent->popInput();
        if (this->isValid(message))
        {
          if (this->needRerouting(message))
            this->_parent->pushOutput(message);
          else
            this->handlePacket(message);
        }
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  this->_keepAlive = false;
  this->_conditionMain.notify_all();
}


bool NetworkInterpretor::isValid(protocol::Packet * message)
{
    return message->magic() == 0xAF;
}

bool NetworkInterpretor::needRerouting(protocol::Packet * message)
{
  unsigned int destination;
  destination = (this->createMask(0 , 3) & message->header());
  return destination != 2;
}


unsigned NetworkInterpretor::createMask(unsigned a, unsigned b)
{
   unsigned r = 0;
   for (unsigned i=a; i<b; i++)
       r |= 1 << i;

   return r;
}

unsigned NetworkInterpretor::createHeader(unsigned type , unsigned from , unsigned to)
{
  return (type << 6) | (from << 3) | to;
}

void NetworkInterpretor::handlePacket(protocol::Packet * message)
{
 logger::log("id : " + std::to_string(message->id()) , logger::logType::WARNING);
  switch (message->id()) {
    case 0x30:
      this->connectionQuery(message);
    break;
    case 0x31:
      this->clearQuery();
    break;
    case 0x32:
      this->cannyQuery(message);
    break;
    case 0x33:
      this->faceQuery(message);
    break;
    case 0x34:
      this->zoomQuery(message);
    break;
    case 0x35:
      this->eyeQuery(message);
    break;
    case 0x36:
      this->upperBodyQuery(message);
    break;
    case 0x37:
      this->lowerBodyQuery(message);
    break;
    case 0x38:
      this->fullBodyQuery(message);
    break;
  }
  delete message;
}

void NetworkInterpretor::connectionQuery(protocol::Packet * message)
{
    std::cout << "Connection query !" << std::endl;
  protocol::Packet * response = new protocol::Packet();
  protocol::Connection payload;
  char header;

  if (response == NULL)
    return;

  std::cout << "Building connection answer !" << std::endl;
  payload.set_port(configuration::port);
  payload.set_cameras(configuration::camera_count);
  response->mutable_payload()->PackFrom(payload);
  response->set_magic(0xAF);
  response->set_id(0x30);
  response->set_header(this->createHeader(DATA , VSERVER , VCLIENT));
  this->_parent->pushOutput(response);
}

void NetworkInterpretor::clearQuery()
{
  this->_parent->getVideoManager()->getProcessingWrapper().clearProcessing();
}

void NetworkInterpretor::cannyQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new CannyEdge(payload.param1(), payload.param2()));
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::CANNY);
}

void NetworkInterpretor::faceQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new FaceDetect());
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::FACEDETECT);
}

void NetworkInterpretor::zoomQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  this->_parent->getVideoManager()->setAll(27 , payload.param1());
}

void NetworkInterpretor::eyeQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new EyeDetect());
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::EYEDETECT);
}

void NetworkInterpretor::upperBodyQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new UpperBodyDetect());
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::UPPERBODY);
}

void NetworkInterpretor::lowerBodyQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new LowerBodyDetect());
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::LOWERBODY);
}

void NetworkInterpretor::fullBodyQuery(protocol::Packet * message)
{
  protocol::Processing payload;

  if (message->payload().UnpackTo(&payload) == false)
    return;

  if (payload.action() == protocol::Processing_Action::Processing_Action_ACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().addProcessing(new FullBodyDetect());
  else if (payload.action() == protocol::Processing_Action::Processing_Action_DESACTIVATE)
    this->_parent->getVideoManager()->getProcessingWrapper().removeProcessing(processingType::FULLBODY);
}
