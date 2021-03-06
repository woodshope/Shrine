#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct Light {
    vec3 position;
	vec3 color;

	vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Cover {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform Light light;
uniform Material material;
uniform Cover cover;
uniform vec3 viewPos;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb * light.color * cover.ambient;// * 2.5;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb * light.color * cover.diffuse;// * 2.5;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb * light.color * cover.specular;// * 2.5;  

	// spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation;   
        
    vec3 result = ambient + diffuse + specular;

	float fogDistance = sqrt(pow(viewPos.x - FragPos.x, 2) + pow(viewPos.z - FragPos.z, 2));
	float fogMax = 40.0f;
	float fogMin = 5.0f;
	float fogFactor = (fogMax - fogDistance) / (fogMax - fogMin);
	fogFactor = clamp(fogFactor, 0.3f, 1.0f);
	vec4 fogColor = vec4(0.8f, 0.8f, 0.8f, 1.0f);
    FragColor = mix(fogColor, vec4(result, 1.0), fogFactor);

   // FragColor = vec4(result, 1.0);
}