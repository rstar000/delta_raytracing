#pragma once

#include <vector>
#include <optional>
#include <iostream>

#include "object.hpp"

using std::vector;
using std::pair;

const double inf=1e9;
const double eps=1e-6;

class Scene
{
public:
    void add(Object *obj) {
        objects.push_back(obj);
    }

    ~Scene() {}

    TracingResult trace(const Ray &ray) const {
        TracingResult result;
        for (auto obj : objects) {
            TracingResult local = obj->Trace(ray);

            if (local.distance > 0 && (local.distance < result.distance || result.distance < 0)){
                result = local;
            }
        }
        return TracingResult();
    }
private:
    vector<Object*> objects;
};
