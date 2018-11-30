Texture2D shaderTexture;
SamplerState SampleType;

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectMatrix;
};

cbuffer LightBuffer
{
	float4 diffuseColor;
	float3 lightDirection;
	float padding;
};

struct VertexInputType
{
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

VOut VShader(VertexInputType input)
{
	VOut output;

	input.position.w = 1.0f;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectMatrix);

	output.tex = input.tex;
	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	return output;
};

float4 PShader(VOut input) : SV_TARGET
{
	float4 texture_color;
	float3 lightDir;
	float lightIntensity;
	float4 color;

	texture_color = shaderTexture.Sample(SampleType, input.tex);

	// Invert the light diretion for calculations.
	lightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	lightIntensity = saturate(dot(input.normal, lightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	color = saturate(diffuseColor * lightIntensity);

	// Multiply the texture pixel and the final diffuse olor to get the final pixel color result.
	color = color * texture_color;

	return color;
};