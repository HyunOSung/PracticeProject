cbuffer perObjectBuffer : register(b0)
{
	matrix world;
};

cbuffer perSceneBuffer : register(b1)
{
	matrix view;
	matrix projection;
};


struct vs_input
{
	float4 position: POSITION;
	float4 color : COLOR;
	//float2 texCoord : TEXCOORD;
};

struct vs_output
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	//float2 texCoord : TEXCOORD;
};

vs_output main(vs_input input)
{
	vs_output output;

	//output.position = input.position;

	output.position = mul(input.position, world);
	output.position = mul(input.position, view);
	output.position = mul(input.position, projection);

	output.color = input.color;
	//output.texCoord = input.texCoord;


	return output;
}