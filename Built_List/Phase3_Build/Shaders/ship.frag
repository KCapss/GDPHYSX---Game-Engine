#version 330 core //Version
uniform sampler2D tex0;
uniform sampler2D norm_tex;

uniform vec3 lightPos; //World Position
uniform vec3 lightColor; //RGB

uniform float ambientStr;
uniform vec3 ambientColor;

uniform vec3 cameraPos;
uniform float specStr;
uniform float specPhong;

uniform float lightType;
uniform float lumens;

// unform vec3 specColor; // Optional

in vec2 texCoord;
in vec3 normCoord;
in vec3 fragPos;

in mat3 TBN;

out vec4 FragColor; //Returns a Color



//Simple shader that colors the model Red
void main()
{

    vec4 pixelColor = texture(tex0, texCoord);

    vec3 normal = texture(norm_tex, texCoord).rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);

    //placeHolder
    vec3 lightDir = normalize(lightPos - fragPos);

    if(lightType == 1){
        lightDir = lightPos;
    }

    //Point Light
    float lightDist = length(lightPos - fragPos);   //Get the Eucleadian Distance && "length function" part of GLSL.
    float lightAtten = 1.0f / ((lightDist * lightDist) + lightDist/3.0f + 3.0f ) ; //Getting Light Intensity in relation to the distance of the source and target
    float amplify = lightAtten * lumens;
    if (amplify > 1.10f){

       amplify = 1.10f;

    }

    else if (amplify < 0.01f){
         amplify = 0.05f;
    
    }


    
    //normalLight Comp
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 ambientCol = ambientColor * ambientStr;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(reflectDir, viewDir), 0.1), specPhong);

    vec3 specColor = spec * specStr * lightColor;
    FragColor = (vec4((specColor + ambientCol + diffuse), 1.0)) * pixelColor;

    if(lightType == 0)
	{
		FragColor = (vec4((specColor + ambientCol + diffuse) * amplify, 1.0)) * pixelColor;
	}
	else if(lightType == 1)
	{
		FragColor = (vec4((specColor + ambientCol + diffuse), 1.0)) * pixelColor;
	}
}