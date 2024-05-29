
cbuffer grobal
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matW;				//���[���h�s��
	float4x4	g_matWLP;			//��������݂�����g_matWVP
	float4x4	g_matWLPT;			//���Ƀe�N�X�`�����W�s������������z
	float4x4    g_matNormal;		//�@���ό`�s��(��]�s��Ɗg��s��̋t�s��)
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
	float4 pos : SV_POSITION;
	float4 depth	: TEXCOORD0;
};

VS_OUT VS(float4 pos : POSITION)
{
	VS_OUT outWLP;
	outWLP.pos = mul(pos, g_matWLP);
	outWLP.depth = outWLP.pos;
	return outWLP;
}

float4 PS(VS_OUT inData) : SV_Target
{
	float4 color = float4(0,0,0,1);
	color.r = inData.depth.z / inData.depth.w;
	color.g = color.r * color.r;
	color.a = 1;
	return color;
	//return float4(1,1,1,1);
}