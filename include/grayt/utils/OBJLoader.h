#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__
#include <memory>
#include "grayt/geometry/Point.h"
#include "grayt/geometry/Normal.h"
namespace grayt {
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