#include "dx12Hook.h"


bool Dx12Hook::Dx12Enabled = false;

t_Present Dx12Hook::PtroPresent = nullptr;
t_Present Dx12Hook::oPresent = nullptr;

bool Dx12Hook::D3DInitalized = false;

ID3D12Device* Dx12Hook::device = nullptr;
ID3D12Resource* Dx12Hook::backBuffer = nullptr;
ID3D12DescriptorHeap* Dx12Hook::descriptorHeap = nullptr;
ID3D12CommandAllocator* Dx12Hook::commandAlloc = nullptr;
D3D12_CPU_DESCRIPTOR_HANDLE Dx12Hook::rtvHandle = { 0 };
ID3D12GraphicsCommandList* Dx12Hook::commandList = nullptr;


HRESULT __stdcall Dx12Hook::hkPresent(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
    if (!D3DInitalized)
    {
        if (swapChain->GetDevice(__uuidof(ID3D12Device), (void**)(&device)) != S_OK)
            MessageBox(NULL, "GetDevice", "Failed", NULL);

        IDXGISwapChain3* swapChain3 = nullptr;

        if (swapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swapChain3) != S_OK)
            MessageBox(NULL, "QueryInterface", "Failed", NULL);

        UINT bufferIndex = swapChain3->GetCurrentBackBufferIndex();

        if (swapChain3->GetBuffer(bufferIndex, __uuidof(ID3D12Resource), (void**)(&backBuffer)) != S_OK)
            MessageBox(NULL, "GetBuffer", "Failed", NULL);

        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.NumDescriptors = 1;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        heapDesc.NodeMask = 0;
            
        if (device->CreateDescriptorHeap(&heapDesc, __uuidof(ID3D12DescriptorHeap), (void**)(&descriptorHeap)) != S_OK)
            MessageBox(NULL, "CreateDescriptorHeap", "Failed", NULL);

        rtvHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
        device->CreateRenderTargetView(backBuffer, nullptr, rtvHandle);

        
        if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)(&commandAlloc)) != S_OK)
            MessageBox(NULL, "CreateCommandAllocator", "Failed", NULL);

        if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAlloc, nullptr, __uuidof(ID3D12CommandList), (void**)(&commandList)) != S_OK)
            MessageBox(NULL, "CreateCommandList", "Failed", NULL);

        if (commandList->Close() != S_OK)
            MessageBox(NULL, "Close", "Failed", NULL);

        
        swapChain3->Release();
        D3DInitalized = true;
    }

    commandAlloc->Reset();
    commandList->Reset(commandAlloc, nullptr);

    commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, nullptr);
    
    
    commandList->Close();

	return oPresent(swapChain, syncInterval, flags);
}


bool Dx12Hook::getPtrPresent()
{
    gameWindow = func::getGameHWND();

    IDXGIFactory4* factory = nullptr;
    ID3D12Device* device = nullptr;
    ID3D12CommandQueue* commandQueue = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    IDXGISwapChain3* swapChain3 = nullptr;

    if (CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)(&factory)) != S_OK)
    {
        swapChain3->Release();
        swapChain->Release();
        commandQueue->Release();
        device->Release();
        factory->Release();
        return false;
    }

    if (D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, __uuidof(ID3D12Device), (void**)(&device)) != S_OK)
    {
        swapChain3->Release();
        swapChain->Release();
        commandQueue->Release();
        device->Release();
        factory->Release();
        return false;
    }

    D3D12_COMMAND_QUEUE_DESC cqDesc{};
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    cqDesc.NodeMask = 0;

    if (device->CreateCommandQueue(&cqDesc, __uuidof(ID3D12CommandQueue), (void**)(&commandQueue)) != S_OK)
    {
        swapChain3->Release();
        swapChain->Release();
        commandQueue->Release();
        device->Release();
        factory->Release();
        return false;
    }

    DXGI_SWAP_CHAIN_DESC scDesc{};
    scDesc.BufferCount = 2;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = gameWindow;
    scDesc.SampleDesc.Count = 1;
    scDesc.Windowed = TRUE;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

    if (factory->CreateSwapChain(commandQueue, &scDesc, &swapChain) != S_OK)
    {
        swapChain3->Release();
        swapChain->Release();
        commandQueue->Release();
        device->Release();
        factory->Release();
        return false;
    }

    if (swapChain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swapChain3) != S_OK)
    {
        swapChain3->Release();
        swapChain->Release();
        commandQueue->Release();
        device->Release();
        factory->Release();
        return false;
    }

    void** vTable = *reinterpret_cast<void***>(swapChain3);
    oPresent = (t_Present)(vTable[8]);
    PtroPresent = oPresent;


    swapChain3->Release();
    swapChain->Release();
    commandQueue->Release();
    device->Release();
    factory->Release();

    return true;
}


bool Dx12Hook::CreateHook()
{
    if (!getPtrPresent())
        return false;

    if (!MinHook)
    {
        if (MH_Initialize() != MH_OK)
            return false;
        MinHook = true;
    }

    if (MH_CreateHook((LPVOID)PtroPresent, &hkPresent, (LPVOID*)&oPresent) != MH_OK)
        return false;

    if (MH_EnableHook(PtroPresent) != MH_OK)
        return false;

    Dx12Enabled = true;
    return true;
}


bool Dx12Hook::Activate()
{
    if (MH_EnableHook(oPresent) != MH_OK)
        return false;

    Dx12Enabled = true;
	return true;
}


bool Dx12Hook::Deactivate()
{
    if (MH_DisableHook(oPresent) != MH_OK)
        return false;

    Dx12Enabled = false;
	return true;
}


void Dx12Hook::Destroy()
{
    commandAlloc->Release();
    commandList->Release();
    descriptorHeap->Release();
    backBuffer->Release();
    device->Release();
}
