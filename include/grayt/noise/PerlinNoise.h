

#ifndef __PERLINNOISE_H__
#define __PERLINNOISE_H__

#include "grayt/math/Vector.h"
#include <memory>
namespace grayt {


	namespace noise
	{
		/*! \class PerlinNoise
		* \brief Class for generating Perlin noise
		*/

		class PerlinNoise
		{
			public:
        //! Return a new smart pointer for PerlinNoise
				std::shared_ptr<PerlinNoise> Ptr();
				PerlinNoise();
				~PerlinNoise();

				void setTime( const float time );

				const float eval( float arg ) const;
				const float eval( const math::Vector &vec ) const;

			private:
        class Impl;
        std::shared_ptr<Impl> mImpl;

		};


		// This is Stefan Gustavson's DSOnoise implementation, ported to a C++ class.
		class PerlinNoiseGustavson
		{
			public:
				std::shared_ptr<PerlinNoiseGustavson> Ptr();

				PerlinNoiseGustavson();
				~PerlinNoiseGustavson();


				void setTime( const float t );

				const float eval( float arg ) const;


				const float eval( const math::Vector &vec ) const;

			private:
        class Impl;
        std::shared_ptr<Impl> mImpl;




		};


	}
}
#endif
