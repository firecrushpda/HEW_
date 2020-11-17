#include "UIController.h"
#include "renderer.h"
#include "MathUtil.h"

D3DXVECTOR3* curve;
D3DXVECTOR3 sp = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3 fp = D3DXVECTOR3(0, 1, 0);
D3DXVECTOR3 secp = D3DXVECTOR3(0, 1, 0);
D3DXVECTOR3 ep = D3DXVECTOR3(1, 1, 0);
#define segmentNum    (60)

HRESULT InitUIController() {
	curve = GetThreePowerBeizerList(sp, fp, secp, ep, segmentNum);
	return S_OK;
}

void UninitUIController() {
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void UpdateUIController(void) {


}

void DrawUIController(void) {
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	////ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiCond_FirstUseEver);
	//ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_Once);
	ImGui::Begin("test window");
	// //context
	//ImGui::Text("Text");
	//ImGui::TextDisabled("Disabled text");
	ImGui::Text("start point = %f, %f, %f", sp.x, sp.y, sp.z);
	ImGui::Text("first point = %f, %f, %f", fp.x, fp.y, fp.z);
	ImGui::Text("second point = %f, %f, %f", secp.x, secp.y, secp.z);
	ImGui::Text("end point = %f, %f, %f", ep.x, ep.y, ep.z);
	if (curve != NULL)
	{
		float LinePointY[segmentNum];
		for (size_t i = 0; i < segmentNum; i++)
		{
			LinePointY[i] = curve[i].y;
		}
		LinePointY[0] = 0.0f;
		LinePointY[segmentNum - 1] = 1.0f;
		ImGui::PlotLines("animation curve", LinePointY, IM_ARRAYSIZE(LinePointY), NULL, NULL, 0.0f, 1.0f, ImVec2(0, 100.0f));
	}

	ImGui::End();

	ImGui::Render();
	auto rtv = GetRenderTargetView();
	float ClearColor[4] = { 0.0f, 0.5f, 0.5f, 1.0f };
	GetDeviceContext()->OMSetRenderTargets(1, &rtv, NULL);
	GetDeviceContext()->ClearRenderTargetView(rtv, ClearColor);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}





