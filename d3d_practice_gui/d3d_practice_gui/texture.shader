Texture2D shaderTexture;
SamplerState SampleType;

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectMatrix;
};

struct VOut
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

VOut VShader(float4 position : POSITION, float2 tex : TEXCOORD0)
{
	VOut output;

	position.w = 1.0f;
	output.position = mul(position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectMatrix);

	output.tex = tex;

	return output;
};

float4 PShader(VOut input) : SV_TARGET
{
	float4 texture_color;
	texture_color = shaderTexture.Sample(SampleType, input.tex);

	return texture_color;
};