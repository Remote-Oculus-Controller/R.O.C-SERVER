#ifndef IMG_PROCESSING_HPP
#define IMG_PROCESSING_HPP

	//====================================================
	// CLASSE DE BASE POUR TOUS LES TRAITEMENTS D'IMAGES
	// TOUS LES TRAITEMENTS DOIVENT ETRE IMPLEMENTES DANS
	// UNE CLASSE HERITANT DE ImgProcessing
	//====================================================

	#include <iostream>
	#include "opencv2/opencv.hpp"
	#include "opencv2/core/cuda.hpp"

	enum processingType
	{
		NONE ,
		CANNY ,
		BLUR ,
		FACEDETECT,
		REDCIRCLESDETECT,
		ARROW,
	};

	class ImgProcessing
	{
		public:

			//====================================================
			// CONSTRUCTEUR
			//====================================================
			
			ImgProcessing(processingType type);

			//====================================================
			// GETTER PERMETTANT DE SAVOIR SI LA TRANSFORMATION VA
			// UTILISER L'ACCELERATION GPU
			//====================================================
			
			bool isGpuAccelerated();

			//====================================================
			// SETTER PERMETTANT DE SWITCHER L'ACCELERATION GPU
			// RETURN FALSE EN CAS D'ERREUR 
			//====================================================
			
			bool setGpuAccelerated();


			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION
			// CETTE FONCTION APELLE apply_cpu si _isGpuAccelerated == true
			// SINON CETTE FONCTION APELLE apply_gpu
			//====================================================
			
			void apply(cv::Mat & image);

			//====================================================
			// FONCTION D'IDENTIFICATION DE LA CLASSE
			//====================================================

			virtual processingType getID() = 0;

			//====================================================
			// FONCTION D'IDENTIFICATION DE LA CLASSE (PRINT)
			//====================================================

			virtual void displayType() = 0;


		private:

			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION CPU
			//====================================================

			virtual void applyCpu(cv::Mat & image) = 0;
			
			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION GPU
			//====================================================

			virtual void applyGpu(cv::Mat & image) = 0;

			//====================================================
			// TOUTE TRANSFORMATION EST SUR CPU PAR DEFAULT
			// _isGpuAccelerated = false;
			//====================================================
			
			bool _isGpuAccelerated;

			processingType _type;

				
	};

#endif // IMG_PROCESSING_HPP
