#include "Draw.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <algorithm>
const float INF = 1000000000;

sf::Color applyLighting(sf::Color c, float ambient, Vec3 normal, Vec3 light) {
	float cosTheta = std::max((float)0, dot(normalize(normal), normalize(light)));
	return sf::Color((float)c.r * ambient * cosTheta, 
		(float)c.g * ambient * cosTheta,(float)c.b * ambient * cosTheta,c.a);
}

void rasterize(triangle t, sf::RenderWindow &window, float ambient, Vec3 normal, Vec3 light, std::vector<std::vector<float> >& zbuffer) {
	
}

void draw(mesh M, sf::RenderWindow &window, Camera cam, Vec3 light) {
	std::vector<std::vector<float> > zbuffer(SCREEN_HEIGHT, std::vector<float>(SCREEN_WIDTH, INF));
	Mat4 compressx = getScaleMatrix(Vec3{ aspect_ratio, 1, 1});
	Mat4 translateCam = getTranslateMatrix(Vec3{ 0, 0, 0 } - cam.position);
	Mat4 camTransform = rotateCam(cam);
	Mat4 Transform = compressx * camTransform * translateCam;
	for (triangle t : M.triangles) {
		Vec4 v1 = t.p1 - t.p0;
		Vec4 v2 = t.p2 - t.p0;
		Vec3 cross_product = v1 * v2;

		if (dot(cross_product, Vec3{t.p0[0], t.p0[1], t.p0[2]} - cam.position) > 0)continue;
		
		Vector<4> pp0 = get2d(Transform*t.p0);
		Vector<4> pp1 = get2d(Transform*t.p1);
		Vector<4> pp2 = get2d(Transform*t.p2);

		Mat4 maptoScreen = getScaleMatrix({ SCREEN_WIDTH / float(2), SCREEN_HEIGHT / float(2), 1 }) * getTranslateMatrix({ 1, 1, 0 });
		pp0 = maptoScreen * pp0;
		pp1 = maptoScreen * pp1;
		pp2 = maptoScreen * pp2;
		
		//rasterize(triangle{ pp0, pp1, pp2, t.fillColor }, window, 1, cross_product, light, zbuffer);

		Vec3 centre = { 0, 0, 0 };
		Vec3 vn0 = normalize(Vec3{t.p0[0], t.p0[1], t.p0[2]} - centre);
		Vec3 vn1 = normalize(Vec3{ t.p1[0], t.p1[1], t.p1[2] } - centre);
		Vec3 vn2 = normalize(Vec3{ t.p2[0], t.p2[1], t.p2[2] } - centre);




		//rasterize

		std::vector<sf::Vertex> vertexarray;
		vertexarray.push_back(sf::Vertex{ sf::Vector2f{-1, -1} });
		int xmin = std::min({ pp0[0], pp1[0], pp2[0] });
		int xmax = std::max({ pp0[0], pp1[0], pp2[0] });
		int ymin = std::min({ pp0[1], pp1[1], pp2[1] });
		int ymax = std::max({ pp0[1], pp1[1], pp2[1] });

		Vec3 arean = (pp1 - pp0) * (pp2 - pp0);
		for (int i = ymin; i <= ymax; i++) {
			for (int j = xmin; j <= xmax; j++) {
				Vec4 currentPoint = { (float)j, (float)i, 0 };
				bool up1 = false, up2 = false, up3 = false;
				Vec3 cp0 = (pp1 - pp0) * (currentPoint - pp0);
				Vec3 cp1 = (pp2 - pp1) * (currentPoint - pp1);
				Vec3 cp2 = (pp0 - pp2) * (currentPoint - pp2);
				if (cp0[2] >= 0)up1 = true;
				if (cp1[2] >= 0)up2 = true;
				if (cp2[2] >= 0)up3 = true;

				if (up1 != up2 || up2 != up3) continue;

				float l2 = abs(cp0[2] / arean[2]);
				float l0 = abs(cp1[2] / arean[2]);
				float l1 = abs(cp2[2] / arean[2]);

				float depth = l0 * pp0[2] + l1 * pp1[2] + l2 * pp2[2];
				if (depth >= zbuffer[i][j])continue;
				zbuffer[i][j] = depth;

				Vec3 normal = l0 * vn0 + l1 * vn1 + l2 * vn2;
				sf::Color c = applyLighting(t.fillColor, 0.2, normal, light);
				vertexarray.push_back(sf::Vertex{ sf::Vector2f{float(j), float(i)}, c });
			}
		}
		window.draw(&vertexarray[0], vertexarray.size(), sf::Points);
	}
}
