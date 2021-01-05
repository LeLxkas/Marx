cbuffer sceneData : register(b0)
{
	matrix viewProjection;
};

struct VS_INPUT
{
	float3 pos : POSITION;
	float3 color : COLOR;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 color : OUT_COLOR;
};

VS_OUTPUT main(VS_INPUT inp)
{
	VS_OUTPUT op;
	op.pos = mul(float4(inp.pos, 1.0f), viewProjection);
	op.color = float4(inp.color, 1.0f);
	return op;
}