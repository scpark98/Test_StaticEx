#include "SCParagraph.h"

CParagraphData::CParagraphData()
{

}

CParagraphData::~CParagraphData()
{
	if (lf)
		delete lf;
}

CParagraph::CParagraph()
{

}

CParagraph::~CParagraph()
{
	for (int i = 0; i < m_data.size(); i++)
	{
		CParagraphData* data = m_data[i];
		delete data;
	}
}

//ex. add("<font size=12><font bold = 1>first line") �Էµ� ��
//add("second line")�̸� �� �� ��Ÿ���� �� ��Ÿ�ϰ��� �״�� �����Ѵ�.
void CParagraph::add(CString data)
{
	CParagraphData	para_data;
	int font_size = get_value(data, _T("font size"));
}

//tag_name�� ���� ���ڿ� �����Ϳ��� ���� �� �����Ƿ� �ݵ�� <, > ��ȣ�� ���������� Ȯ���ؾ� �Ѵ�.
DWORD CParagraph::get_value(CString data, CString tag_name, int start)
{
	int tag_pos = data.Find(tag_name, start);
	if (tag_pos < 0)
		return -1;

	//< font size=1>�� ���� '<'�� tag_name ������ ���� ����
	int tag_start = tag_pos - 1;
	while (tag_start >= 0)
	{
		if (data[tag_start] == '<')
			break;
		else
			tag_start--;
	}

	if (tag_start < 0)
		return -1;

	int tag_end = data.Find('>', tag_start + 1);
	if (tag_end < 0)
		return -1;

	//�� �±׺��� ������ '='��ȣ���� ã�ư���.
	int value_start = tag_end;
	while (value_start >= 0)
	{
		if (data[value_start] == '=')
			break;
		else
			value_start--;
	}

	if (value_start <= 0)
		return -1;

	CString value;
	//value = data.Mid(value_start + 1, tag_end - )
}