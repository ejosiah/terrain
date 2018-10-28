#pragma once
#include <ncl/gl/Scene.h>
#include <ncl/gl/shader_binding.h>

using namespace std;
using namespace ncl;
using namespace gl;
using namespace glm;

class TerrainScene : public Scene {
public:
	TerrainScene(): Scene("Terrain Generator"){
		useImplictShaderLoad(true);
	}

	virtual void init() override {
		font = Font::Arial(15, Font::BOLD, YELLOW);
		float outer[4] = { grids, grids, grids, grids };
		float inner[2] = { grids, grids };
		glPatchParameteri(GL_PATCH_VERTICES, 4);
		
		glPatchParameterfv(GL_PATCH_DEFAULT_OUTER_LEVEL, outer);
		glPatchParameterfv(GL_PATCH_DEFAULT_INNER_LEVEL, inner);
		texture = new NoiseTex2D("noise", 1);
		initPatch();
		glClearColor(0, 0, 0, 1);
	}

	void initPatch() {
		vec3 v[] = { { -lenght, 0, lenght },{ lenght, 0, lenght},{ lenght, 0, -lenght },{ -lenght, 0, -lenght } };
		Mesh mesh;
		mesh.positions = vector<vec3>(begin(v), end(v));
		mesh.primitiveType = GL_PATCHES;

		patch = new ProvidedMesh(vector<Mesh>(1, mesh));
	}

	virtual void display() override {
		font->render("FPS: " + std::to_string(fps), 10, _height - 20);
		cam.view = lookAt({1.0f, 15.25f, 25.25f}, vec3(0), { 0, 1, 0 });
		cam.model = rotate(mat4(1), radians(angle), { 0, 1, 0 });

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		shader("shader")([&](Shader& s) {
			send(texture);
			s.sendComputed(cam);
			patch->draw(s);
		});
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	virtual void resized() override {
		cam.projection = perspective(radians(60.0f), aspectRatio, 0.3f, 1000.0f);
	//	font->resize(_width, _height);
	}

	virtual void update(float dt) override {
		angle += dt * 20;
		if (angle >= 360) angle -= 360;
	}
private:
	ProvidedMesh* patch;
	float angle;
	float grids =  10000;
	float lenght = 30;
	Texture2D* texture;
	Font* font;
};