//
// Created by 10239 on 2023/3/9.
//

#ifndef PHYSICALENGINE_OBJECT_H
#define PHYSICALENGINE_OBJECT_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <learnopengl/shader.h>

#include <string>
#include <vector>
#include <cmath>

class Vertex {
public:
    glm::vec3 position{};

    Vertex() = default;

    explicit Vertex(glm::vec3 position) {
        this->position = position;
    }
};

class Object {

};


class Circle: public Object {
public:
    unsigned int VAO;
    unsigned int pointCount = 180;
    glm::vec2 pos{0.0f, 0.0f};
    glm::vec2 lastPos{0.0f, 0.0f};
    glm::vec2 acceleration{0.0f, 0.0f};
    float r;
    std::vector<Vertex> vertices;

    Circle(glm::vec2 pos, float r) {
        this->pos = pos;
        lastPos = pos;
        this->r = r;

        setup();
    }

    void draw(Shader &shader)
    {
        setup();
        glBindVertexArray(VAO);
        glDrawArrays(GL_LINE_STRIP, 0, pointCount + 1);
    }

    void update(float elapsedTime) {
        glm::vec2 tempPos = pos;
        pos = 2.0f * pos - lastPos + elapsedTime * elapsedTime * acceleration;
        lastPos = tempPos;
        acceleration = glm::vec2(0.0f, 0.0f);
    }

    void accelerate(glm::vec2 a) {
        acceleration += a;
    }

private:
    // render data
    unsigned int VBO;

    void setup() {
        // generate points
        vertices.clear();
        float angle = 0;
        float deltaAngle = 2 * M_PI / pointCount;
        for (int i = 0; i < pointCount; i++) {
            angle = i * deltaAngle;
            vertices.push_back(Vertex(glm::vec3(pos.x + r * sin(angle), pos.y + r * cos(angle), 0.0f)));
        }
        vertices.push_back(vertices[0]);

        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    }
};

glm::vec2 operator * (float num, glm::vec2 vec) {
    return glm::vec2(num * vec.x, num * vec.y);
}

#endif //PHYSICALENGINE_OBJECT_H
