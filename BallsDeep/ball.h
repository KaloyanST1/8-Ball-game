#ifndef ball_h
#define ball_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

glm::vec3 ballPos;
std::vector <float> vertices;
std::vector <int> indices;
std::vector <float> UV;
int Stacks = 50;
int Slices = 50;
float Radius = 1;
 

// CALCULATING VERTICES
void makeBall(){

    for (int i = 0; i <= Stacks; ++i) {
        float V = i / (float)Stacks;
        float phi = V * glm::pi <float>();
 
        for (int j = 0; j <= Slices; ++j) {
 
            float U = j / (float)Slices;
            float theta = U * (glm::pi <float>() * 2);
 
            float x = cosf(theta) * sinf(phi);
            float y = cosf(phi);
            float z = sinf(theta) * sinf(phi);
 
            vertices.push_back(x * Radius);
            vertices.push_back(y * Radius);
            vertices.push_back(z * Radius);
        }
    }
    for (int i = 0; i < Slices * Stacks + Slices; ++i) {
        indices.push_back(i);
        indices.push_back(i + Slices + 1);
        indices.push_back(i + Slices);
        indices.push_back(i + Slices + 1);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    for (int i = 0; i < vertices.size(); i++) {

        if (i % 3 == 0) {
            glm::vec3 d = glm::vec3(vertices[i] - ballPos[0], vertices[i + 1] - ballPos[1], vertices[i + 2] - ballPos[2]);
            d = glm::normalize(d);
            float u = 1 - (0.5 + (glm::atan(d[2], d[0]) / (glm::pi<float>() * 2)));
            float v = 0.5 - (glm::asin(d[1])) / glm::pi<float>();
 
            UV.push_back(u);
            UV.push_back(v);
        }
    }

}





#endif