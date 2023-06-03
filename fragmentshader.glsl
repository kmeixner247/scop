#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec4 Normal;
in vec3 FragPos;

// uniform vec4 ourColor;
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform sampler2D ourTexture;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	vec3 ambientColor2 = vec3(0.5, 0.5, 0.5);
	vec3 diffuseColor2 = vec3(0.5, 0.5, 0.5);
	vec3 specularColor2 = vec3(0.9, 0.9, 0.9);
	// FragColor = vec4(0, 0, 0, 0);
	// FragColor = vec4(ambientColor, 0);
	// FragColor = texture(ourTexture, texCoord) * vec4(ambientColor, 0);
	vec3 norm;
	norm = vec3(Normal.xyz);
	norm = normalize(norm);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	// vec3 diffuse = diff * diffuseColor;
	vec3 diffuse = diff * diffuseColor2;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	// vec3 specular = spec * specularColor;
	vec3 specular = spec * specularColor2;
	// vec3 result = (ambientColor	+ diffuse + specular);
	vec3 result = (ambientColor2	+ diffuse + specular);
	FragColor =  vec4(1.0) * vec4(result, 1.0);
	// FragColor =  texture(ourTexture, TexCoord) * vec4(result, 1.0);
}