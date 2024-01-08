#include "pch.h"
#include "material.h"
#include "gl_program.h"
#include "gl_texture.h"

void Material::SetToProgram(const Program* program) const
{
    if (diffuse) {
        glActiveTexture(GL_TEXTURE0);
        program->SetUniform("material.diffuse", 0);
        diffuse->Bind();
    }
    if (specular) {
        glActiveTexture(GL_TEXTURE1);
        program->SetUniform("material.specular", 1);
        specular->Bind();
    }
    program->SetUniform("material.shininess", shininess);
}
