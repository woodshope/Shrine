#pragma once
#include <vector>
#include "../shader.h"
#include "../model.h"
#include "../camera.h"

using namespace std;

class Rock {
public:
	Shader rockShader;

	Rock()
		: rockShader(Shader("rock/rock.vs", "rock/rock.fs", "rock/rock.gs")),
		rockModel(Model("resources/objects/rock/rockkk.obj")),
		startTime(glfwGetTime()), doExplode(false)
	{}

	void drawRock(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Camera camera) {
		rockShader.use();
		rockShader.setMat4("projection", projection);
		rockShader.setMat4("view", view);
		rockShader.setMat4("model", model);
		rockShader.setInt("material.diffuse", 0);
		rockShader.setInt("material.specular", 1);
		rockShader.setFloat("material.shininess", 32.0f);
		rockShader.setVec3("light.position", camera.Position);
		rockShader.setVec3("light.color", 1.0f, 1.0f, 1.0f);
		rockShader.setVec3("light.direction", camera.Front);
		rockShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
		rockShader.setFloat("light.outerCutOff", glm::cos(glm::radians(30.0f)));
		rockShader.setVec3("viewPos", camera.Position);
		float ambientValue = 0.3f;
		float diffuseValue = camera.IsLightOn ? 0.8f : 0.0f;
		float specularValue = camera.IsLightOn ? 1.0f : 0.0f;
		rockShader.setVec3("light.ambient", ambientValue, ambientValue, ambientValue);
		rockShader.setVec3("light.diffuse", diffuseValue, diffuseValue, diffuseValue);
		rockShader.setVec3("light.specular", specularValue, specularValue, specularValue);
		rockShader.setFloat("light.constant", 1.0f);
		rockShader.setFloat("light.linear", 0.09f);
		rockShader.setFloat("light.quadratic", 0.032f);
		rockShader.setFloat("time", glfwGetTime() - startTime);
		rockShader.setBool("doExplode", this->doExplode);
		rockModel.Draw(rockShader);
	}

	void startExplode() {
		this->doExplode = true;
		this->startTime = glfwGetTime();
	}

private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
	Model rockModel;
	float startTime;
	bool doExplode;
};