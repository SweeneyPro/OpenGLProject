#include "shader.h"
#include <iostream>
#include <fstream>
static void CheckShaderError(GLuint shader, GLuint flag, bool bIsProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	m_program = glCreateProgram(); // Creates a "program object" that we will attach our shaders to
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);	// Creates shader from directory and type
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);	// Creates shader from directory and type

	for (unsigned int i = 0; i < NUM_SHADERS; i++) // Attaches shaders to the program object
	{
		glAttachShader(m_program, m_shaders[i]); 
	}

	glBindAttribLocation(m_program, 0, "position");	// program object, FIND THIS, the variable from the shader
	glBindAttribLocation(m_program, 1, "texCoord");	// FIND OUT WHAT THIS DOES
	glBindAttribLocation(m_program, 2, "normal");	// FIND OUT WHAT THIS DOES

	glLinkProgram(m_program);	// NOT SURE, THINK IT IS THE FINAL STEP IN LINKING THE SHADER TO THE PROJECT
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

	glValidateProgram(m_program);	// CHECK IF PROGRAM IS VALID I GUESS
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}


Shader::~Shader()
{

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);	// Detach shader from the program object
		glDeleteShader(m_shaders[i]);	// Delete the shader
	}
	glDeleteProgram(m_program);	// Delete the program object
}

void Shader::Bind()
{
	glUseProgram(m_program);	// Link to the project
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType)	// Generates a shader from a file directory of the shader and a shader type
{
	GLuint shader = glCreateShader(shaderType);	// Creates shader of specified Type

	if (shader == 0)	// Shaders are allocated numbers, if 0 then no shader was created
	{
		std::cerr << "Error: Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringsLengths[1];

	shaderSourceStrings[0] = text.c_str();	// Shader directory string
	shaderSourceStringsLengths[0] = text.length();	// Shader directory string length - NOT SURE WHY NEEDED

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringsLengths);	// Puts the code from shader directory into the shader - FUCK KNOWS
	glCompileShader(shader);		// Compiles all shader

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");	// Checks if shader compile failed


	return shader;
}

static std::string LoadShader(const std::string& fileName)	// loads file off hard drive
{
	std::ifstream file;
	file.open((fileName).c_str());

	std::string output;
	std::string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "unable to load shader:" << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool bIsProgram, const std::string& errorMessage)	// Checks if errors occured when compiling the shader
{
	GLint success = 0;
	GLchar error[1024];

	if (bIsProgram)
	{
		glGetProgramiv(shader, flag, &success);

	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (bIsProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		}
		else
		{

			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}