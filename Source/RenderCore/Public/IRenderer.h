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

	/** 렌더하기전에 호출해야 합니다. */
	virtual void BeginRender() = 0;

	/** 렌더할것을 모두그리고 호출해야합니다. */
	virtual void EndRender() = 0;

	/**
	 * @brief 렌더 리소스를 렌더합니다.
	 * @param renderResource 렌더에 사용할 리소스
	 *						 GetRenderResource로 생성 합니다.
	 * @param renderData 렌더에 필요한 데이터
	 */
	virtual void RenderObject(IUnknown* renderResource, RenderData* renderData) = 0;

	/**
	 * @brief Resource/ 경로의 해당 이름의 리소스를 가져옵니다.
	 * @param name 리소스의 이름, 경로
	 * @return 생성된 리소스
	 */
	virtual IUnknown* GetRenderResource(std::wstring name) = 0;


	/** 렌더할 버퍼의 폭 */
	virtual unsigned int GetWidth() = 0;

	/** 렌더할 버퍼의 높이 */
	virtual unsigned int GetHeight() = 0;

	/**
	 * @brief 렌더할 버퍼를 재조정 합니다.
	 * @param width 새로운 폭
	 * @param height 새로운 높이
	 */
	virtual void ReSize(unsigned int newWidth, unsigned int newHeight) = 0;
private:

};



class RENDERCOREMODULEAPI RendererFactory : public Factory<IRenderer, String> {};