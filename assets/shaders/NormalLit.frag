#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBiTangent;

out vec4 outputColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform vec3 cameraPosition;

uniform float specularPower = 1;

uniform sampler2D diffuseSampler;
uniform sampler2D normalSampler;

void main()
{
    mat3 TBN = mat3 (
        normalize( vTangent ),
        normalize( vBiTangent ),
        normalize( vNormal ),
    );
    
    vec3 localNormal = texture(normal, vTexCoord).xyz * 2 -1;

    float d = max(0, dot( normalize(TBN * localNormal), lightDirection ) );
    
    outputColor = texture(diffuseSampler, vTexCoord);
    outputColor.rgb = outputColor.rgb * d;
}
