#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

#define NR_POINT_LIGHTS 4
#define NR_DIRECTIONAL_LIGHTS 1
#define NR_SPOT_LIGHTS 4

uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform PointLight pointLights[NR_POINT_LIGHTS];

// Gets the Texture Unit from the main function
uniform sampler2D diffuse0;
// Gets the Specular Texture Unit from the main function
uniform sampler2D specular0;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

vec4 pointLight()
{
	// Light should be less bright over distance.
	vec3 lightVec = lightPos - crntPos;
	float dist = length(lightVec);
	float a = .05f;
	float b = 0.01f;
	float inten = 1.0f; // / (a * dist * dist + b * dist + 1.0f);

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting - (BlinnPhong Shading)
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 directionLight()
{
	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f)); // Points in one direction
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting - (BlinnPhong Shading)
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	float outerCone = .60f; //  Imagine the light  is an arrow. The inner is  the first circle which is  of max strength. The outter circle is circle where light is 0.
	float innerCone = .95f;

	// ambient lighting
	float ambient = 0.20f;

	// diffuse lighting
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(spotLights[3].position - crntPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular lighting - (BlinnPhong Shading)
	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	// Calculate the light circles.
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, texCoord) * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 CalcPointLight(PointLight pointLight, vec3 viewDirection, vec3 normal )
{
	vec3 lightDirection = normalize(pointLight.position - crntPos);

    // diffuse shading
    float diff = max(dot(normal, lightDirection), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDir), 0.0), 16);
   
    // attenuation
    float distance = length(pointLight.position - crntPos);
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));    
   
    // combine results
    vec3 ambient = pointLight.ambient * vec3(texture(diffuse0, texCoord));
    vec3 diffuse = pointLight.diffuse * diff * vec3(texture(diffuse0, texCoord));
    vec3 specular = pointLight.specular * spec * vec3(texture(specular0, texCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return  vec4((ambient + diffuse + specular),1.0f);
}

vec4 CalcSpotLight(SpotLight spotLight, vec3 viewDirection, vec3 normal)
{
	// Get the direction of the light!
	vec3 lightDirection = normalize(spotLight.position - crntPos);

	// diffuse lighting
	float diff = max(dot(normal, lightDirection), 0.0f);

	// specular lighting - (BlinnPhong Shading)
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16); // the 16 is shininess

	 // attenuation
    float distance = length(spotLight.position - crntPos);
    float attenuation = 1.0 / (spotLight.constant + spotLight.linear * distance + spotLight.quadratic * (distance * distance));

	// Calculate the light circles.
	float angle = dot(spotLight.direction, lightDirection); 
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
    float intensity = clamp((angle - spotLight.outerCutOff) / epsilon, 0.0, 1.0);

	// combine results
    vec3 ambient = spotLight.ambient * vec3(texture(diffuse0, texCoord));
    vec3 diffuse = spotLight.diffuse * diff * vec3(texture(diffuse0, texCoord));
    vec3 specular = spotLight.specular * specAmount * vec3(texture(specular0, texCoord));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return vec4((specular + ambient + diffuse),1.0f);
}

void main()
{
	vec3 viewDirection = normalize(camPos - crntPos);
	vec3 normal = normalize(Normal);

	vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);

	//for(int i = 0; i < NR_SPOT_LIGHTS; i++)
		//result += CalcSpotLight(spotLights[i], viewDirection, normal);    
	
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], viewDirection, normal);    
	

	// outputs final color
	FragColor =  result;
}