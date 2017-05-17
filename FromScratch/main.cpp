#include "Window.h"
#include "ContentManager.h"
#include "SimpleRenderer.h"
#include "Model.h"
#include "Entity.h"
#include "MathsUtil.h"
#include "Camera.h"
#include "BasicLight.h"
#include <cstdlib>
#include <ctime>
#include "InstancedRenderer.h"
#include "Terrain.h"

#define FS_WINDOW_W 960
#define FS_WINDOW_H 540


int main() {
	using namespace fs;
	window::Window window("An Engine From Scratch", FS_WINDOW_W, FS_WINDOW_H);
	glClearColor(0.2f, 0.7f, 0.5f, 1.0f);

	graphics::ContentManager contentManager;
	std::vector<graphics::VertexTextureNormal> vertices;

#if FS_NOT_BLENDER
#if FS_QUAD
	std::vector<unsigned int> indices = {
		0,1,2,
		2,3,0
	};
#else 
	std::vector<unsigned int> indices = {
		0,1,3,
		3,1,2,
		4,5,7,
		7,5,6,
		8,9,11,
		11,9,10,
		12,13,15,
		15,13,14,
		16,17,19,
		19,17,18,
		20,21,23,
		23,21,22

	};
#endif
#if FS_QUAD

	graphics::VertexTexture v0;
	v0.position = maths::Vector3(-0.5f, -0.5f, 0.0f);
	v0.uv = maths::Vector2(0, 0);
	vertices.push_back(v0);

	graphics::VertexTexture v1;
	v1.position = maths::Vector3(-0.5f, 0.5f, 0.0f);
	v1.uv = maths::Vector2(0, 1);
	vertices.push_back(v1);

	graphics::VertexTexture v2;
	v2.position = maths::Vector3(0.5f, 0.5f, 0.0f);
	v2.uv = maths::Vector2(1, 1);
	vertices.push_back(v2);

	graphics::VertexTexture v3;
	v3.position = maths::Vector3(0.5f, -0.5f, 0.0f);
	v3.uv = maths::Vector2(1, 0);
	vertices.push_back(v3);
#else
	float tempV[] = {
		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,0.5f,-0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,-0.5f,0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		0.5f,0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,0.5f,-0.5f,
		-0.5f,-0.5f,-0.5f,
		-0.5f,-0.5f,0.5f,
		-0.5f,0.5f,0.5f,

		-0.5f,0.5f,0.5f,
		-0.5f,0.5f,-0.5f,
		0.5f,0.5f,-0.5f,
		0.5f,0.5f,0.5f,

		-0.5f,-0.5f,0.5f,
		-0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,-0.5f,
		0.5f,-0.5f,0.5f
	};

	for (int i = 0; i < 72; i += 12) {
		graphics::VertexTextureNormal v1;
		v1.position = maths::Vector3(tempV[i], tempV[i+1], tempV[i+2]);
		v1.uv = maths::Vector2(0, 0);
		v1.normal = maths::Vector3(0, 0, 0);
		vertices.push_back(v1);

		graphics::VertexTextureNormal v2;
		v2.position = maths::Vector3(tempV[i + 3], tempV[i + 4], tempV[i + 5]);
		v2.uv = maths::Vector2(0, 1);
		v2.normal = maths::Vector3(0, 0, 0);
		vertices.push_back(v2);

		graphics::VertexTextureNormal v3;
		v3.position = maths::Vector3(tempV[i + 6], tempV[i + 7], tempV[i + 8]);
		v3.uv = maths::Vector2(1, 1);
		v3.normal = maths::Vector3(0, 0, 0);
		vertices.push_back(v3);

		graphics::VertexTextureNormal v4;
		v4.position = maths::Vector3(tempV[i + 9], tempV[i + 10], tempV[i + 11]);
		v4.uv = maths::Vector2(1, 0);
		v4.normal = maths::Vector3(0, 0, 0);
		vertices.push_back(v4);
	}

	
#endif

#endif
	ShaderPtr shader = contentManager.loadShader("basic.frag", "basic.vert");
	graphics::BasicLight basicLight;
	basicLight.position = maths::Vector3(2000, 2000, 2000);
	basicLight.color = maths::Vector4(1, 1, 1, 1);

	srand(static_cast <unsigned> (time(0)));

	graphics::SimpleRenderer renderer;

	graphics::Terrain* terrain = new graphics::Terrain(contentManager, "Grass_9b.png", "heightmap_06.png", 0, -1);
	std::vector<graphics::Terrain> terrains;
	terrains.push_back(*terrain);

	ModelPtr temp_TM = contentManager.loadModel("tree01b.obj", "tree01b_diffuse02.png", 1);
	std::vector<graphics::Entity> entities;
	for (int i = 0; i < 1; i++) {
		float x = 65; // (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 200 + 50;
		float z = -50; // (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * -300 - 100;
		float y = terrain->getHeight(x, z);
		std::cout << "Y:" << y << std::endl;
		float t = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 4;
		graphics::Entity entity(temp_TM, maths::Vector3(x, y, z), 0, 0, 0, 1, 2, 1);
		entities.push_back(entity);
	}
	
	/*graphics::Terrain* plane2 = new graphics::Terrain(contentManager, "Grass_9b.png", "heightmapTest.png", 0, -1);
	graphics::Terrain* plane3 = new graphics::Terrain(contentManager, "Grass_9b.png", "heightmapTest.png", -1, 0);
	graphics::Terrain* plane4 = new graphics::Terrain(contentManager, "Grass_9b.png", "heightmapTest.png", 0, 0);*/

	
	/*terrains.push_back(*plane2);
	terrains.push_back(*plane3);
	terrains.push_back(*plane4);*/

	shader->enable();
	shader->setProjection(maths::Matrix4::perspective(70.0f, FS_WINDOW_W/FS_WINDOW_H, 0.1f, 1000.0f));
	shader->setLight(basicLight);
	shader->setSpecularity(temp_TM->getTexture()->getReflectivity(), temp_TM->getTexture()->getShineDamper());
	shader->disable();

	graphics::Camera camera(maths::Vector3(0, 3, 5), 0, 0, 0);
	GLfloat fogColor[4] = { 0.2f, 0.7f, 0.5f, 1.0f };
	float rotation = 0.0f;
	bool wireframe = false;
	while (!window.closed()) {
		window.clear();
		shader->enable();
		shader->setView(maths::MathsUtil::createViewMatrix(camera));
		shader->setUniform("tiling", 1.0f);
		for (size_t i = 0; i < entities.size(); i++) {
			maths::Matrix4 transformation = maths::MathsUtil::createTransformation(entities[i].getPosition(), 0, maths::Vector3(0, 0, 0), entities[i].getScale());
			renderer.render(entities[i].getModel()->getTexture()->getId(),
				entities[i].getModel()->getTexture()->getRows(),
				maths::Vector2(entities[i].getTextureXOffset(), entities[i].getTextureYOffset()),
				transformation,
				entities[i].getModel()->getMesh()->getVertexCount(),
				entities[i].getModel()->getMesh()->getVAO(),
				entities[i].getModel()->getMesh()->getVBO(),
				entities[i].getModel()->getMesh()->getIBO(),
				shader);
		}
		shader->setUniform("tiling", 40.0f);
		for (size_t i = 0; i < terrains.size(); i++) {
			maths::Matrix4 transform = maths::MathsUtil::createTransformation(maths::Vector3(terrains[i].m_X, 0, terrains[i].m_Z), 0, maths::Vector3(0, 0, 0), 1);

			renderer.render(terrains[i].m_Model->getTexture()->getId(),
				-1,
				maths::Vector2(),
				transform,
				terrains[i].m_Model->getMesh()->getVertexCount(),
				terrains[i].m_Model->getMesh()->getVAO(),
				terrains[i].m_Model->getMesh()->getVBO(),
				terrains[i].m_Model->getMesh()->getIBO(),
				shader);
		}
		shader->disable();

		if (window.isKeyDown(GLFW_KEY_W)) {
			camera.move(0, 0, -0.02f);
		}
		else if (window.isKeyDown(GLFW_KEY_S)) {
			camera.move(0, 0, 0.02f);
		}

		if (window.isKeyDown(GLFW_KEY_A)) {
			camera.move(-0.02f, 0, 0);
		}
		else if (window.isKeyDown(GLFW_KEY_D)) {
			camera.move(0.02f, 0, 0);
		}

		if (window.isKeyDown(GLFW_KEY_SPACE)) {
			camera.move(0, 0.02f, 0);
		}
		else if (window.isKeyDown(GLFW_KEY_C)) {
			camera.move(0, -0.02f, 0);
		}

		if (window.isKeyDown(GLFW_KEY_RIGHT)) {
			entities[0].increasePosition(0.01f, 0, 0);
			entities[0].setHeight(terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z));
			std::cout << "Y:" << terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z) << std::endl;
		}
		else if (window.isKeyDown(GLFW_KEY_LEFT)) {
			entities[0].increasePosition(-0.01f, 0, 0);
			entities[0].setHeight(terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z));
			std::cout << "Y:" << terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z) << std::endl;
		}

		if (window.isKeyDown(GLFW_KEY_UP)) {
			entities[0].increasePosition(0, 0, -0.01f);
			entities[0].setHeight(terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z));
			std::cout << "Y:" << terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z) << std::endl;
		}
		else if (window.isKeyDown(GLFW_KEY_DOWN)) {
			entities[0].increasePosition(0, 0, 0.01f);
			entities[0].setHeight(terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z));
			std::cout << "Y:" << terrain->getHeight(entities[0].getPosition().x, entities[0].getPosition().z) << std::endl;
		}
		if (window.isKeyDown(GLFW_KEY_G)) {
			if (!wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				wireframe = true;
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				wireframe = false;
			}
		}

		if (window.wasKeyPressed(GLFW_KEY_ESCAPE)) {
			break;
		}
		window.update();
	}
	return 0;
}