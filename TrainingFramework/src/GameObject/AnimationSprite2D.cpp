#include "AnimationSprite2D.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"
#include <iostream>

AnimationSprite2D::AnimationSprite2D():Sprite2D() {}

AnimationSprite2D
	::AnimationSprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int _numFrame, float _fameTime)
	:Sprite2D(model, shader, texture), m_numFrame(_numFrame), m_frameTime(_fameTime),m_currentFrame(0), m_currentTime(0.0f)
{}

void AnimationSprite2D:: Init()
{
	Sprite2D::Init();
}
void AnimationSprite2D::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);

	//take Currentframe
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_currentFrame");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_currentFrame);
		//std::cout << "\n m_CurrenFrame == " << m_currentFrame;
	}

		

	//take Numframe
	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_numFrame");
	if (iTempShaderVaribleGLID != -1)
	{
		glUniform1f(iTempShaderVaribleGLID, m_numFrame);
		//std::cout << "\n m_NUMFRAME == " << m_numFrame;
	}

		

	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void AnimationSprite2D::Update(GLfloat deltatime)
{
	m_currentTime += deltatime;
	if (m_currentTime > m_frameTime)
	{
		m_currentFrame ++;
		if (m_currentFrame == m_numFrame)
		{
			m_currentFrame = 0;
		}
		m_currentTime -= m_frameTime;
	}
}