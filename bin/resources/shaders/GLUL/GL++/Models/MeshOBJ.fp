#version 330 core

in vec2 fragmentUV;
in vec3 fragmentNormal;
in vec3 fragmentPosition;

out vec4 color;

uniform vec4 uColorD;
uniform vec4 uColorA;
uniform vec4 uColorS;

uniform bvec4 hasTextures;
uniform sampler2D texSampler;

const float diffuseFactor  = 0.5;
const float ambientFactor  = 0.3;
const float specularFactor = 0.0;

void main() {
	vec3 fragmentNormalNormalized = normalize(fragmentNormal);

	vec3 cameraPos = vec3(-1, 0.5, -4.0);
	vec3 lightDir  = normalize(vec3(-1.0, 1.0, 0.5));
	vec3 cameraToFragmentDir = fragmentPosition - cameraPos;

	float diffuseCosine   = clamp(dot(fragmentNormalNormalized, lightDir), 0.0, 1.0);
	float specularPower   = uColorS.a;
	float specularCosine  = clamp(dot(normalize(cameraToFragmentDir), reflect(lightDir, fragmentNormalNormalized)), 0.0, 1.0);
	float specularCosineP = pow(specularCosine, specularPower);

	vec3 lightColor = vec3(1.0, 1.0, 1.0);

	if(hasTextures.x)
		lightColor = texture(texSampler, fragmentUV).rgb;

	color.rgb  = vec3(0.0);
	color.rgb += uColorA.rgb * ambientFactor;
	color.rgb += uColorD.rgb * lightColor *  diffuseFactor * diffuseCosine;
	color.rgb += uColorS.rgb * lightColor * specularFactor * specularCosineP;
	color.a = uColorA.a;
}