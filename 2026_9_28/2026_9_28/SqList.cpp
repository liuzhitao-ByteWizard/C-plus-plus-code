#include "SqList.h"

void SqListInit(SqList* ps) {
	ps->arr = new SqDataType[4]{0};
	ps->size = 0;
	ps->capacity = 4;
}


void SqListDestroy(SqList* ps) {
	assert(!EmptySqList(ps));
	delete[] ps->arr;
	ps->arr = nullptr;
	ps->capacity = ps->size = 0;
}

SqDataType GetElem(SqList* ps, int i) {
	assert(ps);
	assert(i >= 0 && i < ps->size);
	return ps->arr[i];
}

int LocateElem(SqList* ps, SqDataType x) {
	assert(ps);
	for (int i = 0; i < ps->size; i++) {
		if (ps->arr[i] == x)
			return i;
	}
	return -1;
}

void SqListInsert(SqList* ps, int i, SqDataType x) {
	assert(ps);
	assert(i >= 0 && i <= ps->size);
	//插入是需要考虑扩容的问题
	if (ps->size == ps->capacity) {
		//异地扩容
		SqDataType* tmp = new SqDataType[ps->capacity * 2]{ 0 };
		for (int k = 0; k < ps->size; ++k) {
			tmp[k] = ps->arr[k];
		}
		ps->arr = tmp;
		ps->capacity *= 2;
	}
	int j = ps->size - 1;
	while (j >= i) {
		ps->arr[j + 1] = ps->arr[j];
		j--;
	}

	//将要插入的数据移动到当前位置
	ps->arr[i] = x;
	//更新size
	ps->size++;
}







