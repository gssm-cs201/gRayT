#include "gssmraytracer/utils/OBJLoader.h"
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Normal.h"
#include <string>
#include <fstream>
#include <iterator>
#include <vector>
using namespace gssmraytracer::geometry;
namespace gssmraytracer {
	namespace utils {
		class OBJLoader::Impl {
		public:
			Impl() : vertices(), normals(), faces() {}
			std::vector<Point> vertices;
			std::vector<Normal> normals;
			std::vector<std::vector<Point> > faces;
		};

		void parseLineForFace(const std::string &line,
			std::vector<Point> &face_vertices_info) {
			std::string token;
			std::stringstream ss(line);
			std::string s = line;
			std::string delimiter = "/";
			std::string ws_delimiter = " ";
			size_t pos = 0;

			// parse on white space
			if ((pos = s.find("f ")) != std::string::npos) {
				s.erase(0, pos + std::string("f ").length());
			}
			while ((pos = s.find(ws_delimiter)) != std::string::npos) {
				std::string face_info = s.substr(0, pos);
				size_t fi_pos = 0;
				Point face_vertex(-1,-1,-1);
				int index = 0;
				while ((fi_pos = face_info.find(delimiter)) != std::string::npos) {
					face_vertex[index++] = std::stof(face_info.substr(0, fi_pos)) - 1;
					face_info.erase(0, fi_pos + delimiter.length());
				}

				face_vertex[index] = std::stof(face_info) - 1;
				face_vertices_info.push_back(face_vertex);

				s.erase(0, pos + ws_delimiter.length());
			}
			Point face_vertex(-1,-1,-1);
			int index = 0;
			while ((pos = s.find(delimiter)) != std::string::npos) {
					face_vertex[index++] = std::stof(s.substr(0, pos)) - 1;
					s.erase(0, pos + delimiter.length());
				}
				if (s != "")
					face_vertex[index] = std::stof(s) - 1;
			face_vertices_info.push_back(face_vertex);

			
		}
	OBJLoader::OBJLoader(const char *obj_file) : mImpl(new Impl) {
		// read the file
		std::ifstream file(obj_file);
		// check to see if the file is not null
		if (!file.is_open()) {
			std::cout << "Unable to open file " << obj_file << std::endl;
			return;
		}

		

		// if not null read the obj information from the file
		std::string line;
		std::string name;
		while (std::getline(file, line)) {
			// check to see if it is a comment.  If so, ignore
			if (line == "" || line[0] == '#')
				continue;

			// parse the line to find information

			std::istringstream lineStream(line);
			lineStream >> name;

			if (name == "v") { // Vector
				Point vertex;
				//std::string::iterator line_iter = line.begin();
				lineStream >> vertex[0];
				lineStream >> vertex[1];
				lineStream >> vertex[2];
				mImpl->vertices.push_back(vertex);
			}
			else if (name == "vn") {
				Point vNormal;

				lineStream >> vNormal[0];
				lineStream >> vNormal[1];
				lineStream >> vNormal[2];
				mImpl->normals.push_back(Normal(vNormal.x(), vNormal.y(), vNormal.z()));
			}

			else if (name == "f") {
				std::vector<Point> face_vertices_info;
				parseLineForFace(line, face_vertices_info);
				mImpl->faces.push_back(face_vertices_info);
			}
		}


		file.close();
	}
	OBJLoader::OBJLoader(const OBJLoader &other) : mImpl(new Impl()) {

			mImpl->vertices = other.mImpl->vertices;
			mImpl->normals = other.mImpl->normals;
			mImpl->faces = other.mImpl->faces;

	}
	OBJLoader::~OBJLoader() {}


	OBJLoader& OBJLoader::operator=(const OBJLoader &other) {
		if (this != &other) {
			mImpl->vertices = other.mImpl->vertices;
			mImpl->normals = other.mImpl->normals;
			mImpl->faces = other.mImpl->faces;
		}

		return *this;

	}
	}
}