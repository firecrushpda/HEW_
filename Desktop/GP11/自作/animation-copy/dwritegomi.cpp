#include "SelectMenu.h"
#include "renderer.h"

IDWriteFactory* pDWriteFactory_;
IDWriteTextFormat* pTextFormat_;

const wchar_t* wszText_;
UINT32 cTextLength_;

//ID2D1RenderTarget* pRT_ = NULL;
ID2D1HwndRenderTarget* pRT_;
ID2D1SolidColorBrush* pBlackBrush_;
ID2D1Factory* pD2DFactory_;

float dpiScaleX_ = 1.0f;
float dpiScaleY_ = 1.0f;

D2D1_RECT_F layoutRect;

IDXGISurface*	surface;

RECT rc;

HRESULT InitSelectMenu(HWND hWnd) {
	D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory_
	);

	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory_)
	);

	pDWriteFactory_->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.0f,
		L"en-us",
		&pTextFormat_
	);

	pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

	wszText_ = L"Hello World using  DirectWrite!";
	cTextLength_ = (UINT32)wcslen(wszText_);

	GetClientRect(hWnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	if (!pRT_)
	{
		// Create a Direct2D render target.
		pD2DFactory_->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(
				hWnd,
				size
			),
			&pRT_
		);
		/*GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(surface));
		D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
			D2D1_RENDER_TARGET_TYPE_DEFAULT,
			D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
		HRESULT hr = pD2DFactory_->CreateDxgiSurfaceRenderTarget(surface, &props, &pRT_);
		surface->Release();*/

		// Create a black brush.
		pRT_->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&pBlackBrush_
		);
	}
	return S_OK;
}

void UninitSelectMenu() {
	pRT_->Release();
	pRT_ = NULL;
	pBlackBrush_->Release();
	pBlackBrush_ = NULL;
	//
}

void UpdateSelectMenu(void) {
	

}

void DrawSelectMenu(void) {
	
	/*pRT_->BeginDraw();
	pRT_->DrawTextA(wszText_, cTextLength_, pTextFormat_,
		D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, pBlackBrush_);
	pRT_->EndDraw();*/

	pRT_->BeginDraw();

	pRT_->SetTransform(D2D1::IdentityMatrix());

	pRT_->Clear(D2D1::ColorF(D2D1::ColorF::White));
	pRT_->DrawTextA(wszText_, cTextLength_, pTextFormat_,
	D2D1_RECT_F{ 0.0f, 0.0f, 600.0f, 200.0f }, pBlackBrush_);

	//layoutRect = D2D1::RectF(
	//	static_cast<FLOAT>(rc.left),// / dpiScaleX_,
	//	static_cast<FLOAT>(rc.top), // / dpiScaleY_,
	//	static_cast<FLOAT>(rc.right - rc.left),// / dpiScaleX_,
	//	static_cast<FLOAT>(rc.bottom - rc.top)// / dpiScaleY_
	//);

	//pRT_->DrawText(
	//	wszText_,        // The string to render.
	//	cTextLength_,    // The string's length.
	//	pTextFormat_,    // The text format.
	//	layoutRect,       // The region of the window where the text will be rendered.
	//	pBlackBrush_     // The brush used to draw the text.
	//);

	pRT_->EndDraw();
}





