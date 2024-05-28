Texture2D	 g_texture:register(t0);//�e�N�X�`��
SamplerState g_sampler:register(s0);//�T���v���[
//�R���X�^���g�o�b�t�@
cbuffer global
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matW;				//���[���h�s��
	float4x4    g_matNormal;		//�@���ό`�s��(��]�s��Ɗg��s��̋t�s��)
	float4x4	g_matWLP;			//��������݂�����g_matWVP
	float4x4	g_matWLPT;			//���Ƀe�N�X�`�����W�s������������z
	float4		g_diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		g_ambient;			//�A���r�G���g
	float4		g_speculer;			//�X�y�L�����[
	float4		g_lightDirection;	//���C�g�̌���
	float4		g_cameraPosition;	//�J�����̈ʒu
	float4      g_customColor;		//�v���O�������ŐF��ς���ꍇ�̕ϐ�
	float		g_shininess;		//�n�C���C�g�̋���
	bool		g_isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
	bool		g_isNormal;  //�v���O�������ŕς���F
};
struct VS_OUT
{
	float4 pos: SV_POSITION;
	float4 normal : TEXCOORD0;
	float2 uv:TEXCOORD1;
	float4 color:COLOR0;
};
VS_OUT VS( float4 pos : POSITION ,float4 uv:TEXCOORD,float4 normal:NORMAL)
{
	VS_OUT outData;
	//���_�̍��W��m�[�}���ɍs�񂩂��ăs�N�Z���V�F�[�_�[�ɓn��
	outData.pos = mul(pos, g_matWVP);
	normal.w = 0;
	outData.normal = mul(normal, g_matNormal);
	outData.uv = uv;

	return outData;
}

float4 PS(VS_OUT inData) : SV_Target
{
	inData.normal = normalize(inData.normal);
	//�g�U���ˌ�(�f�B�t���[�Y)
	float4 diffuse;
	if (g_isTexture == true)
	{
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		diffuse = g_diffuseColor;
	}
	
	//����(�A���r�G���g)
	float4 ambient = g_ambient;
	ambient.a = 1;

	float4 outColor;
	outColor = diffuse * ambient;
	return outColor;
}


