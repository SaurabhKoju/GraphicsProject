#include "Draw.h"
#include <iostream>
#include <algorithm>
#include <vector>
const float INF = 1000000000;

float min(float x, float y){ return x < y ? x : y;}
float max(float x, float y){ return x > y ? x : y;}

sf::Color applyLighting(sf::Color c, float ambient, Vec3 normal, Vec3 light) {
	float ka  = 1;
	float cosTheta = max((dot(normalize(normal), normalize(light))), 0);
	return sf::Color(
			min((float)c.r * (ambient * ka + cosTheta), 255),
			min((float)c.g * (ambient * ka + cosTheta), 255),
			min((float)c.b * (ambient * ka + cosTheta), 255),
			c.a);
}

void rasterize(triangle t, sf::RenderWindow &window, float ambient, Vec3 normal, Vec3 light, std::vector<std::vector<float> >& zbuffer) {
	std::vector<sf::Vertex> vertexarray;
	vertexarray.push_back(sf::Vertex{ sf::Vector2f{-1, -1} });
	int xmin = std::min({ t.p0[0], t.p1[0], t.p2[0] });
	int xmax = std::max({ t.p0[0], t.p1[0], t.p2[0] });
	int ymin = std::min({ t.p0[1], t.p1[1], t.p2[1] });
	int ymax = std::max({ t.p0[1], t.p1[1], t.p2[1] });

	Vec3 arean = (t.p1 - t.p0) * (t.p2 - t.p0);
	for (int i = ymin; i <= ymax; i++) {
		for (int j = xmin; j <= xmax; j++) {
			Vec4 currentPoint = { (float)j, (float)i, 0 };
			bool up1 = false, up2 = false, up3 = false;
			Vec3 cp0 = (t.p1 - t.p0) * (currentPoint - t.p0);
			Vec3 cp1 = (t.p2 - t.p1) * (currentPoint - t.p1);
			Vec3 cp2 = (t.p0 - t.p2) * (currentPoint - t.p2);
			if (cp0[2] >= 0)up1 = true;
			if (cp1[2] >= 0)up2 = true;
			if (cp2[2] >= 0)up3 = true;

			if (up1 != up2 || up2 != up3) continue;

			float l2 = abs(cp0[2] / arean[2]);
			float l0 = abs(cp1[2] / arean[2]);
			float l1 = abs(cp2[2] / arean[2]);

			float depth = l0 * t.p0[2] + l1 * t.p1[2] + l2 * t.p2[2];
			if (depth >= zbuffer[i][j])continue;
			zbuffer[i][j] = depth;
			
			sf::Color c = applyLighting(t.fillColor,ambient, normal, light);
			vertexarray.push_back(sf::Vertex{ sf::Vector2f{float(j), float(i)}, c });
		}
	}
	window.draw(&vertexarray[0], vertexarray.size(), sf::Points);
}

void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec3 light) {
	std::vector<std::vector<float> > zbuffer(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH, INF));
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
		pp0 = maptoScreen * pp0;
		pp1 = maptoScreen * pp1;
		pp2 = maptoScreen * pp2;
		
		rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window, 1, cross_product, light, zbuffer);
		/*

		Vec4 temp = (t.p1 + t.p2 + t.p0) / 3;
		Vec3 surfaceCenter = {temp[0], temp[1], temp[2]};;
		
		rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window, 0.2, cross_product, {light - surfaceCenter});
		*/
	}
}

void drawline(Vector<2> p1, Vector<2> p2, sf::RenderWindow &window) {
	sf::Vertex line[2];
	line[0].position = sf::Vector2f((p1[0] + 1) / 2 * SCREEN_WIDTH, (p1[1] + 1) / 2 * SCREEN_HEIGHT);
	line[1].position = sf::Vector2f((p2[0] + 1) / 2 * SCREEN_WIDTH, (p2[1] + 1) / 2 * SCREEN_HEIGHT);
	line[0].color = line[1].color = sf::Color::Blue;
	window.draw(line, 2, sf::Lines);
}

