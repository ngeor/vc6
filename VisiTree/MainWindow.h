#if !defined MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "..\WinObj\WinObj.h"
#include "AbstractTree.h"
#include "TreeFactory.h"

class MainWindow : public WinObj::CDialog
{
private:
	TreeFactory treeFactory;
	AbstractTree *myTree;
	void OpenTreeFile(LPCTSTR szFile);
	void OnOpenTreeFile();
	void OnSaveMetafile();
	void OnAdd();
	void SetKeyType(KeyType keyType);
	void KeyTypeChanged(KeyType keyType);
	void SetTreeType(TreeType treeType);
	void TreeTypeChanged(TreeType treeType);
	LRESULT OnCommand(UINT message, WPARAM wParam, LPARAM lParam);
	void SizeControls();

	/**
	 * Adds an entry to the key type drop down box.
	 *
	 * The entry is specified by the keyType, which needs to be one of the
	 * values defined in Node.h, such as KeyTypeInteger.
	 *
	 * The text value comes from a string table. The IDs are mapped to the key
	 * type by adding the offset 100 (e.g. KeyTypeInteger = 1 has the
	 * corresponding string ID = 101)
	 */
	void CbAddKeyType(int keyType);

	/// Adds a string to the combo box.
	int CbAddString(int id, LPCTSTR string);

	/// Sets item data on a item in the combo box.
	int CbSetItemData(int id, int index, LPARAM data);

public:
	MainWindow();
	virtual ~MainWindow();
	virtual LRESULT OnMessage(UINT, WPARAM, LPARAM) OVERRIDE;

protected:
	virtual LRESULT OnInitDialog(LPARAM lParam) OVERRIDE;
};

#endif
