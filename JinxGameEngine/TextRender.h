#include <map>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <ft2build.h>
#include "Shader.h"
#include FT_FREETYPE_H

class TextRender
{
public:
	Shader textShader;
	GLuint VAO, VBO;
	TextRender();
	~TextRender();
	void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void init(int width, int height);

};

