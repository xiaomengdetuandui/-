#include"WorkerManager.h"
#include<string>
WorkerManager::WorkerManager()//构造函数空实现
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	//1.文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		//初始化人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//2.文件存在 数据为空
	char ch;
	ifs >> ch;//读一个字符，若读到EOF，说明文件读到了文件尾部
	if (ifs.eof())//eof（）函数为真代表读完了文件
	{
		//文件为空
		cout << "文件为空" << endl;
		//初始化人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3.文件存在，并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];

	//将文件中数据存到数组中
	this->init_Emp();

	for (int i=0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id
			<< "姓名：" << this->m_EmpArray[i]->m_Name
			<< "部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	}
}

//统计文件中人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读文件打开
	int id;
	string name;
	int did;

	int num=0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		num++;
	}
	return num;//读到文件中的人数
}

//展示菜单

void WorkerManager::Show_Menu()
{
	cout << "***************************************************************" << endl;
	cout << "*********************欢迎使用职工管理系统**********************" << endl;
	cout << "************************0.退出管理系统*************************" << endl;
	cout << "************************1.增加职工信息*************************" << endl;
	cout << "************************2.显示职工信息*************************" << endl;
	cout << "************************3.删除职工信息*************************" << endl;
	cout << "************************4.修改职工信息*************************" << endl;
	cout << "************************5.查找职工信息*************************" << endl;
	cout << "************************6.按照编号排序*************************" << endl;
	cout << "************************7.清空所有文档*************************" << endl;
	cout << "***************************************************************" << endl;
	cout << endl;
}
 //0.退出系统
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//1.添加职工
void WorkerManager::Add_Emp()
{
	cout << "请输入添加职工数量：" << endl;

	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数 =原来记录人数+ 新增人数

		//开辟新空间
		Worker **newSpace = new Worker*[newSize];

		//将原来空间下数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工姓名" << endl;
			cin >> name;

			cout << "请选择该职工岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch(dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
            }
			//将创建的职工指针保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}

		//释放原有空间
		delete[]this->m_EmpArray;//释放数组时要加[]

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;

		//更新职工不为空标志
		this->m_FileIsEmpty = false;

		//成功添加后保存到文件中
		this->save();
		//提示添加成功
		cout << "成功添加了" << addNum << "名职工" << endl;
	}
	else
	{
		cout << "输入有误！" << endl;
	}
	system("pause");
	system("cls");
}

//2.显示职工信息
void WorkerManager::Show_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在,如果存在则返回职工所在数组中的位置，不存在则返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//3.删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);
		if (index != -1)//说明职工存在，可以进行删除
		{
			//数据前移
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "删除成功！" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工！" << endl;
		}
	}
	system("pause");
	system("cls");
}

//4.修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入要查找的职工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//查到该编号的职工
			delete this->m_EmpArray[ret];//删除原先位置的数据

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查到" << id << "号职工，请进行修改：" << endl;
			cin >> newId;
			
			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请选择职工新岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更改数据到数组中
			this->m_EmpArray[ret] = worker;
			cout << "修改成功！" << this->m_EmpArray[ret]->m_DeptId << endl;
			//保存到文件中
			this->save();
		}
		else
		{
			cout << "查无此人，无法修改！" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//5.查找职工
void WorkerManager :: Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按姓名查找" << endl;

		int select = 0;
		cin >> select;
		if (select == 1)//按职工编号查找
		{
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人，无法修改！" << endl;
			}
		}

		else if (select == 2)//按姓名查找
		{
			string name;
			cout << "请输入查找的职工姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为："
						<< this->m_EmpArray[i]->m_Id
						<< "的职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入错误！" << endl;
		}
	}
	//按任意键清屏
	system("pause");
	system("cls");
}

//6.按照职工编号排序
void WorkerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1.按照升序进行排序" << endl;
		cout << "2.按照降序进行排序" << endl;

		int select = 0;
		cin >> select;
		
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;//声明最小值 或 最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//只要select不等于1，我们都认定是降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}
			//判定一开始认定最大值或最小值 是不是 计算后的最大值或最小值 如果不是交换数据
			if (i!= minOrMax)
			{
				Worker *temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！排序后的结果为：" << endl;
		this->save();//排序后的结果保存到文件中
		this->Show_Emp();//展示所有职工
	}
}

//7.清空文件
void WorkerManager::Clean_File()
{
	cout << "是否确定清空？" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "删除成功！" << endl;
	}
	system("pause");
	system("cls");
}

//保存文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//用输出的方式打开文件--写文件、

	//将每个人数据写入文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}

//初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//打开文件 读文件打开
	int id;
	string name;
	int did;

	int index=0;
	while (ifs >> id && ifs >> name && ifs >> did)
	{
		Worker *worker = NULL;
		if (did == 1)//普通员工
		{
			worker = new Employee(id, name, did);
		}
		else if (did == 2)//经理
		{
			worker = new Manager(id, name, did);
		}
		else//老板
		{
			worker = new Boss(id, name, did);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}

WorkerManager::~WorkerManager()//析构函数空实现
{
	if (this->m_EmpArray != NULL)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}