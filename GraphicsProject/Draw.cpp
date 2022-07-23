#include "Draw.h"
#include <iostream>
#include <algorithm>
#include <vector>

sf::Color applyAmbient(sf::Color c, float ambient) {
	return sf::Color((float)c.r * ambient, 
		(float)c.g * ambient,(float)c.b * ambient,c.a);
}

sf::Color applyDiffuse(sf::Color c, Vec3 normal, Vec3 light) {
	float intensity = abs(dot(normalize(normal), normalize(light)));
	return sf::Color((float)c.r * intensity, 
		(float)c.g * intensity,(float)c.b * intensity,c.a);
}

void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec3 light) {
	float ambient = 1;

<<<<<<< Updated upstream
void rasterize(triangle t, sf::RenderWindow &window) {
	std::vector<sf::Vertex> vertexarray;
	vertexarray.push_back(sf::Vertex{ sf::Vector2f{1, 2} });
	int xmin = std::min({ t.p0[0], t.p1[0], t.p2[0] });
	int xmax = std::max({ t.p0[0], t.p1[0], t.p2[0] });
	int ymin = std::min({ t.p0[1], t.p1[1], t.p2[1] });
	int ymax = std::max({ t.p0[1], t.p1[1], t.p2[1] });

	for (int i = ymin; i <= ymax; i++) {
		for (int j = xmin; j <= xmax; j++) {
			Vec4 currentPoint = { j, i, 0 };
			bool up1 = false, up2 = false, up3 = false;
			Vec3 cp1 = (t.p1 - t.p0) * (currentPoint - t.p0);
			Vec3 cp2 = (t.p2 - t.p1) * (currentPoint - t.p1);
			Vec3 cp3 = (t.p0 - t.p2) * (currentPoint - t.p2);
			if (cp1[2] >= 0)up1 = true;
			if (cp2[2] >= 0)up2 = true;
			if (cp3[2] >= 0)up3 = true;

			if (up1 == up2 && up2 == up3) {
				vertexarray.push_back(sf::Vertex{ sf::Vector2f{float(j), float(i)}, t.fillColor });
			}
		}
	}
	window.draw(&vertexarray[0], vertexarray.size(), sf::Points);
}

void draw(mesh M, sf::RenderWindow &window, Camera cam) {
	//std::vector<std::vector<float> > zbuffer(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH));
=======
>>>>>>> Stashed changes
	Mat4 compressx = getScaleMatrix(Vec3{ aspect_ratio, 1, 1});
	Mat4 translateCam = getTranslateMatrix(Vec3{ 0, 0, 0 } - cam.position);
	Mat4 camTransform = rotateCam(cam);
	Mat4 Transform = compressx * camTransform * translateCam;
	for (triangle t : M.triangles) {
		Vec4 v1 = t.p1 - t.p0;
		Vec4 v2 = t.p2 - t.p1;
		Vec3 cross_product = v1 * v2;

		if (dot(cross_product, Vec3{t.p0[0], t.p0[1], t.p0[2]} - cam.position) > 0)continue;
		
		Vector<4> pp0 = get2d(Transform*t.p0);
		Vector<4> pp1 = get2d(Transform*t.p1);
		Vector<4> pp2 = get2d(Transform*t.p2);

		Mat4 maptoScreen = getScaleMatrix({ SCREEN_WIDTH / float(2), SCREEN_HEIGHT / float(2), 1 }) * getTranslateMatrix({ 1, 1, 0 });

<<<<<<< Updated upstream
		pp0 = maptoScreen * pp0;
		pp1 = maptoScreen * pp1;
		pp2 = maptoScreen * pp2;
		
		/*sf::VertexArray drawt(sf::Triangles, 3);
		drawt[0].color = t.fillColor;
		drawt[1].color = t.fillColor;
		drawt[2].color = t.fillColor;
		drawt[2].position = sf::Vector2f(pp0[0], pp0[1]);
		drawt[0].position = sf::Vector2f(pp1[0], pp1[1]);
		drawt[1].position = sf::Vector2f(pp2[0], pp2[1]);
		window.draw(drawt);*/



		rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window);
=======

		sf::VertexArray drawt(sf::Triangles, 3);
		drawt[0].color = applyDiffuse(applyAmbient(t.fillColor, ambient), cross_product, light);
		drawt[1].color = applyDiffuse(applyAmbient(t.fillColor, ambient), cross_product, light);
		drawt[2].color = applyDiffuse(applyAmbient(t.fillColor, ambient), cross_product, light);

		drawt[0].position = sf::Vector2f(pp1[0], pp1[1]);
		drawt[1].position = sf::Vector2f(pp2[0], pp2[1]);
		drawt[2].position = sf::Vector2f(pp3[0], pp3[1]);
		
		 window.draw(drawt);
>>>>>>> Stashed changes
	}
}

void drawline(Vector<2> p1, Vector<2> p2, sf::RenderWindow &window) {
	sf::Vertex line[2];
	line[0].position = sf::Vector2f((p1[0] + 1) / 2 * SCREEN_WIDTH, (p1[1] + 1) / 2 * SCREEN_HEIGHT);
	line[1].position = sf::Vector2f((p2[0] + 1) / 2 * SCREEN_WIDTH, (p2[1] + 1) / 2 * SCREEN_HEIGHT);
	line[0].color = line[1].color = sf::Color::Blue;
	window.draw(line, 2, sf::Lines);
}
