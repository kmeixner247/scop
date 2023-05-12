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
	// FragColor = vec4(0, 0, 0, 0);
	// FragColor = vec4(ambientColor, 0);
	// FragColor = texture(ourTexture, texCoord) * vec4(ambientColor, 0);
	vec3 norm;
	norm = vec3(Normal.xyz);
	// vec3 norm = normalize(Normal);
	norm = normalize(norm);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * diffuseColor;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = spec * specularColor;
	vec3 result = (ambientColor	+ diffuse + specular);
	FragColor =  vec4(1.0) * vec4(result, 1.0);
	// FragColor =  texture(ourTexture, TexCoord) * vec4(result, 1.0);
}