#ifndef IMG_PROCESSING_HPP
#define IMG_PROCESSING_HPP

	//====================================================
	// CLASSE DE BASE POUR TOUS LES TRAITEMENTS D'IMAGES
	// TOUS LES TRAITEMENTS DOIVENT ETRE IMPLEMENTES DANS
	// UNE CLASSE HERITANT DE ImgProcessing
	//====================================================

	#include "Processing/ImgProcessingParams.hpp"

	class ImgProcessing
	{
		public:

			//====================================================
			// CONSTRUCTEUR
			//====================================================
			
			ImgProcessing();

			//====================================================
			// GETTER PERMETTANT DE SAVOIR SI LA TRANSFORMATION VA
			// UTILISER L'ACCELERATION GPU
			//====================================================
			
			bool isGpuAccelerated();

			//====================================================
			// SETTER PERMETTANT DE SWITCHER L'ACCELERATION GPU
			// RETURN FALSE EN CAS D'ERREUR 
			//====================================================
			
			bool setGpuAccelerated(bool value);

			//====================================================
			// FONCTION PERMETTANT A LA TRANSFORMATION DE RECUPERER
			// SES PARAMETRES DANS UNE CLASSE ImgProcessingParams
			// CETTE FONCTION DOIT ETRE REDEFINIE DANS LES CLASSES
			// HERITANT DE ImgProcessing
			//====================================================
			
			virtual int getParams(ImgProcessingParams & params) = 0;

			//====================================================
			// FONCTION APPELEE POUR APPLIQUER LA TRANSFORMATION
			//====================================================
			
			virtual int apply() = 0;

		private:

			//====================================================
			// TOUTE TRANSFORMATION EST SUR CPU PAR DEFAULT
			// _isGpuAccelerated = false;
			//====================================================
			
			bool _isGpuAccelerated;
				
	};

#endif // IMG_PROCESSING_HPP
