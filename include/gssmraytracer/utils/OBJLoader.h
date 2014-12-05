#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__
#include <memory>
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Normal.h"
namespace gssmraytracer {
	namespace utils {
	class OBJLoader {
	public:
	OBJLoader(const char *obj_file);
	OBJLoader(const OBJLoader &);
	~OBJLoader();
	OBJLoader& operator=(const OBJLoader &);

	const int numTriangles() const;

    const int numVertices() const;

    const int* vertexIndices() const;

    const geometry::Point* vertices() const;

    const geometry::Normal* normals() const;

	private:
	class Impl;
	std::shared_ptr<Impl> mImpl; 
	};

	}
}
#endif // __OBJLOADER_H__