#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 vFragPos;
in vec3 vNormal;
out vec4 FragColor;

uniform Material uMaterial;
uniform Light uLight;
uniform vec3 uViewPos;

void main() {
    vec3 normal = normalize(vNormal);
    vec3 lightDir = normalize(uLight.position - vFragPos);
    vec3 viewDir = normalize(uViewPos - vFragPos);
    vec3 halfDir = normalize(lightDir + viewDir);

    float diff = max(dot(normal, lightDir), 0.0);
    float spec = pow(max(dot(normal, halfDir), 0.0), uMaterial.shininess);

    vec3 ambient = uLight.ambient * uMaterial.ambient;
    vec3 diffuse = uLight.diffuse * (diff * uMaterial.diffuse);
    vec3 specular = uLight.specular * (spec * uMaterial.specular);

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
