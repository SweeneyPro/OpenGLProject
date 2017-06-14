#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include <windows.h>
#include <WinUser.h>
#define WIDTH 800
#define HEIGHT 600
int main()
{

	Display display(1500, 1000, "Michael Sweeney - OpenGL - 3D Model Viewer");
	Mesh mesh2("./res/chair.obj");
	Shader shader("./res/basicShader");
	Texture texture("./res/brick.jpg");
	Camera camera(glm::vec3(0, 0, -5), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 5000.0f);
	Transform transform;
	glm::vec3 rot = glm::vec3(1, 1, 1);
	float counter = 0.0f;
	while (!display.IsClosed())
	{
		
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
	
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);
	
		//transform.GetPos().x = sinCounter;
		//transform.GetPos().z = cosCounter;
		//transform.GetRot().x = counter * 0.5f;
		//transform.GetRot().y = counter * 0.5f;
		//transform.GetRot().z = counter * 0.5f;
		
		
		//transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);
		mesh2.Draw();
		display.Update();
		counter += 0.001f;
			
		
	}
	return 0;
}


