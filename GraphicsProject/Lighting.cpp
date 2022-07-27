#include "Lighting.h"

sf::Color applyLighting2(Vec4 light, Vec4 normal, Vec4 view, float ambientIntensity, material m) {
	light = normalize(light);
	normal = normalize(normal);
	view = normalize(view);

	uint8_t color[3];

	Vec4 reflection = 2 * dot(light, normal) * normal - light;
	for (int i = 0; i < 3; i++) {
		float intensity = 0;
		float ambient = m.ka[i] * ambientIntensity;
		float diffuse = max(dot(light, normal), 0) * m.kd[i] / magnitudeSquared(light);
		float specular = diffuse > 0 ? pow(max(dot(reflection, view), 0), m.ns) * m.ks[i] : 0;
		intensity = ambient + diffuse + specular;
		intensity = min(intensity, 1);
		color[i] = 255 * intensity;
	}
	return(sf::Color(color[0], color[1], color[2]));
}