#pragma once

#include "gl_object.h"

class Cubemap : public GLBindableObject {
public:
    Cubemap(const std::vector<std::string>& files);
    ~Cubemap();

public:
    void Bind(void) override;
    void Unbind(void) override;
};
