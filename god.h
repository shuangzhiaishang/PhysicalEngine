//
// Created by 10239 on 2023/3/9.
//

#ifndef PHYSICALENGINE_GOD_H
#define PHYSICALENGINE_GOD_H

#include "object.h"

class God {
public:
    God(float gravity=0.1) {
        this->gravity = gravity;

        objects.clear();
    }

    ~God() {
        free(constraintBackground);
    }

    void addObject(Circle c) {
        objects.push_back(c);
    }

    void update(float elapsedTime) {
        applyGravity();
        applyConstraint();
        for (auto &obj: objects) {
            obj.update(elapsedTime);
        }
    }

    void draw(Shader &shader) {
        shader.use();
        for (auto &obj: objects) {
            obj.draw(shader);
        }
    }

    void addConstraint(Circle *constraint) {
        constraintBackground = constraint;
        constraintCenter = constraintBackground->pos;
        constraintRadius = constraintBackground->r;
    }

    void drawConstraint(Shader &shader) {
        constraintBackground->draw(shader);
    }

private:
    float gravity = 0.005;
    glm::vec2 constraintCenter{0.0f, 0.0f};
    float constraintRadius = 1.0f;
    Circle *constraintBackground = nullptr;
    std::vector<Circle> objects{};

    void applyGravity() {
        for (auto &obj: objects) {
            obj.accelerate(glm::vec2(0, -gravity));
        }
    }

    void applyConstraint() {
        for (auto &obj: objects) {
            float dx = constraintCenter.x - obj.pos.x;
            float dy = constraintCenter.y - obj.pos.y;
            float dist = sqrt(dx * dx + dy * dy);
            if (dist > constraintRadius - obj.r) {
                obj.pos.x = constraintCenter.x - (constraintRadius - obj.r) * dx / dist;
                obj.pos.y = constraintCenter.y - (constraintRadius - obj.r) * dy / dist;
            }
        }

    }
};


#endif //PHYSICALENGINE_GOD_H
