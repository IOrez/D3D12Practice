## D3D12Practice :rocket: :metal: 
DirectX 12를 이용한 3D 게임 프로그래밍 입문의 예제들을 연습하는 공간입니다.

--------------------------------------------------------------------------------
## 2021년 6월 23일 (1일차): DirectX 12 라이브러리 적용하기


> DirectX 12 라이브러리를 적용하여 Part6 Box의 예제를 출력하였다. 
> 
> 책이 오래전에 출간되어서 몇몇 부분에서 오류가 나타났다. (**특히 L-value!**) 
> 
> 이를 해결하고 정상 출력하였다. 


![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) **변경내용** 

1.Chapter6 Drawing in Direct3D 의 Box 프로젝트의 BoxApp.cpp를 현재 프로젝트에 추가하였음. 

2.Common 폴더의 내용을 현재 프로젝트에 추가하였음. (**추후 Common폴더의 .cpp, .h 파일의 내용은 직접 작성하기로 함**) 

3.BoxApp.cpp의 현재 프로젝트에 포함된 Common폴더경로에 맞게 #include 헤더경로를 수정함 

4.BoxApp.cpp에서 발생하는 L-value 오류를 임시방편으로 변수를 만들어 오류를 해결 

```c++ 
 auto resourceBarrier1 = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), 
        D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET); 
	mCommandList->ResourceBarrier(1, &resourceBarrier1); 
  
  auto currentBackBufferView = CurrentBackBufferView(); 
    auto depthStencilView = DepthStencilView(); 
	mCommandList->OMSetRenderTargets(1, &currentBackBufferView, true, &depthStencilView); 
  
   auto vertexBufferView = mBoxGeo->VertexBufferView(); 
    auto indexBufferView = mBoxGeo->IndexBufferView(); 
	mCommandList->IASetVertexBuffers(0, 1, &vertexBufferView); 
	mCommandList->IASetIndexBuffer(&indexBufferView); 

   auto resourceBarrier2 = CD3DX12_RESOURCE_BARRIER::Transition(CurrentBackBuffer(), 
        D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT); 
	mCommandList->ResourceBarrier(1, &resourceBarrier2); 
  
```

![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)  **출력이미지** 

<img src="OutputImage/directx12_2021_6_23_output1.PNG"> 

--------------------------------------------------------------------------------
## 2021년 6월 24일 (2일차): Window 창 생성 예제 수행

> 부록A의 윈도우 창을 생성해 보았다.
>
> 예전에 작성해 보았던 내용들이 새록새록 떠오르는 느낌을 받았다.
> 
> 책의 주석을 작성하여 평생 잊지 않도록 만들었다.

![#c5f015](https://via.placeholder.com/15/c5f015/000000?text=+) **핵심 기능**
1. 창 초기화
 * WNDCLASS 작성 (WndProc 연동)
 * WNDCLASS 등록
2. 창 생성
3. 창 표기, 갱신
4. 연동한 WndProc 작성


![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+)  **출력이미지** 

<img src="OutputImage/directx12_2021_6_24_output1.PNG" width ="1000" height = "500"> 
