// funcx.h: interface for the funcx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCX_H__A439E284_6A59_47DE_A5BB_5D8F3722E1FF__INCLUDED_)
#define AFX_FUNCX_H__A439E284_6A59_47DE_A5BB_5D8F3722E1FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <funcs.hpp>

class funcx  
{
public:
	int GetFirstArgument();

	int GetArgumentsSize();

	int OverflowReturnAddressSize(ea_t ea, int operand);

	int GetBufferSize(ea_t ea, int operand);

	char * GetStackVariableName(ea_t ea, int operand);

	int IsStackVariableALocalVariable(ea_t ea, int operand);

	int GetOrderOfVariable(ea_t ea, int operand);

	int IsStackVariableAParameter(ea_t ea, int operand);

	int GetNumberOfArguments();

	int GetFrameSize();

	int GetSavedRegsSize();

	int HasArguments();

	int GetReturnAddressSize();

	ea_t GetStackOffset(ea_t ea, int operand);

	int GetLocalVariableSize();
	
	funcx( int fid);
	funcx( ea_t ea);
	funcx( func_t *func_);
	
	virtual ~funcx();
private:
	func_t * func; 
	struc_t * struc;

};

#endif // !defined(AFX_FUNCX_H__A439E284_6A59_47DE_A5BB_5D8F3722E1FF__INCLUDED_)
