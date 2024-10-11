#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct Vertex
{
    float x, y, z;
};

struct Normal
{
    float x, y, z;
};

struct UV
{
    float u, v;
};

struct Indice
{
    int vertexIndex, uvIndex, normalIndex;
};

class ObjParser
{
public:
    std::vector<Vertex> vertices;
    std::vector<Normal> normals;
    std::vector<UV> uvs;
    std::vector<Indice> indices;

    bool loadOBJ(const std::string& path)
    {
        std::ifstream file(path);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << path << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v")
            {
                Vertex vertex;
                iss >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            }
            else if (prefix == "vt")
            {
                UV uv;
                iss >> uv.u >> uv.v;
                uvs.push_back(uv);
            }
            else if (prefix == "vn")
            {
                Normal normal;
                iss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            else if (prefix == "f")
            {
                Indice indice1, indice2, indice3;
                std::string v1, v2, v3;
                iss >> v1 >> v2 >> v3;

                std::replace(v1.begin(), v1.end(), '/', ' ');
                std::replace(v2.begin(), v2.end(), '/', ' ');
                std::replace(v3.begin(), v3.end(), '/', ' ');

                std::istringstream v1ss(v1);
                std::istringstream v2ss(v2);
                std::istringstream v3ss(v3);

                v1ss >> indice1.vertexIndex >> indice1.uvIndex >> indice1.normalIndex;
                v2ss >> indice2.vertexIndex >> indice2.uvIndex >> indice2.normalIndex;
                v3ss >> indice3.vertexIndex >> indice3.uvIndex >> indice3.normalIndex;

                indice1.vertexIndex--;
                indice1.uvIndex--;
                indice1.normalIndex--;

                indice2.vertexIndex--;
                indice2.uvIndex--;
                indice2.normalIndex--;

                indice3.vertexIndex--;
                indice3.uvIndex--;
                indice3.normalIndex--;

                indices.push_back(indice1);
                indices.push_back(indice2);
                indices.push_back(indice3);
            }
        }

        file.close();

        return true;
    }

    std::vector<float> getData()
    {
        std::vector<float> data;
        for (const auto& indice : indices)
        {
            const Vertex& vertex = vertices[indice.vertexIndex];
            data.push_back(vertex.x);
            data.push_back(vertex.y);
            data.push_back(vertex.z);

            const Normal& normal = normals[indice.normalIndex];
            data.push_back(normal.x);
            data.push_back(normal.y);
            data.push_back(normal.z);

            const UV& uv = uvs[indice.uvIndex];
            data.push_back(uv.u);
            data.push_back(uv.v);
        }

        return data;
    }
};
