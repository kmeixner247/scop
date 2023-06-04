// #version 330 core

// out vec4 FragColor;

// in vec2 TexCoord;
// in vec4 Normal;
// in vec3 FragPos;

// // uniform vec4 ourColor;
// uniform vec3 ambientColor;
// uniform vec3 diffuseColor;
// uniform vec3 specularColor;
// uniform sampler2D ourTexture;
// uniform vec3 lightPos;
// uniform vec3 viewPos;

// void main()
// {
// 	// FragColor = vec4(0, 0, 0, 0);
// 	// FragColor = vec4(ambientColor, 0);
// 	// FragColor = texture(ourTexture, texCoord) * vec4(ambientColor, 0);

// 	vec3 norm;
// 	norm = vec3(Normal.xyz);
// 	norm = normalize(norm);
// 	vec3 lightDir = normalize(lightPos - FragPos);
// 	float diff = max(dot(norm, lightDir), 0.0);

// 	vec3 diffuse = diff * diffuseColor;

// 	vec3 viewDir = normalize(viewPos - FragPos);
// 	vec3 reflectDir = reflect(lightDir, norm);
// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

// 	vec3 specular = spec * specularColor;

// 	vec3 result = (ambientColor + diffuse + specular);
// 	float test = max(max(result.x, result.y), result.z);
// 	result /= test;
// 	FragColor =  vec4(0.5) * vec4(result, 1.0);
// 	// FragColor =  texture(ourTexture, TexCoord) * vec4(result, 1.0);
// }

#version 330



// uniform vec3 lightDirection;  // Direction of the light source
uniform vec3 ambientColor;    // Ambient color of the material
uniform vec3 diffuseColor;       // Diffuse color of the material
uniform vec3 specularColor;   // Specular color of the material

uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 FragPos;
in vec4 Normal;         // Normal vector of the fragment

out vec4 fragColor;

void main()
{
	vec3 lightDirection = normalize(FragPos - lightPos);

    // Normalize the vertex normal
    vec3 normal = normalize(Normal.xyz);

    // Calculate the dot product between the light direction and the vertex normal
    float diffuseFactor = max(dot(normal, lightDirection), 0.0);

    // Calculate the final diffuse color by multiplying the diffuse factor with the diffuse color
    vec3 diffuse = diffuseColor * diffuseFactor;

    // Calculate the reflection vector for specular lighting
    vec3 reflection = reflect(-lightDirection, normal);
    
    // Calculate the view direction (assuming camera at (0, 0, 0))
    vec3 viewDirection = normalize(viewPos - gl_FragCoord.xyz);
    
    // Calculate the specular factor based on the dot product of reflection and view direction
    float specularFactor = pow(max(dot(reflection, viewDirection), 0.0), 32.0);
    
    // Calculate the final specular color by multiplying the specular factor with the specular color
    vec3 specular = specularColor * specularFactor;

    // Set the fragment color as the sum of diffuse and specular colors
    fragColor = vec4(ambientColor + diffuse + specular, 1.0);
}