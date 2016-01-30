#version 410

in vec4 vPosition;
in vec4 vNormal;
in vec2 vTexCoord;

out vec4 outputColor;

uniform vec3 lightDirection;
uniform vec3 lightColor;
uniform vec3 cameraPosition;
uniform float specularPower = 1;
uniform sampler2D tex;
uniform sampler2D tex1;
uniform sampler2D tex2;


void main()
{
    float d = max(0, dot( normalize(vNormal.xyz), lightDirection ) );
    vec3 e = normalize( cameraPosition - vPosition.xyz );
    vec3 r = reflect( -lightDirection, vNormal.xyz );
    float s = max( 0, dot( e, r ) );
    s = pow( s, specularPower );
    vec4 lightOutputColor = vec4(lightColor * d + lightColor * s, 1);

   vec4 texColor0 = texture( tex, vTexCoord );
   vec4 texColor1 = texture( tex1, vTexCoord );
   vec4 texColor2 = texture( tex2, vTexCoord );
   
   outputColor = texColor0 * lightOutputColor;
}
