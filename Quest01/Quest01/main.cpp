#include<stdio.h>
#include"Engine.h"


int main()
{
	//프로그램 시작, 시동부


	Engine* engine = new Engine(); //Engine의 메모리 참조, 새 엔진 생성
	engine->Init(); //Engine 객체 생성 메시지

	//engine->Term(); //Engine 객체 삭제 메시지
	delete engine; //Engine 객체 삭제

}