#pragma once

class Image {
public:
    Image(const std::string& filename, bool flip = true);
    ~Image();

public: // getter
    int GetWidth(void) const { return m_width; }
    int GetHeight(void) const { return m_height; }
    GLenum GetFormat(void) const { return m_channels == 4 ? GL_RGBA : GL_RGB; }
    uint8_t* GetData(void) const { return m_data; }

private:
    int m_width;
    int m_height;
    int m_channels;
    uint8_t* m_data {};
};
