#include "Network/NetworkManager.hpp"

NetworkManager::NetworkManager(Manager * parent , unsigned short port) {
    this->_server = new TcpServer(port);
    this->_parent = parent;
    this->_run = false;
    this->_isAsyncRunning = false;
}

NetworkManager::~NetworkManager() {
  this->waitRunner();
  logger::log(STOP_NETWORK_JOB , logger::logType::SUCCESS);
  if (this->_server)
    delete this->_server;
}

bool NetworkManager::init() {
  if ((this->_server != NULL && this->_parent != NULL && this->_server->initServer() == true) == true)
      return true;
  logger::log(std::strerror(errno) , logger::logType::FAILURE);
}

void NetworkManager::run() {
  this->_run = true;
  std::thread * thread = new std::thread(&NetworkManager::runner , this);
	thread->detach();
}

bool NetworkManager::waitClient()
{
    bool status;
    while (this->_run)
    {
         status = this->_server->runServer();
        if (status == false && errno != EWOULDBLOCK)
        {
            logger::log(ERROR_TCP , logger::logType::FAILURE);
            return false;
        }
        else if (status == false && errno == EWOULDBLOCK)
          std::this_thread::sleep_for(std::chrono::milliseconds(50));
        else if (status == true)
            return true;
    }
    return true;
}
void NetworkManager::runner() {
    this->_isAsyncRunning = true;
    int read;
    protocol::Packet * message;

    while (this->_run)
    {
    logger::log("Waiting TCP connection..." , logger::logType::INFO);
        if (this->waitClient() == -1)
            break;
        logger::log(SUCCESS_TCP_CLIENT , logger::logType::SUCCESS);
        while (this->_run)
        {
            CLEAR(this->_buffer);
            if (this->_server->isDataAvailable())
            {
                read = this->_server->Read(this->_buffer , TCP_BUFFER_SIZE);
                if (read <= 0)
                {
                    logger::log(WARNING_TCP_DISCONNECTED , logger::logType::WARNING);
                    this->_server->discardClient();
                    break;
                }
                logger::log("TCP readed : " + std::to_string(read) + " bytes" , logger::logType::WARNING);
                if ((message = NetworkInterface::get(this->_buffer , read)) != NULL)
                    this->_parent->pushInput(message);
            }
            while (this->_parent->isOutputAvailable())
            {
              protocol::Packet * elem = this->_parent->popOutput();
              NetworkInterface::put(elem , this->_buffer);
              this->_server->Send(this->_buffer  , elem->ByteSize());
              delete elem;
            }
        }
    }
    this->_isAsyncRunning = false;
    this->_condition.notify_all();
  }

void NetworkManager::waitRunner() {

  std::unique_lock<std::mutex> lock(this->_lock);

  if (this->_run == false)
    return;

  this->_run = false;

  while (this->_isAsyncRunning)
    this->_condition.wait(lock);
}
