cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectMatrix;
};

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR)
{
	VOut output;

	position.w = 1.0f;
	output.position = mul(position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	//output.position = mul(output.position, projectionMatrix);

	//output.position = position;
	output.color = color;

	return output;
};

float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
};