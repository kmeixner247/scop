#version 330



// uniform vec3 lightDirection;  // Direction of the light source
uniform vec3 ambientColor;    // Ambient color of the material
uniform vec3 diffuseColor;       // Diffuse color of the material
uniform vec3 specularColor;   // Specular color of the material

uniform vec3 lightPos;
in vec3 FragPos;
in vec2 TexCoord;
in vec4 Normal;         // Normal vector of the fragment

uniform sampler2D ourTexture;
uniform float textureRandomRatio;


out vec4 fragColor;
in vec4 aRandomColor;

void main()
{
	vec4 baseColor = texture(ourTexture, TexCoord).zyxw;

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
    vec3 viewDirection = normalize(-gl_FragCoord.xyz);
    
    // Calculate the specular factor based on the dot product of reflection and view direction
    float specularFactor = pow(max(dot(reflection, viewDirection), 0.0), 64.0);
    
    // Calculate the final specular color by multiplying the specular factor with the specular color
    vec3 specular = specularColor * specularFactor;
    vec4 test = vec4(ambientColor, 1.0) * textureRandomRatio * aRandomColor + (1.0 - textureRandomRatio) * baseColor;
    // Set the fragment color as the sum of diffuse and specular colors
    fragColor = test * vec4(ambientColor + diffuse + specular, 1.0);
}