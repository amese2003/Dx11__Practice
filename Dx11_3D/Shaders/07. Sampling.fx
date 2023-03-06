matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;

struct VertexInput
{
    float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);

    output.uv = input.uv;

    return output;
}

SamplerState Sampler0;

float4 PS(VertexOutput input) : SV_TARGET
{
    return Texture0.Sample(Sampler0, input.uv);
}

// Sampling
uint Filter;

SamplerState SamplerFilterPoint
{
    Filter = MIN_MAG_MIP_POINT;
};

SamplerState SamplerFilterLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
};

float4 PS_Filter(VertexOutput input) : SV_Target
{
    if (Filter == 0)
        return Texture0.Sample(SamplerFilterPoint, input.uv);

    if (Filter == 1)
        return Texture0.Sample(SamplerFilterLinear, input.uv);

    return Texture0.Sample(Sampler0, input.uv);
}

uint Address;

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState SamplerAddressMirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};

SamplerState SamplerAddressClamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};

SamplerState SamplerAddressBorder
{
    AddressU = Border;
    AddressV = Border;

    BorderColor = float4(0, 0, 1, 1);
};

float4 PS_Address(VertexOutput input) : SV_Target
{
    if (Address == 0)
        return Texture0.Sample(SamplerAddressWrap, input.uv);

    if (Address == 1)
        return Texture0.Sample(SamplerAddressMirror, input.uv);

    if (Address == 2)
        return Texture0.Sample(SamplerAddressClamp, input.uv);

    if (Address == 3)
        return Texture0.Sample(SamplerAddressBorder, input.uv);

    return Texture0.Sample(Sampler0, input.uv);
}

technique11 T0
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }

    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Filter()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_Address()));
    }
}