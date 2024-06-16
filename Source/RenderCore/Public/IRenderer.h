#pragma once

#include "Containers/String.h"
#include "Template/Factory.h"

struct IUnknown;
struct RenderData { };


class RENDERCOREMODULEAPI IRenderer
{
public:
	IRenderer() = default;
	virtual ~IRenderer() = default;

	virtual void Init() = 0;
	virtual void EndPlay() = 0;

	/** �����ϱ����� ȣ���ؾ� �մϴ�. */
	virtual void BeginRender() = 0;

	/** �����Ұ��� ��α׸��� ȣ���ؾ��մϴ�. */
	virtual void EndRender() = 0;

	/**
	 * @brief ���� ���ҽ��� �����մϴ�.
	 * @param renderResource ������ ����� ���ҽ�
	 *						 GetRenderResource�� ���� �մϴ�.
	 * @param renderData ������ �ʿ��� ������
	 */
	virtual void RenderObject(IUnknown* renderResource, RenderData* renderData) = 0;

	/**
	 * @brief Resource/ ����� �ش� �̸��� ���ҽ��� �����ɴϴ�.
	 * @param name ���ҽ��� �̸�, ���
	 * @return ������ ���ҽ�
	 */
	virtual IUnknown* GetRenderResource(std::wstring name) = 0;


	/** ������ ������ �� */
	virtual unsigned int GetWidth() = 0;

	/** ������ ������ ���� */
	virtual unsigned int GetHeight() = 0;

	/**
	 * @brief ������ ���۸� ������ �մϴ�.
	 * @param width ���ο� ��
	 * @param height ���ο� ����
	 */
	virtual void ReSize(unsigned int newWidth, unsigned int newHeight) = 0;
private:

};



class RENDERCOREMODULEAPI RendererFactory : public Factory<IRenderer, String> {};