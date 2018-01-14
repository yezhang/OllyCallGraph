#pragma once

//************************************
// Method:    Evaluate
// FullName:  Evaluate
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: char * result, 表达式返回值
// Parameter: DWORD ip, 表达式所在的内存地址
// Parameter: char * expression, 表达式
//************************************
void Evaluate(char* result, DWORD ip, char * expression);