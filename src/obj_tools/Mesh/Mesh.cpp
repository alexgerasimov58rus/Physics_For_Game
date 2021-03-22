
#include "../Vector/Vector2D.hpp"
#include "../Vector/Vector3D.hpp"
#include "../String/String.hpp"
#include "Mesh.hpp"
#include <fstream>

#ifdef WIN32
    #include <windows.h>
    #include <gl/gl.h>
#endif

using namespace obj_tools;
using namespace std;

Mesh::Mesh(const string& name) {
    this->name_ = name;
    this->callIndex_ = -1;
}

Mesh::~Mesh(void) {
    deleteCallList();
}

bool Mesh::loadFromObjFile(const string& path) {
    string line;
    string name;

    clear();

    ifstream file(path.c_str());
    
    if (file.fail()) return false;

    while (getline(file, line)) {
        if (line.size() < 5) continue;
        if (line[0] == 'o' && line[1] == ' ') {
            name = line.substr(2);
            continue;
        }
        
        if (this->name_ != name) continue;

        if (line[0] == 'v' && line[1] == ' '                    ) { if (!addVertex(line.substr(2))) return false; }
        if (line[0] == 'v' && line[1] == 't' && line[2] == ' '  ) { if (!addTexel (line.substr(3))) return false; }
        if (line[0] == 'v' && line[1] == 'n' && line[2] == ' '  ) { if (!addNormal(line.substr(3))) return false; }
        if (line[0] == 'f' && line[1] == ' '                    ) { if (!addFace  (line.substr(2))) return false; }
    }

    return faces_.size() > 0;
}

void Mesh::compile(void) {
    deleteCallList();

    callIndex_ = glGenLists(1);

    glNewList(callIndex_, GL_COMPILE);
        glBegin(GL_TRIANGLES);
        int n = faces_.size();
        for(int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
                if (faces_[i].isValid(0, 1)) {
                    glTexCoord2f(
                        texels_[faces_[i].indexes_[j][1]].getX(),
                        texels_[faces_[i].indexes_[j][1]].getY()
                    );
                }

                if (faces_[i].isValid(0, 2)) {
                    glNormal3f(
                        normals_[faces_[i].indexes_[j][2]].getX(),
                        normals_[faces_[i].indexes_[j][2]].getY(),
                        normals_[faces_[i].indexes_[j][2]].getZ()
                    );
                }

                glVertex3f(
                    vertices_[faces_[i].indexes_[j][0]].getX(),
                    vertices_[faces_[i].indexes_[j][0]].getY(),
                    vertices_[faces_[i].indexes_[j][0]].getZ()
                );
            }
        }        
        glEnd();
    glEndList();
}

void Mesh::draw(void) {
    glCallList(callIndex_);
}

void Mesh::clear(){
    vertices_.clear();
    normals_.clear();
    texels_.clear();
    faces_.clear();
}

void Mesh::deleteCallList(void) {
    if (callIndex_ != -1) {
        glDeleteLists(callIndex_, 1);
        callIndex_ = -1;
    }
}

bool Mesh::addVertex(const std::string& line) {
    vector<string> strings; 
 
    if ((strings = String::split(line, ' ')).size() != 3) return false;

    vertices_.push_back(
        Vector3D(
            (float)atof(strings[0].c_str()),
            (float)atof(strings[1].c_str()),
            (float)atof(strings[2].c_str())
        )
    );

    return true;
}

bool Mesh::addTexel(const std::string& line) {
    vector<string> strings;

    if ((strings = String::split(line, ' ')).size() != 2) return false;

    texels_.push_back(
        Vector2D(
            (float)atof(strings[0].c_str()),
            (float)atof(strings[1].c_str())
        )
    );

    return true;
}

bool Mesh::addNormal(const std::string& line) {
    vector<string> strings;

    if ((strings = String::split(line, ' ')).size() != 3) return false;

    normals_.push_back(
        Vector3D(
            (float)atof(strings[0].c_str()),
            (float)atof(strings[1].c_str()),
            (float)atof(strings[2].c_str())
        )
    );

    return true;
}

bool Mesh::addFace(const std::string& line) {
    Face face;
    vector<string> strings = String::split(line, ' ');

    if (strings.size() != 3) return false;

    for(int i = 0; i < 3; i++) {
        string s = strings[i];
        int indexes[3] = {-1};
       
        if (s.find('/')) {  if (!parseFaceWithSeparator     (indexes, s)) return false; }
        else {              if (!parseFaceWithoutSeparator  (indexes, s)) return false; }

        memcpy(face.indexes_[i], indexes, sizeof(int) * 3);
    }

    faces_.push_back(face);

    return true;
}

bool Mesh::parseFaceWithSeparator(int* indexes, const string& s) const {
    int index;
    vector<string> strings = String::split(s, '/');

    if (strings.size() != 3) return false;

    if (strings[0].empty()) return false;

    index = atoi(strings[0].c_str());
    if (index < 1) return false;
    if (index > vertices_.size()) return false;

    indexes[0] = index - 1;

    if (!strings[1].empty()) {
        index = atoi(strings[1].c_str());
        if (index < 1) return false;
        if (index > texels_.size()) return false;

        indexes[1] = index - 1;
    }

    if (!strings[2].empty()) {
        index = atoi(strings[2].c_str());
        if (index < 1) return false;
        if (index > normals_.size()) return false;

        indexes[2] = index - 1;
    }

    return true;
}

bool Mesh::parseFaceWithoutSeparator(int* indexes, const string& s) const {
    int index = atoi(s.c_str());
    if (index < 1) return false;
    if (index > vertices_.size()) return false;

    indexes[0] = index - 1;
}
