
struct VS_INPUT
{
	float4 position : POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};

texture2D texture0 : register(t0);
texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);
SamplerState sampler1 : register(s1);

// Buffer
cbuffer CameramData : register(b0)
{
	row_major matrix matView;
	row_major matrix matProjection;
}

cbuffer TransformData : register(b1)
{
	row_major matrix matWorld;
}

cbuffer AnimationData : register(b2)
{
	float2 spriteOffset;
	float2 spriteSize;
	float2 textureSize;
	float useAnimation;
}


// IA - VS - RS - PS - OM
VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	
	float4 position = mul(input.position, matWorld);
	position = mul(position, matView);
	position = mul(position, matProjection);

	output.position = position;
	output.uv = input.uv;

	if (useAnimation == 1.0f)
	{
		output.uv *= spriteSize / textureSize;
		output.uv += spriteOffset / textureSize;
	}

	return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 color = texture0.Sample(sampler0, input.uv);

	return color;
}