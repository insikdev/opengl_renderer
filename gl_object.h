#pragma once

class GLObject {
public:
    GLObject() = default;
    virtual ~GLObject() = default;

public: // getter
    GLuint GetId(void) const { return m_id; }

protected:
    GLuint m_id {};
};

class GLBindableObject : public GLObject {
public:
    virtual void Bind(void) = 0;
    virtual void Unbind(void) = 0;
};