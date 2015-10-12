#pragma once

//#include "Skin/StyleEdit.h"
// COrangeEdit

class COrangeEdit : public CEdit
{
	DECLARE_DYNAMIC(COrangeEdit)

public:
	COrangeEdit();
	virtual ~COrangeEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


