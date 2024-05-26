//this does post processing effects
cbuffer PostProcessBuffer : register(b0)
{
    int mode;
    float params0;
    float params1;
    float params2;
}

Texture2D textureMap0 : register(t0);
Texture2D textureMap1 : register(t1);
Texture2D textureMap2 : register(t2);
Texture2D textureMap3 : register(t3);

SamplerState textureSampler : register(s0);

struct VS_INPUT
{
    float3 postion : POSITION;
    float2 texCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.postion, 1.0f);
    output.texCoord = input.texCoord;
    return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
    float4 finalColor = 1.0f;
    //none
    if(mode == 0)
    {
        finalColor = textureMap0.Sample(textureSampler, input.texCoord);
    }
    //monochrome
    else if(mode ==1)
    {
        float4 color = textureMap0.Sample(textureSampler, input.texCoord);
        finalColor = (color.r + color.g + color.b) / 3.0f;
    }
    //invert
    else if(mode == 2)
    {
        float4 color = textureMap0.Sample(textureSampler, input.texCoord);
        finalColor = 1.0f - color;
    }
    //mirror
    else if (mode == 3)
    {
        float2 texCoord = input.texCoord;
        texCoord.x *= params0;
        texCoord.y *= params1;
        finalColor = textureMap0.Sample(textureSampler, texCoord);
    }
    //blur
    else if (mode == 4)
    {
        float u = input.texCoord.x;
        float v = input.texCoord.y;
        finalColor =
        textureMap0.Sample(textureSampler, float2(u, v))
        + textureMap0.Sample(textureSampler, float2(u + params0, v))
        + textureMap0.Sample(textureSampler, float2(u - params0, v))
        + textureMap0.Sample(textureSampler, float2(u, v + params1))
        + textureMap0.Sample(textureSampler, float2(u, v - params1))
        + textureMap0.Sample(textureSampler, float2(u + params0, v + params1))
        + textureMap0.Sample(textureSampler, float2(u + params0, v - params1))
        + textureMap0.Sample(textureSampler, float2(u - params0, v + params1))
        + textureMap0.Sample(textureSampler, float2(u - params0, v - params1));
        
        finalColor *= 0.1111f;
    }
    //combine2
    else if (mode == 5)
    {
        float4 color0 = textureMap0.Sample(textureSampler, input.texCoord);
        float4 color1 = textureMap1.Sample(textureSampler, float2(input.texCoord.x + params0, input.texCoord.y + params1));
        finalColor = (color0 + color1) * 0.5f;
        //finalColor = ((1.0f - color1.a) * color0) + (color1.a + color1);
    }
    //chromaticaberration
    else if (mode == 6)
    {
        float2 distortion = float2(params0, -params0);
        float4 redChannel = textureMap0.Sample(textureSampler, input.texCoord + distortion.x * input.texCoord);
        float4 greenChannel = textureMap0.Sample(textureSampler, input.texCoord);
        float4 blueChannel = textureMap0.Sample(textureSampler, input.texCoord + distortion.y * input.texCoord);
        
        finalColor = float4(redChannel.r, greenChannel.g, blueChannel.b, 1.0f);
    }
     //wave
    else if (mode == 7)
    {
        float waveValue = input.texCoord.x * (3.14159 * params0);
        float2 texCoord = input.texCoord;
        texCoord.y += sin(waveValue) * params1;
        finalColor = textureMap0.Sample(textureSampler, texCoord);
    }
    return finalColor;
}
