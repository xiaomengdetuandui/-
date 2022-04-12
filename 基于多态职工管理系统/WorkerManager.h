#pragma once  //��ֹͷ�ļ��ظ�����
#include<iostream>
using namespace std;
#include "worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#include<fstream>
#define FILENAME "empFile.txt"


class WorkerManager
{
public: 
	//���캯��
	WorkerManager();

	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	void Add_Emp();
	//��¼ְ������
	int m_EmpNum;

	//��ʾְ����Ϣ
	void Show_Emp();

	//�ж�ְ���Ƿ����,��������򷵻�ְ�����������е�λ�ã��������򷵻�-1
	int IsExist(int id);

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//����ְ���������
	void Sort_Emp();

	//����ļ�
	void Clean_File();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int get_EmpNum();

	//��ʼ��Ա��
	void init_Emp();

	//ְ������ָ��

	Worker **m_EmpArray;
	//��������
	~WorkerManager();
};