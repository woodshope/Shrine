#pragma once
#include <vector>
#include "../shader.h"
#include "../model.h"
#include "../camera.h"

using namespace std;

class Temple {
public:
	Shader templeShader;

	Temple()
		: templeShader(Shader("temple/temple.vs", "temple/temple.fs")),
		  templeModel(Model("resources/objects/temple/Japanese_country_house_3_obj.obj"))
	{}

	void drawTemple(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Camera camera) {
		templeShader.use();
		templeShader.setMat4("projection", projection);
		templeShader.setMat4("view", view);
		templeShader.setMat4("model", model);
		templeShader.setInt("material.diffuse", 0);
		templeShader.setInt("material.specular", 1);
		templeShader.setFloat("material.shininess", 32.0f);
		templeShader.setVec3("light.position", camera.Position);
		templeShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);
		templeShader.setVec3("light.direction", camera.Front);
		templeShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		templeShader.setFloat("light.outerCutOff", glm::cos(glm::radians(30.0f)));
		templeShader.setVec3("viewPos", camera.Position);
		float ambientValue = 0.3f;
		float diffuseValue = camera.IsLightOn ? 0.8f : 0.0f;
		float specularValue = camera.IsLightOn ? 1.0f : 0.0f;
		templeShader.setVec3("light.ambient", ambientValue, ambientValue, ambientValue);
		templeShader.setVec3("light.diffuse", diffuseValue, diffuseValue, diffuseValue);
		templeShader.setVec3("light.specular", specularValue, specularValue, specularValue);
		templeShader.setFloat("light.constant", 1.0f);
		templeShader.setFloat("light.linear", 0.09f);
		templeShader.setFloat("light.quadratic", 0.032f);

		templeShader.setVec3("pointLights1.position", -4.6f, 4.3f, 8.7f);
		templeShader.setVec3("pointLights1.ambient", 0.05f, 0.05f, 0.05f);
		templeShader.setVec3("pointLights1.diffuse", 1.0f, 0.6f, 0.0f);
		templeShader.setVec3("pointLights1.specular", 2.0f, 2.0f, 2.0f);
		templeShader.setFloat("pointLights1.constant", 1.5f);
		templeShader.setFloat("pointLights1.linear", 0.3);
		templeShader.setFloat("pointLights1.quadratic", 0.3);

		templeShader.setVec3("pointLights2.position", -4.6f, 4.3f, -8.7f);
		templeShader.setVec3("pointLights2.ambient", 0.05f, 0.05f, 0.05f);
		templeShader.setVec3("pointLights2.diffuse", 1.0f, 0.6f, 0.0f);
		templeShader.setVec3("pointLights2.specular", 2.0f, 2.0f, 2.0f);
		templeShader.setFloat("pointLights2.constant", 1.5f);
		templeShader.setFloat("pointLights2.linear", 0.3);
		templeShader.setFloat("pointLights2.quadratic", 0.3);
		templeModel.Draw(templeShader);
	}

private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	Model templeModel;
};