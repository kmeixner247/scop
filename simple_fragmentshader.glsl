#version 330


in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float textureRandomRatio;


out vec4 fragColor;
in vec4 aRandomColor;

void main()
{
	vec4 baseColor = texture(ourTexture, TexCoord).zyxw;
    
    // Mix random colors and texture depending on the Ratio (for smooth transition)
    fragColor = textureRandomRatio * aRandomColor + (1.0 - textureRandomRatio) * baseColor;
}