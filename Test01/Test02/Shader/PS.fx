struct ps_input
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	//float2 texCoord : TEXCOORD;
};

//Texture2D diffuseMap;
//SamplerState diffuseSampler;

float4 main(ps_input input) : SV_TARGET
{
	//float4 textureColor = diffuseMap.Sample(diffuseSampler, input.texCoord);

	//return textureColor;

	return input.color;
}