#ifndef __OBJLOADER_H__
#define __OBJLOADER_H__
#include <memory>
namespace gssmraytracer {
	namespace utils {
	class OBJLoader {
	public:
	OBJLoader(const char *obj_file);
	OBJLoader(const OBJLoader &);
	~OBJLoader();
	OBJLoader& operator=(const OBJLoader &);

	private:
	class Impl;
	std::shared_ptr<Impl> mImpl; 
	};

	}
}
#endif // __OBJLOADER_H__