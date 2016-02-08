#ifndef IMG_PROCESSING_HPP
#define IMG_PROCESSING_HPP

	//====================================================
	// CLASSE DE BASE POUR TOUS LES TRAITEMENTS D'IMAGES
	// TOUS LES TRAITEMENTS DOIVENT ETRE IMPLEMENTES DANS
	// UNE CLASSE HERITANT DE ImgProcessing
	//====================================================

	#include "opencv2/opencv.hpp"
	#include "opencv2/core/cuda.hpp"

	#include "Processing/ImgProcessingParams.hpp"

	class ImgProcessing
	{
		public:

			//====================================================
			// CONSTRUCTEUR
			//====================================================
			
			ImgProcessing(ImgProcessingParams * params);

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
			
			virtual int apply() = 0;

		private:

			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION CPU
			//====================================================

			virtual int apply_cpu() = 0;
			
			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION GPU
			//====================================================

			virtual int apply_gpu() = 0;

			//====================================================
			// TOUTE TRANSFORMATION EST SUR CPU PAR DEFAULT
			// _isGpuAccelerated = false;
			//====================================================
			
			bool _isGpuAccelerated;
			ImgProcessingParams * _params;


				
	};

#endif // IMG_PROCESSING_HPP
