#ifndef IMG_PROCESSING_CONTAINER_HPP
#define IMG_PROCESSING_CONTAINER_HPP

#include <list>
#include <mutex>
#include "Processing/ImgProcessing.hpp"

class ImgProcessingContainer
{
	public:

	ImgProcessingContainer();
	~ImgProcessingContainer();

	addFront(ImgProcessing *);
	addBack(ImgProcessing *);
	addAt(int index);

	removeFront();
	removeBack();
	removeAt(int index);

	size();

	void lock();
	void unlock();

	private:
	
	//=================================================
	// LISTE DE ImgProcessing * CONTENANT TOUS LES 
	// TRAITEMENTS A EFFECTUER DANS L'ORDRE
	//=================================================
	std::list<ImgProcessing * > _ImgProcessingList;

	//=================================================
	// MUTEX POUR PROTEGER LA LISTE DES ACCES
	// CONCURENTIELS
	//=================================================

	std::mutex mutex;
};


#endif // IMG_PROCESSING_CONTAINER_HPP
